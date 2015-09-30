m4_define([v_maj], [0])
m4_define([v_min], [0])
m4_define([v_mic], [1])
m4_define([v_ver], [v_maj.v_min.v_mic])

AC_INIT([fingered], [v_ver], [guillaume@friloux.me])

AC_PREREQ(2.01)
AC_CONFIG_SRCDIR([configure.ac])

AM_INIT_AUTOMAKE([1.6 dist-bzip2])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
AC_CONFIG_MACRO_DIR([m4])

dnl we just have set the version info, then:
version_number=v_ver
AC_SUBST(version_number)

AC_PROG_LIBTOOL
GCC_STACK_PROTECT_LIB
GCC_STACK_PROTECT_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_MKDIR_P
AC_PROG_MAKE_SET

PKG_PROG_PKG_CONFIG

EFL_CHECK_FUNCS([fingered], [fnmatch])
EFL_CHECK_TESTS([fingered], [enable_tests="yes"], [enable_tests="no"])

if test "x${enable_tests}" = "xyes" ; then
   CFLAGS="-W -Wall -g -O1 -DDEBUG -fprofile-arcs -ftest-coverage"
   LDFLAGS="-lgcov -rdynamic -fvisibility=default"
else
   CFLAGS="$CFLAGS -W -Wall -O2"
   LDFLAGS="-Wl,--as-needed -rdynamic -fvisibility=default"
fi

AC_CONFIG_FILES([
Makefile
])

build_libs=
LIBS_REQUIRES="eina ecore eio"
PKG_CHECK_MODULES(LIBS, [$LIBS_REQUIRES], [build_libs=yes], [build_libs=no])

build_fingered=
if test "x${build_libs}" = "xyes"; then
   BIN_REQUIRES="eina ecore ecore-con eio"
   PKG_CHECK_MODULES(BIN, [$BIN_REQUIRES], [build_fingered=yes], [build_fingered=no])
else
  build_fingered=no
fi

AM_CONDITIONAL(ENABLE_TESTS, [test "x${enable_tests}" = "xyes"])

AC_CONFIG_HEADER([config.h])

AC_OUTPUT([
])

echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE_NAME $PACKAGE_VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Configuration Options Summary:"
echo
echo "  fingered.....: ${build_fingered}"
echo "  prefix.......: ${prefix}"
echo "  tests........: ${enable_tests} (Coverage: ${efl_enable_coverage})"
echo
echo "Build Options:"
echo "  CPPFLAGS.....: $CPPFLAGS"
echo "  CFLAGS.......: $CFLAGS"
echo "  LDFLAGS......: $LDFLAGS"
echo
