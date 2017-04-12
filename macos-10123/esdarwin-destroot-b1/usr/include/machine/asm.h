/* ESDARWIN Header for ancient Libm */
#ifndef __MACHINE_ASM_H_ESDARWIN_
#define __MACHINE_ASM_H_ESDARWIN_

#ifdef __ESDARWIN__

#define PRIVATE_ENTRY(x) /* nothing */
#define ENTRY(x) x:
#define RCSID(x) /* nothing */

#else /* !__ESDARWIN__ */
#include_next <machine/asm.h>
#endif /* __ESDARWIN__ */

#endif /* __MACHINE_ASM_H_ESDARWIN_ */

