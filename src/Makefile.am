AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libarray.la
libarray_la_CPPFLAGS = $(GLITTER_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
libarray_la_LIBADD   = $(GLITTER_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)
include_HEADERS += array.h

bin_PROGRAMS += array-test
EXTRA_array_test_DEPENDENCIES = libarray.la
array_test_CPPFLAGS =         $(GLITTER_CFLAGS) $(SIMON_CFLAGS) $(SWAP_CFLAGS) $(MMALLOC_CFLAGS)
array_test_LDADD    = -larray $(GLITTER_LIBS)   $(SIMON_LIBS)   $(SWAP_LIBS)   $(MMALLOC_LIBS)

