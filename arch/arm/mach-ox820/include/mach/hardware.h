/*
 * arch/arm/mach-0x820/include/mach/hardware.h
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

#include <asm/page.h>
#include <asm/memory.h>
#include <asm/sizes.h>
#include <mach/vmalloc.h>
#include <mach/timex.h>

#define IO_ADDRESS(x)	(x)
#define __io_address(n)	((void __iomem *)IO_ADDRESS(n))

/* The base of virtual address mappings for hardware cores starts directly
 * after the end of the vmalloc mapping region
 */
#define OXNAS_HW_PA_TO_VA(x) (VMALLOC_END + (x))

/* Virtual address mapping of hardware core */
#define USBHOST_BASE			OXNAS_HW_PA_TO_VA(0x00200000)
#define ETHA_BASE				OXNAS_HW_PA_TO_VA(0x00400000)
#define MAC_BASE	(ETHA_BASE)
#define ETHB_BASE				OXNAS_HW_PA_TO_VA(0x00800000)
#define MAC_BASE_2	(ETHB_BASE)
#define USBDEV_BASE				OXNAS_HW_PA_TO_VA(0x00E00000)
#define STATIC_CS0_BASE			OXNAS_HW_PA_TO_VA(0x01000000)
#define STATIC_CS1_BASE			OXNAS_HW_PA_TO_VA(0x01400000)
#define STATIC_CONTROL_BASE		OXNAS_HW_PA_TO_VA(0x01C00000)
#define CIPHER_BASE				OXNAS_HW_PA_TO_VA(0x02000000)
#define GPIO_A_BASE				OXNAS_HW_PA_TO_VA(0x04000000)
#define GPIO_B_BASE				OXNAS_HW_PA_TO_VA(0x04100000)
#define UART_1_BASE				OXNAS_HW_PA_TO_VA(0x04200000)
#define UART_2_BASE				OXNAS_HW_PA_TO_VA(0x04300000)
#define RPSA_BASE				OXNAS_HW_PA_TO_VA(0x04400000)
#define RPSC_BASE				OXNAS_HW_PA_TO_VA(0x04500000)
#define FAN_MON_BASE			OXNAS_HW_PA_TO_VA(0x04600000)
#define DDR_REGS_BASE			OXNAS_HW_PA_TO_VA(0x04700000)
#define IRRX_BASE				OXNAS_HW_PA_TO_VA(0x04800000)
#define SATA_PHY_BASE			OXNAS_HW_PA_TO_VA(0x04900000)
#define PCIE_PHY				OXNAS_HW_PA_TO_VA(0x04A00000)
#define AHB_MON_BASE			OXNAS_HW_PA_TO_VA(0x04D00000)
#define SYS_CONTROL_BASE		OXNAS_HW_PA_TO_VA(0x04E00000)
#define SEC_CONTROL_BASE		OXNAS_HW_PA_TO_VA(0x04F00000)
#define SD_REG_BASE				OXNAS_HW_PA_TO_VA(0x05400000)
#define AUDIO_BASE				OXNAS_HW_PA_TO_VA(0x05500000)
#define DMA_BASE				OXNAS_HW_PA_TO_VA(0x05600000)
#define DMA_SG_BASE	(DMA_BASE + 0x10000)
#define CIPHER_REG_BASE			OXNAS_HW_PA_TO_VA(0x05700000)
#define SATA_REG_BASE			OXNAS_HW_PA_TO_VA(0x05900000)
#define COPRO_REGS_BASE			OXNAS_HW_PA_TO_VA(0x05B00000)
#define PERIPH_BASE				OXNAS_HW_PA_TO_VA(0x07000000)
#define PCIEA_DBI_BASE			OXNAS_HW_PA_TO_VA(0x07C00000)
#define PCIEA_ELBI_BASE			OXNAS_HW_PA_TO_VA(0x07D00000)
#define PCIEB_DBI_BASE			OXNAS_HW_PA_TO_VA(0x07E00000)
#define PCIEB_ELBI_BASE			OXNAS_HW_PA_TO_VA(0x07F00000)
#define PCIEA_CLIENT_BASE		OXNAS_HW_PA_TO_VA(0x08000000)
#define PCIEB_CLIENT_BASE		OXNAS_HW_PA_TO_VA(0x0c000000)

#define LEON_IMAGE_BASE       OXNAS_HW_PA_TO_VA(0x10000000)
#define SRAM_BASE             OXNAS_HW_PA_TO_VA(0x11000000)

#ifdef CONFIG_SUPPORT_LEON
#define LEON_IMAGE_SIZE			(CONFIG_LEON_PAGES * PAGE_SIZE)
#define LEON_IMAGE_BASE_PA		(((SRAM_END) + 1) - (LEON_IMAGE_SIZE))
#else // CONFIG_SUPPORT_LEON
#define LEON_IMAGE_SIZE		0
#define LEON_IMAGE_BASE_PA	0
#endif // CONFIG_SUPPORT_LEON

