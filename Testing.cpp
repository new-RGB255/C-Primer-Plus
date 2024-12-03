#include<iostream>
#include "fakedstl.h"


int main(void) {

	using namespace std;

	/*string s1("A");
	string s2("");

	string ans = (fakedSTL::kmp(s1, s2) == true) ? "true" : "false";
	cout << ans;*/
	

	//using fakedSTL::arrayList;
	//using fakedSTL::unionFindNode;

	
	using fakedSTL::adjacencyWDigraph;
	int num;
	cout << "enter numbers of nodes:";
	cin >> num;
	adjacencyWDigraph<int> adj(num);

	int _1, _2;
	cout << "from _1 point to _2\n";
	while (cin >> _1 >> _2) {
		adj.insert_edge(_1, _2);
		cout << "from _1 point to _2\n";
	}
	cin.clear();
	cin.ignore();
	int _index1, _index2;
	vector<vector<int>> c;
	vector<vector<int>> kay;
	adj.allPairs(c, kay);
	cout << "enter the shortest path to be found\n";
	while (cin >> _index1 >> _index2) {
		cout << "this is the Dijkstra:\n";
		int shortestpath = adj.shortestPaths(_index1, _index2);
		cout << "the shorest length is ";
		cout << shortestpath << endl;
		cout << "\nthis is the Floyd:\n";
		adj.outputPath(c, kay, _index1, _index2);
		cout << "enter the shortest path to be found\n";
	}
	cin.clear();
	cin.ignore();


	/*if (adj.topologicalOrder(res)) {
		for (auto num : res)
			cout << num << " ";
	}
	else {
		cout << "has a circle";
	}*/
	

	return 0;
}
