#pragma once
#ifndef _FAKED_STL_H
#define _FAKED_STL_H

#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<valarray>
#include<cmath>
#include<string>
#include<stack>
#include<map>
#include<unordered_map>

#include "vertexIterator.h"

//statemate
namespace fakedSTL {

	template<class T>
	class linearList {
	public:
		virtual ~linearList() {}
		virtual bool empty() const = 0;
		//返回true,当前仅当线性表为空时
		virtual int size() const = 0;
		//返回线性表的元素个数
		virtual T& get(int theIndex) const = 0;
		//返回索引为theIndex的元素
		virtual int indexOf(const T& theElement) const = 0;
		//返回元素theElement第一次出现时的索引
		virtual void erase(int theIndex) = 0;
		//删除索引为theIndex的元素
		virtual void insert(int theIndex, const T& theElement) = 0;
		//把theElement插入线性表中索引为theIndex的位置上
		virtual void output(std::ostream& out) const = 0;
		//把线性表插入输出流out
	};

	

	template<class T>
	class arrayList :public linearList<T> {
	public:
		//friend
		template<class _T>
		friend std::ostream& operator<<(std::ostream& out, const arrayList<_T>& array);
	public:
		arrayList(int initialCapacity = 10);
		arrayList(const arrayList<T>& array);
		virtual ~arrayList() { delete[] element; }
		virtual bool empty() const { return listSize == 0; }
		virtual int size() const { return listSize; }
		virtual T& get(int theIndex) const;
		virtual int indexOf(const T& theElement) const;
		virtual void erase(int theIndex);
		virtual void insert(int theIndex, const T& theElement);
		virtual void output(std::ostream& out) const;
		int capacity() const { return arrayLength; }
	private:
		T* element;
		int arrayLength;
		int listSize;
		const int initialSize = 10;
		void checkIndex(int theIndex) const;
	};



	/*
		*并查集声明
	*/
	template<class T>
	class unionFindNode {
	public:
		unionFindNode(const std::vector<T>& vt);
		~unionFindNode() {}
		int find(const T& element);
		void unite(const T& element1, const T& element2);
		int getHeight(const T& element) {
			return _ufs[_indexmap[element]];
		}
		int getNum() {
			int count = 0;
			for (auto val : _ufs) {
				if (val < 0) ++count;
			}
			return count;
		}
	private:
		std::vector<int> _ufs;
		std::unordered_map<T, int> _indexmap;
	};



	
	template<class T>
	class graph {
	public:
		virtual ~graph() {}
		virtual int numberOfVertices() const = 0;
		virtual int numberOfEdge() const = 0;
		virtual bool existsEdge(int, int) const = 0;
		virtual void insertEdge(int, int) = 0;
		virtual void eraseEdge(int, int) = 0;
		virtual int degree(int) const = 0;
		virtual int inDegree(int) const = 0;
		virtual int outDegree(int) const = 0;
		virtual bool topologicalOrder(std::vector<int>&) = 0;
		//
		virtual bool directed() const = 0;
		//当前仅当是有向图时返回值是true
		virtual bool weighted() const = 0;
		//当前仅当是加权图时返回值是true
		virtual void bfs(int, std::vector<int>&) = 0;
		virtual void dfs(int, std::vector<int>&) = 0;
	};



	template<class T>
	class adjacencyWDigraph :public graph<T> {
	public:
		adjacencyWDigraph(int numberOfVertices = 0) {
			if (numberOfVertices < 0) {
				std::cout << "number of vertices must be >= 0\n";
				exit(EXIT_FAILURE);
			}
			ver = numberOfVertices;
			edg = 0;
			vt.resize(ver + 1, std::vector<int>(ver + 1));
			for (int i = 1; i <= ver; ++i) {
				for (int j = 1; j <= ver; ++j) {
					vt[i][j] = MAX;
				}
			}
			T ch;
			std::cout << "enter value:";
			for (int i = 1; i <= ver; ++i) {
				std::cin >> ch;
				_mp[ch] = i;
			}
		}