#if (LEON_IMAGE_BASE_PA >= SRAM_PA) && (LEON_IMAGE_BASE_PA <= SRAM_END)
#define LEON_IMAGE_IN_SRAM
#endif

/* Amount of SRAM allocated to GMAC descriptors */
#define DESCRIPTORS_SIZE	(CONFIG_DESCRIPTORS_PAGES * PAGE_SIZE)

#ifdef CONFIG_DESCRIPTORS_PAGES
#if (CONFIG_DESCRIPTORS_PAGES > CONFIG_SRAM_NUM_PAGES)
#error "Too many descriptor pages defined - greater than total SRAM pages"
#endif
#endif // CONFIG_DESCRIPTORS_PAGES

/* Various DMA descriptors are stored at the base of SRAM */
#define DESCRIPTORS_BASE_PA	SRAM_PA
#define DESCRIPTORS_BASE	SRAM_BASE

/* Record the address of the first free location in SRAM */
#define AVAIL_SRAM_START_PA	(DESCRIPTORS_BASE_PA + DESCRIPTORS_SIZE)

#if (AVAIL_SRAM_START_PA > SRAM_END)
#error "Descriptor area extends beyond end of SRAM"
#endif
                                
#ifdef LEON_IMAGE_IN_SRAM
#if (AVAIL_SRAM_START_PA > LEON_IMAGE_BASE_PA)
#error "Overlapping LEON and Descriptor areas in SRAM"
#endif
#endif

/*
 * Location of flags and vectors in SRAM for controlling the booting of the
 * secondary ARM11 processors.
 */
#define HOLDINGPEN_CPU          (SYS_CONTROL_BASE + 0xc8)
#define HOLDINGPEN_LOCATION     (SYS_CONTROL_BASE + 0xc4)

/***************************************************************************/
/* Physical memory map */
//#define ROM_BASE_PA             0x40000000
#define USBHOST_BASE_PA         0x40200000
#define ETHA_BASE_PA            0x40400000
#define ETHB_BASE_PA            0x40800000
#define USBDEV_BASE_PA          0x40E00000
#define STATIC_CS0_BASE_PA      0x41000000
#define STATIC_CS1_BASE_PA      0x41400000
#define STATIC_CONTROL_BASE_PA  0x41C00000
#define CIPHER_BASE_PA			0x42000000
#define GPIO_A_BASE_PA          0x44000000
#define GPIO_B_BASE_PA          0x44100000
#define UART_1_BASE_PA          0x44200000
#define UART_2_BASE_PA          0x44300000
#define RPSA_BASE_PA            0x44400000
#define RPSC_BASE_PA            0x44500000
#define FAN_MON_BASE_PA			0x44600000
#define DDR_REGS_BASE_PA        0x44700000
#define IRRX_BASE_PA            0x44800000
#define SATA_PHY_BASE_PA        0x44900000
#define PCIE_PHY_PA             0x44a00000
#define AHB_MON_BASE_PA			0x44d00000
#define SYS_CONTROL_BASE_PA     0x44e00000
#define SEC_CONTROL_BASE_PA     0x44f00000
#define SD_REG_BASE_PA          0x45400000
#define AUDIO_BASE_PA           0x45500000
#define DMA_BASE_PA             0x45600000
#define CIPHER_REG_BASE_PA      0x45700000
#define SATA_REG_BASE_PA        0x45900000
#define COPRO_REGS_BASE_PA      0x45b00000
#define PERIPH_BASE_PA          0x47000000
#define PCIEA_DBI_BASE_PA       0x47c00000
#define PCIEA_ELBI_BASE_PA		0x47d00000
#define PCIEB_DBI_BASE_PA       0x47e00000
#define PCIEB_ELBI_BASE_PA		0x47f00000
#define PCIEA_CLIENT_BASE_PA	0x48000000
#define PCIEB_CLIENT_BASE_PA	0x4c000000

/* System clock frequencies */
#ifdef CONFIG_ARCH_OXNAS_FPGA
/* FPGA CPU clock is entirely independent of rest of SoC */
#define NOMINAL_ARMCLK (CONFIG_OXNAS_CORE_CLK)
#else // CONFIG_ARCH_OXNAS_FPGA
/* ASIC CPU clock is derived from SoC master clock */
#define NOMINAL_ARMCLK (CONFIG_NOMINAL_PLL400_FREQ / 2)
#endif // CONFIG_ARCH_OXNAS_FPGA

#define NOMINAL_SYSCLK (CONFIG_NOMINAL_PLL400_FREQ / 4)

/* RPS timer setup */
#define TIMER_1_MODE           TIMER_MODE_PERIODIC
#define TIMER_2_PRESCALE_ENUM  TIMER_PRESCALE_256
#define TIMER_2_MODE           TIMER_MODE_FREE_RUNNING

/* Useful macros for dealing with sub timer-interrupt intervals - preserve
 * as much precision as possible without using floating point and minimising
 * runtime CPU requirement */
