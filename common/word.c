/* 
 * word.c - CS50 'word' module
 *
 * see word.h for more information.
 *
 * Sydney Friedland, May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include <ctype.h>

/**************** functions ****************/

/**************** normalize_word ****************/
char* normalize_word(char* word)
{
    for(int i = 0; i < (strlen(word) + 1); i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}