AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libarray.la
libarray_la_CPPFLAGS = $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
libarray_la_LIBADD   = $(SWAP_LIBS)   $(MMALLOC_LIBS)
include_HEADERS += array.h

bin_PROGRAMS += array-test
EXTRA_array_test_DEPENDENCIES = libarray.la
array_test_CPPFLAGS =         $(SIMON_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
array_test_LDADD    = -larray $(SIMON_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)

