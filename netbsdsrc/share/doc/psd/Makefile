#	$NetBSD: Makefile,v 1.6.2.1 1997/10/23 06:36:06 mellon Exp $
#	@(#)Makefile	8.2 (Berkeley) 5/23/94

# The following modules do not build/install:
# 10.gdb, 13.rcs

# Missing:
# 07.pascal 14.sccs 17.m4

# Missing from 4.4BSD-Lite:
# 01.cacm 02.implement 03.iosys 04.uprog 06.Clang 08.f77 09.f77io
# 11.adb 15.yacc 16.lex

BINDIR=	/usr/share/doc/psd
FILES=	00.contents Makefile Title
SUBDIR=	05.sysman 20.ipctut 21.ipc
.if exists(12.make)
SUBDIR+= 12.make
.endif
.if exists(18.gprof)
SUBDIR+= 18.gprof
.endif
.if exists(19.curses)
SUBDIR+= 19.curses
.endif
#SUBDIR=	01.cacm 02.implement 03.iosys 04.uprog 05.sysman 06.Clang \
#	07.pascal 08.f77 09.f77io 11.adb 12.make 14.sccs 15.yacc \
#	16.lex 17.m4 18.gprof 19.curses 20.ipctut 21.ipc

Title.ps: ${FILES}
	groff Title > ${.TARGET}

.include <bsd.prog.mk>
.include <bsd.subdir.mk>
