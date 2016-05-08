AUTOMAKE_OPTIONS = subdir-objects
SUBDIRS = macisamuele

noinst_PROGRAMS = test
test_SOURCES = main.cpp

test_DEPENDS = ./macisamuele/.libs/libconcrete-connection-pool.a ../src/macisamuele/.libs/libmysql-connection-pool.a
test_LDADD = ./macisamuele/.libs/libconcrete-connection-pool.a ../src/macisamuele/.libs/libmysql-connection-pool.a


test_CPPFLAGS = $(BOOST_CPPFLAGS)
test_LDPATH = $(BOOST_LDPATH)