#define TIMER_1_LOAD_VALUE     ((CLOCK_TICK_RATE) / HZ)
#define TICKS_TO_US_SCALING    1024
#define TICKS_TO_US_FACTOR     (((2 * TICKS_TO_US_SCALING * 1000000) + CLOCK_TICK_RATE) / (2 * CLOCK_TICK_RATE))
#define TICKS_TO_US(ticks)     ((((ticks) * TICKS_TO_US_FACTOR * 2) + TICKS_TO_US_SCALING) / (2 * TICKS_TO_US_SCALING))

/* Remap and pause */
#define RPS_REMAP_AND_PAUSE    (RPS_BASE + 0x300)

#define USBA_POWO_SEC_MFP  10
#define USBA_OVERI_SEC_MFP 11
#define USBA_POWO_TER_MFP  48
#define USBA_OVERI_TER_MFP 49

#define USBB_POWO_SEC_MFP  28
#define USBB_OVERI_SEC_MFP 29
#define USBB_POWO_TER_MFP  5
#define USBB_OVERI_TER_MFP 0

/* RPS GPIO registers */
#define RPS_GPIO_BASE                         (RPS_BASE + 0x3C0)
#define RPS_GPIO_OUTPUT                       (RPS_BASE + 0x3C0)
#define RPS_GPIO_OUTPUT_ENABLE                (RPS_BASE + 0x3C4)
#define RPS_GPIO_INTERRUPT_ENABLE             (RPS_BASE + 0x3C8)
#define RPS_GPIO_INTERRUPT_EVENT              (RPS_BASE + 0x3CC)
#define RPS_GPIO_CHIPID                       (RPS_BASE + 0x3FC)

/* GPIO A registers */
#define GPIO_A_DATA                            GPIO_A_BASE
#define GPIO_A_OUTPUT_ENABLE                  (GPIO_A_BASE + 0x0004)
#define GPIO_A_INTERRUPT_ENABLE               (GPIO_A_BASE + 0x0008)
#define GPIO_A_INTERRUPT_EVENT                (GPIO_A_BASE + 0x000C)
#define GPIO_A_OUTPUT_VALUE                   (GPIO_A_BASE + 0x0010)
#define GPIO_A_OUTPUT_SET                     (GPIO_A_BASE + 0x0014)
#define GPIO_A_OUTPUT_CLEAR                   (GPIO_A_BASE + 0x0018)
#define GPIO_A_OUTPUT_ENABLE_SET              (GPIO_A_BASE + 0x001C)
#define GPIO_A_OUTPUT_ENABLE_CLEAR            (GPIO_A_BASE + 0x0020)
#define GPIO_A_INPUT_DEBOUNCE_ENABLE          (GPIO_A_BASE + 0x0024)
#define GPIO_A_RISING_EDGE_ACTIVE_HIGH_ENABLE (GPIO_A_BASE + 0x0028)
#define GPIO_A_FALLING_EDGE_ACTIVE_LOW_ENABLE (GPIO_A_BASE + 0x002C)
#define GPIO_A_RISING_EDGE_DETECT             (GPIO_A_BASE + 0x0030)
#define GPIO_A_FALLING_EDGE_DETECT            (GPIO_A_BASE + 0x0034)
#define GPIO_A_LEVEL_INTERRUPT_ENABLE         (GPIO_A_BASE + 0x0038)
#define GPIO_A_INTERRUPT_STATUS_REGISTER      (GPIO_A_BASE + 0x003C)

/* GPIO B registers */
#define GPIO_B_DATA                            GPIO_B_BASE
#define GPIO_B_OUTPUT_ENABLE                  (GPIO_B_BASE + 0x0004)
#define GPIO_B_INTERRUPT_ENABLE               (GPIO_B_BASE + 0x0008)
#define GPIO_B_INTERRUPT_EVENT                (GPIO_B_BASE + 0x000C)
#define GPIO_B_OUTPUT_VALUE                   (GPIO_B_BASE + 0x0010)
#define GPIO_B_OUTPUT_SET                     (GPIO_B_BASE + 0x0014)
#define GPIO_B_OUTPUT_CLEAR                   (GPIO_B_BASE + 0x0018)
#define GPIO_B_OUTPUT_ENABLE_SET              (GPIO_B_BASE + 0x001C)
#define GPIO_B_OUTPUT_ENABLE_CLEAR            (GPIO_B_BASE + 0x0020)
#define GPIO_B_INPUT_DEBOUNCE_ENABLE          (GPIO_B_BASE + 0x0024)
#define GPIO_B_RISING_EDGE_ACTIVE_HIGH_ENABLE (GPIO_B_BASE + 0x0028)
#define GPIO_B_FALLING_EDGE_ACTIVE_LOW_ENABLE (GPIO_B_BASE + 0x002C)
#define GPIO_B_RISING_EDGE_DETECT             (GPIO_B_BASE + 0x0030)
#define GPIO_B_FALLING_EDGE_DETECT            (GPIO_B_BASE + 0x0034)
#define GPIO_B_LEVEL_INTERRUPT_ENABLE         (GPIO_B_BASE + 0x0038)
#define GPIO_B_INTERRUPT_STATUS_REGISTER      (GPIO_B_BASE + 0x003C)

