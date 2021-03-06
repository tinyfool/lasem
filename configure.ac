AC_PREREQ(2.63.0)

m4_define([lasem_version_major], [0])
m4_define([lasem_version_minor], [3])
m4_define([lasem_version_micro], [2])
m4_define([lasem_version], [lasem_version_major.lasem_version_minor.lasem_version_micro])

m4_define([lasem_libtool_current], m4_eval(100 * lasem_version_major + lasem_version_minor))

AC_INIT([lasem], [lasem_version], [http://bugzilla.gnome.org/], [lasem])

AM_INIT_AUTOMAKE([-Wno-portability dist-bzip2])
AM_MAINTAINER_MODE

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_SUBST([LASEM_API_VERSION], [0.4])
AC_SUBST([LASEM_API_VERSION_U],[AS_TR_SH([$LASEM_API_VERSION])])
AC_SUBST([LASEM_LIBTOOL_VERSION], [lasem_libtool_current:lasem_version_micro:0])

AC_SEARCH_LIBS([strerror],[cposix])
AC_PROG_CC

AC_HEADER_STDC

AM_PROG_LEX
AC_PROG_YACC

AC_SUBST(GETTEXT_PACKAGE, lasem-${LASEM_API_VERSION})
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

LT_INIT()

PKG_CHECK_MODULES(LASEM, [gobject-2.0
			  glib-2.0
			  gio-2.0
			  gdk-pixbuf-2.0 >= 2.16
			  cairo >= 1.2
			  pangocairo >= 1.16.0
			  libxml-2.0])
AC_SUBST(LASEM_CFLAGS)
AC_SUBST(LASEM_LIBS)

AC_PATH_PROG(GLIB_MKENUMS, glib-mkenums)

GOBJECT_INTROSPECTION_CHECK([0.6.7])
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
AM_CONDITIONAL([BUILD_GTK_DOC], [test "x$enable_gtk_doc" = "xyes" || test ! -f "autogen.sh"])

AC_CONFIG_FILES([
Makefile
itex2mml/Makefile
src/Makefile
tests/Makefile
po/Makefile.in
docs/Makefile
docs/reference/Makefile
docs/reference/lasem/Makefile
lasem.pc
])
AC_OUTPUT

echo ""
echo "Configuration:"
echo ""
echo "    Yacc:                   ${YACC}"
echo "    Lex:                    ${LEX}"
echo "    Compiler:               ${CC}"
echo "    Compiler flags:         ${CFLAGS} ${LASEM_CFLAGS}"
echo ""
