ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
AM_MAKEFLAGS = --no-print-directory

MAINTAINERCLEANFILES = \
ABOUT-NLS \
Makefile.in \
aclocal.m4 \
autom4te.cache \
config.guess \
config.h.in \
config.h.in~ \
config.rpath \
config.sub \
configure \
depcomp \
install-sh \
ltmain.sh \
missing \
mkinstalldirs \
$(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz \
$(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.bz2 \
$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)-doc.tar.bz2 \
m4/libtool.m4 \
m4/lt~obsolete.m4 \
m4/ltoptions.m4 \
m4/ltsugar.m4 \
m4/ltversion.m4 \
m4/codeset.m4 \
m4/gettext.m4 \
m4/glibc21.m4 \
m4/iconv.m4 \
m4/intdiv0.m4 \
m4/inttypes_h.m4 \
m4/inttypes.m4 \
m4/inttypes-pri.m4 \
m4/isc-posix.m4 \
m4/lcmessage.m4 \
m4/lib-ld.m4 \
m4/lib-link.m4 \
m4/lib-prefix.m4 \
m4/nls.m4 \
m4/po.m4 \
m4/progtest.m4 \
m4/stdint_h.m4 \
m4/uintmax_t.m4 \
m4/ulonglong.m4 \
debian/files \
debian/smman.debhelper.log \
debian/smman.substvars \
debian/stamp*

EXTRA_DIST =

bin_PROGRAMS =
EXTRA_CPPFLAGS = \
-I$(top_srcdir) \
-I$(top_srcdir)/src/include/

include src/lib/Makefile.mk
include src/bin/Makefile.mk

maintainer-clean-local:
	rm -rf autom4te.cache

if ENABLE_TESTS

lcov-reset:
	@rm -rf $(top_builddir)/coverage
	@find $(top_builddir) -name "*.gcda" -delete
	@lcov --zerocounters --directory $(top_builddir)

lcov-report:
	@mkdir $(top_builddir)/coverage
	lcov --capture --compat-libtool --output-file $(top_builddir)/coverage/coverage.info --directory $(top_builddir)
	lcov --remove $(top_builddir)/coverage/coverage.info '*.h' --output-file $(top_builddir)/coverage/coverage.cleaned.info
	genhtml -t "$(PACKAGE_STRING)" -o $(top_builddir)/coverage/html $(top_builddir)/coverage/coverage.cleaned.info
	@echo "Coverage Report at $(top_builddir)/coverage/html"
	if test -d $(top_builddir)/doc/html/; then cp -vfr $(top_builddir)/coverage/html $(top_builddir)/doc/html/; mv $(top_builddir)/doc/html/html $(top_builddir)/doc/html/coverage/; fi

check-local:
	@$(MAKE) lcov-reset
else

lcov-reset:
	@echo "reconfigure with --enable-tests"

lcov-report:
	@echo "reconfigure with --enable-tests"

check-local:
	@echo "reconfigure with --enable-tests"
endif
