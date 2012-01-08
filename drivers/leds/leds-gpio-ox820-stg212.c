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

#include <linux/module.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/stddef.h>
#include <linux/leds.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/pm_runtime.h>
#include <mach/hardware.h>

#if 1
#define ox820_printk(x...) printk(x)
#else
#define ox820_printk(x...) {}
#endif

struct ox820_gpio_led {
	struct led_classdev led;
	unsigned gpio;
	u8 active_low;
};

static void ox820_gpioleds_set(struct led_classdev* led_cdev,
						enum led_brightness value)
{
	struct ox820_gpio_led* led_dat = 
		container_of(led_cdev, struct ox820_gpio_led, led);
	int level;
	if(value == LED_OFF) {
		level = 0;
	} else {
		level = 1;
	}
	if(led_dat->active_low) {
		level = !level;
	}
	
	gpio_set_value(led_dat->gpio, level);
}

static struct ox820_gpio_led ox820_leds[] = {
	{
		.led = {
			.name = "sysled.blue",
			.brightness_set = ox820_gpioleds_set
		},
		.gpio = 37,
		.active_low = 0
	},
	{
		.led = {
			.name = "sysled.red",
			.brightness_set = ox820_gpioleds_set
		},
		.gpio = 38,
		.active_low = 1
	},
	{
		.led = {
			.name = "copyled",
			.brightness_set = ox820_gpioleds_set
		},
		.gpio = 40,
		.active_low = 1
	},
#ifdef CONFIG_LEDS_OX820_STG212_BUZZER
	{
		.led = {
			.name = "buzzer",
			.brightness_set = ox820_gpioleds_set
		},
		.gpio = 47,
		.active_low = 1
	}
#endif
};

static int __devinit ox820_gpioleds_probe(struct platform_device* pdev)
{
	int ret = 0;
	
	return ret;
}

static int __devexit ox820_gpioleds_remove(struct platform_device* pdev)
{
	int ret = 0;
	return ret;
}

static struct platform_driver ox820_gpioleds_driver = {
	.driver = {
		.name = "ox820-led-gpio-stg212",
	},
	.probe = ox820_gpioleds_probe,
	.remove = ox820_gpioleds_remove
};

static void ox820_gpioleds_release(struct device* dev)
{
}

static struct platform_device ox820_gpioleds_dev = 
{
	.name = "ox820-led-gpio-stg212",
	.id = 0,
	.num_resources = 0,
	.resource  = NULL,
	.dev.coherent_dma_mask = 0,
	.dev.release = ox820_gpioleds_release
}; 

static int __init ox820_gpioleds_platform_init(void)
{
	int ret, idx;

	ret = platform_driver_register(&ox820_gpioleds_driver);
	if(0 == ret) {
		ret = platform_device_register(&ox820_gpioleds_dev);
		if(0 != ret) {
			platform_driver_unregister(&ox820_gpioleds_driver);
		}
	}
	
	if(0 == ret) {
		ox820_printk(KERN_INFO"ox820_led_gpio: requesting GPIOs\n");
		for(idx = 0; idx < sizeof(ox820_leds) / sizeof(ox820_leds[0]); ++idx) {
			ret = gpio_request(ox820_leds[idx].gpio, ox820_leds[idx].led.name);
			if(0 == ret) {
				ret = gpio_direction_output(ox820_leds[idx].gpio, ox820_leds[idx].active_low);
				if(0 != ret) {
					gpio_free(ox820_leds[idx].gpio);
				}
			}
			if (0 != ret) {
				break;
			}
		}
		
		if(0 != ret) {
			while(idx-- != 0) {
				gpio_free(ox820_leds[idx].gpio);
			}
			platform_device_unregister(&ox820_gpioleds_dev);
			platform_driver_unregister(&ox820_gpioleds_driver);
		}
	}
	
	if(0 == ret) {
		ox820_printk(KERN_INFO"ox820_led_gpio: registering LEDs\n");
		for(idx = 0; idx < sizeof(ox820_leds) / sizeof(ox820_leds[0]); ++idx) {
			ret = led_classdev_register(&ox820_gpioleds_dev.dev, &ox820_leds[idx].led);
			if(0 != ret) {
				break;
			}
		}
		
		if(0 != ret) {
			while(idx-- != 0) {
				led_classdev_unregister(&ox820_leds[idx].led);
			}
			for(idx = 0; idx < sizeof(ox820_leds) / sizeof(ox820_leds[0]); ++idx) {
				gpio_free(ox820_leds[idx].gpio);
			}
			platform_device_unregister(&ox820_gpioleds_dev);
			platform_driver_unregister(&ox820_gpioleds_driver);
		}
	}
	
	if(0 != ret) {
		printk(KERN_ERR"ox820_led_gpio: initialization result %d\n", ret);
	} else {	
		printk(KERN_INFO"ox820_led_gpio: initialized\n");
	}
	
	return ret;
}

static void __exit ox820_gpioleds_platform_exit(void)
{
	int idx;
	for(idx = 0; idx < sizeof(ox820_leds) / sizeof(ox820_leds[0]); ++idx) {
		led_classdev_unregister(&ox820_leds[idx].led);
		gpio_free(ox820_leds[idx].gpio);
	}
	platform_device_unregister(&ox820_gpioleds_dev);
	platform_driver_unregister(&ox820_gpioleds_driver);
}

MODULE_DESCRIPTION("OX820 GPIO-LED STG212 driver");
MODULE_AUTHOR("Sven Bormann");
MODULE_LICENSE("GPL");

module_init(ox820_gpioleds_platform_init);
module_exit(ox820_gpioleds_platform_exit);
