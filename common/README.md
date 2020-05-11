# Sydney Friedland
## CS50 Spring 2020, Lab 4, Common

### common directory

The `common` directory contains code that will eventually be shared by the crawler, indexer, and querier. As of now, it comprises code for initializing the “pageDirectory” and saving webpages there. The code in `common` can be compiled to build the `common.a` library. Modules in the `common` directory leverage modules from `libcs50-given.a`.

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
normalizeword
```

#### index

*index* is defined in `index.h` and implemented in `index.c`. The following functions are exported through `index.h`:

```c
build save load
```

### Compilation

To build the library, simply `make` (will produce `common.a`).

To clean up directory, simply `make clean`.