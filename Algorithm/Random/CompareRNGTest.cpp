using HashMap = unordered_map < int, int > ;
#define MAXNUM 10

void GetRandomNumberByRand(HashMap& map)
{
	std::random_device rd;

	std::mt19937 mt(rd());
	std::uniform_int_distribution<> dist(0, MAXNUM);

	// Generate 100 numbers randomly
	for (int idx = 0; idx < MAXNUM; ++idx) {
		++map[dist(mt)];
	}
}

void GetRandomNumberByKiss(HashMap& map)
{
	RNG rng;
	for (int idx = 0; idx < MAXNUM; ++idx) {
		++map[rng.GetRNG(0, MAXNUM)];
	}	
}

int _tmain(int argc, _TCHAR* argv[])
{
	HashMap map1;
	for (int idx = 0; idx < MAXNUM; ++idx) {
		map1[idx] = 0;
	}

	for (int i = 0; i < 100; ++i)
		GetRandomNumberByRand(map1);

	for (auto& e : map1)
		cout << e.second << " ";
	cout << endl;

	HashMap map2;
	for (int idx = 0; idx < MAXNUM; ++idx) {
		map2[idx] = 0;
	}

	for (int i = 0; i < 100; ++i)
		GetRandomNumberByKiss(map2);

	for (auto& e : map2)
		cout << e.second << " ";
	cout << endl;
