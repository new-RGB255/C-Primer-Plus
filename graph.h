#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "fakedstl.h"
#if _FAKEDSTL_FEASIBLE

#endif // _FAKEDSTL_FEASIBLE

namespace fakedSTL {
	template<class T>
	class graph {
	public:
		virtual ~graph() {}
		virtual int numberOfVertices() const = 0;
		virtual int numberOfEdge() const = 0;
		virtual bool existsEdge(int, int) const = 0;
		virtual void insertEdge(int, int) = 0;
		virtual void eraseEdge(int, int) = 0;
		virtual int degree(int) const = 0;
		virtual int inDegree(int) const = 0;
		virtual int outDegree(int) const = 0;
		virtual bool topologicalOrder(std::vector<int>&) = 0;
		//
		virtual bool directed() const = 0;
		//当前仅当是有向图时返回值是true
		virtual bool weighted() const = 0;
		//当前仅当是加权图时返回值是true
		virtual void bfs(int, std::vector<int>&) = 0;
		virtual void dfs(int, std::vector<int>&, std::vector<bool>&) = 0;
	};



	template<class T, class weightType = int>
	class adjacencyWDigraph :public graph<T> {
		using _wt = weightType;
	public:
		adjacencyWDigraph(int numberOfVertices = 0) {
			if (numberOfVertices < 0) {
				std::cout << "number of vertices must be >= 0\n";
				exit(EXIT_FAILURE);
			}
			ver = numberOfVertices;
			edg = 0;
			vt.resize(ver, std::vector<_wt>(ver));
			for (int i = 0; i < ver; ++i) {
				for (int j = 0; j < ver; ++j) {
					vt[i][j] = notaccessible;
				}
			}
			T key_name;
			std::cout << "enter value:";
			variables.resize(ver);
			for (int i = 0; i < ver; ++i) {
				std::cin >> key_name;
				variables[i] = key_name;
			}
		}

		virtual ~adjacencyWDigraph() {}
		virtual int numberOfVertices() const { return ver; }
		virtual int numberOfEdge() const { return edg; }
		virtual bool directed() const { return true; }
		virtual bool weighted() const { return true; }

		virtual void thePosVertices() const {
			std::cout << "current vertices list: ";
			for (auto& vertice : variables) {
				std::cout << vertice << " ";
			}
			std::cout << std::endl;
		}

		virtual bool existsEdge(int i, int j) const {
			if (i < 0 || j < 0 || i >= ver || j >= ver || vt[i][j] == notaccessible) {
				return false;
			}
			else {
				return true;
			}
		}

	protected:
		class none_exist :public std::exception {
		public:
			none_exist() {}
			virtual ~none_exist() {}
			virtual void problem() {
				std::cout << "the element you entered cannot be found" << std::endl;
			}
		};

		class existed :public std::exception {
		public:
			existed() {}
			virtual ~existed() {}
			virtual void problem() {
				std::cout << "the element you entered is existed" << std::endl;
			}
		};

		virtual void insertEdge(int v1, int v2) {
			if (v1 < 0 || v2 < 0 || v1 >= ver || v2 >= ver || v1 == v2) {
				std::cout << "(" << v1 << "," << v2 << ")"
					<< "is not a permissible edge\n";
				exit(EXIT_FAILURE);
			}
			try {
				if (existsEdge(v1, v2)) {
					existed et;
					throw et;
				}
				else {
					++edg;
					_wt weight;
					std::cout << "enter weight:";
					std::cin >> weight;
					vt[v1][v2] = weight;
				}
			}
			catch (existed& et) {
				et.problem();
			}
		}

		virtual void eraseEdge(int v1, int v2) {
			if (v1 >= 0 && v2 >= 0 && v1 < ver && v2 < ver && vt[v1][v2] != notaccessible) {
				vt[v1][v2] = notaccessible;
				--edg;
			}
		}

		virtual int inDegree(int v) const {
			int sum = 0;
			for (int i = 0; i < ver; ++i) {
				if (vt[i][v] != notaccessible)
					++sum;
			}
			return sum;
		}

		virtual int outDegree(int v) const {
			int sum = 0;
			for (int j = 0; j < ver; ++j) {
				if (vt[v][j] != notaccessible)
					++sum;
			}
			return sum;
		}

		virtual int degree(int v) const {
			return inDegree(v) + outDegree(v);
		}

	public:
		virtual int degree(T _variable_name) {
			try {
				int v = return_mapped_index(_variable_name);
				return inDegree(v) + outDegree(v);
			}
			catch (none_exist& ne) {
				ne.problem();
				return 0;
			}
		}

		virtual int in_degree(T _variable_name) {
			try {
				int v = return_mapped_index(_variable_name);
				return inDegree(v);
			}
			catch (none_exist& ne) {
				ne.problem();
				return 0;
			}
		}

