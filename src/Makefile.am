AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
#SUBDIRS += ../swap
#AM_CPPFLAGS += -I $(top_srcdir)/swap/src
#
#SUBDIRS += ../MultiMalloc
#AM_CPPFLAGS += -I $(top_srcdir)/MultiMalloc/src
#endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

#include Makefile-LIBADD.inc
#dist_bin_SCRIPTS = libarray_config array_test_config

lib_LTLIBRARIES += libarray.la
#libarray_la_LIBADD = $(LIBARRAY_LIBADD)
#libarray_la_LIBADD = @LIBARRAY_LIBADD@
#libarray_la_LIBADD = $(shell ./libarray_config --libs)
libarray_la_CPPFLAGS = $(GLITTER_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
libarray_la_LIBADD   = $(GLITTER_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)
include_HEADERS += array.h

#include ../../StD/src/Makefile-LIBADD.inc
bin_PROGRAMS += array-test
#array_test_LDADD = libarray.la $(LIBARRAY_LIBADD) -lsimon $(LIBSIMON_LIBADD)
#array_test_LDADD = libarray.la $(shell ./libarray_test_config --libs)
#array_test_LDADD = $(ARRAY_TEST_LIBADD)
#array_test_LDADD = @ARRAY_TEST_LIBADD@
EXTRA_array_test_DEPENDENCIES = libarray.la
array_test_CPPFLAGS =         $(GLITTER_CFLAGS) $(SIMON_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
array_test_LDADD    = -larray $(GLITTER_LIBS)   $(SIMON_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)

