/* 
 * pagedir.c - CS50 'pagedir' module
 *
 * see pagedir.h for more information.
 *
 * Sydney Friedland, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pagedir.h"
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

/**************** functions ****************/

/**************** pagefetcher ****************/
bool pagefetcher(webpage_t *page)
{
    char *url = webpage_getURL(page); // get URL from page
    if (!IsInternalURL(url)) {
        fprintf (stderr, "URL is not internal\n");
        return false;
    }
    else if (!webpage_fetch(page)) {
        fprintf(stderr, "could not fetch webpage\n");
        return false;
    }
    return true;
}

/**************** pagesaver ****************/
void pagesaver(int file_num, char *directory, webpage_t *page)
{
    char filepath[300];
    sprintf(filepath, "%s/%d", directory, file_num); // create path name
    FILE *fp = fopen(filepath, "w");
    
    if (fp != NULL) {
        fprintf(fp, "%s\n", webpage_getURL(page)); // print URL to file
        fprintf(fp, "%d\n", webpage_getDepth(page)); // print depth to file
        fprintf(fp, webpage_getHTML(page)); // print html to new file
        fclose(fp);
    }
    else fprintf(stderr, "NULL filepointer\n");
}

/**************** pagescanner ****************/
void pagescanner(webpage_t *page, hashtable_t *ht, bag_t *bag)
{
    int pos = 0;
    char *result;

    // parse the webpage to extract all its embedded URLs
    while ((result = webpage_getNextURL(page, &pos)) != NULL) {
        if (NormalizeURL(result)) {
            if (IsInternalURL(result)) { // check again if normalized url is internal
                // try to insert URL into the hashtable of URLs seen
                if (hashtable_insert(ht, result, " ")) {
                    // make a new webpage for URL, at depth+1
                    webpage_t *new = webpage_new(result, webpage_getDepth(page) + 1, NULL);
                    if (new != NULL) {
                        // add the new webpage to the bag of webpages to be crawled
                        bag_insert(bag, new);
                        printf("Found new URL: %s\n", result); // progress indicator
                    }
                }
                else {
                    printf("Found seen URL: %s\n", result); // progress indicator
                    free(result);
                }
            }
            else {
                printf("Found external URL: %s\n", result); // progress indicator
                free(result);
            }
        }
        else free(result);
    }
}

/************** isCrawlerDirectory **************/
bool isCrawlerDirectory(char *dir) {
    int length = strlen(dir);
    char path[length+10]; // create string with space for dir and /.crawler
    sprintf(path, "%s/%s", dir, "/.crawler"); // create path name
    FILE *fp = fopen(path, "r"); // attempt to open file for reading

    if (fp != NULL) {
        fclose(fp); // close only if opened successfully
        return true;
    }
    else {
        fprintf(stderr, "could not verify if dir is a Crawler-produced directory\n");
        return false;
    }
}