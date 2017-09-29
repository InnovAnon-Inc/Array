AC_INIT([libswap], [0.0], [laurence.a.maddox@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SUBDIRS([glitter swap])

AC_CHECK_HEADERS([stdlib.h sys/types.h string.h])
AC_CHECK_HEADERS([glitter.h swap.h])

AC_CHECK_LIB([stdlib],[malloc,free])
AC_CHECK_LIB([stdlib],[memcpy])
AC_CHECK_LIB([swap],[swap,swap2,swaps,swaps2])

INNOVANON_WARNINGS([])

AC_OUTPUT
