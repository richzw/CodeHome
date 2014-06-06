class BitMap{
private:
	char* M;
	int N;
protected:
	void init(int n) { M = new char[N=(n+7)/8]; memset(M, 0, N);}
	
public:
	BitMap(int n = 8) { init(n); }
	BitMap(char* file, int n = 8){
		init(n);
		FILE* fp = fopen(file, "r");
		fread(M, sizeof(char), N, fp);
		fclose(fp);
	}
	~BitMap() {
		delete []M;
		M = NULL;
	}
	
	void set(int k)   { expand(k); 		M[k>>3] |= (0x80 >> (k & 0x07)); }
	void clear(int k) { expand(k); 		M[k>>3] &= ~(0x80 >> (k & 0x07)); }	
	bool test(int k)  { expand(k); return M[k>>3] & (0x80 >> (k & 0x07)); }
	
	void expand(int k){
		if (k < 8*N) return;
		int oldN = N; 
		char* oldM = M;
		
		memcpy_s(M, N, oldM, oldN);
		delete [] oldM;
	}
};

class Bitmap{
private:
	Rank* F; Rank N; // vector F and size is N, record [k] the order
	Rank* T; Rank top; // stack T and capacity is N, 
	
protected:
	inline bool valid(Rank r) { return (0 <= r)&&(r < top); }
	inline bool erased(Rank k) // if it is erased, set T[F[k]] = -1-k
	{ return valid(F[k]) && !(T[F[k] + 1 + k]); }
	
public:
	Bitmap(Rank n = 8){
		N = n; F = new Rank[N]; T = new Rank[N]; top = 0;
	}
	~Bitmap() { delete [] F; delete [] T; }
	
	inline void set(Rank k){
		if (test(k)) return;
		if (!erased(k)) F[k] = top++;
		T[F[k]] = k;
	}
	
	inline void clear(Rank k){
		if (test(k))
			T[F[k]] = -1-k;
	}
	inline bool test(Rank k){
		return valid(F[k])&&(k == T[F[k]]);
	}
};
