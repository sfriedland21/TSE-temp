/* 
 * word.h - header file for 'word' module
 *
 * 'word' contains helper function for 'indexer' and 'querier'
 * 
 * Sydney Friedland, May 2020
 */

#ifndef __WORD_H
#define __WORD_H

#include <stdio.h>

/**************** normalize_word ****************/
/* Converts all letters in a string to lowercase */
char* normalize_word(char* word);

#endif // __WORD_H