		virtual ~adjacencyWDigraph() {}
		virtual int numberOfVertices() const { return ver; }
		virtual int numberOfEdge() const { return edg; }
		virtual bool directed() const { return true; }
		virtual bool weighted() const { return true; }

		virtual bool existsEdge(int i, int j) const {
			if (i < 1 || j < 1 || i > ver || j > ver || vt[i][j] == MAX) {
				return false;
			}
			else {
				return true;
			}
		}

		/*class myIterator :public vertexIterator<T> {
		public:
			
		protected:
			T* row;
			int n;
			int currentVertex;
		};*/

		virtual void insertEdge(int, int);
		virtual void eraseEdge(int, int);

		virtual int degree(int v) const { 
			return inDegree(v) + outDegree(v); 
		}

		virtual int inDegree(int v) const {
			int sum = 0;
			for (int i = 1; i <= ver; ++i) {
				if (vt[i][v] != MAX)
					++sum;
			}
			return sum;
		}

		virtual int outDegree(int v) const {
			int sum = 0;
			for (int j = 1; j <= ver; ++j) {
				if (vt[v][j] != MAX)
					++sum;
			}
			return sum;
		}

		virtual int degree(T _variable_name) {
			int v = _mp[_variable_name];
			return inDegree(v) + outDegree(v);
		}

		virtual int in_degree(T _variable_name) {
			int v = _mp[_variable_name];
			return inDegree(v);
		}

		virtual int out_degree(T _variable_name) {
			int v = _mp[_variable_name];
			return outDegree(v);
		}

		virtual void insert_edge(T _1_variable_name, T  _2_variable_name) {
			int v1 = _mp[_1_variable_name];
			int v2 = _mp[_2_variable_name];
			insertEdge(v1, v2);
		}

		virtual void erase_edge(T _1_variable_name, T  _2_variable_name) {
			int v1 = _mp[_1_variable_name];
			int v2 = _mp[_2_variable_name];
			eraseEdge(v1, v2);
		}

		virtual bool topologicalOrder(std::vector<int>& nums);

		virtual void bfs(int, std::vector<int>&);
		virtual void BFS(T, std::vector<int>&);
		virtual void dfs(int, std::vector<int>&);
		virtual void DFS(T, std::vector<int>&);

	protected:
		int ver;
		int edg;
		std::vector<std::vector<int>> vt;
		std::unordered_map<T, int> _mp;
		const int MAX = INT32_MAX;
	};








}


/*
	
	*以下为函数定义

*/


//definition
namespace fakedSTL {

	template<class T>
	void arrayList<T>::checkIndex(int theIndex) const {
		if (theIndex < 0 || theIndex >= listSize) {
			std::cout << "index = " << theIndex << " size = " << listSize;
			exit(EXIT_FAILURE);
		}
	}

	template<class T>
	arrayList<T>::arrayList(int initialCapacity) {
		if (initialCapacity < 1) {
			std::cout << "Initial capacity = " << initialCapacity << "Must be > 0\n";
			std::cout << "The default initialzation format has been automatically "
				<< "generated\n";
			arrayLength = initialCapacity;
			element = new T[arrayLength];
			listSize = 0;
		}
		arrayLength = initialCapacity;
		element = new T[arrayLength];
		listSize = 0;
	}

	template<class T>
	arrayList<T>::arrayList(const arrayList<T>& array) {
		arrayLength = array.arrayLength;
		listSize = array.listSize;
		element = new T[arrayLength];
		std::copy(array.element, array.element + array.listSize, element);
	}

	template<class T>
	T& arrayList<T>::get(int theIndex) const {
		checkIndex(theIndex);
		return element[theIndex];
	}

	template<class T>
	int arrayList<T>::indexOf(const T& theElement) const {
		int theIndex = int(std::find(element, element + listSize, theElement) - element);
		if (theIndex == listSize) {
			std::cout << "The theElement doesn't exist\n";
			return -1;
		}
		else {
			return theIndex;
		}
	}