/* UART_A multi function pins */
#define UART_A_RI_GPIOA_PIN		24
#define UART_A_CD_GPIOA_PIN		25
#define UART_A_DSR_GPIOA_PIN	26
#define UART_A_DTR_GPIOA_PIN	27
#define UART_A_CTS_GPIOA_PIN	28
#define UART_A_RTS_GPIOA_PIN	29
#define UART_A_SIN_GPIOA_PIN	30
#define UART_A_SOUT_GPIOA_PIN	31

/* UART_B multi function pins */
#define UART_B_RI_GPIOB_PIN		8
#define UART_B_CD_GPIOB_PIN		9
#define UART_B_DSR_GPIOB_PIN	10
#define UART_B_DTR_GPIOB_PIN	11
#define UART_B_CTS_GPIOA_PIN	5
#define UART_B_RTS_GPIOA_PIN	6
#define UART_B_SIN_GPIOA_PIN	7
#define UART_B_SOUT_GPIOA_PIN	8

/* Eth A multi function pins */
#define MACA_MDC_MF_PIN                3
#define MACA_MDIO_MF_PIN               4

/* CoProcessor RPS GPIO registers */
#define COPRO_GPIO_A_BASE            (COPRO_RPS_BASE + 0x3C0)
#define COPRO_GPIO_A_DATA             COPRO_GPIO_A_BASE
#define COPRO_GPIO_A_OUTPUT_ENABLE   (COPRO_GPIO_A_BASE + 0x04)
#define COPRO_GPIO_A_INTERRUPT_MASK  (COPRO_GPIO_A_BASE + 0x08)
#define COPRO_GPIO_A_INTERRUPT_EVENT (COPRO_GPIO_A_BASE + 0x0C)

/* Static bus registers */
#define STATIC_CONTROL_VERSION (STATIC_CONTROL_BASE + 0x0)
#define STATIC_CONTROL_BANK0   (STATIC_CONTROL_BASE + 0x4)
#define STATIC_CONTROL_BANK1   (STATIC_CONTROL_BASE + 0x8)
#define STATIC_CONTROL_BANK2   (STATIC_CONTROL_BASE + 0xC)

