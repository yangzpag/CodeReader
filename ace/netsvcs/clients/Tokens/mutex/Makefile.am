##----------------------------------------------------------------------------
##       Makefile.am,v 4.1 1999/03/20 08:06:20 othman Exp
##
##       Makefile for repeating token client application
##----------------------------------------------------------------------------

##
##  Process this file with automake to create Makefile.in
##

## The number in AUTOMAKE_OPTIONS is the minimum required version automake
## needed to process this file.
AUTOMAKE_OPTIONS = 1.4

INCLUDES = -I$(top_builddir) -I$(top_srcdir)

noinst_PROGRAMS = \
         test_mutex

test_mutex_SOURCES = test_mutex.cpp
test_mutex_LDADD = \
                 $(top_builddir)/netsvcs/lib/libnetsvcs.la \
                 $(top_builddir)/ace/libACE.la


