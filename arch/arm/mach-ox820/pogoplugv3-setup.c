/*
 * arch/arm/mach-ox820/pogoplugv3-setup.c
 *
 * Pogoplug V3 (without PCI) Setup
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/completion.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/serial_8250.h>
#include <linux/io.h>
#include <asm/sizes.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/hardware/gic.h>
#include <mach/hardware.h>
#include <mach/dma.h>
#include <mach/rps-irq.h>
#include "common.h"



static void __init pogoplugv3_init(void)
{
	/* Initialise the spinlock used to make GPIO register set access atomic */
	spin_lock_init(&oxnas_gpio_spinlock);
	
	/*
	 * Initialise the support for our multi-channel memory-to-memory DMAC
	 * The interrupt subsystem needs to be available before we can initialise
	 * the DMAC support
	 */
	//    oxnas_dma_init();
	
	#ifdef CONFIG_LEON_START_EARLY
	init_copro(leon_early_srec, 0);
	#endif // CONFIG_LEON_START_EARLY
	
	// Add any platform bus devices
	platform_add_devices(platform_devices, ARRAY_SIZE(platform_devices));
	
	pm_power_off = arch_poweroff;
	
}



MACHINE_START(POGOPLUGV3, "Pogoplug V3")
	/* Maintainer: ALARM */
	#if 0
	#ifdef CONFIG_ARCH_OXNAS_UART1
	.phys_io = UART_1_BASE_PA,
	.io_pg_offst = (((u32)UART_1_BASE) >> 18) & 0xfffc,
	#elif defined(CONFIG_ARCH_OXNAS_UART2)
	.phys_io = UART_2_BASE_PA,
	.io_pg_offst = (((u32)UART_2_BASE) >> 18) & 0xfffc,
	#endif
	#endif    
	.boot_params = SDRAM_PA + 0x100,
	.fixup = oxnas_fixup,
	.map_io = oxnas_mapio,
	.init_irq = oxnas_init_irq,
	.timer = &oxnas_timer,
	.init_machine = pogoplugv3_init,
MACHINE_END
