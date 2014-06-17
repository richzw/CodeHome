typedef struct cacheNode{
	int key;
	int value;
	cacheNode(int key, int val):key(key),value(val){}
}cacheNode;

// double link list(add, delete high efficience) and hashmap 
class LRUCache{
public:
	LRUCache(int size):capacity(size){}

	int get(int k){
		if (m_map.find(k) != m_map.end()){
			m_cachelist.splice(m_cachelist.begin(), m_cachelist, m_map[key]);
			m_map[key] = m_cachelist.begin();
			return m_map[key]->value;
		}else{
			return -1;
		}
	}

	void set(int key, int value){
		if (m_map.find(key) == m_map.end()){
			if (m_map.size() == capacity){
				m_map.erase(m_cachelist.back().key);
				m_cachelist.pop_back();
			}
			m_cachelist.push_front(cacheNode(key, value));
			m_map[key] = m_cachelist.begin();
		}else{
			m_map[key]->value = value;
			m_cachelist.splice(m_cachelist.begin(), m_cachelist, m_map[key]);
			m_map[key] = m_cachelist.begin();
		}
	}

private:
	list<cacheNode> m_cachelist;
	unordered_map<int, list<cacheNode>::iterator> m_map;
	int capacity;
};
