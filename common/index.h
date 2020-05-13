/* 
 * index.h - header file for 'index' module
 *
 * 'index' contains helper functions for 'indexer'
 * 
 * Sydney Friedland, May 2020
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include "hashtable.h"

/**************** index_build ****************/
/* Builds an inverted-index data structure mapping from words to (docID, count)
 * pairs, wherein each count represents the number of occurrences of the given
 * word in the given document. The function receives an empty index hashtable
 * as a parameter, then populates and returns a the hashtable. Words with
 * fewer than three characters are ignored and are "normalized" before they
 * are indexed. Here, "normalized" means all letters are converted to lower-case. 
 */ 
hashtable_t* index_build(hashtable_t *ht, char *dir);

/**************** index_save ****************/
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

/**************** index_load ****************/
/* Loads the index from the user provided oldIndexFilename
 * into an inverted-index data structure and saves that 
 * structure in newIndexFilename. The function receives
 * a hashtable_t type as a parameter then returns the 
 * populated hashtable.
 */ 
hashtable_t* index_load(hashtable_t *ht, FILE *fp);

#endif // __INDEX_H