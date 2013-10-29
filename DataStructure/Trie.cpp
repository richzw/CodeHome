// Trie implementation with C++
class Node{
public:
	Node():m_content(' '),m_is_word(false){}
	~Node(){}
	char content() const { return m_content; }
	void setContent(char c) { m_content = c; }
	bool isWord() const { return m_is_word; }
	void setWord() { m_is_word = true; }
	void resetWord() { m_is_word = false; }
	void appendChild(Node* child) { m_children.push_back(child); }
	vector<Node*> children() const { return m_children; }
	bool hasChild() const { return m_children.size() == 0; }
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
	char m_content;
	bool m_is_word;
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
	void addWord(string s){
		Node* current = root;

		if (s.length() == 0){
			current->setWord();
			return;
		}

		for (int i = 0; i < s.length(); ++i){
			Node* child = current->findChild(s.at(i));
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
	bool searchWord(string s){
		Node* current = root;

		for (int i = 0; i < s.length(); ++i){
			Node* child = current->findChild(s.at(i));
			if (child == NULL)
				return false;
			current = child;
		}
		if (current->isWord())
			return true;
		else
			return false;
	}
	bool deleteWord(string s){
		Node* current = root;
		Node* pre = root;

		for (int i = 0; i < s.length(); ++i){
			Node* child = current->findChild(s.at(i));
			if (child == NULL)
				return false;
			else{
				if (pre != current){
					pre->deleteChild(current);
					if (!pre->hasChild())
						delete pre;
				}
			}
			pre = current;
			current = child;
		}
		current->resetWord();
		if (!current->hasChild()){
			pre->deleteChild(current);
			delete current;
		}
		return true;
	}

private:
	Node* root;
};
