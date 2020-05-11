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

/* Converts all letters in a word to lowercase */
char* normalize_word();

#endif // __WORD_H