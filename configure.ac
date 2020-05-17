AC_INIT([libarray], [0.0], [laurence.a.maddox@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/array.pc
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_SUBDIRS([glitter swap MultiMalloc])

AC_CHECK_HEADERS([stdlib.h sys/types.h string.h])
AC_CHECK_HEADERS([glitter.h swap.h mmalloc.h])

AC_CHECK_LIB([stdlib],[malloc,free])
AC_CHECK_LIB([stdlib],[memcpy])
AC_CHECK_LIB([swap],[swap,swap2,swaps,swaps2])
AC_CHECK_LIB([mmalloc],[mmalloc,mfree])

#srcdir = @srcdir@
#LIBARRAY_LIBADD="`PATH=$(srcdir)src:$PATH libarray_config --libs`"
#LIBARRAY_LIBADD="`PATH=src:$PATH libarray_config --libs`"
#AC_SUBST(LIBARRAY_LIBADD)

#ARRAY_TEST_LIBADD="libarray.la `PATH=$(srcdir)src:$PATH array_test_config --libs`"
#ARRAY_TEST_LIBADD="`PATH=$(srcdir)src:$PATH array_test_config --libs`"
#ARRAY_TEST_LIBADD="`PATH=src:$PATH array_test_config --libs`"
#AC_SUBST(ARRAY_TEST_LIBADD)

PKG_CHECK_MODULES([GLITTER],[glitter],,)
PKG_CHECK_MODULES([SWAP],[swap],,)
PKG_CHECK_MODULES([MMALLOC],[mmalloc],,)
PKG_CHECK_MODULES([SIMON],[simon],,)

INNOVANON_WARNINGS([])

AC_OUTPUT
