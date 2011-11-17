TOPDIR := $(shell pwd)
CFLAGS := -std=c99 -Wall $(shell pkg-config --libs --cflags libxml-2.0)
ifneq ($(DEBUG),)
    CFLAGS := -O0 -DREADABLE_DEBUG -std=c99 -ggdb3 $(CFLAGS)
else
    CFLAGS := -O3 $(CFLAGS)
endif

ifeq ($(ICU),)
    CFLAGS := $(CFLAGS) $(shell pkg-config --libs --cflags libpcre)
else
    CFLAGS := -DREADABLE_USE_LIBICU $(shell icu-config --cflags --ldflags) $(CFLAGS)
endif

ifneq ($(READABLE_TEST),)
    CFLAGS := $(CFLAGS) -DREADABLE_TEST
endif

all: readable readable.so

readable: readable.c rd_list.c main.c
	gcc $(CFLAGS) readable.c rd_list.c main.c -o readable

readable.so: py.c readable.c rd_list.c Makefile
	CFLAGS="$(CFLAGS)" python setup.py build \
	    && mv build/*/readable.so . \
	    && rm -fr build \
	    && touch __init__.py

clean:
	rm -f *.so *.o __init__.py* readable
