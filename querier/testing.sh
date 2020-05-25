#!/bin/bash
# Testing script for querier.c
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
pageDir="../data/letters"
indexFile="../data/index_letters"

echo "Beginning test..."

#####################################
### These tests should fail ###

## Test various arguments for querier

# 1 argument
./querier
if [ $? -eq 1 ]
then
	echo "Querier passed test w/ 1 argument"
else
	echo "Querier failed test w/ 1 argument"
fi

# 2 arguments
./querier $pageDir
if [ $? -eq 1 ]
then
	echo "Querier passed test w/ 2 arguments"
else
	echo "Querier failed test w/ 2 arguments"
fi

# 4 arguments
./querier $pageDir $indexFile extraarg
if [ $? -eq 1 ]
then
	echo "Querier passed test w/ 4 arguments"
else
	echo "Querier failed test w/ 4 arguments"
fi

# invalid pageDir
./querier ../fake/randompagedir $indexFile
if [ $? -eq 1 ]
then
	echo "Querier passed test w/ invalid pageDirectory"
else
	echo "Querier failed test w/ invalid pageDirectory"
fi

# invalid indexFilename
./querier $pageDir index/File
if [ $? -eq 1 ]
then
	echo "Querier passed test w/ invalid indexFilename"
else
	echo "Querier failed test w/ invalid indexFilename"
fi

######################################
### These tests should pass ###

# pipe in queries with syntax errors, querier should run but print errors
cat testsyntax.txt | ./querier $pageDir $indexFile
if [ $? -eq 0 ]
then
	echo "Successfully ran querier"
else
	echo "Failed to run querier"
fi

# fuzz test, 50 random queries
./fuzzquery $indexFile 50 0 | ./querier $pageDir $indexFile
if [ $? -eq 0 ]
then
	echo "Successfully ran querier"
else
	echo "Failed to run querier"
fi

echo "Testing complete."