/*
 * OX820 chip GPIO driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Supports:
 * OX820
 */

#include "leds-gpio-ox820-common.h"

#define DRIVER_NAME "ox820-led-gpio-pogoplugpro"

static struct ox820_gpio_led ox820_leds[] = {
	{
		.led = {
			.name = "power",
			.brightness_set = ox820_gpioleds_set
		},
		.gpio = 25,
		.active_low = 0,
		.delayed_switch_to_output = 0
	},
};

#include "leds-gpio-ox820-common.c"

MODULE_DESCRIPTION("OX820 GPIO-LED PogoPlugPro driver");
MODULE_AUTHOR("Sven Bormann");
MODULE_LICENSE("GPL");
