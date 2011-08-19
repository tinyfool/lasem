include $(top_srcdir)/Makefile.decl

-include $(INTROSPECTION_MAKEFILE)
  INTROSPECTION_GIRS =
  INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir)
  INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(LASEM_CFLAGS) \
	-DG_LOG_DOMAIN=\"Lasem\"

AM_CFLAGS = -Wall

lib_LTLIBRARIES = liblasem-dom-@LASEM_API_VERSION@.la

BUILT_SOURCES = lsmdomenumtypes.h	\
		lsmdomenumtypes.c

EXTRA_DIST = lsmdomenumtypes.h.template 	\
	     lsmdomenumtypes.c.template

liblasem_dom_@LASEM_API_VERSION@_la_LIBADD = 	\
	../itex2mml/libitex2mml.la		\
	$(LASEM_LIBS)

LASEM_DOM_SRCS =				\
	lsm.c					\
	lsmdebug.c				\
	lsmstr.c				\
	lsmtraits.c				\
	lsmproperties.c				\
	lsmattributes.c				\
	lsmcairo.c				\
	lsmdomenumtypes.c			\
	lsmdomnode.c				\
	lsmdomnodelist.c			\
	lsmdomnamednodemap.c			\
	lsmdomdocument.c			\
	lsmdomdocumentfragment.c		\
	lsmdomelement.c				\
	lsmdomcharacterdata.c			\
	lsmdomtext.c				\
	lsmdomview.c				\
	lsmdomparser.c				\
	lsmdomimplementation.c

LASEM_DOM_HDRS = 				\
	lsm.h					\
	lsmtypes.h				\
	lsmcairo.h				\
	lsmstr.h				\
	lsmdebug.h				\
	lsmtraits.h				\
	lsmproperties.h				\
	lsmattributes.h				\
	lsmdom.h				\
	lsmdomtypes.h				\
	lsmdomnode.h				\
	lsmdomnodelist.h			\
	lsmdomnamednodemap.h			\
	lsmdomdocument.h			\
	lsmdomdocumentfragment.h		\
	lsmdomelement.h				\
	lsmdomcharacterdata.h			\
	lsmdomtext.h				\
	lsmdomview.h				\
	lsmdomparser.h				\
	lsmdomimplementation.h

liblasem_dom_@LASEM_API_VERSION@_ladir = $(includedir)/lasem-@LASEM_API_VERSION@

liblasem_dom_@LASEM_API_VERSION@_la_SOURCES = $(LASEM_DOM_SRCS)

liblasem_dom_@LASEM_API_VERSION@_la_HEADERS = $(LASEM_DOM_HDRS)
liblasem_dom_@LASEM_API_VERSION@_la_HEADERS += lsmdomenumtypes.h

liblasem_dom_@LASEM_API_VERSION@_la_LDFLAGS = -version-info $(LASEM_LIBTOOL_VERSION)

lsmdomenumtypes.h: lsmdomenumtypes.h.template $(LASEM_DOM_HDRS) $(GLIB_MKENUMS)
	$(AM_V_GEN) (cd $(srcdir) && $(GLIB_MKENUMS) --template lsmdomenumtypes.h.template $(LASEM_DOM_HDRS)) > $@

lsmdomenumtypes.c: lsmdomenumtypes.c.template $(LASEM_DOM_HDRS) $(GLIB_MKENUMS)
	$(AM_V_GEN) (cd $(srcdir) && $(GLIB_MKENUMS) --template lsmdomenumtypes.c.template $(LASEM_DOM_HDRS)) > $@

bin_PROGRAMS = lasem-render-@LASEM_API_VERSION@

lasem_render_@LASEM_API_VERSION@_SOURCES = 				\
	lasemrender.c

lasem_render_@LASEM_API_VERSION@_LDFLAGS =

lasem_render_@LASEM_API_VERSION@_LDADD = $(LASEM_LIBS) liblasem-dom-@LASEM_API_VERSION@.la ../itex2mml/libitex2mml.la

CLEANFILES = $(BUILT_SOURCES)

if HAVE_INTROSPECTION

introspection_files = $(liblasem_dom_@LASEM_API_VERSION@_la_SOURCES) \
		      $(liblasem_dom_@LASEM_API_VERSION@_la_HEADERS)

Lasem-@LASEM_API_VERSION@.gir: $(INTROSPECTION_SCANNER)
Lasem_0_4_gir_INCLUDES = GObject-2.0 cairo-1.0 Gio-2.0 Pango-1.0 GdkPixbuf-2.0
Lasem_0_4_gir_SCANNERFLAGS = --strip-prefix=Lsm
Lasem_0_4_gir_CFLAGS = $(INCLUDES)
Lasem_0_4_gir_LIBS = liblasem-dom-@LASEM_API_VERSION@.la
Lasem_0_4_gir_FILES = $(addprefix $(srcdir)/,$(introspection_files))

INTROSPECTION_GIRS += Lasem-@LASEM_API_VERSION@.gir

girdir = $(datadir)/gir-1.0
dist_gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(dist_gir_DATA) $(typelib_DATA)

endif
