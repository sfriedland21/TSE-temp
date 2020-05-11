# Makefile for 'crawler'
#
# Sydney Friedland, May 2020
# 
# Based on Makefile for bags module by:
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Temi Prioleau, January 2020

L = ../libcs50

PROG = crawler
OBJS = crawler.o
LIBS =
LLIBS = $L/libcs50-given.a ../common/common.a

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I../common
CC = gcc
MAKE = make

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

.PHONY: test clean

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks
	rm -f core
test:
	bash testing.sh

