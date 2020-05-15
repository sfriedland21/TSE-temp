/* 
 * indextest.c - CS50
 *
 * see README.md for more information.
 *
 * Sydney Friedland, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagedir.h"
#include "word.h"
#include "index.h"
#include "hashtable.h"
#include "counters.h"
#include "webpage.h"

//function prototypes
void item_delete();

int main(int argc, char* argv[]) {

    // validate parameters
    if (argc != 3) {
        fprintf (stderr, "incorrect number of parameters\n"); // check number of params
        return 1;
    }

    // check if oldIndexFilename is the pathname of a readable file
    FILE *ofp = fopen(argv[1], "r");
    if (ofp == NULL) {
        fprintf (stderr, "oldIndexFilename could not be opened for reading\n");
        return 1;
    }
    else { // load the inverted index
        const int NUMSLOTS = 500;
        hashtable_t* index = hashtable_new(NUMSLOTS); // create empty hashtable
        if (index == NULL) {
            fprintf(stderr, "hashtable_new failed\n");
            fclose(ofp);
            return 1;
        }

        printf("Loading index...\n");
        index = index_load(index, ofp); // load the index structure
        fclose(ofp);

        printf("Saving index...\n");
        index_save(index, argv[2]); // save the index structure
        
        hashtable_delete(index, item_delete); // clean up
        printf("Done.\n");
    }

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