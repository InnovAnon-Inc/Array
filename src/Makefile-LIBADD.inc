include $(top_srcdir)/swap/src/Makefile-LIBADD.inc

if USE_SUBMODULES
LIBARRAY_LIBADD = ../swap/src/.libs/libswap.la $(LIBSWAP_LIBADD)
else
LIBARRAY_LIBADD = -lswap $(LIBSWAP_LIBADD)
endif
