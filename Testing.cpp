#include<iostream>
#include "fakedstl.h"


int main(void) {

	using namespace std;
	//using fakedSTL::arrayList;
	//using fakedSTL::unionFindNode;


	using fakedSTL::adjacencyWDigraph;
	adjacencyWDigraph<char> adj(4);
	
	adj.insert_edge('a', 'b');
	
	vector<int> res;

	if (adj.topologicalOrder(res)) {
		for (auto num : res)
			cout << num << " ";
	}
	else {
		cout << "has a circle";
	}
	

	return 0;
}