/* System Control registers */
#define SYS_CTRL_PCI_STAT               (SYS_CONTROL_BASE + 0x20)
#define SYS_CTRL_CKEN_CTRL              (SYS_CONTROL_BASE + 0x24)
#define SYS_CTRL_RSTEN_CTRL             (SYS_CONTROL_BASE + 0x28)
#define SYS_CTRL_CKEN_SET_CTRL          (SYS_CONTROL_BASE + 0x2C)
#define SYS_CTRL_CKEN_CLR_CTRL          (SYS_CONTROL_BASE + 0x30)
#define SYS_CTRL_RSTEN_SET_CTRL         (SYS_CONTROL_BASE + 0x34)
#define SYS_CTRL_RSTEN_CLR_CTRL         (SYS_CONTROL_BASE + 0x38)
#define SYS_CTRL_USBHSMPH_CTRL          (SYS_CONTROL_BASE + 0x40)
#define SYS_CTRL_USBHSMPH_STAT          (SYS_CONTROL_BASE + 0x44)
#define SYS_CTRL_PLLSYS_CTRL            (SYS_CONTROL_BASE + 0x48)
#define SYS_CTRL_SEMA_STAT              (SYS_CONTROL_BASE + 0x4C)
#define SYS_CTRL_SEMA_SET_CTRL          (SYS_CONTROL_BASE + 0x50)
#define SYS_CTRL_SEMA_CLR_CTRL          (SYS_CONTROL_BASE + 0x54)
#define SYS_CTRL_SEMA_MASKA_CTRL        (SYS_CONTROL_BASE + 0x58)
#define SYS_CTRL_SEMA_MASKB_CTRL        (SYS_CONTROL_BASE + 0x5C)
#define SYS_CTRL_SEMA_MASKC_CTRL        (SYS_CONTROL_BASE + 0x60)
#define SYS_CTRL_CKCTRL_CTRL            (SYS_CONTROL_BASE + 0x64)
#define SYS_CTRL_COPRO_CTRL             (SYS_CONTROL_BASE + 0x68)
#define SYS_CTRL_PLLSYS_KEY_CTRL        (SYS_CONTROL_BASE + 0x6C)
#define SYS_CTRL_GMACA_CTRL             (SYS_CONTROL_BASE + 0x78)
#define SYS_CTRL_USBHSPHY_CTRL          (SYS_CONTROL_BASE + 0x84)
#define SYS_CTRL_REF300_DIV             (SYS_CONTROL_BASE + 0xF8)
#define SYS_CTRL_USB_CTRL               (SYS_CONTROL_BASE + 0x90)
#define SYS_CTRL_UART_CTRL              (SYS_CONTROL_BASE + 0x94)
#define SYS_CTRL_GMACB_CTRL             (SYS_CONTROL_BASE + 0xEC)
#define SYS_CTRL_GMACA_DELAY_CTRL       (SYS_CONTROL_BASE +0x100)
#define SYS_CTRL_GMACB_DELAY_CTRL       (SYS_CONTROL_BASE +0x104)
#define SYS_CTRL_HCSL_CTRL          (SYS_CONTROL_BASE +0x114)
#define SYS_CTRL_PCIEA_CTRL       		(SYS_CONTROL_BASE +0x120)
#define SYS_CTRL_PCIEB_CTRL       		(SYS_CONTROL_BASE +0x124)
#define SYS_CTRL_PCIEPHY_CTRL       	(SYS_CONTROL_BASE +0x128)
#define SYS_CTRL_PCIEPHY_CR       		(SYS_CONTROL_BASE +0x12C)
#define SYS_CTRL_PCIEA_POM0_MEM_ADDR	(SYS_CONTROL_BASE +0x138)
#define SYS_CTRL_PCIEA_POM1_MEM_ADDR	(SYS_CONTROL_BASE +0x13C)
#define SYS_CTRL_PCIEA_IN0_MEM_ADDR		(SYS_CONTROL_BASE +0x140)
#define SYS_CTRL_PCIEA_IN1_MEM_ADDR		(SYS_CONTROL_BASE +0x144)
#define SYS_CTRL_PCIEA_IN_IO_ADDR		(SYS_CONTROL_BASE +0x148)
#define SYS_CTRL_PCIEA_IN_CFG0_ADDR		(SYS_CONTROL_BASE +0x14C)
#define SYS_CTRL_PCIEA_IN_CFG1_ADDR		(SYS_CONTROL_BASE +0x150)
#define SYS_CTRL_PCIEA_IN_MSG_ADDR		(SYS_CONTROL_BASE +0x154)
#define SYS_CTRL_PCIEA_IN0_MEM_LIMIT	(SYS_CONTROL_BASE +0x158)
#define SYS_CTRL_PCIEA_IN1_MEM_LIMIT	(SYS_CONTROL_BASE +0x15C)
#define SYS_CTRL_PCIEA_IN_IO_LIMIT		(SYS_CONTROL_BASE +0x160)
#define SYS_CTRL_PCIEA_IN_CFG0_LIMIT	(SYS_CONTROL_BASE +0x164)
#define SYS_CTRL_PCIEA_IN_CFG1_LIMIT	(SYS_CONTROL_BASE +0x168)
#define SYS_CTRL_PCIEA_IN_MSG_LIMIT		(SYS_CONTROL_BASE +0x16C)
#define SYS_CTRL_PCIEA_AHB_SLAVE_CTRL	(SYS_CONTROL_BASE +0x170)
#define SYS_CTRL_PCIEB_POM0_MEM_ADDR	(SYS_CONTROL_BASE +0x174)
#define SYS_CTRL_PCIEB_POM1_MEM_ADDR	(SYS_CONTROL_BASE +0x178)
#define SYS_CTRL_PCIEB_IN0_MEM_ADDR		(SYS_CONTROL_BASE +0x17C)
#define SYS_CTRL_PCIEB_IN1_MEM_ADDR		(SYS_CONTROL_BASE +0x180)
#define SYS_CTRL_PCIEB_IN_IO_ADDR		(SYS_CONTROL_BASE +0x184)
#define SYS_CTRL_PCIEB_IN_CFG0_ADDR		(SYS_CONTROL_BASE +0x188)
#define SYS_CTRL_PCIEB_IN_CFG1_ADDR		(SYS_CONTROL_BASE +0x18C)
#define SYS_CTRL_PCIEB_IN_MSG_ADDR		(SYS_CONTROL_BASE +0x190)
#define SYS_CTRL_PCIEB_IN0_MEM_LIMIT	(SYS_CONTROL_BASE +0x194)
#define SYS_CTRL_PCIEB_IN1_MEM_LIMIT	(SYS_CONTROL_BASE +0x198)
#define SYS_CTRL_PCIEB_IN_IO_LIMIT		(SYS_CONTROL_BASE +0x19C)
#define SYS_CTRL_PCIEB_IN_CFG0_LIMIT	(SYS_CONTROL_BASE +0x1A0)
#define SYS_CTRL_PCIEB_IN_CFG1_LIMIT	(SYS_CONTROL_BASE +0x1A4)
#define SYS_CTRL_PCIEB_IN_MSG_LIMIT		(SYS_CONTROL_BASE +0x1A8)
#define SYS_CTRL_PCIEB_AHB_SLAVE_CTRL	(SYS_CONTROL_BASE +0x1AC)

/* System control multi-function pin function selection */
#define SYS_CTRL_SECONDARY_SEL          (SYS_CONTROL_BASE + 0x14)
#define SYS_CTRL_TERTIARY_SEL           (SYS_CONTROL_BASE + 0x8c)
#define SYS_CTRL_QUATERNARY_SEL         (SYS_CONTROL_BASE + 0x94)
#define SYS_CTRL_DEBUG_SEL              (SYS_CONTROL_BASE + 0x9c)
#define SYS_CTRL_ALTERNATIVE_SEL        (SYS_CONTROL_BASE + 0xa4)
#define SYS_CTRL_PULLUP_SEL        		(SYS_CONTROL_BASE + 0xac)

