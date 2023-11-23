/* SPDX-License-Identifier: GPL-2.0-only
 *
 * Copyright (c) 2021, MediaTek Inc.
 * Copyright (c) 2021-2022, Intel Corporation.
 *
 * Authors:
 *  Haijun Liu <haijun.liu@mediatek.com>
 *  Chiranjeevi Rapolu <chiranjeevi.rapolu@intel.com>
 *
 * Contributors:
 *  Amir Hanania <amir.hanania@intel.com>
 *  Andy Shevchenko <andriy.shevchenko@linux.intel.com>
 *  Eliot Lee <eliot.lee@intel.com>
 *  Moises Veleta <moises.veleta@intel.com>
 *  Ricardo Martinez <ricardo.martinez@linux.intel.com>
 *  Sreehari Kancharla <sreehari.kancharla@intel.com>
 */

#ifndef __T7XX_REG_H__
#define __T7XX_REG_H__

#include <linux/bits.h>

/* Device base address offset */
#define MHCCIF_RC_DEV_BASE			0x10024000

#define REG_RC2EP_SW_BSY			0x04
#define REG_RC2EP_SW_INT_START			0x08

#define REG_RC2EP_SW_TCHNUM			0x0c
#define H2D_CH_EXCEPTION_ACK			1
#define H2D_CH_EXCEPTION_CLEARQ_ACK		2
#define H2D_CH_DS_LOCK				3
/* Channels 4-8 are reserved */
#define H2D_CH_SUSPEND_REQ			9
#define H2D_CH_RESUME_REQ			10
#define H2D_CH_SUSPEND_REQ_AP			11
#define H2D_CH_RESUME_REQ_AP			12
#define H2D_CH_DEVICE_RESET			13
#define H2D_CH_DRM_DISABLE_AP			14

#define REG_EP2RC_SW_INT_STS			0x10
#define REG_EP2RC_SW_INT_ACK			0x14
#define REG_EP2RC_SW_INT_EAP_MASK		0x20
#define REG_EP2RC_SW_INT_EAP_MASK_SET		0x30
#define REG_EP2RC_SW_INT_EAP_MASK_CLR		0x40

#define D2H_INT_DS_LOCK_ACK			BIT(0)
#define D2H_INT_EXCEPTION_INIT			BIT(1)
#define D2H_INT_EXCEPTION_INIT_DONE		BIT(2)
#define D2H_INT_EXCEPTION_CLEARQ_DONE		BIT(3)
#define D2H_INT_EXCEPTION_ALLQ_RESET		BIT(4)
#define D2H_INT_PORT_ENUM			BIT(5)
/* Bits 6-10 are reserved */
#define D2H_INT_SUSPEND_ACK			BIT(11)
#define D2H_INT_RESUME_ACK			BIT(12)
#define D2H_INT_SUSPEND_ACK_AP			BIT(13)
#define D2H_INT_RESUME_ACK_AP			BIT(14)
#define D2H_INT_ASYNC_AP_HK			BIT(15)
#define D2H_INT_ASYNC_MD_HK			BIT(16)

/* Register base */
#define INFRACFG_AO_DEV_CHIP			0x10001000

/* ATR setting */
#define T7XX_PCIE_REG_TRSL_ADDR_CHIP		0x10000000
#define T7XX_PCIE_REG_SIZE_CHIP			0x00400000

/* Reset Generic Unit (RGU) */
#define TOPRGU_CH_PCIE_IRQ_STA			0x1000790c

#define ATR_PORT_OFFSET				0x100
#define ATR_TABLE_OFFSET			0x20
#define ATR_TABLE_NUM_PER_ATR			8
#define ATR_TRANSPARENT_SIZE			0x3f

/* PCIE_MAC_IREG Register Definition */

#define ISTAT_HST_CTRL				0x01ac
#define ISTAT_HST_CTRL_DIS			BIT(0)

