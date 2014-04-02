// which line does the core dump happened??

struct str{
	int len;
	char s[0];
};

struct foo{
	struct str *a;
};

int _tmain(int argc, _TCHAR* argv[])
{
	struct foo myf = {0};

	if (myf.a->s){
		printf(myf.a->s);  // in here
	}
	
}

/////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
 
struct line {
   int length;
   char contents[0]; // C99的玩法是：char contents[]; 没有指定数组长度
};
 
int main(){
    int this_length=10;
    struct line *thisline = (struct line *)
                     malloc (sizeof (struct line) + this_length);
    thisline->length = this_length;
    memset(thisline->contents, 'a', this_length);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
//在一台主流配置的PC机上，调用f(35)所需要的时间大概是——
  
int f(int x)
{
  
int s = 0;
  
while(x-->0) s+=f(x);
  
return max(s, 1);
  
}
  
//A、几毫秒 B、几秒   C、几分钟 D、几小时 
