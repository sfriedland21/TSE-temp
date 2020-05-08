# Makefile for 'common' 
#
# Sydney Friedland, May 2020
# 
# Based on Makefile for CS50 library by:
# David Kotz, April 2016, July 2017, April 2019
# Updated by Xia Zhou, July 2016
# Updated by Temi Prioleau, January 2020

L = ../libcs50

PROG = 
OBJS = pagedir.o
LIB = common.a
LLIBS = $L/libcs50-given.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L
CC = gcc
MAKE = make

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
pagedir.o: pagedir.h $L/webpage.h

.PHONY: clean

clean:
	rm -f core
	rm -f $(LIB) *~ *.o