#define T7XX_PCIE_MISC_CTRL			0x0348
#define T7XX_PCIE_MISC_MAC_SLEEP_DIS		BIT(7)

#define T7XX_PCIE_CFG_MSIX			0x03ec
#define ATR_PCIE_WIN0_T0_ATR_PARAM_SRC_ADDR	0x0600
#define ATR_PCIE_WIN0_T0_TRSL_ADDR		0x0608
#define ATR_PCIE_WIN0_T0_TRSL_PARAM		0x0610
#define ATR_PCIE_WIN0_ADDR_ALGMT		GENMASK_ULL(63, 12)

#define ATR_SRC_ADDR_INVALID			0x007f

#define T7XX_PCIE_PM_RESUME_STATE		0x0d0c

enum t7xx_pm_resume_state {
	PM_RESUME_REG_STATE_L3,
	PM_RESUME_REG_STATE_L1,
	PM_RESUME_REG_STATE_INIT,
	PM_RESUME_REG_STATE_EXP,
	PM_RESUME_REG_STATE_L2,
	PM_RESUME_REG_STATE_L2_EXP,
};

#define T7XX_PCIE_MISC_DEV_STATUS		0x0d1c
#define MISC_STAGE_MASK				GENMASK(2, 0)
#define MISC_RESET_TYPE_PLDR			BIT(26)
#define MISC_RESET_TYPE_FLDR			BIT(27)
#define LINUX_STAGE				4

#define T7XX_PCIE_RESOURCE_STATUS		0x0d28
#define T7XX_PCIE_RESOURCE_STS_MSK		GENMASK(4, 0)

#define DISABLE_ASPM_LOWPWR			0x0e50
#define ENABLE_ASPM_LOWPWR			0x0e54
#define T7XX_L1_BIT(i)				BIT((i) * 4 + 1)
#define T7XX_L1_1_BIT(i)			BIT((i) * 4 + 2)
#define T7XX_L1_2_BIT(i)			BIT((i) * 4 + 3)

#define MSIX_ISTAT_HST_GRP0_0			0x0f00
#define IMASK_HOST_MSIX_SET_GRP0_0		0x3000
#define IMASK_HOST_MSIX_CLR_GRP0_0		0x3080
#define EXT_INT_START				24
#define EXT_INT_NUM				8
#define MSIX_MSK_SET_ALL			GENMASK(31, 24)

enum t7xx_int {
	DPMAIF_INT,
	CLDMA0_INT,
	CLDMA1_INT,
	CLDMA2_INT,
	MHCCIF_INT,
	DPMAIF2_INT,
	SAP_RGU_INT,
	CLDMA3_INT,
};

/* DPMA definitions */

#define DPMAIF_PD_BASE				0x1022d000
#define BASE_DPMAIF_UL				DPMAIF_PD_BASE
#define BASE_DPMAIF_DL				(DPMAIF_PD_BASE + 0x100)
#define BASE_DPMAIF_AP_MISC			(DPMAIF_PD_BASE + 0x400)
#define BASE_DPMAIF_MMW_HPC			(DPMAIF_PD_BASE + 0x600)
#define BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX		(DPMAIF_PD_BASE + 0x900)
#define BASE_DPMAIF_PD_SRAM_DL			(DPMAIF_PD_BASE + 0xc00)
#define BASE_DPMAIF_PD_SRAM_UL			(DPMAIF_PD_BASE + 0xd00)

#define DPMAIF_AO_BASE				0x10014000
#define BASE_DPMAIF_AO_UL			DPMAIF_AO_BASE
#define BASE_DPMAIF_AO_DL			(DPMAIF_AO_BASE + 0x400)

#define DPMAIF_UL_ADD_DESC			(BASE_DPMAIF_UL + 0x00)
#define DPMAIF_UL_CHK_BUSY			(BASE_DPMAIF_UL + 0x88)
#define DPMAIF_UL_RESERVE_AO_RW			(BASE_DPMAIF_UL + 0xac)
#define DPMAIF_UL_ADD_DESC_CH0			(BASE_DPMAIF_UL + 0xb0)

