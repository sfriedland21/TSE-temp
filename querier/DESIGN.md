# Sydney Friedland
## CS50 Spring 2020, Lab 6 Querier Design

### User interface 

The querier must always receive two arguments.

```
./querier pageDirectory indexFilename
```

For example:

``` bash
$ ./querier ../crawler/data ../indexer/indexfile
```

The querier will then request queries from the user via stdin until EOF.

### Inputs and outputs
Input: the inputs for querier are command-line parameters and queries received from stdin; see the User Interface above. An acceptable query consists of alphabet characters only. 'and' 'or' cannot appear at the beginning or end of the query, and cannot be adjacent within the query. 

Output: if the querier receives a valid query, that is a query without synax errors, it prints:
 * `No documents match` if the word is not contained in the indexFile
 * Otherwise... 
    * `Query:` and the query in lowercase format
    * `Matches x document(s):`
    * `score   x doc   x: URL`
    * `-----------------------------------------------`
        * Where... 
            * `score` is the number of times words in the query appear in a document
            * `doc` is the document that contains those words
            * `URL` is the URL from which that document was created
 
### Functional decomposition into modules
For querier we anticipate the following modules or functions:
   1. main, which parses arguments and initializes other modules
   2. index_build, which takes in each file and processes the words contained in the file
   3. normalize_word, which takes in a word changes all its letters to lowercase 
   4. read_query, which reads queries from stdin, one line at a time, and parses individual words from the query
   5. check_word, which checks for bad characters
   6. check_andor, which checks for syntax errors involving operators 'and' 'or'
   7. get_ctrskey, which gives one counterset's item another counterset's key
   8. get_ctrssize, which determines how many key item pairs exist in a counterset
   9. initialize_result, which shifts information from countersets into an array of result_t structs
   10. sort_result, which sorts the the array of result_t structs into descending order by score
   11. print_query, which prints the query in a format defined by the specs
   12. print_URL, which acquires the document URL from the crawler produced directory and prints it to stdout
   13. item_delete, which frees items in the index hashtable

And some helper modules:
   1. hashtable (as the index) 
   2. set (built into hashtable)
   3. countersets (of docID docID, docID score, and docID count pairs)
   4. array of result_t structs (of docID score pairs, a count component keeps track of the number of structs in the array)

### Pseudo code for logic/algorithmic flow
The querier will run as follows:

1. Check and validate parameters
2. Create the index (initialize an empty hashtable)
3. Build the index
4. Request a query then repeat the following until EOF
5. For each query
    6. Normalize the query (convert to lowercase) and extract individual words
    7. Check for syntax errors, if no errors
    8. For each word in the query
        9. If the word exists in the index, create a new counterset to hold the docIDs corresponding to the documents in which the word appears 
        10. If the first time coming across a docID, set the score in a separate counterset to that docID's count
        12. If not first time coming across a docID, increment the docID's score to be the sum of it's current score and the count corresponding to the docID's count for the word under investigation
        13. Once all words in the query have been investigated, determine the size of the counterset containing docID score pairs 
        14. Insert into an array of result_t structs 
        15. Sort the array into descending order by score
        16. Print according to format in the specs

### Dataflow through modules

   1. main parses parameters and passes them to *read_query*.
   2. *read_query* then leverages the remaining helper functions to determine docID score pairs, sort them,
   and print them to stdout.

### Testing plan

Assemble the querier and test it as a whole using testing.sh. In each case, examine the output to be sure docID score pairs were determined correctly.

1. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly. These cases are commented in `testing.sh`.
2. Fuzz test the program with 50 random queries (accomplished by `testing.sh`).

Note: the querier assumes that:
 * pageDirectory has files named 1, 2, 3, ..., without gaps.
 * The content of files in pageDirectory follow the format as defined in the specs.
 * The content of the file named by `indexFilename` follows the [Index file format]({{site.labs}}/Lab5/REQUIREMENTS.html#index-file-format).
* Queries consist of words no longer than 50 characters.
* There are no more than 500 documents in the crawler directory.