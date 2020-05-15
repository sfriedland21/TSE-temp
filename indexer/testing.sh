#!/bin/bash
# Testing script for indexer.c, indextest.c
# 
# Author: Sydney Friedland
# May, 2020
#
# Based on testing script by Temi Prioleau
# Feb 5, 2020
#
# usage: bash -v testing.sh

chmod +x testing.sh

# Define variables
pageDir="../crawler/data"
oldFile="indexfileold"
newFile="indexfilenew"

echo "Beginning test..."

#####################################
### These tests should fail ###

## Test various arguments for indexer

# 1 argument
./indexer
if [ $? -eq 1 ]
then
	echo "Indexer passed test w/ 1 argument"
else
	echo "Indexer failed test w/ 1 argument"
fi

# 2 arguments
./indexer $pageDir
if [ $? -eq 1 ]
then
	echo "Indexer passed test w/ 2 arguments"
else
	echo "Indexer failed test w/ 2 arguments"
fi

# 4 arguments
./indexer $pageDir indexFile extraarg
if [ $? -eq 1 ]
then
	echo "Indexer passed test w/ 4 arguments"
else
	echo "Indexer failed test w/ 4 arguments"
fi

# invalid pageDir
./indexer ../fake/randompagedir indexFile
if [ $? -eq 1 ]
then
	echo "Indexer passed test w/ invalid pageDirectory"
else
	echo "Indexer failed test w/ invalid pageDirectory"
fi

# invalid indexFilename
./indexer $pageDir index/File
if [ $? -eq 1 ]
then
	echo "Indexer passed test w/ invalid indexFilename"
else
	echo "Indexer failed test w/ invalid indexFilename"
fi

## Test various arguments for indextest

# 1 argument
./indextest
if [ $? -eq 1 ]
then
	echo "Indextest passed test w/ 1 argument"
else
	echo "Indextest failed test w/ 1 argument"
fi

# 2 arguments
./indextest $oldFile
if [ $? -eq 1 ]
then
	echo "Indextest passed test w/ 2 arguments"
else
	echo "Indextest failed test w/ 2 arguments"
fi

# 4 arguments
./indextest $oldFile $newFile extraarg
if [ $? -eq 1 ]
then
	echo "Indextest passed test w/ 4 arguments"
else
	echo "Indextest failed test w/ 4 arguments"
fi

# invalid oldIndexFilename
./indextest index/File $newFile
if [ $? -eq 1 ]
then
	echo "Indextest passed test w/ invalid oldIndexFilename"
else
	echo "Indextest failed test w/ invalid oldIndexFilename"
fi

# invalid newIndexFilename (will run but will not crash)
./indextest $oldFile index/File

######################################
### These tests should pass ###

## Assumes crawler has been run with pageDirectory data

# run indexer
./indexer $pageDir $oldFile
if [ $? -eq 0 ]
then
	echo "Successfully created index"
else
	echo "Failed to create index"
fi

# run indextest
./indextest $oldFile $newFile
if [ $? -eq 0 ]
then
	echo "Successfully created testindex"
else
	echo "Failed to create testindex"
fi

# sort both files
chmod +x indexsort.awk
gawk -f ./indexsort.awk $oldFile > oldindex.sorted
gawk -f ./indexsort.awk $newFile > newindex.sorted

# compare "old" and "new" index files produced by indexer and indextest
diff -q oldindex.sorted newindex.sorted
RET=$?
if [ $RET -eq 0 ]
then
    echo "no differences"
else
    echo "differences"
fi

echo "Done."