	template<class T>
	void arrayList<T>::erase(int theIndex) {
		checkIndex(theIndex);
		std::copy(element + theIndex + 1, element + listSize, element + theIndex);
		--listSize;
		if (listSize < arrayLength / 4) {
			/*
				*当满足listSize < arrayLength / 4时
				* 缩容节省内存
			*/
			T* newElement = new T[std::max(arrayLength / 2, initialSize)];
			std::copy(element, element + listSize, newElement);
			delete[] element;
			element = new T[std::max(arrayLength / 2, initialSize)];
			std::copy(newElement, newElement + listSize, element);
			arrayLength = std::max(arrayLength / 2, initialSize);
			delete[] newElement;
		}
	}

	template<class T> 
	void arrayList<T>::insert(int theIndex, const T& theElement) {
		if (theIndex < 0 || theIndex > listSize) {
			std::cout << "index = " << theIndex << " size = " << listSize;
			exit(EXIT_FAILURE);
		}
		if (listSize == arrayLength) {
			//扩容
			arrayLength *= 2;
			T* newElement = new T[arrayLength];
			std::copy(element, element + listSize, newElement);
			delete[] element;
			element = new T[arrayLength];
			std::copy(newElement, newElement + listSize, element);
			delete[] newElement;
		}
		std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
		element[theIndex] = theElement;
		++listSize;
	}

	template<class T> 
	void arrayList<T>::output(std::ostream& out) const {
		std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
	}

	template<class T>
	std::ostream& operator<<(std::ostream& out, const arrayList<T>& array) {
		for (int i = 0; i < array.listSize; ++i) {
			out << array.element[i] << " ";
		}
		return out;
	}



	/*
		*并查集函数定义
	*/
	template<class T>
	unionFindNode<T>::unionFindNode(const std::vector<T>& vt) :_ufs(vt.size(), -1) {
		for (int i = 0; i < vt.size(); ++i) {
			_indexmap[vt[i]] = i;
		}
	}

	template<class T>
	int unionFindNode<T>::find(const T& element) {
		int root = _indexmap[element];
		int pos = _indexmap[element];
		while (_ufs[root] >= 0) {
			root = _ufs[root];
		}
		while (_ufs[pos] >= 0) {
			int parent = _ufs[pos];
			_ufs[pos] = root;
			pos = parent;
		}
		return root;
	}

	template<class T>
	void unionFindNode<T>::unite(const T& element1, const T& element2) {
		int root1 = find(element1), root2 = find(element2);
		if (_ufs[root1] < _ufs[root2]) _ufs[root1] = root2;
		else {
			if (_ufs[root1] == _ufs[root2]) --_ufs[root1];
			_ufs[root2] = root1;
		}
	}



	//图论
	template<class T>
	void adjacencyWDigraph<T>::insertEdge(int v1, int v2) {
		if (v1 < 1 || v2 < 1 || v1 > ver || v2 > ver || v1 == v2) {
			std::cout << "(" << v1 << "," << v2 << ")"
				<< "is not a permissible edge\n";
			exit(EXIT_FAILURE);
		}
		if (!existsEdge(v1, v2)) {
			int weight;
			std::cout << "enter weight:";
			std::cin >> weight;
			vt[v1][v2] = weight;
		}
	}

	template<class T>
	void adjacencyWDigraph<T>::eraseEdge(int v1, int v2) {
		if (v1 >= 1 && v2 >= 1 && v1 <= ver && v2 <= ver && vt[v1][v2] != MAX) {
			vt[v1][v2] = MAX;
			--edg;
		}
	}

