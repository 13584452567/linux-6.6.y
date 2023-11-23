// SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <adf_accel_devices.h>
#include <adf_common_drv.h>
#include <adf_cfg.h>
#include <adf_dbgfs.h>
#include "adf_dh895xccvf_hw_data.h"

static const struct pci_device_id adf_pci_tbl[] = {
	{ PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_QAT_DH895XCC_VF), },
	{ }
};
MODULE_DEVICE_TABLE(pci, adf_pci_tbl);

static int adf_probe(struct pci_dev *dev, const struct pci_device_id *ent);
static void adf_remove(struct pci_dev *dev);

static struct pci_driver adf_driver = {
	.id_table = adf_pci_tbl,
	.name = ADF_DH895XCCVF_DEVICE_NAME,
	.probe = adf_probe,
	.remove = adf_remove,
};

static void adf_cleanup_pci_dev(struct adf_accel_dev *accel_dev)
{
	pci_release_regions(accel_dev->accel_pci_dev.pci_dev);
	pci_disable_device(accel_dev->accel_pci_dev.pci_dev);
}

static void adf_cleanup_accel(struct adf_accel_dev *accel_dev)
{
	struct adf_accel_pci *accel_pci_dev = &accel_dev->accel_pci_dev;
	struct adf_accel_dev *pf;
	int i;

	for (i = 0; i < ADF_PCI_MAX_BARS; i++) {
		struct adf_bar *bar = &accel_pci_dev->pci_bars[i];

		if (bar->virt_addr)
			pci_iounmap(accel_pci_dev->pci_dev, bar->virt_addr);
	}

	if (accel_dev->hw_device) {
		switch (accel_pci_dev->pci_dev->device) {
		case PCI_DEVICE_ID_INTEL_QAT_DH895XCC_VF:
			adf_clean_hw_data_dh895xcciov(accel_dev->hw_device);
			break;
		default:
			break;
		}
		kfree(accel_dev->hw_device);
		accel_dev->hw_device = NULL;
	}
	adf_dbgfs_exit(accel_dev);
	adf_cfg_dev_remove(accel_dev);
	pf = adf_devmgr_pci_to_accel_dev(accel_pci_dev->pci_dev->physfn);
	adf_devmgr_rm_dev(accel_dev, pf);
}

static int adf_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct adf_accel_dev *accel_dev;
	struct adf_accel_dev *pf;
	struct adf_accel_pci *accel_pci_dev;
	struct adf_hw_device_data *hw_data;
	unsigned int i, bar_nr;
	unsigned long bar_mask;
	int ret;

	switch (ent->device) {
	case PCI_DEVICE_ID_INTEL_QAT_DH895XCC_VF:
		break;
	default:
		dev_err(&pdev->dev, "Invalid device 0x%x.\n", ent->device);
		return -ENODEV;
	}

	accel_dev = kzalloc_node(sizeof(*accel_dev), GFP_KERNEL,
				 dev_to_node(&pdev->dev));
	if (!accel_dev)
		return -ENOMEM;

	accel_dev->is_vf = true;
	pf = adf_devmgr_pci_to_accel_dev(pdev->physfn);
	accel_pci_dev = &accel_dev->accel_pci_dev;
	accel_pci_dev->pci_dev = pdev;

	/* Add accel device to accel table */
	if (adf_devmgr_add_dev(accel_dev, pf)) {
		dev_err(&pdev->dev, "Failed to add new accelerator device.\n");
		kfree(accel_dev);
		return -EFAULT;
	}
	INIT_LIST_HEAD(&accel_dev->crypto_list);

	accel_dev->owner = THIS_MODULE;
	/* Allocate and configure device configuration structure */
	hw_data = kzalloc_node(sizeof(*hw_data), GFP_KERNEL,
			       dev_to_node(&pdev->dev));
	if (!hw_data) {
		ret = -ENOMEM;
		goto out_err;
	}
	accel_dev->hw_device = hw_data;
	adf_init_hw_data_dh895xcciov(accel_dev->hw_device);

	/* Get Accelerators and Accelerators Engines masks */
	hw_data->accel_mask = hw_data->get_accel_mask(hw_data);
	hw_data->ae_mask = hw_data->get_ae_mask(hw_data);
	accel_pci_dev->sku = hw_data->get_sku(hw_data);

	/* Create device configuration table */
	ret = adf_cfg_dev_add(accel_dev);
	if (ret)
		goto out_err;

	/* enable PCI device */
	if (pci_enable_device(pdev)) {
		ret = -EFAULT;
		goto out_err;
	}

	/* set dma identifier */
	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(48));
	if (ret) {
		dev_err(&pdev->dev, "No usable DMA configuration\n");
		goto out_err_disable;
	}

	if (pci_request_regions(pdev, ADF_DH895XCCVF_DEVICE_NAME)) {
		ret = -EFAULT;
		goto out_err_disable;
	}

	/* Find and map all the device's BARS */
	i = 0;
	bar_mask = pci_select_bars(pdev, IORESOURCE_MEM);
	for_each_set_bit(bar_nr, &bar_mask, ADF_PCI_MAX_BARS * 2) {
		struct adf_bar *bar = &accel_pci_dev->pci_bars[i++];

		bar->base_addr = pci_resource_start(pdev, bar_nr);
		if (!bar->base_addr)
			break;
		bar->size = pci_resource_len(pdev, bar_nr);
		bar->virt_addr = pci_iomap(accel_pci_dev->pci_dev, bar_nr, 0);
		if (!bar->virt_addr) {
			dev_err(&pdev->dev, "Failed to map BAR %d\n", bar_nr);
			ret = -EFAULT;
			goto out_err_free_reg;
		}
	}
	pci_set_master(pdev);
	/* Completion for VF2PF request/response message exchange */
	init_completion(&accel_dev->vf.msg_received);

	adf_dbgfs_init(accel_dev);

	ret = adf_dev_up(accel_dev, false);
	if (ret)
		goto out_err_dev_stop;

	return ret;

out_err_dev_stop:
	adf_dev_down(accel_dev, false);
out_err_free_reg:
	pci_release_regions(accel_pci_dev->pci_dev);
out_err_disable:
	pci_disable_device(accel_pci_dev->pci_dev);
out_err:
	adf_cleanup_accel(accel_dev);
	kfree(accel_dev);
	return ret;
}

static void adf_remove(struct pci_dev *pdev)
{
	struct adf_accel_dev *accel_dev = adf_devmgr_pci_to_accel_dev(pdev);

	if (!accel_dev) {
		pr_err("QAT: Driver removal failed\n");
		return;
	}
	adf_flush_vf_wq(accel_dev);
	adf_dev_down(accel_dev, false);
	adf_cleanup_accel(accel_dev);
	adf_cleanup_pci_dev(accel_dev);
	kfree(accel_dev);
}

static int __init adfdrv_init(void)
{
	request_module("intel_qat");

	if (pci_register_driver(&adf_driver)) {
		pr_err("QAT: Driver initialization failed\n");
		return -EFAULT;
	}
	return 0;
}

static void __exit adfdrv_release(void)
{
	pci_unregister_driver(&adf_driver);
	adf_clean_vf_map(true);
}

module_init(adfdrv_init);
module_exit(adfdrv_release);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel");
MODULE_DESCRIPTION("Intel(R) QuickAssist Technology");
MODULE_VERSION(ADF_DRV_VERSION);