/* Secure control multi-function pin function selection */
#define SEC_CTRL_SECONDARY_SEL          (SEC_CONTROL_BASE + 0x14)
#define SEC_CTRL_TERTIARY_SEL           (SEC_CONTROL_BASE + 0x8c)
#define SEC_CTRL_QUATERNARY_SEL         (SEC_CONTROL_BASE + 0x94)
#define SEC_CTRL_DEBUG_SEL              (SEC_CONTROL_BASE + 0x9c)
#define SEC_CTRL_ALTERNATIVE_SEL        (SEC_CONTROL_BASE + 0xa4)
#define SEC_CTRL_PULLUP_SEL        		(SYS_CONTROL_BASE + 0xac)

#define SEC_CTRL_COPRO_CTRL             (SEC_CONTROL_BASE + 0x68)
#define SEC_CTRL_SECURE_CTRL		(SEC_CONTROL_BASE + 0x98)
#define SEC_CTRL_LEON_DEBUG		(SEC_CONTROL_BASE + 0xF0)
#define SEC_CTRL_PLLB_DIV_CTRL          (SEC_CONTROL_BASE + 0xF8)
#define SEC_CTRL_PLLB_CTRL0             (SEC_CONTROL_BASE + 0x1F0)
#define SEC_CTRL_PLLB_CTRL1             (SEC_CONTROL_BASE + 0x1F4)
#define SEC_CTRL_PLLB_CTRL8             (SEC_CONTROL_BASE + 0x1F4)

/* There are 32 MFP in sys_ctrl and another 18 in sec_ctrl */
#define SYS_CTRL_NUM_PINS	32

/* clock control bits */
#define SYS_CTRL_CKEN_COPRO_BIT         0
#define SYS_CTRL_CKEN_DMA_BIT           1
#define SYS_CTRL_CKEN_CIPHER_BIT        2
#define SYS_CTRL_CKEN_SD_BIT            3
#define SYS_CTRL_CKEN_SATA_BIT          4
#define SYS_CTRL_CKEN_I2S_BIT           5
#define SYS_CTRL_CKEN_USBHS_BIT         6
#define SYS_CTRL_CKEN_MAC_BIT           7
#define SYS_CTRL_CKEN_PCIEA_BIT         8
#define SYS_CTRL_CKEN_STATIC_BIT        9
#define SYS_CTRL_CKEN_MAC_2_BIT         10
#define SYS_CTRL_CKEN_PCIEB_BIT         11
#define SYS_CTRL_CKEN_REF600_BIT        12
#define SYS_CTRL_CKEN_USBDEV_BIT        13
#define SYS_CTRL_CKEN_DDR_BIT           14
#define SYS_CTRL_CKEN_DDRPHY_BIT        15
#define SYS_CTRL_CKEN_DDRCK_BIT         16

/* reset control bits */
#define SYS_CTRL_RSTEN_SCU_BIT          0
#define SYS_CTRL_RSTEN_COPRO_BIT        1
#define SYS_CTRL_RSTEN_ARM0_BIT         2
#define SYS_CTRL_RSTEN_ARM1_BIT         3
#define SYS_CTRL_RSTEN_USBHS_BIT        4
#define SYS_CTRL_RSTEN_USBPHYA_BIT      5
#define SYS_CTRL_RSTEN_MAC_BIT          6
#define SYS_CTRL_RSTEN_PCIEA_BIT        7
#define SYS_CTRL_RSTEN_SGDMA_BIT        8
#define SYS_CTRL_RSTEN_CIPHER_BIT       9
#define SYS_CTRL_RSTEN_DDR_BIT          10
#define SYS_CTRL_RSTEN_SATA_BIT         11
#define SYS_CTRL_RSTEN_SATA_LINK_BIT    12
#define SYS_CTRL_RSTEN_SATA_PHY_BIT     13
#define SYS_CTRL_RSTEN_PCIEPHY_BIT      14
#define SYS_CTRL_RSTEN_STATIC_BIT       15
#define SYS_CTRL_RSTEN_GPIO_BIT         16
#define SYS_CTRL_RSTEN_UART1_BIT        17
#define SYS_CTRL_RSTEN_UART2_BIT        18
#define SYS_CTRL_RSTEN_MISC_BIT         19
#define SYS_CTRL_RSTEN_I2S_BIT          20
#define SYS_CTRL_RSTEN_SD_BIT           21
#define SYS_CTRL_RSTEN_MAC_2_BIT        22
#define SYS_CTRL_RSTEN_PCIEB_BIT        23
#define SYS_CTRL_RSTEN_VIDEO_BIT        24
#define SYS_CTRL_RSTEN_DDR_PHY_BIT      25
#define SYS_CTRL_RSTEN_USBPHYB_BIT      26
#define SYS_CTRL_RSTEN_USBDEV_BIT       27
#define SYS_CTRL_RSTEN_ARMDBG_BIT       29
#define SYS_CTRL_RSTEN_PLLA_BIT         30
#define SYS_CTRL_RSTEN_PLLB_BIT         31

