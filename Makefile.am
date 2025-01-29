AUTOMAKE_OPTIONS = foreign subdir-objects
AM_CFLAGS = -Wall -Wextra -Wpedantic
AM_CPPFLAGS = -I $(top_srcdir)/include

bin_PROGRAMS = bin/mat
default = src/main.c src/error.c src/util_text.c
libdata = src/sll.c src/mnode.c
libop = src/matrix_op.c src/eval.c src/stack.c

if RANLIB
libraries = lib/libdata.a lib/libop.a
noinst_LIBRARIES = $(libraries)
lib_libdata_a_SOURCES = $(libdata)
lib_libop_a_SOURCES = $(libop)

bin_mat_SOURCES = $(default)
bin_mat_LDADD = $(libraries)
else
bin_mat_SOURCES = $(default) $(libdata) $(libop)
endif

EXTRA_DIST = include

test:
	valgrind --leak-check=full bin/mat
