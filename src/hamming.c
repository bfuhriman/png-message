#include "../hdr/hamming.h"

/* Checks the codeword for errors. Returns the index of a single-bit error if there is one, and -1 otherwise. */
int findErrors(int *codeword, int len) {
    int err = 0;
    for (int i = 1; i < len; i *= 2) {
        if (getParity(codeword, len, i) != 0) {
            err |= i;
        }
    }

    if (!err && getOverallParity(codeword,len)) {
        return 0;
    } else if (err && !getOverallParity(codeword, len)) {
        return -1;
    }
    return err;
}

/* Returns the parity for all bits covered by the parity bit at index. */
int getParity(int *arr, int len, int index) {
    int parity = 0;
    for (int i = 0; i < len; i++) {
        if (index & i) {
            parity ^= arr[i];
        }
    }
    return parity;
}

/* Returns the parity of the entire codeword. */
int getOverallParity(int *codeword, int len) {
    int parity = 0;
    for(int i = 0; i < len; i++) {
        parity ^= codeword[i];
    }
    return parity;
}

/* Calculates the minimum amount of redundancy required to encode d bits of data. */
int minRedundancy(int d) {
    int p = 0;
    while ((1 << p) < (d + p + 1)) {
	p++;
    }
    return p + 1;
}

/* Calculates the maximum amount of data bits that can be stored in a codeword of length n. */
int maxData(int n) {
    int p = 0;
    while ((1 << p) < (n + 1)) {
        p++;
    }
    return n - p - 1;
}
