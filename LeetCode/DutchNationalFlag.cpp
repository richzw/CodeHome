/*
DutchNationalFlag
*/
class DutchNationalFlag{
private:
	enum Color{
		RED;
		WHITE;
		BLUE;
	};

	Color* m_arr;
	int m_len;
public:
	DutchNationalFlag(int length):m_len(length){ m_arr = new Color[length]; }
	~DutchNationalFlag() { if (m_arr) delete[] m_arr; }

	Color color(int idx) { return m_arr[idx]; }
	void setColor(vector<byte> colorVec) {
		// assert colorVec.length <= m_len
		for (vector<byte>::iterator itor = colorVec.begin(); itor != colorVec.end(); ++itor){
			m_arr[idx] = *itor;
		}
	}

	void func(){
		int red = 0; 
		int blue = m_len - 1;

		while (color(red) == RED){
			++red;
		}

		while (color(blue) == BLUE){
			--blue;
		}

		for (int idx = red; idx < blue;){
			if (color(idx) == RED){
				std::swap(idx, red++);
			}else if (color(idx) == BLUE){
				std::swap(idx, blue--);
			}else{
				++idx;
			}

		}
	}
};
