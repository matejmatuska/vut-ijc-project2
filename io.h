// io.h
// Řešení IJC-DU2, příklad 2), 15.4.2021
// Autor: Matej Matuška, FIT
// Přeloženo: gcc 10.2.1

#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>

/*
 * Reads one word from file to char array and returns 
 * the lenght of the word. If the word is longer than max,
 * max - 1 chars are read and remainder is skipped.
 * If end of file is encountered, EOF is returned.
 *
 * @note Word is a continuos sequence of characters 
 * separated by non-whitespace characters
 * isspace is used to determine if character is whitespace
 *
 * @param s Array of chars to read into
 * @param max Maximum of chars to read
 * @param f File to read from
 * @return The lenght of read word or EOF
 */
int read_word(char *s, int max, FILE *f);

#endif // _IO_H_