		virtual int out_degree(T _variable_name) {
			try {
				int v = return_mapped_index(_variable_name);
				return outDegree(v);
			}
			catch (none_exist& ne) {
				ne.problem();
				return 0;
			}
		}

		virtual void insert_edge(T _1_variable_name, T _2_variable_name) {
			try {
				int v1 = return_mapped_index(_1_variable_name);
				int v2 = return_mapped_index(_2_variable_name);
				insertEdge(v1, v2);
			}
			catch (none_exist& ne) {
				ne.problem();
			}
		}

		virtual void erase_edge(T _1_variable_name, T _2_variable_name) {
			try {
				int v1 = return_mapped_index(_1_variable_name);
				int v2 = return_mapped_index(_2_variable_name);
				eraseEdge(v1, v2);
			}
			catch (none_exist& ne) {
				ne.problem();
			}
		}

		virtual void change_weight(T _1_variable_name, T _2_variable_name) {
			try {
				int v1 = return_mapped_index(_1_variable_name);
				int v2 = return_mapped_index(_2_variable_name);
				if (!existsEdge(v1, v2)) {
					none_exist ne;
					throw ne;
				}
				_wt changedweight;
				std::cout << "enter changed weight:";
				std::cin >> changedweight;
				vt[v1][v2] = changedweight;
			}
			catch (none_exist& ne) {
				ne.problem();
			}
		}

		virtual void erase_vertice(T _variable_name) {
			try {
				int v = return_mapped_index(_variable_name);
				variables.erase(variables.begin() + v);
				for (int i = 0; i < ver && i != v; ++i) {
					vt[i].erase(vt[i].begin() + v);
				}
				vt.erase(vt.begin() + v);
				--ver;
			}
			catch (none_exist& ne) {
				ne.problem();
			}
		}

		virtual void insert_vertice(T _variable_name) {
			try {
				auto iter = std::find(variables.begin(), variables.end(), _variable_name);
				if (iter != variables.end()) {
					existed et;
					throw et;
				}
				variables.push_back(_variable_name);
				for (int i = 0; i < ver; ++i) {
					vt[i].push_back(notaccessible);
				}
				vt.push_back(std::vector<_wt>(ver + 1, notaccessible));
				++ver;
			}
			catch (existed& et) {
				et.problem();
			}
		}

		virtual bool topologicalOrder(std::vector<T>& nums) {
			int n = numberOfVertices();
			nums.resize(n);
			std::vector<int> indegree(n, 0);
			for (int i = 0; i < n; ++i) {
				indegree[i] = inDegree(i);
			}
			std::queue<int> q;
			for (int i = 0; i < n; ++i) {
				if (indegree[i] == 0)
					q.push(i);
			}
			int theVertex = 0;
			while (!q.empty()) {
				int currentVertex = q.front();
				q.pop();
				nums[theVertex++] = variables[currentVertex];
				for (int j = 0; j < n; ++j) {
					if (vt[currentVertex][j] != notaccessible) {
						--indegree[j];
						if (indegree[j] == 0)
							q.push(j);
					}
				}
			}
			return theVertex == n;
		}

	protected:
		virtual void bfs(int v, std::vector<T>& res) {
			res.clear();
			int n = numberOfVertices();
			std::vector<bool> visited(n, false);
			std::queue<int> q;
			visited[v] = true;
			q.push(v);
			while (!q.empty()) {
				int theVertex = q.front();
				res.push_back(variables[theVertex]);
				q.pop();
				for (int j = 0; j < n; ++j) {
					if (vt[theVertex][j] != notaccessible && visited[j] == false) {
						q.push(j);
						visited[j] = true;
					}
				}
			}
		}

		virtual void dfs(int v, std::vector<T>& res, std::vector<bool>& visited) {
			visited[v] = true;
			res.push_back(variables[v]);
			for (int j = 0; j < numberOfVertices(); ++j) {
				if (vt[v][j] != notaccessible && visited[j] == false)
					dfs(j, res, visited);
			}
		}
	public:
		virtual void BFS(T  _variable_name, std::vector<T>& res) {
			try {
				int v = return_mapped_index(_variable_name);
				bfs(v, res);
			}
			catch (none_exist& ne) {
				ne.problem();
			}
		}

		virtual void DFS(T  _variable_name, std::vector<T>& res) {
			try {
				res.clear();
				std::vector<bool> visited(numberOfVertices(), false);
				int v = return_mapped_index(_variable_name);
				dfs(v, res, visited);
			}
			catch (none_exist& ne) {
				ne.problem();
			}
		}