#define DPMAIF_DL_BAT_INIT			(BASE_DPMAIF_DL + 0x00)
#define DPMAIF_DL_BAT_ADD			(BASE_DPMAIF_DL + 0x04)
#define DPMAIF_DL_BAT_INIT_CON0			(BASE_DPMAIF_DL + 0x08)
#define DPMAIF_DL_BAT_INIT_CON1			(BASE_DPMAIF_DL + 0x0c)
#define DPMAIF_DL_BAT_INIT_CON2			(BASE_DPMAIF_DL + 0x10)
#define DPMAIF_DL_BAT_INIT_CON3			(BASE_DPMAIF_DL + 0x50)
#define DPMAIF_DL_CHK_BUSY			(BASE_DPMAIF_DL + 0xb4)

#define DPMAIF_AP_L2TISAR0			(BASE_DPMAIF_AP_MISC + 0x00)
#define DPMAIF_AP_APDL_L2TISAR0			(BASE_DPMAIF_AP_MISC + 0x50)
#define DPMAIF_AP_IP_BUSY			(BASE_DPMAIF_AP_MISC + 0x60)
#define DPMAIF_AP_CG_EN				(BASE_DPMAIF_AP_MISC + 0x68)
#define DPMAIF_AP_OVERWRITE_CFG			(BASE_DPMAIF_AP_MISC + 0x90)
#define DPMAIF_AP_MEM_CLR			(BASE_DPMAIF_AP_MISC + 0x94)
#define DPMAIF_AP_ALL_L2TISAR0_MASK		GENMASK(31, 0)
#define DPMAIF_AP_APDL_ALL_L2TISAR0_MASK	GENMASK(31, 0)
#define DPMAIF_AP_IP_BUSY_MASK			GENMASK(31, 0)

#define DPMAIF_AO_UL_INIT_SET			(BASE_DPMAIF_AO_UL + 0x0)
#define DPMAIF_AO_UL_CHNL_ARB0			(BASE_DPMAIF_AO_UL + 0x1c)
#define DPMAIF_AO_UL_AP_L2TIMR0			(BASE_DPMAIF_AO_UL + 0x80)
#define DPMAIF_AO_UL_AP_L2TIMCR0		(BASE_DPMAIF_AO_UL + 0x84)
#define DPMAIF_AO_UL_AP_L2TIMSR0		(BASE_DPMAIF_AO_UL + 0x88)
#define DPMAIF_AO_UL_AP_L1TIMR0			(BASE_DPMAIF_AO_UL + 0x8c)
#define DPMAIF_AO_UL_APDL_L2TIMR0		(BASE_DPMAIF_AO_UL + 0x90)
#define DPMAIF_AO_UL_APDL_L2TIMCR0		(BASE_DPMAIF_AO_UL + 0x94)
#define DPMAIF_AO_UL_APDL_L2TIMSR0		(BASE_DPMAIF_AO_UL + 0x98)
#define DPMAIF_AO_AP_DLUL_IP_BUSY_MASK		(BASE_DPMAIF_AO_UL + 0x9c)

#define DPMAIF_AO_UL_CHNL0_CON0			(BASE_DPMAIF_PD_SRAM_UL + 0x10)
#define DPMAIF_AO_UL_CHNL0_CON1			(BASE_DPMAIF_PD_SRAM_UL + 0x14)
#define DPMAIF_AO_UL_CHNL0_CON2			(BASE_DPMAIF_PD_SRAM_UL + 0x18)
#define DPMAIF_AO_UL_CH0_STA			(BASE_DPMAIF_PD_SRAM_UL + 0x70)

