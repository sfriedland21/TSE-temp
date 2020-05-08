# Sydney Friedland
## CS50 Spring 2020, Lab 4 Testing

### Testing
Crawler can be tested by running `testing.sh` (integration testing) from the command line once `crawler` has been assembled. `testing.sh` tests the crawler's response to invalid parameters, an incorrect number of parameters,
different depths, and different seed URLs. When testing whether crawler has crawled successfully, `testing.sh` checks if the correct number of files have been created in the given `pageDirectory`. 

`crawler` also prints the following "progress" indicators as it runs:
  1. Exploring URL: `URL`
  2. Found seen URL: `URL`
  3. Found external URL: `URL`

### Limitations
The user must manually look through the webpages to determine if they were explored correctly. The user may also run the example cases listed [here](http://old-www.cs.dartmouth.edu/~cs50/data/tse-output/) from the command line and compare the crawler output with those examples.