	protected:
		// Dijkstra算法
		virtual void shortestPaths(int sourceVertex, std::vector<_wt>& distanceFromSource, std::vector<int>& predecessor) {
			int n = numberOfVertices();
			if (sourceVertex < 0 || sourceVertex >= n) {
				std::cout << "Invalid source vertex\n";
				exit(EXIT_FAILURE);
			}
			std::list<int> newReachableVertices;
			for (int i = 0; i < n; ++i) {
				distanceFromSource[i] = vt[sourceVertex][i];
				if (distanceFromSource[i] == notaccessible) {
					predecessor[i] = -1;
				}
				else {
					predecessor[i] = sourceVertex;
					newReachableVertices.push_back(i);
				}
			}
			distanceFromSource[sourceVertex] = 0;
			predecessor[sourceVertex] = -2;
			while (!newReachableVertices.empty()) {
				std::list<int>::iterator inewReachableVertices = newReachableVertices.begin();
				std::list<int>::iterator theEnd = newReachableVertices.end();
				std::list<int>::iterator vposnewReachableVertices;
				int v = *inewReachableVertices;
				while (inewReachableVertices != theEnd) {
					int w = *inewReachableVertices;
					++inewReachableVertices;
					v = distanceFromSource[w] < distanceFromSource[v] ? w : v;
					vposnewReachableVertices = std::find(newReachableVertices.begin(), newReachableVertices.end(), v);
				}
				newReachableVertices.erase(vposnewReachableVertices);
				for (int j = 0; j < n; ++j) {
					if (vt[v][j] != notaccessible && (predecessor[j] == -1 || distanceFromSource[j] > distanceFromSource[v] + vt[v][j])) {
						distanceFromSource[j] = distanceFromSource[v] + vt[v][j];
						if (predecessor[j] == -1)
							newReachableVertices.push_back(j);
						predecessor[j] = v;
					}
				}
			}
		}
	public:
		virtual _wt shortestPaths(T _1_variable_name, T _2_variable_name) {
			try {
				int n = numberOfVertices();
				int v1 = return_mapped_index(_1_variable_name);
				int v2 = return_mapped_index(_2_variable_name);
				std::vector<_wt> distanceFromSource(n);
				std::vector<int> predecessor(n);
				shortestPaths(v1, distanceFromSource, predecessor);
				if (distanceFromSource[v2] == notaccessible) {
					std::cout << "no path can be to connect " << _1_variable_name << " with "
						<< _2_variable_name << std::endl;
					return distanceFromSource[v2];
				}
				std::vector<int> res;
				int v = v2;
				while (true) {
					res.push_back(predecessor[v]);
					v = predecessor[v];
					if (predecessor[v] == -2) break;
				}
				std::reverse(res.begin(), res.end());
				std::cout << "the shortest path is ";
				for (auto ans : res) {
					std::cout << variables[ans] << " -> ";
				}
				std::cout << variables[v2] << std::endl;
				return distanceFromSource[v2];
			}
			catch (none_exist& ne) {
				ne.problem();
				return notaccessible;
			}
		}

		// Floyd算法
		virtual void allPairs(std::vector<std::vector<_wt>>& c, std::vector<std::vector<int>>& kay) {
			int n = numberOfVertices();
			std::vector<_wt> temp(n);
			c.resize(n, temp);
			kay.resize(n, std::vector<int>(n));
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					c[i][j] = vt[i][j];
					kay[i][j] = 0;
				}
				c[i][i] = 0;
			}
			for (int k = 0; k < n; ++k) {
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < n; ++j) {
						if (c[i][k] != notaccessible && c[k][j] != notaccessible &&
							(c[i][j] == notaccessible || c[i][j] > c[i][k] + c[k][j])) {
							c[i][j] = c[i][k] + c[k][j];
							kay[i][j] = k;
						}
					}
				}
			}
		}

		virtual void outputPath(std::vector<std::vector<_wt>>& c, std::vector<std::vector<int>>& kay, int start, int end) {
			try {
				int i = return_mapped_index(start);
				int j = return_mapped_index(end);
				if (c[i][j] == notaccessible) {
					std::cout << "There is no path from " << variables[i] << " to " << variables[j] << std::endl;
				}
				else {
					std::cout << "The path is " << variables[i] << " ";
					outputPath(kay, i, j);
					std::cout << "\nthe shorest length is " << c[i][j];
					std::cout << std::endl;
				}
			}
			catch (none_exist& ne) {
				ne.problem();
			}
		}

	protected:
		virtual void outputPath(std::vector<std::vector<int>>& kay, int i, int j) {
			if (i == j) return;
			if (kay[i][j] == 0) {
				std::cout << variables[j] << " ";
			}
			else {
				outputPath(kay, i, kay[i][j]);
				outputPath(kay, kay[i][j], j);
			}
		}
	protected:
		int ver;
		int edg;
		std::vector<std::vector<_wt>> vt;
		std::vector<T> variables;
		const int notaccessible = INT32_MAX;
		int return_mapped_index(T& key) {
			if (std::find(variables.begin(), variables.end(), key) == variables.end()) {
				none_exist ne;
				throw ne;
			}
			return std::find(variables.begin(), variables.end(), key) - variables.begin();
		}
	};
}

#endif // !_GRAPH_H_
