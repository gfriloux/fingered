MAINTAINERCLEANFILES += src/lib/*.gc{no,da}

lib_LTLIBRARIES = src/lib/libfingered.la

src_lib_libfingered_la_SOURCES = \
src/lib/fingered_main.c \
src/lib/fingered_event.c \
src/lib/fingered_private.h \
src/include/Fingered.h
src_lib_libfingered_la_CFLAGS = $(LIBS_CFLAGS) $(EXTRA_CPPFLAGS)
src_lib_libfingered_la_LDFLAGS = $(LIBS_LIBS)
