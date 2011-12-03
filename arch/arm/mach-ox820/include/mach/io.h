/*
 * arch/arm/mach-0x820/include/mach/io.h
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARM_ARCH_IO_H
#define __ASM_ARM_ARCH_IO_H

#include <mach/hardware.h>

#define IO_SPACE_LIMIT 0xffffffff

#define __mem_pci(a)	(a)


#define	__io(v)		__typesafe_io(v)

#endif //__ASM_ARM_ARCH_IO_H
