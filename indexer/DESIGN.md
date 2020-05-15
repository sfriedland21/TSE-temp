# Sydney Friedland
## CS50 Spring 2020, Lab 5 Indexer Design

### User interface 

The indexer's only interface with the user is on the command-line; it must always receive two arguments.

```
./indexer pageDirectory indexFilename
```

For example:

``` bash
$ ./indexer ../crawler/data indexfile1
```

The index tester’s only interface with the user is also on the command-line; it must always receive two arguments.

./indextest oldIndexFilename newIndexFilename

For example:

``` bash
$ ./indextest indexfile1 indexfile2
```

### Inputs and outputs
Input: the only inputs for indexer and indextest are command-line parameters; see the User Interface above.

Output (indexer): after reading the documents produced by the TSE crawler and building an index, indexer writes that index to a file. We use the indexFilename command line argument as the file name. Within a file, we write:
 * one line per word, one word per line
 * each line provides the word and one or more (docID, count) pairs, in the format
    * word docID count [docID count]...
 
Output (indextest): after loading an index file produced by the indexer into an index data structure, indextest saves that index to another file. We use the newIndexFilename command line argument as the file name. Files are written in the same format as files produced by indexer.
 
### Functional decomposition into modules
For indexer we anticipate the following modules or functions:
   1. main, which parses arguments and initializes other modules
   2. index_build, which takes in each file and processes the words contained in the file
   3. normalize_word, which takes in a word changes all its letters to lowercase 
   4. index_save, which saves the inverted index to a file

And some helper modules that provide data structures:
   1. hashtable (as the index) 
   2. set (built into hashtable)
   3. counterset (of docID count pairs)

For indextest we anticipate the following modules or functions:
   1. main, which parses arguments and initializes other modules
   2. index_load, which loads file created by indexer into an index data structure
   3. index_save, which saves the the loaded index to another file

Indextest leverages the same helper modules (that provide data structures) as indexer.

### Pseudo code for logic/algorithmic flow
The indexer will run as follows:

1. Check and validate parameters
2. Create the index (initialize an empty hashtable)
3. Build the index
4. For each document in the crawler directory:
    5. Read the URL, depth, and HTML to create a new webpage struct
    6. For each word in the webpage:
        7. If it has three or more letters, normalize
        8. Check if that word has already been found
            9. If it is the first time coming across the word, add it to the hashtable with the corresponding docID and count = 1
            10. If the word already exists in the hashtable for that docID, increment its count
11. Save the index
12. For each word in the hashtable:
    13. Obtain each of its [docID count] pair and write to the them to `indexFilename`, one word per line, with the word at the beginning of the line followed by each of its [docID count] pairs

### Dataflow through modules

   1. main parses parameters and passes them to *indexbuild*.
   2. *indexbuild* takes each file and processes the words contained in the file. When *indexbuild* finds a word, it passes it to normalizeword, then stores the result in the hashtable and updates the corresponding counts. The entire hashtable, once populated, is then passed to *indexsave*.
   4. *indexsave* saves the inverted index to a file.

### Testing plan

Assemble the indexer and test it as a whole using testing.sh. In each case, examine the output indexFilename carefully to be sure that the file is in the following format:
 * one line per word, one word per line
 * each line provides the word and one or more (docID, count) pairs, in the format
    * word docID count [docID count]…
 * where word is a string of lower-case letters,
 * where docID is a positive non-zero integer,
 * where count is a positive non-zero integer,
 * where the word and integers are separated by spaces.

1. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly. These cases are commented in `testing.sh`.
2. Compare the index produced by `indexer` with the index loaded by `indextest`.

Note: the indexer assumes that:
 * pageDirectory has files named 1, 2, 3, ..., without gaps.
 * The content of files in pageDirectory follow the format as defined in the specs.