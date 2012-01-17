/*
 * arch/arm/mach-ox820/ox820.c
 *
 * Copyright (C) 2006,2009 Oxford Semiconductor Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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







static void __init oxnas_init_machine(void)
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



MACHINE_START(OX820, "Oxsemi NAS")
    /* Maintainer: Oxford Semiconductor Ltd */
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
    .init_machine = oxnas_init_machine,
MACHINE_END
