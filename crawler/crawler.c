/* 
 * crawler.c - CS50
 *
 * see README.md for more information.
 *
 * Sydney Friedland, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

//function prototypes
void crawler();
void item_delete();

int main(int argc, char *argv[]) {
    const int NUMSLOTS = 200;
    int max_depth;
    
    // validate parameters
    if (argc != 4) {
        fprintf (stderr, "incorrect number of parameters\n"); // check number of params
        return 1;
    }
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) { // check if params != NULL
        fprintf (stderr, "NULL parameters\n");
        return 1;
    }
    if (sscanf(argv[3], "%d", &max_depth) != 1) { // check if third arg is valid int
        fprintf (stderr, "maxDepth must be an integer\n");
        return 1;
    }
    if (max_depth < 0) { // check if maxDepth is a pos int
        fprintf (stderr, "maxDepth must be a positive integer\n");
        return 1;
    }

    if (max_depth > 20) max_depth = 20; // set max allowable value for max_depth

    char *page_dir = argv[2]; // check if directory exists and is writable
    char testfile[300];
    sprintf (testfile, "%s/.crawler", page_dir); // create path
    FILE *fp = fopen(testfile, "w"); // open a test file
    if (fp == NULL) { 
        fprintf (stderr, "directory does not exist or is not writable\n");
        return 1;
    }
    fclose(fp); // close test file if directory passed the check

    char *seed_URL = (char *)malloc((strlen(argv[1]) + 1)*sizeof(char)); // allocate memory for seed URL
    if (seed_URL == NULL) {
        fprintf (stderr, "could not allocate memory for seed_URL\n");
        return 1;
    }
    seed_URL = (char *)strcpy(seed_URL, argv[1]); // get seed URL if memory was allocated
    if (!IsInternalURL(seed_URL)) { // check if internal
        fprintf (stderr, "URL is not internal\n");
        return 1;
    }

    webpage_t *seedpage = webpage_new(seed_URL, 0, NULL); // make a webpage for the seedURL, marked with depth = 0
    if (seedpage == NULL) {
        fprintf (stderr, "could not allocate memory for webpage_t\n");
        return 1;
    }

    bag_t *tocrawl = bag_new(); // create bag to hold webpages
    if (tocrawl == NULL) {
        fprintf (stderr, "bag_new failed\n");
        return 1;
    }
    bag_insert(tocrawl, seedpage); // add page for seedURL to the bag of webpages to crawl

    hashtable_t *seen = hashtable_new(NUMSLOTS); // create hashtable to hold seen URLs
    if (seen == NULL) {
        fprintf (stderr, "hashtable_new failed\n");
        return 1;
    }
    hashtable_insert(seen, webpage_getURL(seedpage), " "); // add seedURL to the hashtable of URLs seen

    crawler(seen, tocrawl, page_dir, max_depth); // crawl webpages

    bag_delete(tocrawl, *webpage_delete); // clean up
    hashtable_delete(seen, *item_delete);

    return 0;
}

/**************** crawler ****************/
/* Crawl webpages. Errors and additional progress
 * indicators are reported from pagedir */
void crawler(hashtable_t *ht, bag_t *bag, char* dir, int depth) {
    webpage_t *page; // get first page
    int file_num = 1; // keep track of file number, increment later

    while ((page = bag_extract(bag)) != NULL) { // while there are more webpages to crawl 
        if (pagefetcher(page)) { // retrieve a webpage for page URL, pause for at least one second between fetches
            // write the webpage to the pageDirectory with a unique document ID
            printf ("Exploring URL: %s\n", webpage_getURL(page)); // progress indicator
            pagesaver(file_num, dir, page);
            file_num++;
        }
        // if the webpage depth is < maxDepth, explore the webpage to find links
        if (webpage_getDepth(page) < depth) {
            pagescanner(page, ht, bag); 
        }
        webpage_delete(page);
    }
}

/**************** item_delete ****************/
/* Deletes each item in hashtable */
void item_delete(void *item)
{
    // nothing to delete since memory was not dynamically allocated for items
}