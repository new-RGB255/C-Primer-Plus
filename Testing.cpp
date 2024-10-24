#include<iostream>
#include "fakedstl.h"


int main(void) {

	using namespace std;
	//using fakedSTL::arrayList;
	//using fakedSTL::unionFindNode;


	using fakedSTL::adjacencyWDigraph;
	adjacencyWDigraph<int> adj(7);

	int _1, _2;
	while (cin >> _1 >> _2) {
		adj.insert_edge(_1, _2);
	}
	
	vector<int> res;

	adj.bfs(1, res);
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
