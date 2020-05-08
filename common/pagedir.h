/* 
 * pagedir.h - header file for 'pagedir' module
 *
 * 'pagedir' contains helper functions for 'crawler'
 * 
 * Sydney Friedland, May 2020
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdbool.h>
#include "webpage.h"
#include "bag.h"
#include "hashtable.h"

/* Fetches the contents (HTML) for a page from a URL */
bool pagefetcher(webpage_t *page);

/* Outputs a page to the appropriate file.
 * Assumes file path is no longer than 300 characters. */
void pagesaver(int file_num, char *directory, webpage_t *page);

/* Extracts URLs from a page and returns one at a time */
void pagescanner(webpage_t *page, hashtable_t *ht, bag_t *bag);

#endif // __PAGEDIR_H