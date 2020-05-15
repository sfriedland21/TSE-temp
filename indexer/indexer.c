/* 
 * indexer.c - CS50
 *
 * see README.md for more information.
 *
 * Sydney Friedland, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "pagedir.h"
#include "word.h"
#include "hashtable.h"
#include "counters.h"

//function prototypes
void item_delete();

int main(int argc, char* argv[]) {

    // validate parameters
    if (argc != 3) {
        fprintf (stderr, "incorrect number of parameters\n"); // check number of params
        return 1;
    }
    
    // check if pageDirectory is the pathname for an existing directory produced by the crawler
    if (!isCrawlerDirectory(argv[1])) return 1; // check if error printed from pagedir

    // check if indexFilename is the pathname of a writeable file
    FILE *fp = fopen(argv[2], "w"); // attempt to open file for writing
    if (fp == NULL) {
        fprintf (stderr, "indexFilename could not be opened for writing\n");
        return 1;
    }
    else fclose(fp);

    const int NUMSLOTS = 500;
    hashtable_t* index = hashtable_new(NUMSLOTS);
    if (index == NULL) {
        fprintf(stderr, "hashtable_new failed\n");
        return 1;
    }

    printf("Building index...\n");
    index = index_build(index, argv[1]); // build the index

    printf("Saving index...\n");
    index_save(index, argv[2]); // save the index

    hashtable_delete(index, item_delete); // clean up
    printf("Done.\n");

    return 0;
}

/**************** item_delete ****************/
/* Frees item memory in hashtable, in this case,
 * a counterset.
 */
void item_delete(void *item)
{
    if (item != NULL) {
        counters_delete(item); // delete the counterset
        item = NULL;
    }
}