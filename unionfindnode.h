#pragma once
#ifndef _UNION_FIND_NODE_H_
#define _UNION_FIND_NODE_H_
#include "fakedstl.h"

namespace fakedSTL {
	template<class T>
	class unionFindNode {
	public:
		unionFindNode(const std::vector<T>& vt) :_ufs(vt.size(), -1) {
			for (int i = 0; i < vt.size(); ++i) {
				_indexmap[vt[i]] = i;
			}
		}
		~unionFindNode() {}

		int find(const T& element) {
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

		void unite(const T& element1, const T& element2) {
			int root1 = find(element1), root2 = find(element2);
			if (_ufs[root1] < _ufs[root2]) _ufs[root1] = root2;
			else {
				if (_ufs[root1] == _ufs[root2]) --_ufs[root1];
				_ufs[root2] = root1;
			}
		}

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
}

#endif // _UNION_FIND_NODE_H_
