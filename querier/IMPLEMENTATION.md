# Sydney Friedland
## CS50 Spring 2020, Lab 6 Querier Implementation

### Functions/modules

`querier` is structured as follows:

  1. *main* parses parameters and initializes an empty index.
  2. *read_query*, which reads queries from stdin, one line at a time, and parses individual words from the query
  3. *check_word*, which checks for bad characters
  4. *check_andor*, which checks for syntax errors involving operators 'and' 'or'
  5. *get_ctrskey*, which gives one counterset's item another counterset's key
  6. *get_ctrssize*, which determines how many key item pairs exist in a counterset
  7. *initialize_result*, which shifts information from countersets into an array of result_t structs
  8. *sort_result*, which sorts the the array of result_t structs into descending order by score
  9. *print_query*, which prints the query in a format defined by the specs
  10. *print_URL*, which acquires the document URL from the crawler produced directory and prints it to stdout
  11. *item_delete*, which frees items in the index hashtable

`querier` uses following helpfer functions from the `common` library:
  1. *indexbuild*, which builds the index from `crawler` produced documents.
  2. *normalize_word*, which converts a query to lowercase
  3. *isCrawlerDirectory*, which determines if pageDirectory was produced by `crawler`.

### Major data structures

 1. *hashtable* (as the index) 
 2. *set* (built into hashtable)
 3. *countersets* (of docID docID, docID score, and docID count pairs)
 4. *array* (of result_t structs containing docID score pairs; a count component keeps track of the number of structs in the array)

### Pseudo code for logic/algorithmic flow

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

### Limits

Index hashtable caps at 500.