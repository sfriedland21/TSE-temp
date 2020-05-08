#!/bin/bash
# Testing script for crawler.c
# 
# Author: Sydney Friedland
# May, 2020
#
# Based on testing script by Temi Prioleau
# Feb 5, 2020
#
# usage: bash -v testing.sh

chmod +x testing.sh

mkdir data # create directory

# Define variables
seedURL=http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html
externalURL=www.google.com

echo "Beginning test..."

#####################################
### These tests should fail ###

## Test various arguments

# 1 argument
./crawler
if [ $? -eq 1 ]
then
	echo "Passed test w/ 1 argument"
else
	echo "Failed test w/ 1 argument"
fi

# 2 arguments
./crawler $seedURL
if [ $? -eq 1 ]
then
	echo "Passed test w/ 2 arguments"
else
	echo "Failed test w/ 2 arguments"
fi

# 3 arguments
./crawler $seedURL data
if [ $? -eq 1 ]
then
	echo "Passed test w/ 3 arguments"
else
	echo "Failed test w/ 3 arguments"
fi

# 4 arguments + externalURL
./crawler $externalURL data 2
if [ $? -eq 1 ]
then
	echo "Passed test w/ external URL"
else
	echo "Failed test w/ external URL"
fi

4 arguments + non-existent server
./crawler http://example.com/error.php data 2
if [ $? -eq 1 ]
then
	echo "Passed test w/ non-existent server"
else
	echo "Failed test w/ non-existent server"
fi

# 4 arguments + valid server, non-existent page
./crawler http://www.abcfake.com/ data 2 # URL from Marlee Montella
if [ $? -eq 1 ]
then
	echo "Passed test w/ valid server, non-existent page"
else
	echo "Failed test w/ valid server, non-existent page"
fi

# 4 arguments + negative page depth
./crawler $seedURL data -10
if [ $? -eq 1 ]
then
	echo "Passed test w/ negative page depth"
else
	echo "Failed test w/ negative page depth"
fi

######################################
### These tests should pass ####

## Crawl closed set of cross-linked web pages, should not produce duplicate files

# at depth 0
./crawler $seedURL data 0
if [ $? -eq 0 ]
then
    if [ -f data/1 ]
    then
        echo "Passed test at depth = 0"
    else
        echo "Failed test at depth = 0"
	fi
else
	echo "Failed test at depth = 0"
fi

# at depth 1
./crawler $seedURL data 1
if [ $? -eq 0 ]
then
    if [ -f data/2 ]
    then
        echo "Passed test at depth = 1"
    else
        echo "Failed test at depth = 1"
	fi
else
	echo "Failed test at depth = 1"
fi

# at depth 2
./crawler $seedURL data 2
if [ $? -eq 0 ]
then
    if [ -f data/3 ]
    then
        echo "Passed test at depth = 2"
    else
        echo "Failed test at depth = 2"
	fi
else
	echo "Failed test at depth = 2"
fi

# at depth 3
./crawler $seedURL data 3
if [ $? -eq 0 ]
then
    if [ -f data/6 ]
    then
        echo "Passed test at depth = 3"
    else
        echo "Failed test at depth = 3"
	fi
else
	echo "Failed test at depth = 3"
fi

# at depth 4
./crawler $seedURL data 4 
if [ $? -eq 0 ]
then
    if [ -f data/8 ]
    then
        echo "Passed test at depth = 4"
    else
        echo "Failed test at depth = 4"
	fi
else
	echo "Failed test at depth = 4"
fi

# at depth 5
./crawler $seedURL data 5
if [ $? -eq 0 ]
then
    if [ -f data/9 ]
    then
        echo "Passed test at depth = 5"
    else
        echo "Failed test at depth = 5"
	fi
else
	echo "Failed test at depth = 5"
fi

## Repeat prev test with a different seed page in the same site
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/D.html data 6
if [ $? -eq 0 ]
then
	if ! [ -f data/10 ]
	then
		echo "Passed test w/ closed set of cross-linked pages, different seed page"
	else
		echo "Failed test w/ closed set of cross-linked pages, different seed page"
	fi
else
    echo "Failed test w/ closed set of cross-linked pages, different seed page"
fi

## Crawl Wikipedia playground

mkdir wikidata

# at depth 0
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ wikidata 0
if [ $? -eq 0 ]
then
    if [ -f wikidata/1 ]
    then
        echo "Passed wiki test at depth = 0"
    else
        echo "Failed wiki test at depth = 0"
	fi
else
	echo "Failed wiki test at depth = 0"
fi

# at depth 1
./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia/ wikidata 1
if [ $? -eq 0 ]
then
    if [ -f wikidata/7 ]
    then
        echo "Passed wiki test at depth = 1"
    else
        echo "Failed wiki test at depth = 1"
	fi
else
	echo "Failed wiki test at depth = 1"
fi

echo "Done."