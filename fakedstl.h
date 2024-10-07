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
	private:
		T* element;
		int arrayLength;
		int listSize;
		const int initialSize = 10;
		void checkIndex(int theIndex) const;
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

	};

	







}


/*
	
	*以下为函数定义

*/


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

	

















}



#endif // !_FAKED_STL_H
