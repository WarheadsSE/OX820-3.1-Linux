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
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/pm_runtime.h>
#include <mach/hardware.h>

spinlock_t ox820_lock;

static inline void ox820_switch_to_gpio(unsigned nr)
{
	unsigned long flags;
	unsigned long gpio_mask;

	spin_lock_irqsave(&ox820_lock, flags);
	
	if(nr <= SYS_CTRL_NUM_PINS)
	{
		gpio_mask = 1 << nr;
		writel(readl(SYS_CTRL_SECONDARY_SEL)   & ~(gpio_mask), SYS_CTRL_SECONDARY_SEL);
		writel(readl(SYS_CTRL_TERTIARY_SEL)    & ~(gpio_mask), SYS_CTRL_TERTIARY_SEL);
		writel(readl(SYS_CTRL_QUATERNARY_SEL)  & ~(gpio_mask), SYS_CTRL_QUATERNARY_SEL);
		writel(readl(SYS_CTRL_DEBUG_SEL)       & ~(gpio_mask), SYS_CTRL_DEBUG_SEL);
		writel(readl(SYS_CTRL_ALTERNATIVE_SEL) & ~(gpio_mask), SYS_CTRL_ALTERNATIVE_SEL);
	} else {
		gpio_mask = 1 << (nr - SYS_CTRL_NUM_PINS);
		writel(readl(SEC_CTRL_SECONDARY_SEL)   & ~(gpio_mask), SEC_CTRL_SECONDARY_SEL);
		writel(readl(SEC_CTRL_TERTIARY_SEL)    & ~(gpio_mask), SEC_CTRL_TERTIARY_SEL);
		writel(readl(SEC_CTRL_QUATERNARY_SEL)  & ~(gpio_mask), SEC_CTRL_QUATERNARY_SEL);
		writel(readl(SEC_CTRL_DEBUG_SEL)       & ~(gpio_mask), SEC_CTRL_DEBUG_SEL);
		writel(readl(SEC_CTRL_ALTERNATIVE_SEL) & ~(gpio_mask), SEC_CTRL_ALTERNATIVE_SEL);
	}
	
	spin_unlock_irqrestore(&ox820_lock, flags);
}

static int ox820_gpio_direction_input(struct gpio_chip* gpio, unsigned nr)
{
	if(nr >= 50) {
		return -EINVAL;
	}
	
	ox820_switch_to_gpio(nr);

	if(nr <= SYS_CTRL_NUM_PINS)
	{
		writel(1 << (nr & 31), GPIO_A_OUTPUT_ENABLE_CLEAR);
	}
	else
	{
		nr -= SYS_CTRL_NUM_PINS;
		writel(1 << (nr & 31), GPIO_B_OUTPUT_ENABLE_CLEAR);
	}
	
	return 0;
}

static int ox820_gpio_get(struct gpio_chip* gpio, unsigned nr)
{
	if(nr >= 50) {
		return 0;
	}
	
	if(nr <= SYS_CTRL_NUM_PINS) {
		return !!(readl(GPIO_A_DATA) & (1 << nr));
	} else {
		return !!(readl(GPIO_A_DATA) & (1 << (nr - SYS_CTRL_NUM_PINS)));
	}
}

static int ox820_gpio_set_debounce(struct gpio_chip* chip,
					unsigned nr,
					unsigned debounce)
{
	unsigned long flags;
	if(nr >= 50) {
		return -EINVAL;
	}
	
	ox820_switch_to_gpio(nr);
	
	spin_lock_irqsave(&ox820_lock, flags);
	if(nr <= SYS_CTRL_NUM_PINS) {
		writel(readl(GPIO_A_INPUT_DEBOUNCE_ENABLE) | (1 << (nr & 31)), GPIO_A_INPUT_DEBOUNCE_ENABLE);
	}
	else {
		nr -= SYS_CTRL_NUM_PINS;
		writel(readl(GPIO_B_INPUT_DEBOUNCE_ENABLE) | (1 << (nr & 31)), GPIO_B_INPUT_DEBOUNCE_ENABLE);
	}
	spin_unlock_irqrestore(&ox820_lock, flags);
	
	return 0;
}

static int ox820_gpio_direction_output(struct gpio_chip* gpio,
					unsigned nr,
					int val)
{
	if(nr >= 50) {
		return -EINVAL;
	}
	
	ox820_switch_to_gpio(nr);
	
	if(nr <= SYS_CTRL_NUM_PINS) {
		writel(1 << (nr & 31), GPIO_A_OUTPUT_ENABLE_SET);
	}
	else {
		nr -= SYS_CTRL_NUM_PINS;
		writel(1 << (nr & 31), GPIO_B_OUTPUT_ENABLE_SET);
	}
	
	return 0;
}

