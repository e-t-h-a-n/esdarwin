/*
 * Copyright (c) 2000-2016 Apple Inc. All rights reserved.
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

#ifndef	_KERN_DEBUG_H_
#define _KERN_DEBUG_H_

#include <kern/kcdata.h>

#include <sys/cdefs.h>
#include <stdint.h>
#include <uuid/uuid.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>

#include <TargetConditionals.h>

#ifdef __APPLE_API_PRIVATE
#ifdef __APPLE_API_UNSTABLE

struct thread_snapshot {
	uint32_t 		snapshot_magic;
	uint32_t 		nkern_frames;
	uint32_t 		nuser_frames;
	uint64_t 		wait_event;
	uint64_t 	 	continuation;
	uint64_t 		thread_id;
	uint64_t 		user_time;
	uint64_t 		system_time;
	int32_t  		state;
	int32_t			priority;    /*	static priority */
	int32_t			sched_pri;   /* scheduled (current) priority */
	int32_t			sched_flags; /* scheduler flags */
	char			ss_flags;
	char			ts_qos;      /* effective qos */
	char			ts_rqos;     /* requested qos */
	char			ts_rqos_override; /* requested qos override */
	char			io_tier;
	char			_reserved[3]; /* pad for 4 byte alignement packing */

	/*
	 * I/O Statistics
	 * XXX: These fields must be together
	 */
	uint64_t 		disk_reads_count;
	uint64_t 		disk_reads_size;
	uint64_t 		disk_writes_count;
	uint64_t 		disk_writes_size;
	uint64_t 		io_priority_count[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t 		io_priority_size[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t 		paging_count;
	uint64_t 		paging_size;
	uint64_t 		non_paging_count;
	uint64_t 		non_paging_size;
	uint64_t 		data_count;
	uint64_t 		data_size;
	uint64_t 		metadata_count;
	uint64_t 		metadata_size;
	/* XXX: I/O Statistics end */

	uint64_t		voucher_identifier; /* obfuscated voucher identifier */
	uint64_t		total_syscalls;
	char			pth_name[STACKSHOT_MAX_THREAD_NAME_SIZE];

} __attribute__((packed));

/* old, non kcdata format */
struct task_snapshot {
	uint32_t snapshot_magic;
	int32_t pid;
	uint64_t		uniqueid;
	uint64_t		user_time_in_terminated_threads;
	uint64_t		system_time_in_terminated_threads;
	uint8_t			shared_cache_identifier[16];
	uint64_t		shared_cache_slide;
	uint32_t		nloadinfos;
	int			suspend_count; 
	int			task_size;	/* pages */
	int			faults;		/* number of page faults */
	int			pageins;	/* number of actual pageins */
	int			cow_faults;	/* number of copy-on-write faults */
	uint32_t		ss_flags;
	uint64_t		p_start_sec;	/* from the bsd proc struct */
	uint64_t		p_start_usec;	/* from the bsd proc struct */

	/* 
	 * We restrict ourselves to a statically defined
	 * (current as of 2009) length for the
	 * p_comm string, due to scoping issues (osfmk/bsd and user/kernel
	 * binary compatibility).
	 */
	char			p_comm[17];
	uint32_t 		was_throttled;
	uint32_t 		did_throttle;
	uint32_t		latency_qos;
	/*
	 * I/O Statistics
	 * XXX: These fields must be together.
	 */
	uint64_t 		disk_reads_count;
	uint64_t 		disk_reads_size;
	uint64_t 		disk_writes_count;
	uint64_t 		disk_writes_size;
	uint64_t 		io_priority_count[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t 		io_priority_size[STACKSHOT_IO_NUM_PRIORITIES];
	uint64_t 		paging_count;
	uint64_t 		paging_size;
	uint64_t 		non_paging_count;
	uint64_t 		non_paging_size;
	uint64_t 		data_count;
	uint64_t 		data_size;
	uint64_t 		metadata_count;
	uint64_t 		metadata_size;
	/* XXX: I/O Statistics end */

	uint32_t		donating_pid_count;

} __attribute__ ((packed));



struct micro_snapshot {
	uint32_t		snapshot_magic;
	uint32_t		ms_cpu;	 /* cpu number this snapshot was recorded on */
	uint64_t		ms_time; /* time at sample (seconds) */
	uint64_t		ms_time_microsecs;
	uint8_t			ms_flags;
	uint16_t		ms_opaque_flags;	/* managed by external entity, e.g. fdrmicrod */
} __attribute__ ((packed));



struct _dyld_cache_header
{
    char    	magic[16];				// e.g. "dyld_v0    i386"
    uint32_t	mappingOffset;          // file offset to first dyld_cache_mapping_info
    uint32_t    mappingCount;           // number of dyld_cache_mapping_info entries
    uint32_t    imagesOffset;           // file offset to first dyld_cache_image_info
    uint32_t    imagesCount;            // number of dyld_cache_image_info entries
    uint64_t    dyldBaseAddress;        // base address of dyld when cache was built
    uint64_t    codeSignatureOffset;    // file offset of code signature blob
    uint64_t    codeSignatureSize;     	// size of code signature blob (zero means to end of file)
    uint64_t    slideInfoOffset;        // file offset of kernel slid info
    uint64_t    slideInfoSize;          // size of kernel slid info
    uint64_t    localSymbolsOffset;     // file offset of where local symbols are stored
    uint64_t    localSymbolsSize;       // size of local symbols information
    uint8_t     uuid[16];               // unique value for each shared cache file
};


enum micro_snapshot_flags {
	kInterruptRecord	= 0x1,
	kTimerArmingRecord	= 0x2,
	kUserMode 		= 0x4, /* interrupted usermode, or armed by usermode */
	kIORecord 		= 0x8,
};

/*
 * Flags used in the following assortment of snapshots.
 */
enum generic_snapshot_flags {
	kUser64_p 			= 0x1,
	kKernel64_p 		= 0x2
};


#define VM_PRESSURE_TIME_WINDOW 5 /* seconds */

enum {
	STACKSHOT_GET_DQ                           = 0x01,
	STACKSHOT_SAVE_LOADINFO                    = 0x02,
	STACKSHOT_GET_GLOBAL_MEM_STATS             = 0x04,
	STACKSHOT_SAVE_KEXT_LOADINFO               = 0x08,
	STACKSHOT_GET_MICROSTACKSHOT               = 0x10,
	STACKSHOT_GLOBAL_MICROSTACKSHOT_ENABLE     = 0x20,
	STACKSHOT_GLOBAL_MICROSTACKSHOT_DISABLE    = 0x40,
	STACKSHOT_SET_MICROSTACKSHOT_MARK          = 0x80,
	STACKSHOT_ACTIVE_KERNEL_THREADS_ONLY       = 0x100,
	STACKSHOT_GET_BOOT_PROFILE                 = 0x200,
	STACKSHOT_SAVE_IMP_DONATION_PIDS           = 0x2000,
	STACKSHOT_SAVE_IN_KERNEL_BUFFER            = 0x4000,
	STACKSHOT_RETRIEVE_EXISTING_BUFFER         = 0x8000,
	STACKSHOT_KCDATA_FORMAT                    = 0x10000,
	STACKSHOT_ENABLE_BT_FAULTING               = 0x20000,
	STACKSHOT_COLLECT_DELTA_SNAPSHOT           = 0x40000,
	/*
	 * STACKSHOT_TAILSPIN flips on several features aimed at minimizing the size
	 * of stackshots.  It is meant to be used only by the tailspin daemon.  Its
	 * behavior may be changed at any time to suit the needs of the tailspin
	 * daemon.  Seriously, if you are not the tailspin daemon, don't use this
	 * flag.  If you need these features, ask us to add a stable SPI for what
	 * you need.   That being said, the features it turns on are:
	 *
	 * minimize_uuids: If the set of loaded dylibs or kexts has not changed in
	 * the delta period, do then not report them.
	 *
	 * iostats: do not include io statistics.
	 *
	 * trace_fp: do not include the frame pointers in stack traces.
	 *
	 * minimize_nonrunnables: Do not report detailed information about threads
	 * which were not runnable in the delta period.
	 */
	STACKSHOT_TAILSPIN                         = 0x80000,
	/*
	 * Kernel consumers of stackshot (via stack_snapshot_from_kernel) can ask
	 * that we try to take the stackshot lock, and fail if we don't get it.
	 */
	STACKSHOT_TRYLOCK                          = 0x100000,
	STACKSHOT_ENABLE_UUID_FAULTING             = 0x200000,
	STACKSHOT_FROM_PANIC                       = 0x400000,
	STACKSHOT_NO_IO_STATS                      = 0x800000,
};

#define STACKSHOT_THREAD_SNAPSHOT_MAGIC 	0xfeedface
#define STACKSHOT_TASK_SNAPSHOT_MAGIC   	0xdecafbad
#define STACKSHOT_MEM_AND_IO_SNAPSHOT_MAGIC	0xbfcabcde
#define STACKSHOT_MICRO_SNAPSHOT_MAGIC		0x31c54011

#endif /* __APPLE_API_UNSTABLE */
#endif /* __APPLE_API_PRIVATE */


extern unsigned int	systemLogDiags;
#if (!defined(__arm64__) && !defined(NAND_PANIC_DEVICE)) || defined(LEGACY_PANIC_LOGS)
extern char debug_buf[];
#endif
extern char *debug_buf_addr;
extern char *debug_buf_stackshot_start;
extern char *debug_buf_stackshot_end;

extern unsigned int	debug_boot_arg;
extern unsigned char *kernel_uuid;
extern char kernel_uuid_string[];
extern char   panic_disk_error_description[];
extern size_t panic_disk_error_description_size;


#define DB_HALT		0x1
#define DB_PRT		0x2
#define DB_NMI		0x4
#define DB_KPRT		0x8
#define DB_KDB		0x10
#define DB_SLOG		0x20
#define DB_ARP          0x40
#define DB_KDP_BP_DIS   0x80
#define DB_LOG_PI_SCRN	0x100
#define DB_KDP_GETC_ENA 0x200

#define DB_KERN_DUMP_ON_PANIC		0x400 /* Trigger core dump on panic*/
#define DB_KERN_DUMP_ON_NMI		0x800 /* Trigger core dump on NMI */
#define DB_DBG_POST_CORE		0x1000 /*Wait in debugger after NMI core */
#define DB_PANICLOG_DUMP		0x2000 /* Send paniclog on panic,not core*/
#define DB_REBOOT_POST_CORE		0x4000 /* Attempt to reboot after
						* post-panic crashdump/paniclog
						* dump.
						*/
#define DB_NMI_BTN_ENA  	0x8000  /* Enable button to directly trigger NMI */
#define DB_PRT_KDEBUG   	0x10000 /* kprintf KDEBUG traces */
#define DB_DISABLE_LOCAL_CORE   0x20000 /* ignore local kernel core dump support */
#define DB_DISABLE_GZIP_CORE    0x40000 /* don't gzip kernel core dumps */

#if DEBUG
/*
 * For the DEBUG kernel, support the following:
 *	sysctl -w debug.kprint_syscall=<syscall_mask> 
 *	sysctl -w debug.kprint_syscall_process=<p_comm>
 * <syscall_mask> should be an OR of the masks below
 * for UNIX, MACH, MDEP, or IPC. This debugging aid
 * assumes the task/process is locked/wired and will
 * not go away during evaluation. If no process is
 * specified, all processes will be traced
 */
extern int debug_kprint_syscall;
extern int debug_kprint_current_process(const char **namep);
#define DEBUG_KPRINT_SYSCALL_PREDICATE_INTERNAL(mask, namep)			\
	( (debug_kprint_syscall & (mask)) && debug_kprint_current_process(namep) )
#define DEBUG_KPRINT_SYSCALL_MASK(mask, fmt, args...)	do { 			\
		const char *dks_name = NULL;									\
		if (DEBUG_KPRINT_SYSCALL_PREDICATE_INTERNAL(mask, &dks_name)) {	\
			kprintf("[%s%s%p]" fmt, dks_name ? dks_name : "",			\
					dks_name ? "@" : "", current_thread(), args);			\
		}																\
	} while (0)
#else /* !DEBUG */
#define DEBUG_KPRINT_SYSCALL_PREDICATE_INTERNAL(mask, namep) (0)
#define DEBUG_KPRINT_SYSCALL_MASK(mask, fmt, args...) do { } while (0) /* kprintf(fmt, args) */
#endif /* !DEBUG */

enum {
	DEBUG_KPRINT_SYSCALL_UNIX_MASK = 1 << 0,
	DEBUG_KPRINT_SYSCALL_MACH_MASK = 1 << 1,
	DEBUG_KPRINT_SYSCALL_MDEP_MASK = 1 << 2,
	DEBUG_KPRINT_SYSCALL_IPC_MASK  = 1 << 3
};

#define DEBUG_KPRINT_SYSCALL_PREDICATE(mask)				\
	DEBUG_KPRINT_SYSCALL_PREDICATE_INTERNAL(mask, NULL)
#define DEBUG_KPRINT_SYSCALL_UNIX(fmt, args...)				\
	DEBUG_KPRINT_SYSCALL_MASK(DEBUG_KPRINT_SYSCALL_UNIX_MASK,fmt,args)
#define DEBUG_KPRINT_SYSCALL_MACH(fmt, args...)				\
	DEBUG_KPRINT_SYSCALL_MASK(DEBUG_KPRINT_SYSCALL_MACH_MASK,fmt,args)
#define DEBUG_KPRINT_SYSCALL_MDEP(fmt, args...)				\
	DEBUG_KPRINT_SYSCALL_MASK(DEBUG_KPRINT_SYSCALL_MDEP_MASK,fmt,args)
#define DEBUG_KPRINT_SYSCALL_IPC(fmt, args...)				\
	DEBUG_KPRINT_SYSCALL_MASK(DEBUG_KPRINT_SYSCALL_IPC_MASK,fmt,args)





__BEGIN_DECLS

extern void panic(const char *string, ...) __printflike(1,2);

void _consume_panic_args(int, ...);
void panic_context(unsigned int reason, void *ctx, const char *string, ...);
void panic_with_options(unsigned int reason, void *ctx, uint64_t debugger_options_mask, const char *str, ...);

/* launchd crashed prefix in message to signal special panic handling */
#define	LAUNCHD_CRASHED_PREFIX			"initproc exited"

/*
 * Values for a 64-bit mask that's passed to the debugger.
 */
#define DEBUGGER_OPTION_NONE			0x0ULL
#define DEBUGGER_OPTION_PANICLOGANDREBOOT	0x1ULL /* capture a panic log and then reboot immediately */

#ifdef CONFIG_NO_PANIC_STRINGS
#define panic_plain(x, ...) _consume_panic_args( 0, ## __VA_ARGS__ )
#define panic(x, ...) _consume_panic_args( 0, ## __VA_ARGS__ )
#else /* CONFIGS_NO_PANIC_STRINGS */
#define panic_plain(ex, ...) \
	(panic)(ex, ## __VA_ARGS__)
#define __STRINGIFY(x) #x
#define LINE_NUMBER(x) __STRINGIFY(x)
#define PANIC_LOCATION __FILE__ ":" LINE_NUMBER(__LINE__)
#define panic(ex, ...) \
	(panic)(# ex "@" PANIC_LOCATION, ## __VA_ARGS__)
#endif /* CONFIGS_NO_PANIC_STRINGS */

void 		populate_model_name(char *);
unsigned	panic_active(void);



__END_DECLS


#endif	/* _KERN_DEBUG_H_ */
