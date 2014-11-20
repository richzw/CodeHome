int GetBitOneIndex(__int64 val){
	int index = 0;

	if (!val)
		return index;

	if (!(val & 0xFFFF)){
		val >>= 16;
		index += 16;
	}
	if (!(val & 0xFF)){
		val >>= 8;
		index += 8;
	}
	if (!(val & 0xF)){
		val >>= 4;
		index += 4;
	}
	if (!(val & 3)){
		val >>= 2;
		index += 2;
	}
	if (!(val & 1)){
		val >>= 1;
		index += 1;
	}

	return index;
}
