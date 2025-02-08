#include "fakedstl.h"

using namespace std;
using fakedSTL::RB_tree;

template<class T>
struct returnKey {
	const T& operator()(const T& value) { return value; }
};

int main(void) {

	RB_tree<int, int, returnKey<int>> itree;
	vector<int> temp = { 10,7,8,15,5,6,11,13,12 };
	for (auto& num : temp) {
		itree.insert_unique(num);
	}
	cout << endl;
	itree.erase(11);
	itree.erase(10);
	itree.erase(8);
	itree.erase(15);
	itree.erase(13);
	itree.erase(5);
	itree.erase(6);
	itree.erase(7);
	//itree.erase(12);
	_rb_tree_base_iterator rcolour;
	if (!itree.empty()) {
		for (auto iter = itree.begin(); iter != itree.end(); ++iter) {
			rcolour = _rb_tree_base_iterator(iter);
			cout << *iter << "(" << rcolour.node->colour << ") ";
		}
		cout << endl;
	}

	return 0;
}