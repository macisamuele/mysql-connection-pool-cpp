#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([mysql-connection-pool], [1], [macisamuele@gmail.com])
AM_INIT_AUTOMAKE([1.9 foreign])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL
LT_INIT
AC_LANG_PUSH([C++])


AC_ARG_WITH(memory-tracer,
[AS_HELP_STRING(--with-memory-tracer,Extensive memory tracer logging on stderr)],
[ if test "x$withval" != "xno" ; then
    AC_DEFINE(MEMORY_TRACER_ON,,[enable memory tracing features])
  fi ])

AC_SEARCH_LIBS([strerror],[cposix])
AC_CHECK_LIB(mysqlcppconn, get_driver_instance,
            [LIBS="$LIBS -lmysqlcppconn"],
            AC_MSG_ERROR(*** libmysqlcppconn not found))

BOOST_REQUIRE([1.46])
LIBS="$LIBS -lboost_system"

AC_CHECK_HEADER([boost/lexical_cast.hpp], [],
  [AC_MSG_ERROR([Could not find the boost/lexical_cast.hpp BOOST header])])
AC_CHECK_HEADER([boost/shared_ptr.hpp], [],
  [AC_MSG_ERROR([Could not find the boost/shared_ptr.hpp BOOST header])])
AC_CHECK_HEADER([boost/thread/mutex.hpp], [],
  [AC_MSG_ERROR([Could not find the boost/thread/mutex.hpp BOOST header])])
AC_CHECK_HEADER([boost/date_time/posix_time/posix_time.hpp], [],
  [AC_MSG_ERROR([Could not find the boost/date_time/posix_time/posix_time.hpp BOOST header])])


AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

AC_CONFIG_FILES([Makefile
  src/Makefile src/macisamuele/Makefile
  test/Makefile test/macisamuele/Makefile
])

AC_OUTPUT

