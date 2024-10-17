#include<iostream>
#include "fakedstl.h"


int main(void) {

	using namespace std;
	//using fakedSTL::arrayList;
	//using fakedSTL::unionFindNode;


	using fakedSTL::adjacencyWDigraph;
	adjacencyWDigraph<char> adj(4);
	
	adj.insertEdge('a', 'b');
	
	
	

	return 0;
}
