# Sydney Friedland
## CS50 Spring 2020, Lab 5 Testing

### Testing
Indexer can be tested by running `testing.sh` (integration testing) from the command line once `indexer` has been assembled or `make test`, all within the indexer directory. If the test script is run using these options, the test results will be printed to stdout. `testing.sh` tests the indexer's response to invalid parameters and an incorrect number of parameters, and compares the index created and saved by `indexer` to the index loaded and saved by `indextest` (these two indexes should consist of the same information, although that information may not be in the same order).

`indexer` prints the following "progress" indicators as it runs:
  1. Building index...
  2. Saving index...
  3. Done.

`index test` prints the following "progress" indicators as it runs:
  1. Loading index...
  2. Saving index...
  3. Done.