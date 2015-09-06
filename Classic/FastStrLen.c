/**********************************************************
 * A usual implementation of strlen function scans the string byte-by-byte looking for terminating zero. For example:
*************************/

size_t strlen(const char *s) {
    const char *start = s;
    while(*s)
        s++;
    return s - start;
}

// It's small and easy, but not very fast. That is how we can improve it:

size_t my_strlen(const char *s) {
    size_t len = 0;
    for(;;) {
        unsigned x = *(unsigned*)s;
        if((x & 0xFF) == 0) return len;
        if((x & 0xFF00) == 0) return len + 1;
        if((x & 0xFF0000) == 0) return len + 2;
        if((x & 0xFF000000) == 0) return len + 3;
        s += 4, len += 4;
    }
}

/******************************************************************************
Four bytes are examined at once. The program reads a double word from memory, extracts each of its bytes by ANDing with a mask,
and compares the bytes with zero. That is what Agner Fog calls "vector operations in general purpose registers".
***********/
/*
 * Warning: this function will crash if an non-readable memory page is located right after the end of the string. 
 * The simplest way to prevent this is to allocate 3 additional bytes at the end of string.
*/