#define SYS_CTRL_USBHSMPH_IP_POL_A_BIT  0
#define SYS_CTRL_USBHSMPH_IP_POL_B_BIT  1
#define SYS_CTRL_USBHSMPH_IP_POL_C_BIT  2
#define SYS_CTRL_USBHSMPH_OP_POL_A_BIT  3
#define SYS_CTRL_USBHSMPH_OP_POL_B_BIT  4
#define SYS_CTRL_USBHSMPH_OP_POL_C_BIT  5

#define SYS_CTRL_GMAC_CKEN_RX_IN     	14
#define SYS_CTRL_GMAC_CKEN_RXN_OUT     	13
#define SYS_CTRL_GMAC_CKEN_RX_OUT     	12
#define SYS_CTRL_GMAC_CKEN_TX_IN    	10
#define SYS_CTRL_GMAC_CKEN_TXN_OUT   	9
#define SYS_CTRL_GMAC_CKEN_TX_OUT     	8
#define SYS_CTRL_GMAC_RX_SOURCE     	7
#define SYS_CTRL_GMAC_TX_SOURCE     	6
#define SYS_CTRL_GMAC_LOW_TX_SOURCE     4
#define SYS_CTRL_GMAC_AUTO_TX_SOURCE	3
#define SYS_CTRL_GMAC_RGMII         	2
#define SYS_CTRL_GMAC_SIMPLE_MUX    	1
#define SYS_CTRL_GMAC_CKEN_GTX      	0

#define SYS_CTRL_GMAC_TX_VARDELAY	0
#define SYS_CTRL_GMAC_TXN_VARDELAY	8
#define SYS_CTRL_GMAC_RX_VARDELAY	16
#define SYS_CTRL_GMAC_RXN_VARDELAY	24

#define SYS_CTRL_USBHSPHY_SUSPENDM_MANUAL_ENABLE    16
#define SYS_CTRL_USBHSPHY_SUSPENDM_MANUAL_STATE     15
#define SYS_CTRL_USBHSPHY_ATE_ESET                  14
#define SYS_CTRL_USBHSPHY_TEST_DIN                   6
#define SYS_CTRL_USBHSPHY_TEST_ADD                   2
#define SYS_CTRL_USBHSPHY_TEST_DOUT_SEL              1
#define SYS_CTRL_USBHSPHY_TEST_CLK                   0

#define USB_REF_300_DIVIDER     8
#define USB_REF_300_INV         28
#define USB_REF_300_WCK_DUTY    29

#define PLLB_ENSAT              3
#define PLLB_OUTDIV             4
#define PLLB_REFDIV             8
#define USB_REF_600_DIVIDER     8

#define USB_CLK_INTERNAL    0x2
#define USB_INT_CLK_REF300  0x2
#define USB_INT_CLK_PLLB    0x3
#define USB_CLK_SEL           5

#define SEC_CTRL_COPRO_PROMOTE_IRQ	0
#define SEC_CTRL_COPRO_DOUBLE_CLK	1
#define SEC_CTRL_COPRO_START_ADR	2

/* AHB monitor base addresses */
#define AHB_MON_ARM_D (AHB_MON_BASE + 0x00000)
#define AHB_MON_ARM_I (AHB_MON_BASE + 0x10000)
#define AHB_MON_DMA_A (AHB_MON_BASE + 0x20000)
#define AHB_MON_DMA_B (AHB_MON_BASE + 0x30000)
#define AHB_MON_LEON  (AHB_MON_BASE + 0x40000)
#define AHB_MON_USB   (AHB_MON_BASE + 0x50000)
#define AHB_MON_MAC   (AHB_MON_BASE + 0x60000)
#define AHB_MON_PCI   (AHB_MON_BASE + 0x70000)

/* AHB write monitor registers */
#define AHB_MON_MODE_REG_OFFSET         0x00
#define AHB_MON_HWRITE_REG_OFFSET       0x04
#define AHB_MON_HADDR_LOW_REG_OFFSET    0x08
#define AHB_MON_HADDR_HIGH_REG_OFFSET   0x0C
#define AHB_MON_HBURST_REG_OFFSET       0x10
#define AHB_MON_HPROT_REG_OFFSET        0x14

/* AHB monitor write register field definitions */
#define AHB_MON_MODE_MODE_BIT           0
#define AHB_MON_MODE_MODE_NUM_BITS      2
#define AHB_MON_HWRITE_COUNT_BIT        0
#define AHB_MON_HWRITE_COUNT_NUM_BITS   2
#define AHB_MON_HBURST_MASK_BIT         0
#define AHB_MON_HBURST_MASK_NUM_BITS    3
#define AHB_MON_HBURST_MATCH_BIT        4
#define AHB_MON_HBURST_MATCH_NUM_BITS   3
#define AHB_MON_HPROT_MASK_BIT          0
#define AHB_MON_HPROT_MASK_NUM_BITS     4
#define AHB_MON_HPROT_MATCH_BIT         4
#define AHB_MON_HPROT_MATCH_NUM_BITS    4



