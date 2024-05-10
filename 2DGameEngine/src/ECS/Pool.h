#pragma once

#include <vector>

// Pool Interface
class BasePool 
{
public:
	virtual ~BasePool() {}
};

template<typename T> class Pool : public BasePool
{
private:
	std::vector<T> data;
public:
	Pool(int size = 100) { data.resize(size); }
	virtual ~Pool() = default;

	bool isEmpty() const { return data.empty(); }
	int getSize() const { return data.size(); }
	void resize(int n) { data.resize(n); }
	void clear() { data.clear(); }
	void add(T obj) { data.push_back(obj); }
	void set(int index, T obj) { data[index] = obj; }
	T& get(int index) { return static_cast<T&>(data[index]); }
	T& operator[](unsigned int index) { return data[index]; }
};