AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

SUBDIRS += ../swap
AM_CPPFLAGS += -I $(top_srcdir)/swap/src

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

include $(srcdir)/Makefile-LIBADD.inc

lib_LTLIBRARIES += libarray.la
libarray_la_LIBADD = $(LIBARRAY_LIBADD)
include_HEADERS += array.h
bin_PROGRAMS += array-test
array_test_LDADD = libarray.la $(LIBARRAY_LIBADD)