#define DPMAIF_AO_DL_INIT_SET			(BASE_DPMAIF_AO_DL + 0x00)
#define DPMAIF_AO_DL_IRQ_MASK			(BASE_DPMAIF_AO_DL + 0x0c)
#define DPMAIF_AO_DL_DLQPIT_INIT_CON5		(BASE_DPMAIF_AO_DL + 0x28)
#define DPMAIF_AO_DL_DLQPIT_TRIG_THRES		(BASE_DPMAIF_AO_DL + 0x34)

#define DPMAIF_AO_DL_PKTINFO_CON0		(BASE_DPMAIF_PD_SRAM_DL + 0x00)
#define DPMAIF_AO_DL_PKTINFO_CON1		(BASE_DPMAIF_PD_SRAM_DL + 0x04)
#define DPMAIF_AO_DL_PKTINFO_CON2		(BASE_DPMAIF_PD_SRAM_DL + 0x08)
#define DPMAIF_AO_DL_RDY_CHK_THRES		(BASE_DPMAIF_PD_SRAM_DL + 0x0c)
#define DPMAIF_AO_DL_RDY_CHK_FRG_THRES		(BASE_DPMAIF_PD_SRAM_DL + 0x10)

#define DPMAIF_AO_DL_DLQ_AGG_CFG		(BASE_DPMAIF_PD_SRAM_DL + 0x20)
#define DPMAIF_AO_DL_DLQPIT_TIMEOUT0		(BASE_DPMAIF_PD_SRAM_DL + 0x24)
#define DPMAIF_AO_DL_DLQPIT_TIMEOUT1		(BASE_DPMAIF_PD_SRAM_DL + 0x28)
#define DPMAIF_AO_DL_HPC_CNTL			(BASE_DPMAIF_PD_SRAM_DL + 0x38)
#define DPMAIF_AO_DL_PIT_SEQ_END		(BASE_DPMAIF_PD_SRAM_DL + 0x40)

#define DPMAIF_AO_DL_BAT_RD_IDX			(BASE_DPMAIF_PD_SRAM_DL + 0xd8)
#define DPMAIF_AO_DL_BAT_WR_IDX			(BASE_DPMAIF_PD_SRAM_DL + 0xdc)
#define DPMAIF_AO_DL_PIT_RD_IDX			(BASE_DPMAIF_PD_SRAM_DL + 0xec)
#define DPMAIF_AO_DL_PIT_WR_IDX			(BASE_DPMAIF_PD_SRAM_DL + 0x60)
#define DPMAIF_AO_DL_FRGBAT_RD_IDX		(BASE_DPMAIF_PD_SRAM_DL + 0x78)
#define DPMAIF_AO_DL_DLQ_WR_IDX			(BASE_DPMAIF_PD_SRAM_DL + 0xa4)

#define DPMAIF_HPC_INTR_MASK			(BASE_DPMAIF_MMW_HPC + 0x0f4)
#define DPMA_HPC_ALL_INT_MASK			GENMASK(15, 0)

#define DPMAIF_HPC_DLQ_PATH_MODE		3
#define DPMAIF_HPC_ADD_MODE_DF			0
#define DPMAIF_HPC_TOTAL_NUM			8
#define DPMAIF_HPC_MAX_TOTAL_NUM		8

#define DPMAIF_DL_DLQPIT_INIT			(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x00)
#define DPMAIF_DL_DLQPIT_ADD			(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x10)
#define DPMAIF_DL_DLQPIT_INIT_CON0		(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x14)
#define DPMAIF_DL_DLQPIT_INIT_CON1		(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x18)
#define DPMAIF_DL_DLQPIT_INIT_CON2		(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x1c)
#define DPMAIF_DL_DLQPIT_INIT_CON3		(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x20)
#define DPMAIF_DL_DLQPIT_INIT_CON4		(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x24)
#define DPMAIF_DL_DLQPIT_INIT_CON5		(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x28)
#define DPMAIF_DL_DLQPIT_INIT_CON6		(BASE_DPMAIF_DL_DLQ_REMOVEAO_IDX + 0x2c)

