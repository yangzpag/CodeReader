/*	$NetBSD: exec_conf.c,v 1.19 1996/10/02 05:29:32 cgd Exp $	*/

/*
 * Copyright (c) 1993, 1994 Christopher G. Demetriou
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Christopher G. Demetriou.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/exec.h>

#ifdef EXEC_SCRIPT
#include <sys/exec_script.h>
#endif

#ifdef EXEC_AOUT
/*#include <sys/exec_aout.h> -- automatically pulled in */
#endif

#ifdef EXEC_ECOFF
#include <sys/exec_ecoff.h>
#endif

#if defined(EXEC_ELF32) || defined(EXEC_ELF64)
#include <sys/exec_elf.h>
#endif

#ifdef COMPAT_SVR4
#include <compat/svr4/svr4_exec.h>
#endif

#ifdef COMPAT_IBCS2
#include <compat/ibcs2/ibcs2_exec.h>
#endif

#ifdef COMPAT_LINUX
#include <compat/linux/linux_exec.h>
#endif

#ifdef COMPAT_FREEBSD
#include <compat/freebsd/freebsd_exec.h>
#endif

#ifdef COMPAT_HPUX
#include <compat/hpux/hpux_exec.h>
#endif

#ifdef COMPAT_M68K4K
#include <compat/m68k4k/m68k4k_exec.h>
#endif

struct execsw execsw[] = {
#ifdef LKM
	{ 0, NULL, },					/* entries for LKMs */
	{ 0, NULL, },
	{ 0, NULL, },
	{ 0, NULL, },
	{ 0, NULL, },
#endif
#ifdef EXEC_SCRIPT
	{ MAXINTERP, exec_script_makecmds, },		/* shell scripts */
#endif
#ifdef EXEC_AOUT
	{ sizeof(struct exec), exec_aout_makecmds, },	/* a.out binaries */
#endif
#ifdef EXEC_ECOFF
	{ ECOFF_HDR_SIZE, exec_ecoff_makecmds, },	/* ecoff binaries */
#endif
#ifdef EXEC_ELF32
	{ ELF32_HDR_SIZE, exec_elf32_makecmds, },	/* 32bit ELF bins */
#endif
#ifdef EXEC_ELF64
	{ ELF64_HDR_SIZE, exec_elf64_makecmds, },	/* 64bit ELF bins */
#endif
#ifdef COMPAT_LINUX
	{ LINUX_AOUT_HDR_SIZE, exec_linux_aout_makecmds, }, /* linux a.out */
#endif
#ifdef COMPAT_IBCS2
	{ COFF_HDR_SIZE, exec_ibcs2_coff_makecmds, },	/* coff binaries */
	{ XOUT_HDR_SIZE, exec_ibcs2_xout_makecmds, },	/* x.out binaries */
#endif
#ifdef COMPAT_FREEBSD
	{ FREEBSD_AOUT_HDR_SIZE, exec_freebsd_aout_makecmds, },	/* a.out */
#endif
#ifdef COMPAT_HPUX
	{ HPUX_EXEC_HDR_SIZE, exec_hpux_makecmds, },	/* HP-UX a.out */
#endif
#ifdef COMPAT_M68K4K
	{ sizeof(struct exec), exec_m68k4k_makecmds, },	/* m68k4k a.out */
#endif
};
int nexecs = (sizeof execsw / sizeof(*execsw));
int exec_maxhdrsz;
