/*
 * Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	vm/vm_kern.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Date:	1985
 *
 *	Kernel memory management definitions.
 */

#ifndef	_VM_VM_KERN_H_
#define _VM_VM_KERN_H_

#include <mach/mach_types.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>



extern kern_return_t	kmem_alloc(
				vm_map_t	map,
				vm_offset_t	*addrp,
				vm_size_t	size);

extern kern_return_t	kmem_alloc_pageable(
				vm_map_t	map,
				vm_offset_t	*addrp,
				vm_size_t	size);

extern kern_return_t	kmem_alloc_kobject(
				vm_map_t	map,
				vm_offset_t	*addrp,
				vm_size_t	size);

extern void		kmem_free(
				vm_map_t	map,
				vm_offset_t	addr,
				vm_size_t	size);




extern vm_map_t	kernel_map;
extern vm_map_t	kernel_pageable_map;
extern vm_map_t ipc_kernel_map;



extern vm_offset_t vm_kernel_addrperm_ext;

extern void	vm_kernel_addrperm_external(
			vm_offset_t addr,
			vm_offset_t *perm_addr);

extern void	vm_kernel_unslide_or_perm_external(
		vm_offset_t addr,
		vm_offset_t *up_addr);
#endif	/* _VM_VM_KERN_H_ */
