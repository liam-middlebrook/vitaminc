PREFIX := /usr/local

CPPFLAGS := -I./include
#CPPFLAGS += $(shell pkg-config)

CFLAGS := -std=c99 -Wall -Wextra -fPIC -pedantic

ifeq ($(CC),gcc)
    CFLAGS += -ggdb3
endif
ifeq ($(CC),clang)
    CFLAGS += -Qunused-arguments -ggdb -Weverything
endif

#CFLAGS += $(shell pkg-config)

#LIBRARIES := $(shell pkg-config)

AR=ar
ARFLAGS=rvs

SOURCE := $(wildcard src/*.c)

all: libvitaminc.a libvitaminc.so

libvitaminc.so: vitaminc.o util.o
	$(CC) -shared -o libvitaminc.so vitaminc.o util.o $(LIBRARIES)

libvitaminc.a: vitaminc.o util.o
	$(AR) $(ARFLAGS) libvitaminc.a vitaminc.o util.o

util.o: src/util.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) src/util.c

vitaminc.o: src/vitaminc.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) src/vitaminc.c

test: libvitaminc.a libvitaminc.so
	$(CC) $(CFLAGS) $(CPPFLAGS) -o libvitaminc-tests test/vitaminc_tests.c -lvitaminc -lcunit -lm
	./libvitaminc-tests

.PHONY: install
install:
	install -m 0755 libvitaminc.a $(PREFIX)/lib
	install -m 0755 libvitaminc.so $(PREFIX)/lib
	install -m 0755 include/vitaminc.h $(PREFIX)/include

.PHONY: clean
clean:
	rm -f *.a *.o *.so

