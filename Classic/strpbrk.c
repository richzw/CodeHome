#include <string.h> /* strchr */
char *strpbrk(const char *s1, const char *s2)
{
    while(*s1)
        if(strchr(s2, *s1++))
            return (char*)--s1;
    return 0;
}


// ignore NULL
char* strpbrk(const char* s1, const char* s2)
{
    if (*s1 == 0)
        return NULL;
    
    while (*s1) {
        for (char* tmp = s2; *tmp != 0; ++tmp) {
            if (*tmp == *s1)
                return s1;
        }
        ++s1;
    }
    
    return NULL;
}