#define DPMAIF_ULQSAR_n(q)			(DPMAIF_AO_UL_CHNL0_CON0 + 0x10 * (q))
#define DPMAIF_UL_DRBSIZE_ADDRH_n(q)		(DPMAIF_AO_UL_CHNL0_CON1 + 0x10 * (q))
#define DPMAIF_UL_DRB_ADDRH_n(q)		(DPMAIF_AO_UL_CHNL0_CON2 + 0x10 * (q))
#define DPMAIF_ULQ_STA0_n(q)			(DPMAIF_AO_UL_CH0_STA + 0x04 * (q))
#define DPMAIF_ULQ_ADD_DESC_CH_n(q)		(DPMAIF_UL_ADD_DESC_CH0 + 0x04 * (q))

#define DPMAIF_UL_DRB_RIDX_MSK			GENMASK(31, 16)

#define DPMAIF_AP_RGU_ASSERT			0x10001150
#define DPMAIF_AP_RGU_DEASSERT			0x10001154
#define DPMAIF_AP_RST_BIT			BIT(2)

#define DPMAIF_AP_AO_RGU_ASSERT			0x10001140
#define DPMAIF_AP_AO_RGU_DEASSERT		0x10001144
#define DPMAIF_AP_AO_RST_BIT			BIT(6)

/* DPMAIF init/restore */
#define DPMAIF_UL_ADD_NOT_READY			BIT(31)
#define DPMAIF_UL_ADD_UPDATE			BIT(31)
#define DPMAIF_UL_ADD_COUNT_MASK		GENMASK(15, 0)
#define DPMAIF_UL_ALL_QUE_ARB_EN		GENMASK(11, 8)

#define DPMAIF_DL_ADD_UPDATE			BIT(31)
#define DPMAIF_DL_ADD_NOT_READY			BIT(31)
#define DPMAIF_DL_FRG_ADD_UPDATE		BIT(16)
#define DPMAIF_DL_ADD_COUNT_MASK		GENMASK(15, 0)

#define DPMAIF_DL_BAT_INIT_ALLSET		BIT(0)
#define DPMAIF_DL_BAT_FRG_INIT			BIT(16)
#define DPMAIF_DL_BAT_INIT_EN			BIT(31)
#define DPMAIF_DL_BAT_INIT_NOT_READY		BIT(31)
#define DPMAIF_DL_BAT_INIT_ONLY_ENABLE_BIT	0

#define DPMAIF_DL_PIT_INIT_ALLSET		BIT(0)
#define DPMAIF_DL_PIT_INIT_EN			BIT(31)
#define DPMAIF_DL_PIT_INIT_NOT_READY		BIT(31)

#define DPMAIF_BAT_REMAIN_SZ_BASE		16
#define DPMAIF_BAT_BUFFER_SZ_BASE		128
#define DPMAIF_FRG_BUFFER_SZ_BASE		128

#define DLQ_PIT_IDX_SIZE			0x20

#define DPMAIF_PIT_SIZE_MSK			GENMASK(17, 0)

#define DPMAIF_PIT_REM_CNT_MSK			GENMASK(17, 0)

#define DPMAIF_BAT_EN_MSK			BIT(16)
#define DPMAIF_FRG_EN_MSK			BIT(28)
#define DPMAIF_BAT_SIZE_MSK			GENMASK(15, 0)

#define DPMAIF_BAT_BID_MAXCNT_MSK		GENMASK(31, 16)
#define DPMAIF_BAT_REMAIN_MINSZ_MSK		GENMASK(15, 8)
#define DPMAIF_PIT_CHK_NUM_MSK			GENMASK(31, 24)
#define DPMAIF_BAT_BUF_SZ_MSK			GENMASK(16, 8)
#define DPMAIF_FRG_BUF_SZ_MSK			GENMASK(16, 8)
#define DPMAIF_BAT_RSV_LEN_MSK			GENMASK(7, 0)
#define DPMAIF_PKT_ALIGN_MSK			GENMASK(23, 22)

