MAINTAINERCLEANFILES += \
src/bin/*.gc{no,da}

bin_PROGRAMS += \
src/bin/fingered

src_bin_fingered_SOURCES = \
src/bin/main.c
src_bin_fingered_CPPFLAGS = @BIN_CFLAGS@ $(EXTRA_CPPFLAGS)
src_bin_fingered_LDFLAGS = @BIN_LIBS@
src_bin_fingered_LDADD = \
src/lib/libfingered.la
