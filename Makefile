###############################################################################
# NAME:		    Makefile
#
# AUTHOR:	    Ethan D. Twardy <edtwardy@mtu.edu>
#
# DESCRIPTION:	    Makefile for the Heap API.
#
# CREATED:	    07/21/2018
#
# LAST EDITED:	    07/21/2018
###

CC=gcc
CFLAGS=-Wall -Wextra -pedantic
OBJS=heap.o

ifeq ($(MAKECMDGOALS),debug)
	CFLAGS += -g -O0
	OBJS += test-heap.o
else
	CFLAGS += -O3
endif

$(OBJS):

debug: force test-heap

test-heap: $(OBJS)

force:

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f test-heap

##############################################################################
