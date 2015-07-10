
#if !defined KISS_RNG
#define KISS_RNG

class RNG
{
private:
	unsigned long	x;
	unsigned long	y;
	unsigned long	z;
	unsigned long	w;

private:
	void kiss_init();
	unsigned long kiss_rand();

public:
	RNG();
	RNG(const RNG& rng);
	~RNG() { }

	unsigned long GetRNG(unsigned long rand_min, unsigned long rand_max);
};

#endif
