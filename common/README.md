# Sydney Friedland
## CS50 Spring 2020, Lab 4, Common

### common directory

The `common` directory contains code that will eventually be shared by the crawler, indexer, and querier. The code in `common` can be compiled to build the `common.a` library. Modules in the `common` directory leverage modules from `libcs50-given.a`.

#### pagedir

*pagedir* is defined in `pagedir.h` and implemented in `pagedir.c`. The following functions are exported through `pagedir.h`:

```c
/* Fetches the contents (HTML) for a page from a URL
 * if page contents fetched successfully, return true.
 * If any error, return false. */
bool pagefetcher(webpage_t *page);

/* Outputs a page to the appropriate file.
 * Assumes file path is no longer than 300 characters. */
void pagesaver(int file_num, char *directory, webpage_t *page);

/* Extracts URLs from a page and returns one at a time */
void pagescanner(webpage_t *page, hashtable_t *ht, bag_t *bag);

/* Verifies whether dir is indeed a Crawler-produced directory
 * If isCrawlerDirectory can open a file dir/.crawler for
 * reading, then dir is a Crawler-produced directory and the
 * function will return true; if not, return false. */ 
bool isCrawlerDirectory(char *dir);
```

#### word

*word* is defined in `word.h` and implemented in `word.c`. The following functions are exported through `word.h`:

```c
/* Converts all letters in a string to lowercase */
char* normalize_word(char* word);
```

#### index

*index* is defined in `index.h` and implemented in `index.c`. The following functions are exported through `index.h`:

```c
/* Builds an inverted-index data structure mapping from words to (docID, count)
 * pairs, wherein each count represents the number of occurrences of the given
 * word in the given document. The function receives an empty index hashtable
 * as a parameter, then populates and returns a the hashtable. Words with
 * fewer than three characters are ignored and are "normalized" before they
 * are indexed. Here, "normalized" means all letters are converted to lower-case. 
 */ 
hashtable_t* index_build(hashtable_t *ht, char *dir);

/* Creates a file using the user provided indexFilename 
 * and writes the index to that file in the following format:
 * 
 * one line per word, one word per line
 * each line provides the word and one or more (docID, count) pairs, in the format:
 *      word docID count [docID count]…
 * where word is a string of lower-case letters,
 * where docID is a positive non-zero integer,
 * where count is a positive non-zero integer,
 * where the word and integers are separated by spaces.
 * 
 * Within the file, the lines may be in any order.
 * Within a line, the docIDs may be in any order. 
 */
void index_save(hashtable_t *ht, char *filename);

/* Loads the index from the user provided oldIndexFilename
 * into an inverted-index data structure and saves that 
 * structure in newIndexFilename. The function receives
 * a hashtable_t type as a parameter then returns the 
 * populated hashtable.
 */
hashtable_t* index_load(hashtable_t *ht, FILE *fp); 
```

### Compilation

To build the library, simply `make` (will produce `common.a`).

To clean up directory, simply `make clean`.