#ifndef __ASSEMBLY__
typedef enum AHB_MON_MODES {
    AHB_MON_MODE_IDLE,
    AHB_MON_MODE_ACTIVE,
    AHB_MON_MODE_RESET
} AHB_MON_MODES_T;

typedef enum AHB_MON_HWRITE {
    AHB_MON_HWRITE_INACTIVE,
    AHB_MON_HWRITE_WRITES,
    AHB_MON_HWRITE_READS,
    AHB_MON_HWRITE_READS_AND_WRITES
} AHB_MON_HWRITE_T;

typedef enum AHB_MON_HBURST {
    AHB_MON_HBURST_SINGLE,
    AHB_MON_HBURST_INCR,
    AHB_MON_HBURST_WRAP4,
    AHB_MON_HBURST_INCR4,
    AHB_MON_HBURST_WRAP8,
    AHB_MON_HBURST_INCR8,
    AHB_MON_HBURST_WRAP16,
    AHB_MON_HBURST_INCR16
} AHB_MON_HBURST_T;
#endif // __ASSEMBLY__

/* AHB read monitor registers */
#define AHB_MON_CYCLES_REG_OFFSET       0x00
#define AHB_MON_TRANSFERS_REG_OFFSET    0x04
#define AHB_MON_WAITS_REG_OFFSET        0x08

#define STATIC_BUS1_CONTROL_VALUE   0x04010484  /*  200nS rd/wr cycles to allow DMAing to SMC91x on static bus */

/* PWM register definitions */
#define PWM_DATA_REGISTER_BASE (PWM_BASE)
#define PWM_CLOCK_REGISTER  (PWM_BASE+0X400)

/* MPCore specific registers */
#define OX820_ARM11MP_SCU_BASE       (PERIPH_BASE | 0x0000)
#define OX820_GIC_CPU_BASE_ADDR      (PERIPH_BASE | 0x0100)
#define OX820_GIC_CPUN_BASE_ADDR(n)  (PERIPH_BASE + 0x0200 + ((n) * 0x100))
#define OX820_TWD_BASE               (PERIPH_BASE | 0x0600)
#define OX820_TWD_CPU0_BASE          (PERIPH_BASE | 0x0700)
#define OX820_TWD_CPU1_BASE          (PERIPH_BASE | 0x0800)
#define OX820_TWD_CPU2_BASE          (PERIPH_BASE | 0x0900)
#define OX820_TWD_CPU3_BASE          (PERIPH_BASE | 0x0A00)
#define OX820_GIC_DIST_BASE_ADDR     (PERIPH_BASE | 0x1000)

#define OX820_ARM11MP_TWD_SIZE 0x100

/* PCIe support */
//#define pcibios_assign_all_busses() 1
#define PCIBIOS_MIN_IO	0	/* May need something other than zero once we understand the significance */
#define PCIBIOS_MIN_MEM	0

/* PCIe core register contents */
#define SYS_CTRL_PCIE_DEVICE_TYPE_BIT	0
#define SYS_CTRL_PCIE_DEVICE_TYPE_ENDPOINT			0
#define SYS_CTRL_PCIE_DEVICE_TYPE_LEGACY_ENDPOINT	1
#define SYS_CTRL_PCIE_DEVICE_TYPE_ROOT				4
#define SYS_CTRL_PCIE_LTSSM_BIT			4
#define SYS_CTRL_PCIE_READY_ENTR_L23_BIT	9
#define SYS_CTRL_PCIE_LINK_UP_BIT		11
#define SYS_CTRL_PCIE_OBTRANS_BIT		12

/* PCIe slave control contents */
#define SYS_CTRL_PCIE_SLAVE_BE_BIT	22

/* Inbound address translation register in the PCIe ELBI region */
#define PIM0_MEM_ADDR_LIMIT		(PCIEA_ELBI_BASE + 0x00)
#define PIM1_MEM_ADDR_LIMIT		(PCIEA_ELBI_BASE + 0x08)
#define PIM0_MEM_ADDR_START		(PCIEA_ELBI_BASE + 0x10)
#define PIM1_MEM_ADDR_START		(PCIEA_ELBI_BASE + 0x18)
#define PIM_IO_ADDR_OFFSET		(PCIEA_ELBI_BASE + 0x20)

#define IB_ADDR_XLATE_ENABLE	(PCIEA_ELBI_BASE + 0xFC)
#define ENABLE_IN_ADDR_TRANS_BIT	0

/* Std PCI configuration registers */
#define PCI_CONFIG_VERSION_DEVICEID_REG_OFFSET	0x00
#define PCI_CONFIG_COMMAND_STATUS_REG_OFFSET	0x04

#endif // __ASM_ARCH_HARDWARE_H
