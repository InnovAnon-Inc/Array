lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libarray.la
libarray_la_SOURCES = array.c
libarray_la_LIBADD = -lswap
include_HEADERS += array.h
bin_PROGRAMS += array
array_SOURCES = array-test.c
array_LDADD = libarray.la -lswap

AM_CPPFLAGS = -D__STDC_INT64__
AM_CPPFLAGS += -I $(srcdir)/../glitter/src
AM_CPPFLAGS += -I $(srcdir)/../swap/src
