# Sydney Friedland
## CS50 Spring 2020, Lab 4, `indexer`
Sourced info from CS50 TSE Indexer [Requirements Spec](https://www.cs.dartmouth.edu/~cs50/Labs/Lab5/REQUIREMENTS.html)

### indexer

The TSE *indexer* is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, *indextest*, loads an index file produced by the indexer and saves it to another file.

The *indexer* also prints "progress" indicators as it runs, indicating whether it is building or saving (or in the case of *indextest*, loading) the index. `indexer` leverages modules from `libcs50-given.a`.

The indexer **shall**:

1. execute from a command line with usage syntax
  * `./indexer pageDirectory indexFilename`
  * where `pageDirectory` is the pathname of a directory produced by the Crawler, and
  * where `indexFilename` is the pathname of a file into which the index should be written; the indexer creates the file (if needed) and overwrites the file (if it already exists).
  * Note: the indexer should be able to handle cases in which the index file is not a valid pathname and/or the crawler directory is not a valid.
2. read documents from the `pageDirectory`, each of which has a unique document ID, wherein
   * the document `id` starts at 1 and increments by 1 for each new page,
   * and the filename is of form `pageDirectory/id`,
   * and the first line of the file is the URL,
   * and the second line of the file is the depth,
   * and the rest of the file is the page content (the HTML, unchanged).
3. build an inverted-index data structure mapping from *words* to *(documentID, count) pairs*, wherein each *count* represents the number of occurrences of the given word in the given document.
Ignore words with fewer than three characters, and "normalize" the word before indexing. Here, "normalize" means to convert all letters to lower-case.
4. create a file `indexFilename` and write the index to that file, in the format described below.

See [IMPLEMENTATION](../blob/master/indexer/IMPLEMENTATION.md) for details regarding `indextest`.

### Usage

The indexer's only interface with the user is on the command-line; it must always receive two arguments.

```
./indexer pageDirectory indexFilename
```

For example:

``` bash
$ ./indexer ../crawler/data indexfile1
```

### Compilation (of index and indextest)

To compile `indexer` and `indextest`, simply `make` or `make all`.

To compile only `indexer`, simply `make indexer`.

To compile only `indextest`, simply `make indextest`.

To test, simply `make test` or `make test &> testing.out`.

To clean up directory, simply `make clean`.

Details of test run in [TESTING](../blob/master/indexer/TESTING.md).

Details of implementation choices in [IMPLEMENTATION](../blob/master/indexer/IMPLEMENTATION.md).