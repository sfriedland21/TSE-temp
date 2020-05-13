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

/**************** pagefetcher ****************/
/* Fetches the contents (HTML) for a page from a URL.
 * if page contents fetched successfully, return true.
 * If any error, return false. 
 */
bool pagefetcher(webpage_t *page);

/**************** pagesaver ****************/
/* Outputs a page to the appropriate file.
 * Assumes file path is no longer than 300 characters. 
 */
void pagesaver(int file_num, char *directory, webpage_t *page);

/**************** pagescanner ****************/
/* Extracts URLs from a page and returns one at a time
 */
void pagescanner(webpage_t *page, hashtable_t *ht, bag_t *bag);

/************** isCrawlerDirectory **************/
/* Verifies whether dir is indeed a Crawler-produced directory
 * If isCrawlerDirectory can open a file dir/.crawler for
 * reading, then dir is a Crawler-produced directory and the
 * function will return true; if not, return false. 
 */ 
bool isCrawlerDirectory(char *dir);

#endif // __PAGEDIR_H