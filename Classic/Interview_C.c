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
