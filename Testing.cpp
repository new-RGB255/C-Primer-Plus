//#include<iostream>
//#include "fakedstl.h"
//
//
//int main(void) {
//
//	using namespace std;
//
//	/*string s1("A");
//	string s2("");
//
//	string ans = (fakedSTL::kmp(s1, s2) == true) ? "true" : "false";
//	cout << ans;*/
//	
//
//	//using fakedSTL::arrayList;
//	//using fakedSTL::unionFindNode;
//
//	using fakedSTL::adjacencyWDigraph;
//	int num;
//	cout << "enter numbers of nodes:";
//	cin >> num;
//	adjacencyWDigraph<int, double> adj(num);
//	adj.thePosVertices();
//	int _1, _2;
//	cout << "from _1 point to _2\n";
//	while (cin >> _1 >> _2) {
//		adj.insert_edge(_1, _2);
//		cout << "from _1 point to _2\n";
//	}
//	cin.clear();
//	cin.ignore();
//	int _index1, _index2;
//	cout << "enter the shortest path to be found\n";
//	while (cin >> _index1 >> _index2) {
//		cout << "this is the Dijkstra:\n";
//		auto shortestpath = adj.shortestPaths(_index1, _index2);
//		cout << "the shorest length is ";
//		cout << shortestpath << endl;
//	}
//	cin.clear();
//	cin.ignore();
//
//	
//
//
//	return 0;
//}