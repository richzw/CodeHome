//http://www.cnblogs.com/wuyuegb2312/p/3273337.html

bool finished = false;
backtrack(int a[], int k, data input)
{
	int c[MAXCAND];
	int ncand;
	if (is_a_solution(a, k, input))
		process_solution(a, k, input);
	else 
	{
		k += 1;
		construct_cand(a, k, input, c, &ncand);
		for (int i = 0; i < ncand; ++i)
		{
			a[k] = c[i];
			make_move(a, k, input);
			backtrack(a, k, input);
			unmake_move(a, k, input);
			if (finished)
				return;
		}
	}
}
