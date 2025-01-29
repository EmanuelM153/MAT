#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([mat], [0.1])
AC_CONFIG_HEADERS([config.h:config.h.in])
AC_CONFIG_SRCDIR([src/main.c])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strstr], [],
[
AC_MSG_ERROR([missing strstr])
])

# Automake
AM_INIT_AUTOMAKE
AM_CONDITIONAL([RANLIB], [test x$RANLIB = xranlib])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
