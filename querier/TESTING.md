# Sydney Friedland
## CS50 Spring 2020, Lab 6 Testing

### Testing
Querier can be testing by running `testing.sh` from the command line or `make test` within the querier directory once the following set-up has been achieved. 

``` bash
$ cd tse
$ mkdir data/letters/
$ crawler/crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html data/letters 3
$ indexer/indexer data/letters data/index_letters
$ cd querier
$ make test
```

If the test script is run using these options, the test results will be printed to stdout. `testing.sh` first tests the queriers's response to invalid parameters and queries containing syntax errors (from the file `testsyntax.txt`) then runs a fuzz test to see how querier will react to a number of random cases.

`querier` prints the following "progress" indicators at the beginning and end of its run:
  1. Loading index...
  2. Done.