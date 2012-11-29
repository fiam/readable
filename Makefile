TOPDIR := $(shell pwd)
CFLAGS := -std=c99 -Wall $(shell pkg-config --cflags libxml-2.0)
LDFLAGS := $(shell pkg-config --libs libxml-2.0)
ifneq ($(DEBUG),)
    CFLAGS := -O0 -DREADABLE_DEBUG -std=c99 -ggdb3 $(CFLAGS)
else
    CFLAGS := -O3 $(CFLAGS)
endif

ifeq ($(ICU),)
    CFLAGS := $(CFLAGS) $(shell pkg-config --cflags libpcre)
    LDFLAGS := $(LDFLAGS) $(shell pkg-config --libs libpcre)
else
    CFLAGS := $(CFLAGS) -DREADABLE_USE_LIBICU $(shell icu-config --cflags)
    LDFLAGS := $(LDFLAGS) $(shell icu-config --ldflags)
endif

ifneq ($(READABLE_TEST),)
    CFLAGS := $(CFLAGS) -DREADABLE_TEST
endif

all: readable python

readable: readable.c rd_list.c main.c
	$(CC) $(CFLAGS) readable.c rd_list.c main.c -o readable $(LDFLAGS)

readable.so: py.c readable.c rd_list.c Makefile
	CFLAGS="$(CFLAGS)" LDFLAGS="-Wl,--no-as-needed $(LDFLAGS)" \
	    python setup.py build_ext --inplace \
	    && touch __init__.py

python: readable.so

clean:
	rm -f *.so *.o __init__.py* readable
