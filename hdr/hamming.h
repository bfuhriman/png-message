#ifndef HAMMING_H
#define HAMMING_H

/* Checks the codeword for errors. Returns the index of a single-bit error if there is one, and 0 otherwise. */
int findErrors(int *codeword, int len);

/* Returns the parity for all bits covered by the parity bit at index. */
int getParity(int *arr, int len, int index);

/* Returns the parity of the entire codeword. */
int getOverallParity(int *codeword, int len);

/* Calculates the minimum amount of redundancy required to encode d bits of data. */
int minRedundancy(int d);

/* Calculates the maximum amount of data bits that can be stored in a codeword of length n. */
int maxData(int n);

#endif
