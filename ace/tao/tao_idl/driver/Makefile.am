##----------------------------------------------------------------------------
##       Makefile.am,v 1.7 2000/09/29 21:46:40 othman Exp
##
##       Makefile.am for the TAO IDL compiler --- 'driver' sub-directory
##----------------------------------------------------------------------------

##
##  Process this file with automake to create Makefile.in
##

## The number in AUTOMAKE_OPTIONS is the minimum required version automake
## needed to process this file.
AUTOMAKE_OPTIONS = 1.4

INCLUDES = \
  -I$(top_builddir) \
  -I$(top_srcdir) \
  -I$(top_srcdir)/TAO_IDL/include \
  -I$(top_srcdir)/TAO_IDL/be_include

noinst_LTLIBRARIES = libdriver.la

libdriver_la_SOURCES = \
  drv_args.cpp \
  drv_fork.cpp \
  drv_init.cpp \
  drv_link.cpp \
  drv_preproc.cpp \
  drv_private.cpp

## Additional C++ preprocessor flags to define for the TAO IDL compiler.
AM_CPPFLAGS = \
  -DTAO_IDL_PREPROCESSOR=\"$(CXX)\" \
  -DTAO_IDL_INCLUDE_DIR=\"$(pkgincludedir)\"

## Clean up some additional files/directories possibly created during
## the configure script tests.
clean-local:
	-rm -f *.bak *.rpo *.sym lib*.*_pure_* Makefile.old core
	-rm -rf ptrepository Templates.DB gcctemp.c gcctemp so_locations

