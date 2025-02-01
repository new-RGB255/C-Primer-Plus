#pragma once
#ifndef _FAKED_STL_H_
#define _FAKED_STL_H_

#define _FAKEDSTL_FEASIBLE 1
#ifdef _FAKEDSTL_FEASIBLE
#include<iostream>
#include<exception>
#include<cstdlib>
#include<vector>
#include<list>
#include<queue>
#include<valarray>
#include<cmath>
#include<string>
#include<stack>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<memory>
#include<algorithm>

#include "graph.h"
#include "rbtree.h"
#include "linearlist.h"
#include "unionfindnode.h"
#endif // !_FAKEDSTL_FEASIBLE


//_FAKEDSTL_BEGIN
namespace fakedSTL {

	// _ALGORITHM_BEGIN
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

	

	//归并排序
	//using namespace -> mergeSort
	template<class T> //数组使用vector容器
	void mergeSort(std::vector<T>& vt, size_t left, size_t right) {
		if (vt.size() == 1) return;
		else if (vt.size() == 2) {
			if (vt[0] > vt[1]) std::swap(vt[0], vt[1]);
		}
		else {
			auto merge = [](std::vector<T>& vt, size_t left, size_t middle, size_t right) {
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
				};
			if (left < right) {
				size_t middle = (left + right) >> 1;
				mergeSort(vt, left, middle);
				mergeSort(vt, middle + 1, right);
				merge(vt, left, middle, right);
			}
		}
	}

	

	//快速排序
	template<class T> //数组使用vector容器
	void quickSort(std::vector<T>& vt, size_t left, size_t right) {
		static const int cutoff = 3;
		if (left + cutoff <= right) {
			auto partition = [](std::vector<T>& vt, size_t left, size_t right) -> size_t {
				size_t index = 0;
				auto getMedian_3 = [](std::vector<T>& vt, size_t left, size_t right, size_t& index) -> T {
					size_t middle = (left + right) >> 1;
					if (vt[left] < vt[middle])				// 以a, b, c分别表示vt[left], vt[middle], vt[right]
						if (vt[middle] < vt[right]) {		// a < b < c
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
					};
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
				};
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



	// kmp字符串匹配算法
	bool kmp(const std::string& main, const std::string& pattern) {
		if (!main.size() && !pattern.size()) return true;
		if (!main.size() || !pattern.size()) return false;

		auto func_next = [&pattern]() -> std::vector<int> {
			int m = pattern.size();
			std::vector<int> next(m);
			next[0] = 0;
			for (int i = 1; i < m; ++i) {
				int len = next[i - 1];
				while (len && pattern[i] != pattern[len]) {
					len = next[len - 1];
				}
				next[i] = (pattern[i] == pattern[len]) ? ++len : len;
			}
			return next;
			};

		auto func_kmp = [&](std::vector<int> next) -> bool {
			int main_i = 0; // main中的指针
			int pattern_j = 0; // pattern中的指针
			while (main_i < main.size() && ((main.size() - main_i) >= (pattern.size() - pattern_j))) {
				// 字符匹配, 指针后移
				if (main[main_i] == pattern[pattern_j]) {
					++main_i; ++pattern_j;
				}
				// 字符不匹配, 使用next数组跳过匹配串的一部分字符
				// next数组存储的是当前匹配串字符的最长公共前缀长度
				else if (pattern_j > 0) {
					pattern_j = next[pattern_j - 1];
				}
				// 以上全部不满足就跳过主串的这个字符
				else {
					++main_i;
				}
				if (pattern_j == pattern.size()) return true;
			}
			return false;
			};

		return func_kmp(func_next());
	}




} //_FAKEDSTL_END




#endif // !_FAKED_STL_H_
