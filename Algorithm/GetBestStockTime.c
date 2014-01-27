/*
Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to buy one share of the stock and sell one share of the stock, design an algorithm to find the best times to buy and sell.
*/

void getBestTime(int stocks[], int len, int& buy, int& sell){
	int min = 0;
	int max_diff = 0;
	buy = sell = 0;

	for (int i = 0; i < len; ++i){
		if (stocks[i] < min)
			min = i;

		int diff = stocks[i] - stocks[min];
		if (diff > max_diff){
			buy = i;
			sell = min;
			max_diff = diff;
		}
	}
}
