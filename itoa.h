#ifndef __ITOA_H__
#define __ITOA_H__
/*
 * @func: convert int to string, only support decimal.
 * @params: val {int}, the value should be converted.
 *          buf {string}, the result string after converted
 * @ret: {int}, the length of result string
 */
int itoa(int val, char* buf){
  	const unsigned char radix = 10;
	char* p = buf;
	unsigned int a;
	int len;
	char* begin;
	char tmp;
	unsigned int u;

	if (val < 0){  // handling the negative.
		*p++ = '-';
		val = 0 - val;
	}
	u = (unsigned int)val;
	begin = p;

	do{
		a = u%radix;
		u /= radix;
		*p++ = a + '0';
	}while(u > 0);

	len = (int)p - buf;
	*p-- = 0;

	do{
		tmp = *p;
		*p = *begin;
		*begin = tmp;
		--p;
		++begin;
	}while(begin < p);
}
#endif
