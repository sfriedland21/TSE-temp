# Makefile for 'querier'
#
# Sydney Friedland, May 2020
# 
# Based on Makefile for bags module by:
# David Kotz, April 2016, 2017
# updated by Xia Zhou, July 2016, 2018, January 2019
# updated by Temi Prioleau, January 2020

L = ../libcs50

PROG = querier
OBJS = querier.o ../common/pagedir.o ../common/index.o ../common/word.o
LIBS =
LLIBS = $L/libcs50.a ../common/common.a

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=gnu11 -ggdb $(TESTING) -I$L -I../common
CC = gcc
MAKE = make

all: querier fuzzquery

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

fuzzquery: fuzzquery.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: test clean

clean:
	rm -f *~ *.o *.dSYM
	rm -f querier
	rm -f fuzzquery
	rm -f stocks
	rm -f core
test:
	bash testing.sh