
// integer overflow lead to dead loop
short len = 0;
... ...
while(len< MAX_LEN) {  // in case len is negative number
    len += readFromInput(fd, buf);
    buf += len;
}

// interger overflow lead to leak
int copy_something(char *buf, int len)  // if len is negative number
{
    #define MAX_LEN 256
    char mybuf[MAX_LEN];
    
    if(len > MAX_LEN){ // <-- will pass in this condition
         return -1;
    }
 
    return memcpy(mybuf, buf, len); // <- convert to unsigned int
}

// unsigned integer convert to signed integer
nresp = packet_get_int();
if (nresp > 0) {  // nresp is 0xffffffff/4 + 1
    response = xmalloc(nresp*sizeof(char*)); // integer overflow, xmalloc(4)
    for (i = 0; i < nresp; i++) // however, there will be 1073741825 loops
        response[i] = packet_get_string(NULL);
}

// unsecurity length 
int func(char *buf1, unsigned int len1,
         char *buf2, unsigned int len2 )
{
   char mybuf[256]; 
 
   if((len1 + len2) > 256){    //<--- bad here
       return -1;
   } 
 
   memcpy(mybuf, buf1, len1);
   memcpy(mybuf + len1, buf2, len2); 
 
   do_some_stuff(mybuf); 
 
   return 0;
}

// the good example...
void foo(int m, int n)
{
    size_t s = m + n;
    if ( m>0 && n>0 && (SIZE_MAX - m < n) ){
        //error handling...
    }
    
}
