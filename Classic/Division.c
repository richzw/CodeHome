int division(int numerator, int denominator){
	unsigned int rest, divisor, op, result = 0;
	int flag = 0;
	int bits = 0;

	if (denominator == 0)// assert(denominator != 0);
		return 0;

	// save the negative or positive flag
	if ((numerator > 0 &&denominator < 0 ) || (numerator < 0 &&denominator > 0 ))
		flag = -1;
	else
		flag = 1;

	numerator = abs(numerator);
	denominator = abs(denominator);

	if (numerator < denominator)
		return 0;

	//
	op = denominator;
	while (op <= numerator){
		bits++;
		op <<= 1;
	}
	op >>= 1;
	bits--;

	while (op >= denominator){
		if (numerator >= op){
			numerator -= op;
			result += 1 << bits;
		}

		op = op >> 1;
		bits--;
	}

	return flag*result;
}