#define DPMAIF_BAT_CHECK_THRES_MSK		GENMASK(21, 16)
#define DPMAIF_FRG_CHECK_THRES_MSK		GENMASK(7, 0)

#define DPMAIF_PKT_ALIGN_EN			BIT(23)

#define DPMAIF_DRB_SIZE_MSK			GENMASK(15, 0)

#define DPMAIF_DL_RD_WR_IDX_MSK			GENMASK(17, 0)

/* DPMAIF_UL_CHK_BUSY */
#define DPMAIF_UL_IDLE_STS			BIT(11)
/* DPMAIF_DL_CHK_BUSY */
#define DPMAIF_DL_IDLE_STS			BIT(23)
/* DPMAIF_AO_DL_RDY_CHK_THRES */
#define DPMAIF_DL_PKT_CHECKSUM_EN		BIT(31)
#define DPMAIF_PORT_MODE_PCIE			BIT(30)
#define DPMAIF_DL_BURST_PIT_EN			BIT(13)
/* DPMAIF_DL_BAT_INIT_CON1 */
#define DPMAIF_DL_BAT_CACHE_PRI			BIT(22)
/* DPMAIF_AP_MEM_CLR */
#define DPMAIF_MEM_CLR				BIT(0)
/* DPMAIF_AP_OVERWRITE_CFG */
#define DPMAIF_SRAM_SYNC			BIT(0)
/* DPMAIF_AO_UL_INIT_SET */
#define DPMAIF_UL_INIT_DONE			BIT(0)
/* DPMAIF_AO_DL_INIT_SET */
#define DPMAIF_DL_INIT_DONE			BIT(0)
/* DPMAIF_AO_DL_PIT_SEQ_END */
#define DPMAIF_DL_PIT_SEQ_MSK			GENMASK(7, 0)
/* DPMAIF_UL_RESERVE_AO_RW */
#define DPMAIF_PCIE_MODE_SET_VALUE		0x55
/* DPMAIF_AP_CG_EN */
#define DPMAIF_CG_EN				0x7f

#define DPMAIF_UDL_IP_BUSY			BIT(0)
#define DPMAIF_DL_INT_DLQ0_QDONE		BIT(8)
#define DPMAIF_DL_INT_DLQ1_QDONE		BIT(9)
#define DPMAIF_DL_INT_DLQ0_PITCNT_LEN		BIT(10)
#define DPMAIF_DL_INT_DLQ1_PITCNT_LEN		BIT(11)
#define DPMAIF_DL_INT_Q2TOQ1			BIT(24)
#define DPMAIF_DL_INT_Q2APTOP			BIT(25)

#define DPMAIF_DLQ_LOW_TIMEOUT_THRES_MKS	GENMASK(15, 0)
#define DPMAIF_DLQ_HIGH_TIMEOUT_THRES_MSK	GENMASK(31, 16)

/* DPMAIF DLQ HW configure */
#define DPMAIF_AGG_MAX_LEN_DF			65535
#define DPMAIF_AGG_TBL_ENT_NUM_DF		50
#define DPMAIF_HASH_PRIME_DF			13
#define DPMAIF_MID_TIMEOUT_THRES_DF		100
#define DPMAIF_DLQ_TIMEOUT_THRES_DF		100
#define DPMAIF_DLQ_PRS_THRES_DF			10
#define DPMAIF_DLQ_HASH_BIT_CHOOSE_DF		0

#define DPMAIF_DLQPIT_EN_MSK			BIT(20)
#define DPMAIF_DLQPIT_CHAN_OFS			16
#define DPMAIF_ADD_DLQ_PIT_CHAN_OFS		20

#endif /* __T7XX_REG_H__ */
