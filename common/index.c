/* 
 * index.c - CS50 'index' module
 *
 * see index.h for more information.
 *
 * Sydney Friedland, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "webpage.h"
#include "index.h"
#include "hashtable.h"
#include "counters.h"

/**************** functions ****************/

/*  build an inverted-index data structure mapping from words to (documentID, count) 
    pairs, wherein each count represents the number of occurrences of the given word in 
    the given document. Ignore words with fewer than three characters, and “normalize”
    the word before indexing. Here, “normalize” means to convert all letters to lower-case */

/**************** index_build ****************/
hashtable_t* index_build(hashtable_t* ht, char* dir) {

    int dirlen = strlen(dir);
    int docID = 1; // first file    
    char ifile[dirlen + 30]; // assume docID will be no more than 29 digits...
    sprintf(ifile, "%s/%d", dir, docID); // create path
    FILE* fp = fopen(ifile, "r");

    int URLcount, HTMLcount, c, linenum;
    URLcount = 0;
    HTMLcount = 0;
    linenum = 0;
    while (fp != NULL) { // while there are still files to read in the directory
        
        /* while ((c = fgetc(fp)) != EOF) { // allocate the necessary amount of memory
            if (c == '\n') linenum++;
            else if (linenum == 0) URLcount++;
            else if (linenum >= 2) HTMLcount++;
        }
        fseek(fp, 0, SEEK_SET); // rewind to beginning of file */

        char *url = freadlinep(fp);
        printf("URL: %s\n", url);
        int depth;
        fscanf(fp, "%d\n", &depth);
        printf("depth: %d\n", depth);
        char *html = freadfilep(fp);
        printf("html: %s\n", html);

        webpage_t *page = webpage_new(url, depth, html);
        int pos = 0;
        char *result;

        while ((result = webpage_getNextWord(page, &pos)) != NULL) {
            if (strlen(result) >= 3) {
                printf("Found word: %s\n", result);
                //result = normalizeWord(result);
            }
            free(result);
            
            // Initialize a new counter and call counters_add with docID as key
            // insert into hashtable with the word as the key and the counter as the item
            // Free memory
            // If found, the counter will be returned and you can call counters_add 
            // (whether or not this doc id has already been called) and the count will either
            // be saved as one or increment. 

            // Free webpage memory with delete_webpage
        }

        webpage_delete(page);
        fclose(fp);
        docID++;
        sprintf(ifile, "%s/%d", dir, docID); // create new path
        fp = fopen(ifile, "r"); // open next document in the directory
    }
    
    // if fp was NULL do nothing or print an error message
    return(ht);
    
}

    /* build an inverted-index data structure mapping from words to (documentID, count) 
    pairs, wherein each count represents the number of occurrences of the given word in 
    the given document. Ignore words with fewer than three characters, and “normalize”
    the word before indexing. Here, “normalize” means to convert all letters to lower-case */








/* create a file indexFilename and write the index to that file
 * 
 * The indexer writes the inverted index to a file, and both the index tester and 
 * the querier read the inverted index from a file; the file shall be in the following format.

one line per word, one word per line
each line provides the word and one or more (docID, count) pairs, in the format
word docID count [docID count]…
where word is a string of lower-case letters,
where docID is a positive non-zero integer,
where count is a positive non-zero integer,
where the word and integers are separated by spaces.

Within the file, the lines may be in any order.
Within a line, the docIDs may be in any order. */
/**************** index_save ****************/
// void probably


/**************** index_load ****************/
// hashtable?