	template<class T>
	bool adjacencyWDigraph<T>::topologicalOrder(std::vector<int>& nums) {
		int n = numberOfVertices();
		nums.resize(n);
		std::vector<int> indegree(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			indegree[i] = inDegree(i);
		}
		std::queue<int> q;
		for (int i = 1; i <= n; ++i) {
			if (indegree[i] == 0)
				q.push(i);
		}
		int theVertex = 0;
		while (!q.empty()) {
			int currentVertex = q.front();
			q.pop();
			nums[theVertex++] = currentVertex;
			for (int j = 1; j <= n; ++j) {
				if (vt[theVertex][j] != MAX) {
					--indegree[j];
					if (indegree[j] == 0)
						q.push(j);
				}
			}
		}
		return theVertex == n;
	}

	template<class T>
	void adjacencyWDigraph<T>::bfs(int v, std::vector<int>& res) {
		int n = numberOfVertices();
		std::vector<bool> visited(n + 1, false);
		std::queue<int> q;
		visited[v] = true;
		q.push(v);
		while (!q.empty()) {
			int theVertex = q.front();
			res.push_back(theVertex);
			q.pop();
			for (int j = 1; j <= n; ++j) {
				if (vt[theVertex][j] != MAX && visited[j] == false) {
					q.push(j);
					visited[j] = true;
				}
			}
		}
	}

	template<class T>
	void adjacencyWDigraph<T>::BFS(T  _variable_name, std::vector<int>& res) {
		int v = _mp[_variable_name];
		adjacencyWDigraph<T>::bfs(v, res);
	}

	template<class T>
	void adjacencyWDigraph<T>::dfs(int v, std::vector<int>& res) {
		static std::vector<bool> visited(numberOfVertices() + 1, false);
		visited[v] = true;
		res.push_back(v);
		for (int j = 1; j <= numberOfVertices(); ++j) {
			if (vt[v][j] != MAX && visited[j] == false)
				adjacencyWDigraph<T>::dfs(j, res);
		}
	}

	template<class T>
	void adjacencyWDigraph<T>::DFS(T  _variable_name, std::vector<int>& res) {
		int v = _mp[_variable_name];
		adjacencyWDigraph<T>::dfs(v, res);
	}



	/*
		* 以下为
		* 部分排序算法
		* 数组使用vector容器
	*/

	//插排
	template<class T> //数组使用vector容器
	void insertionSort(std::vector<T>& vt) {
		size_t len = vt.size();
		for (size_t i = 1; i < len; ++i) {
			for (size_t j = i; j > 0 && vt[j - 1] > vt[j]; --j) {
				std::swap(vt[j - 1], vt[j]);
			}
		}
	}

	template<class T>
	void insertionSort(std::vector<T>& vt, size_t left, size_t right) {
		size_t len = right - left + 1;
		for (size_t i = 1; i < len; ++i) {
			for (size_t j = i; j > 0 && vt[j - 1] > vt[j]; --j) {
				std::swap(vt[j - 1], vt[j]);
			}
		}
	}

	template<class T>
	void insertionSort(T& array, size_t len) {
		for (size_t i = 1; i < len; ++i) {
			for (size_t j = i; j > 0 && array[j - 1] > array[j]; --j) {
				std::swap(array[j - 1], array[j]);
			}
		}
	}

	//希尔排序
	template<class T> //数组使用vector容器
	void shellSort(std::vector<T>& vt) {
		size_t len = vt.size();
		/*
			*一种流行的增量序列(但不是最好)满足
			* h(t) = [size / 2]向下取整, h(k) = [h(k + 1) / 2]向下取整
		*/
		for (size_t increase = len >> 1; increase > 0; increase >>= 1) {
			for (size_t i = increase; i < len; ++i) {
				for (size_t j = i; j >= increase && vt[j - increase] > vt[j]; j -= increase) {
					std::swap(vt[j - increase], vt[j]);
				}
			}
		}
	}

	template<class T>
	void shellSort(T& array, size_t len) {
		for (size_t increase = len >> 1; increase > 0; increase >>= 1) {
			for (size_t i = increase; i < len; ++i) {
				for (size_t j = i; j >= increase && array[j - increase] > array[j]; j -= increase) {
					std::swap(array[j - increase], array[j]);
				}
			}
		}
	} 

	//namespace -> mergeSort
	namespace {

