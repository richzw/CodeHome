/*
Q:X和Y都是只有0和1组成的字符串。D(X,Y)称为模糊距离，定义如下：首先删除X和Y从头开始的公共子串
然后将X和Y剩下部分的长度相加得到模糊距离
例如D(1000,1111)，首先，删除子串“1”，然后剩下“000”和“111”长度都是3，相加为6，则
D(1000,1111)=6。
问题是，给定n个只有0和1的字符串，如：
1111
1000
101
1100
...
请找到最大的模糊距离，字符串总数为n，字符串最长为m。

对于模糊距离的第一个条件，我们想到什么呢？公共前缀，不知道同学们，联想到树形结构：trie树没有。
例如：给定000、001、0010，我们构造如下的trie树。

构造过程中，1为左子树，0为右子树。模糊距离的第一个条件是，去掉公共前缀，则计算时，两个字符串，要有公共前缀，
也就意味着，只需要考虑开始分叉的节点，左右子树，可以有一个没有。这样，我们考虑第一个分叉的节点：0，
然后可以计算第二部分了，如何计算剩下长度相加呢？
尤其，为了找到模糊距离的最大值，我们求得当前节点的左子树的最大深度以及右子树的最大深度，两者相加，
及得到一个模糊距离，为3。然后考虑1节点，右子树为空，则模糊距离为1。综合，最大的模糊距离为3。
这里有一个小小的技巧，构建的过程中，可以在节点中，存储左右子树的高度，并随着加入新的字符串，更新左右子树的高度。
总的时间复杂度为O(nm)。 根据上例，存储的左右子树的高度值变化如下 (left_height, right_height):
	* left_height: 左边子树的高度
	* right_height: 右边子树的高度
*/

int get_max_distance(vector<string> vec){
	Trie trie;

	for (vector<string>::iterator iter = vec.begin(); iter != vec.end(); ++iter){
		trie.addWord(*iter);
	}

	return trie.maxDep();
}

class Node{
public:
	Node():m_content(' '),m_is_word(false), m_distance(0){}
	~Node(){}
	char content() const { return m_content; }
	void setContent(char c) { m_content = c; }
	bool isWord() const { return m_is_word; }
	void setWord() { m_is_word = true; }
	void resetWord() { m_is_word = false; }
	int distance() { return m_distance; }
	void setDistance(int dis) { m_distance = dis; }
	void appendChild(Node* child) { m_children.push_back(child); }
	vector<Node*> children() const { return m_children; }
	bool hasChild() const { return m_children.size() > 0; }
	Node* findChild(char c){
		for (int i = 0; i < m_children.size(); ++i)
		{
			Node* tmp = m_children.at(i);
			if (tmp->content() == c)
				return tmp;
		}
		return NULL;
	}
	bool deleteChild(Node* child){
		for (vector<Node*>::iterator iter = m_children.begin(); iter != m_children.end(); ++iter){
			if ((*iter)->content() == child->content()){
				m_children.erase(iter);
				delete *iter;
				return true;
			}
		}
		return false;
	}
private:
	char	m_content;
	bool	m_is_word;
	int		m_distance;
	vector<Node*> m_children;
};

class Trie{
public:
	Trie(){
		root = new Node();
	}
	~Trie(){
		// delete memory
	}

	int maxDep() { return _maxDepth(root); }

	int _maxDepth(Node* current){
		if (!current->hasChild())
			return 0;
		else {
			vector<Node*> child = current->children();
			int max_dep = 0;
			for (vector<Node*>::iterator iter = child.begin(); iter != child.end(); ++iter){
				int dep = _maxDepth(*iter);
				if (dep > max_dep)
					max_dep = dep;
			}
			return max_dep+1;
		}
	}

	int toInt(string s){
		int decimal = 0;

		for (int counter = 0; counter < s.size(); ++counter)
		{
			if (s.c_str()[counter] == '1')
				decimal += pow(2, (float)counter);
		}

		return decimal;
	}
	
	void addWord(string s){
		Node* current = root;

		if (s.length() == 0){
			current->setWord();
			return;
		}

		for (int i = 0; i < s.length(); ++i){
			Node* child = current->findChild(s.at(i));
			int cur_dis = current->distance();
			if (toInt(s.substr(i)) > cur_dis){
				current->setDistance(toInt(s.substr(i)));
			}

			if (child != NULL){
				current = child;
			}else{
				Node* tmp = new Node();
				tmp->setContent(s.at(i));
				current->appendChild(tmp);
				current = tmp;
			}
		}
		current->setWord();
	}
}