static void ox820_gpio_set(struct gpio_chip* gpio,
				unsigned nr,
				int val)
{
	if(nr >= 50) {
		return;
	}

	if(val) {
		if(nr <= SYS_CTRL_NUM_PINS) {
			writel(1 << (nr & 31), GPIO_A_OUTPUT_SET);
		} else {
			nr -= SYS_CTRL_NUM_PINS;
			writel(1 << (nr & 31), GPIO_B_OUTPUT_SET);
		}
	} else {
		if(nr <= SYS_CTRL_NUM_PINS) {
			writel(1 << (nr & 31), GPIO_A_OUTPUT_CLEAR);
		} else {
			nr -= SYS_CTRL_NUM_PINS;
			writel(1 << (nr & 31), GPIO_B_OUTPUT_CLEAR);
		}
	}
}

const char* ox820_gpio_names[50] = {
	"ox820_gpio_00",
	"ox820_gpio_01",
	"ox820_gpio_02",
	"ox820_gpio_03",
	"ox820_gpio_04",
	"ox820_gpio_05",
	"ox820_gpio_06",
	"ox820_gpio_07",
	"ox820_gpio_08",
	"ox820_gpio_09",
	"ox820_gpio_10",
	"ox820_gpio_11",
	"ox820_gpio_12",
	"ox820_gpio_13",
	"ox820_gpio_14",
	"ox820_gpio_15",
	"ox820_gpio_16",
	"ox820_gpio_17",
	"ox820_gpio_18",
	"ox820_gpio_19",
	"ox820_gpio_20",
	"ox820_gpio_21",
	"ox820_gpio_22",
	"ox820_gpio_23",
	"ox820_gpio_24",
	"ox820_gpio_25",
	"ox820_gpio_26",
	"ox820_gpio_27",
	"ox820_gpio_28",
	"ox820_gpio_29",
	"ox820_gpio_30",
	"ox820_gpio_31",
	"ox820_gpio_32",
	"ox820_gpio_33",
	"ox820_gpio_34",
	"ox820_gpio_35",
	"ox820_gpio_36",
	"ox820_gpio_37",
	"ox820_gpio_38",
	"ox820_gpio_39",
	"ox820_gpio_40",
	"ox820_gpio_41",
	"ox820_gpio_42",
	"ox820_gpio_43",
	"ox820_gpio_44",
	"ox820_gpio_45",
	"ox820_gpio_46",
	"ox820_gpio_47",
	"ox820_gpio_48",
	"ox820_gpio_49",
};

static struct gpio_chip ox820_gpio = {
	.label = "ox820_gpio",
	.dev = NULL,
	.owner = NULL,
	.direction_input = ox820_gpio_direction_input,
	.get = ox820_gpio_get,
	.direction_output = ox820_gpio_direction_output,
	.set_debounce = ox820_gpio_set_debounce,
	.set = ox820_gpio_set,
	//.to_irq = ox820_gpio_to_irq,
	.base = 0,
	.ngpio = 50,
	.names = ox820_gpio_names,
};

static int __devinit ox820_gpio_probe(struct platform_device* pdev)
{
	int ret;
	
	/* disable interrupts for now */
	writel(0, GPIO_A_INTERRUPT_ENABLE);
	writel(0, GPIO_B_INTERRUPT_ENABLE);
	
	ret = gpiochip_add(&ox820_gpio);
	
	return ret;
}

static int __devexit ox820_gpio_remove(struct platform_device* pdev)
{
	int ret;
	ret = gpiochip_remove(&ox820_gpio);
	return ret;
}

static struct platform_driver ox820_gpio_driver = {
	.driver = {
		.name = "ox820-gpio",
	},
	.probe = ox820_gpio_probe,
	.remove = ox820_gpio_remove
};

static int __init ox820_gpio_platform_init(void)
{
	int ret;
	spin_lock_init(&ox820_lock);

	ret = platform_driver_register(&ox820_gpio_driver);
	
	if(0 == ret)
	{
	}
	
	return ret;
}

static void __exit ox820_gpio_platform_exit(void)
{
	platform_driver_unregister(&ox820_gpio_driver);
}

MODULE_DESCRIPTION("OX820 GPIO driver");
MODULE_AUTHOR("Sven Bormann");
MODULE_LICENSE("GPL");

module_init(ox820_gpio_platform_init);
module_exit(ox820_gpio_platform_exit);
