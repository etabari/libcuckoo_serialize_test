# make LIBCUCKOO=/path/to/libcuckoo/is/installed
# make DESTDIR=/tmp/stage install

RM=rm -f
INC=includes

UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CXX=clang++
	LDLIBS=-lstdc++ -stdlib=libc++
else
	CXX=g++
	LDLIBS=-lstdc++ -lm -lpthread
endif

CXXFLAGS=-g -std=c++14 -I$(INC)

ifneq ($(LIBCUCKOO),) 
	CXXFLAGS=-std=c++14 -I$(LIBCUCKOO)
endif

all:
	@echo "Making..."
	$(CXX) $(CXXFLAGS) -o test test.cc $(LDLIBS)

clean:
	$(RM) $(BUILDDIR)/*
