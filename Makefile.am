# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libarray.pc src/array-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libarray.pc.in src/array-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

