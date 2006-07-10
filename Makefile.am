##  Process this file with automake to produce Makefile.in
## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

SUBDIRS = src tools

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA = libwbxml2.pc

wbxmldocdir = ${prefix}/share/doc/wbxml2-${VERSION}
wbxmldoc_DATA = \
	AUTHORS\
	bootstrap\
	BUGS\
	ChangeLog\
	COPYING\
	GNU-LGPL\
	INSTALL\
	NEWS\
	README\
	References\
	THANKS\
	TODO\
	doxygen.h

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(wbxmldocdir)/manual
	cp -Rp doc/* $(DESTDIR)$(wbxmldocdir)/manual

dist-bz2: distdir
	sed -e "s/tar.gz/tar.bz2/g" $(distdir)/wbxml2.spec > $(distdir)/wbxml2.spec.aux
	mv $(distdir)/wbxml2.spec.aux $(distdir)/wbxml2.spec
	sed -e "s/tar.gz/tar.bz2/g" $(distdir)/wbxml2.spec.in > $(distdir)/wbxml2.spec.in.aux
	mv $(distdir)/wbxml2.spec.in.aux $(distdir)/wbxml2.spec.in
	$(AMTAR) chof - $(distdir) | bzip2 -c >$(distdir).tar.bz2
	$(am__remove_distdir)

# include wbxml.spec to allow `rpmbuild -ta`
EXTRA_DIST = wbxml2.spec $(wbxmldoc_DATA) doc win32