		template<class T>
		void merge(std::vector<T>& vt, size_t left, size_t middle, size_t right) {
			size_t len1 = middle - left + 1;
			size_t len2 = right - middle;
			size_t t_left = 0;
			size_t t_right = 0;
			size_t pos = left;

			std::vector<T> temp1(len1);
			std::vector<T> temp2(len2);

			for (size_t i = 0; i < len1; ++i) {
				temp1[i] = vt[left + i];
			}
			for (size_t i = 0; i < len2; ++i) {
				temp2[i] = vt[middle + 1 + i];
			}

			while (t_left < len1 && t_right < len2) {
				if (temp1[t_left] <= temp2[t_right]) {
					vt[pos++] = temp1[t_left++];
				}
				else {
					vt[pos++] = temp2[t_right++];
				}
			}

			while (t_left < len1) {
				vt[pos++] = temp1[t_left++];
			}
			while (t_right < len2) {
				vt[pos++] = temp2[t_right++];
			}
		}

	}

	//归并排序
	//using namespace -> mergeSort
	template<class T> //数组使用vector容器
	void mergeSort(std::vector<T>& vt, size_t left, size_t right) {
		if (vt.size() == 1) return;
		else if (vt.size() == 2) {
			if (vt[0] > vt[1]) std::swap(vt[0], vt[1]);
		}
		else {
			if (left < right) {
				size_t middle = (left + right) >> 1;
				mergeSort(vt, left, middle);
				mergeSort(vt, middle + 1, right);
				merge(vt, left, middle, right);
			}
		}
	}

	//namespace -> quickSort
	namespace {

		template<class T>
		T getMedian_3(std::vector<T>& vt, size_t left, size_t right, size_t& index) {
			size_t middle = (left + right) >> 1;
			if (vt[left] < vt[middle])				// 以a, b, c分别表示vt[left], vt[middle], vt[right]
				if (vt[middle] < vt[right])	{		// a < b < c
					index = middle;					// 
					return vt[middle];				// 
				}									// 
				else if (vt[left] < vt[right]) {	// a < b, b >= c, a < c
					index = right;					// 
					return vt[right];				// 
				}									// 
				else {// b > a >= c					// 
					index = left;					// 
					return vt[left];				// 

				}									// 
			else if (vt[left] < vt[right]) {		// c > a >= b
				index = left;						// 
				return vt[left];					// 
			}										// 
			else if (vt[middle] < vt[right]) {		// a >= b, a >= c, b < c
				index = right;						// 
				return vt[right];					// 
			}										// 
			else {									// c >= b >= a
				index = middle;
				return vt[middle];
			}
		}

		template<class T>
		size_t partition(std::vector<T>& vt, size_t left, size_t right) {
			size_t index = 0;
			T pivot = getMedian_3(vt, left, right, index);
			std::swap(vt[left], vt[index]);
			size_t first = left + 1;
			size_t last = right;

			while (true) {
				while (vt[first] < pivot) {
					if (first == vt.size() - 1) break;
					++first;
				}
				while (vt[last] > pivot) {
					--last;
				}
				if (!(first < last)) {
					if (vt[first] < pivot) {
						std::swap(vt[left], vt[first]);
						return first;
					}
					else if (vt[first] > pivot) {
						std::swap(vt[left], vt[first - 1]);
						return first - 1;
					}
					return first;
				}
				std::swap(vt[first], vt[last]);
				++first;
			}
		}

		static const int cutoff = 3;

	}

	//快速排序
	//using namespace -> quickSort
	template<class T> //数组使用vector容器
	void quickSort(std::vector<T>& vt, size_t left, size_t right) {
		if (left + cutoff <= right) {
			if (left < right) {
				size_t median = partition(vt, left, right);
				if (median - 1 == 0) return;
				quickSort(vt, left, median - 1);
				quickSort(vt, median + 1, right);
			}
		}
		else {
			insertionSort(vt, left, right);
		}
	}

	















}



#endif // !_FAKED_STL_H
