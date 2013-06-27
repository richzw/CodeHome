#include <deque>
#include <assert.h>

template <typename T> 
class CStackWithMin{
public:
  CStackWithMin() {}
	virtual ~CStackWithMin() {}

	T& top();
	const T& top() const;

	void push(const T& value);
	void pop();

	const T& min() const;

private:
	deque<T> m_data;
	deque<size_t> m_minIndex;
};

template <typename T> T& CStackWithMin<T>::top(){
	return m_data.back();
}

template <typename T> const T& CStackWithMin<T>::top() const{
	return m_data.back();
}

template <typename T> const T& CStackWithMin<T>::push(const T& value){
	m_data.push_back(value);

	if (m_minIndex.size() == 0)
		m_minIndex.push_back(0)
	else{
		if (value < m_data[m_minIndex.back()])
			m_minIndex.push_back(m_data.size()-1);
		else
			m_minIndex.push_back(m_minIndex.back());
	}
}

template <typename T> void CStackWithMin<T>::pop()
{
	m_data.pop_back();
	m_minIndex.pop_back();
}

template <typename T> const T& CStackWithMin<T>::min() const
{
	return m_data[m_minIndex.back()];
}
