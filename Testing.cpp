#include<iostream>
#include "fakedstl.h"


int main(void) {

	using namespace std;
	//using fakedSTL::arrayList;
	//using fakedSTL::unionFindNode;


	using fakedSTL::adjacencyWDigraph;
	adjacencyWDigraph<int> adj(5);

	int _1, _2;
	cout << "from _1 point to _2\n";
	while (cin >> _1 >> _2) {
		adj.insert_edge(_1, _2);
		cout << "from _1 point to _2\n";
	}
	
	vector<int> res;

	adj.dfs(1, res);
	for (auto num : res)
		cout << num << " ";


	/*if (adj.topologicalOrder(res)) {
		for (auto num : res)
			cout << num << " ";
	}
	else {
		cout << "has a circle";
	}*/
	

	return 0;
}
