#pragma once
#ifndef _LINEARLIST_H_
#define _LINEARLIST_H_
#include "fakedstl.h"

namespace fakedSTL {
	template<class T>
	class linearList {
	public:
		virtual ~linearList() {}
		virtual bool empty() const = 0;
		//����true,��ǰ�������Ա�Ϊ��ʱ
		virtual int size() const = 0;
		//�������Ա��Ԫ�ظ���
		virtual T& get(int theIndex) const = 0;
		//��������ΪtheIndex��Ԫ��
		virtual int indexOf(const T& theElement) const = 0;
		//����Ԫ��theElement��һ�γ���ʱ������
		virtual void erase(int theIndex) = 0;
		//ɾ������ΪtheIndex��Ԫ��
		virtual void insert(int theIndex, const T& theElement) = 0;
		//��theElement�������Ա�������ΪtheIndex��λ����
		virtual void output(std::ostream& out) const = 0;
		//�����Ա���������out
	};

	template<class T>
	class arrayList :public linearList<T> {
		//friend
		template<class _T>
		friend std::ostream& operator<<(std::ostream& out, const arrayList<_T>& array) {
			for (int i = 0; i < array.listSize; ++i) {
				out << array.element[i] << " ";
			}
			return out;
		}
	public:
		arrayList(int initialCapacity = 10) {
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

		arrayList(const arrayList<T>& array) {
			arrayLength = array.arrayLength;
			listSize = array.listSize;
			element = new T[arrayLength];
			std::copy(array.element, array.element + array.listSize, element);
		}

		virtual ~arrayList() { delete[] element; }
		virtual bool empty() const { return listSize == 0; }
		virtual int size() const { return listSize; }

		virtual T& get(int theIndex) const {
			checkIndex(theIndex);
			return element[theIndex];
		}

		virtual int indexOf(const T& theElement) const {
			int theIndex = int(std::find(element, element + listSize, theElement) - element);
			if (theIndex == listSize) {
				std::cout << "The theElement doesn't exist\n";
				return -1;
			}
			else {
				return theIndex;
			}
		}

		virtual void erase(int theIndex) {
			checkIndex(theIndex);
			std::copy(element + theIndex + 1, element + listSize, element + theIndex);
			--listSize;
			if (listSize < arrayLength / 4) {
				/*
					*������listSize < arrayLength / 4ʱ
					* ���ݽ�ʡ�ڴ�
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

		virtual void insert(int theIndex, const T& theElement) {
			if (theIndex < 0 || theIndex > listSize) {
				std::cout << "index = " << theIndex << " size = " << listSize;
				exit(EXIT_FAILURE);
			}
			if (listSize == arrayLength) {
				//����
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

		virtual void output(std::ostream& out) const {
			std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
		}

		int capacity() const { return arrayLength; }
	private:
		T* element;
		int arrayLength;
		int listSize;
		const int initialSize = 10;
		void checkIndex(int theIndex) const {
			if (theIndex < 0 || theIndex >= listSize) {
				std::cout << "index = " << theIndex << " size = " << listSize;
				exit(EXIT_FAILURE);
			}
		}
	};
}

#endif // !_LINEARLIST_H_
