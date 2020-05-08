# Sydney Friedland
## CS50 Spring 2020, Lab 4 Crawler Implementation
Sourced info from CS50 TSE Crawler [Design Spec](https://www.cs.dartmouth.edu/~cs50/Labs/Lab4/DESIGN.html)

### Functions/modules

`crawler` is structured as follows:

  1. *main* parses parameters and passes them to the crawler.
  2. *crawler* uses a bag to track pages to explore, and a hashtable to track pages seen; when it explores a page it gives the page URL to the pagefetcher, then the result to pagesaver, then to the pagescanner.

Crawler uses following helpfer functions from the `common` library:
  1. *pagefetcher*, which fetches a page from a URL.
  2. *pagescanner*, which extracts URLs from a page and processes each one
  3. *pagesaver*, which outputs a page to the the appropriate file

### Major data structures

 1. *bag* of pages the crawler has yet to explore (URL, depth) structures
 2. *set* of URLs (indirectly used by hashtable)
 4. *hashtable* of URLs that have been seen so far (because the hashtable disallows NULL items, it stores URLs as keys and a constant string, " ", as items)

### Pseudo code for logic/algorithmic flow

The crawler runs as follows:

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters, initialize other modules
3. make a *webpage* for the `seedURL`, marked with depth=0
4. add that page to the *bag* of webpages to crawl
5. add that URL to the *hashtable* of URLs seen
3. while there are more webpages to crawl,
	5. extract a webpage (URL,depth) item from the *bag* of webpages to be crawled,
	4. pause for at least one second,
	6. use *pagefetcher* to retrieve a webpage for that URL,
	5. use *pagesaver* to write the webpage to the `pageDirectory` with a unique document ID, as described in the Requirements.
	6. if the webpage depth is < `maxDepth`, explore the webpage to find links:
		7. use *pagescanner* to parse the webpage to extract all its embedded URLs;
		7. for each extracted URL,
			8. 'normalize' the URL (see below)
			9. if that URL is not 'internal' (see below), ignore it;
			9. try to insert that URL into the *hashtable* of URLs seen
				10. if it was already in the table, do nothing;
				11. if it was added to the table,
					12. make a new *webpage* for that URL, at depth+1
					13. add the new webpage to the *bag* of webpages to be crawled

**normalize the URL** means to convert it into a clean, canonical form.

**internal** means the URL stays within the CS50 playground http://old-www.cs.dartmouth.edu/.

### Limits

Maximum allowable depth = 20. If the user enters a value over 20, max_depth will be set to 20.

Hashtable of URLs caps at 200.