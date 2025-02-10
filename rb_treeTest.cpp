#include "fakedstl.h"

using namespace std;
using fakedSTL::RB_tree;

template<class T>
struct returnKey {
	const T& operator()(const T& value) { return value; }
};

using rb_tree_int = RB_tree<int, int, returnKey<int>>;

void testfunc(rb_tree_int it) {
	it.erase(10);
	it.erase(8);
	it.erase(15);
	it.erase(13);
	it.erase(12);
	it.insert_unique(2);
	_rb_tree_base_iterator rcolour;
	if (!it.empty()) {
		for (auto iter = it.begin(); iter != it.end(); ++iter) {
			rcolour = _rb_tree_base_iterator(iter);
			cout << *iter << "(" << rcolour.node->colour << ") ";
		}
		cout << endl;
	}
}

void testfunc2(rb_tree_int& rb) {
	rb_tree_int it = rb;
	it.erase(10);
	it.erase(8);
	it.erase(12);
	it.insert_unique(3);
	_rb_tree_base_iterator rcolour;
	if (!it.empty()) {
		for (auto iter = it.begin(); iter != it.end(); ++iter) {
			rcolour = _rb_tree_base_iterator(iter);
			cout << *iter << "(" << rcolour.node->colour << ") ";
		}
		cout << endl;
	}
}

int main(void) {

	rb_tree_int itree;
	vector<int> temp = { 10,7,8,15,5,6,11,13,12 };
	for (auto& num : temp) {
		itree.insert_unique(num);
	}
	cout << endl;
	testfunc2(itree);
	/*itree.erase(11);
	itree.erase(10);
	itree.erase(8);
	itree.erase(15);
	itree.erase(13);
	itree.insert_unique(25);
	itree.erase(5);
	itree.erase(6);
	itree.erase(7);
	itree.erase(12);
	itree.insert_unique(5);
	itree.insert_unique(1);
	itree.insert_unique(9);
	itree.clear();
	itree.insert_unique(1);
	cout << itree.size() << endl;*/
	cout << endl;
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