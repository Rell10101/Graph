#pragma once


#include <vector>
#include <stack>
#include <queue>
#include "LinkedList.h"

using namespace std;


// ����� �����
template <typename T>
class Graph
{
	private:
		// �������� ������ �������� ������ ������, ������� ���������
		//� ������� ������ (����� ������) �����
		LinkedList<T> vertexList; // ������ ������
		// ** - ��������� ������(�������). ��������� �� ���������
		
		

		// ������ ��� ������ ������� � �������� �� ������� � ������
		int GetVertexPos(const T& vertex1) const;

public:
	int** edge;  // ������� ���������
	int graphsize; // ����� ������ � �����
	int maxGraphSize; // ������������ ����� ������ � �����
	// ����������� � �������� ������������� ����� ������ maxsize
	Graph(int maxsize = 1);

	// ����������
	~Graph();

	// ��������� ���� �����
	int GetWeight(const T& vertex1, const T& vertex2) const;
	int GetWeightByInd(int ver1, int ver2) const;

	// ��������� ������ �� �������� ������
	vector<T> GetNeighbors(const T& vertex) const;
	//vector<T> GetFolowers(const T& vertex) const;

	// ���������� ������
	int NumberOfVertices() const;

	// ���������� ����
	int NumberOfEdges() const;

	// ������ ����������� �����

	// ������� �������
	void InsertVertex(const T& vertex);

	// ������� �����
	void InsertEdge(const T& vertex1, const T& vertex2, int weight);

	// �������� �������
	void DeleteVertex(const T& vertex);

	// �������� �����
	void DeleteEdge(const T& vertex1, const T& vertex2);

	// ����� � �������
	vector<T> DepthFirstSearch(const T& beginVertex) const;

	// ����� � ������
	vector<T> BreadthFirstSearch(const T& beginVertex) const;


	// �������� ��������
	// ���������� ������ �� ���������� ����� �� ������ ������� �� ������� beginVertex
	vector<T> dijkstra(const T& beginVertex) const;
};


// �����������, �������� ������� ��������� � ���������� graphsize
// �������� ������ ��� ������� ���������
template <typename T>
Graph<T>::Graph(int maxsize)
{
	edge = nullptr;

	if (maxsize <= 0) {
		throw invalid_argument("Wrong max size of graph");
	}
	maxGraphSize = maxsize;

	// ��������� ������ ��� �������
	edge = new int* [maxGraphSize];
	for (int i = 0; i < maxGraphSize; i++) {
		edge[i] = new int[maxGraphSize];
	}

	// ���������� ������� ��������� ������
	for (int i = 0; i < maxGraphSize; i++)
		for (int j = 0; j < maxGraphSize; j++)
			edge[i][j] = 0;

	// ����������� ���������� ������ � ����� = 0
	graphsize = 0;
}

// ����������
template <typename T>
Graph<T>::~Graph() {
	// ���������� ������, ���������� ��� �������
	// ���� ��� ������ ���� ���������
	if (edge != nullptr) {

		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}

		delete[] edge;
	}

}


// ��������� ������� ������� � ������
// ���� ������� ���, �� ���������� -1
template <typename T>
int Graph<T>::GetVertexPos(const T& vertex1) const {
	return vertexList.searchNodeInd(vertex1);
}


// ��������� ���� �����
template <typename T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) const {

	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Vertex is not exist");
	}
	else
		return edge[ver1][ver2];

}

// ��������� ���� ����� �� �������� ������
template <typename T>
int Graph<T>::GetWeightByInd(int ver1, int ver2) const {
	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Vertex is not exist");
	}
	else
		return edge[ver1][ver2];
}

// ���������� ������
template <typename T>
int  Graph<T>::NumberOfVertices() const {
	return graphsize;
}

// ���������� ����
template <typename T>
int Graph<T>::NumberOfEdges() const {
	int res = 0;
	for (int i = 0; i < graphsize; i++) {
		for (int j = 0; j < graphsize; j++) {
			if (edge[i][j] != 0)
				res++;
		}
	}
	return res;
}

// ��������� �������
template <typename T>
vector<T> Graph<T>::GetNeighbors(const T& vertex) const {
	vector<T> v = {};
	int pos = GetVertexPos(vertex);

	if (pos <= -1) {
		throw invalid_argument("Vertex is not exist");
	}
	else {
		for (int i = 0; i < graphsize; i++)
		{
			if (edge[pos][i] != 0)
				v.push_back(vertexList.dataByInd(i));
			else if (edge[i][pos] != 0)
				v.push_back(vertexList.dataByInd(i));
		}
		return v;
	}
}



// ����� ������� �������
template <typename T>
void Graph<T>::InsertVertex(const T& vertex)
{
	// ���������, �������� �� ���� �, ���� ��, ��������� maxGraphSize
	if ((graphsize + 1) == maxGraphSize) {

		int newmaxGraphSize = maxGraphSize * 2;

		// �������� ����� ������� ��������� � ����������� ��������
		int** temp = new int* [newmaxGraphSize];
		for (int i = 0; i < newmaxGraphSize; i++) {
			temp[i] = new int[newmaxGraphSize];
		}

		// ���������� ������� ��������� ������
		for (int i = 0; i < newmaxGraphSize; i++)
			for (int j = 0; j < newmaxGraphSize; j++)
				temp[i][j] = 0;

		// ����������� �������� �� ������ ������� ��������� � ����� 
		for (int i = 0; i < maxGraphSize; i++)
		{
			for (int j = 0; j < maxGraphSize; j++)
			{
				temp[i][j] = edge[i][j];
			}
		}

		// ������������ ������ ������ ������� ���������
		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}
		delete[] edge;

		// ��������� ���� ������
		edge = temp;
		maxGraphSize = newmaxGraphSize;
	}

	// ���������� ����� ������� � ������ ������
	vertexList.addNode(vertex);

	// ���������� ���� ���������� ������ �����
	graphsize++;
}


// ������� ������� �� ������ ������ � ��������������� �������
// ���������, ������ ������������� ���� ������� �����
template <typename T>
void Graph<T>::DeleteVertex(const T& vertex)
{
	// �������� ������� ������� � ������ ������
	int pos = GetVertexPos(vertex);
	//int row, col;
	// ���� ����� ������� ���, �������� �� ���� � ������� ����������
	if (pos == -1)
	{
		throw invalid_argument("Vertex is not exist");
	}

	// ������� ������� � ��������� graphsize
	vertexList.removeNode(vertex);

	

	int i = 0;
	// removing the vertex
	while (pos < graphsize) {
		// shifting the rows to left side
		for (i = 0; i < graphsize; ++i) {
			edge[i][pos] = edge[i][pos + 1];
		}

		// shifting the columns upwards
		for (i = 0; i < graphsize; ++i) {
			edge[pos][i] = edge[pos + 1][i];
		}
		pos++;
	}

	// decreasing the number of vertices
	graphsize = vertexList.ListSize();

}


// ������� �����
template <typename T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2, int weight) {
	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Vertex is not exist");
	}
	else {
		edge[ver1][ver2] = weight;
	}

}

// �������� �����
template <typename T>
void Graph<T>::DeleteEdge(const T& vertex1, const T& vertex2) {
	int ver1 = GetVertexPos(vertex1);
	int ver2 = GetVertexPos(vertex2);

	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Vertex is not exist");
	}
	else {
		edge[ver1][ver2] = 0;
	}
}



// ������ �����

// ����� � �������(�� ������ �����)
template <typename T>
vector<T> Graph<T>::DepthFirstSearch(const T& beginVertex) const {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("Vertex is not exist");
	}

	// ���� ��� ���������� �������� ������, ��������� ���������
	stack<T> st;

	// pass - ������ ���������� ������. 
	// neighbours �������� �������, ������� � �������
	vector<T> pass = {}, neighbours = {};

	T vertex1;

	st.push(beginVertex);

	// ���������� �����, ���� �� �������� ����
	while (!st.empty()) {
		// ���������� ������ �������� ��������
		vertex1 = st.top();
		// ��� ��������
		st.pop();
		// ���� ������� ��� �� ���� �������� (�� ��������� � ������ ���������� ������ pass)
		// ������� std::find() ���� �� ������������ ��������� ��������� ������������ ��������.
		// std::begin ���������� ��������� �� ������ �������, � std::end ��������� �� ������������ ������� �� ������ �������
		// ��� ��������� ��������� � ������� ���������� �������� �� ������ � ����� ��������� � ��������, ������� ���� �����. ��������� ������� - �������� �� ��������� ��������. 
		// ���� �� �������� �� �������, �� ������������ �������� ��������� �� ����� ���������. 
		if (find(pass.begin(), pass.end(), vertex1) == pass.end()) {
			//�������� ������� � pass
			pass.push_back(vertex1);

			//� ����� �������� ��� ������� � ��� �������
			neighbours = GetNeighbors(vertex1);

			// ��������� ��� ������� ������� � ����
			for (T item : neighbours) {
				st.push(item);
			}
		}
	}
	// ���������� �������� ������
	return pass;
}




// ����� � ������(�� ������ �������)
template <typename T>
vector<T> Graph<T>::BreadthFirstSearch(const T& beginVertex) const {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("Vertex is not exist");
	}

	// ������� ��� ���������� �������� ������, ��������� ���������
	queue<T> qu;

	// pass - ������ ���������� ������
	// neighbours �������� �������, ������� � �������
	vector<T> pass = {}, neighbours = {};

	T vertex1;

	qu.push(beginVertex);

	// ���������� �����, ���� �� �������� �������
	while (!qu.empty()) {
		// ���������� ������� ��������
		vertex1 = qu.front();
		// ��� ��������, ����� �� ��������� �������� ����� ���� �������� ���������(i+1) �������
		qu.pop();
		// ���� ������� ��� �� ���� �������� (�� ��������� � ������ ���������� ������ pass)
		if (find(pass.begin(), pass.end(), vertex1) == pass.end()) {
			//�������� ������� � pass
			pass.push_back(vertex1);

			//� ����� �������� ��� ������� � ��� �������
			neighbours = GetNeighbors(vertex1);

			// ��������� ��� ������� ������� � �������(� �����)
			for (T item : neighbours) {
				qu.push(item);
			}
		}
	}
	// ���������� �������� ������
	return pass;
}



// �������� ��������
// ���������� ������ �� ���������� ����� �� ������ ������� �� ������� beginVertex
template <typename T>
vector<T> Graph<T>::dijkstra(const T& beginVertex) const {
	int pos = GetVertexPos(beginVertex);
	if (pos == -1) {
		throw invalid_argument("Vertex is not exist");
	}

	vector<int> distant; // ������ ���������� ���������
	vector<bool> pass; // ������ ���������

	// ������ ������� �� V ���������� ����� � ����������� 
	// ��������� ���������� �� ���� ������� �� a.
	// ����� ����� ������� a ���������� ������ 0, 
	// ����� ��������� ������ � �������������
	// 
	// ���������� ���������� �� ������ ���������� (INT_MAX)
	// ��� ������� �� �������� (false)
	for (int i = 0; i < NumberOfVertices(); i++) {
		distant.push_back(INT_MAX);
		pass.push_back(false);
	}
	distant[pos] = 0; // ���������� �� ������� �� ����� ���� ����� 0

	// ��������� ��� ���� ������ �����
	for (int k = 0; k < NumberOfVertices(); k++) {
		// ��� ������ ������� ������� ���������� �� ���� ������ ������ �� ������� ���������
		for (int i = 0; i < NumberOfVertices(); i++) {
			int weight = GetWeightByInd(pos, i);

			if (weight < 0) {
				throw invalid_argument("Dijkstra�s algorithm don't support weight < 0");
			}

			// ���� ���� �� ������� ����, ���� ������� ��� �� ���� �������� �
			// ���� ������� ������� ���������� �� ������ �������
			if ((weight != 0) && (pass[i] == false) && ((distant[pos] + weight) < distant[i])) {
				distant[i] = distant[pos] + weight; // ���������� ����� �������� ����������� ����
			}
		}
		// ������� ��������, ����� �� ������� ��������� ���� ��������� ��� ������� ������������ ������
		pass[pos] = true;

		// ������� ������ � ����������� ��������� ���������� �� ������ ������
		// (�� ��������������� ������)
		int min1 = INT_MAX;
		for (int j = 0; j < NumberOfVertices(); j++) {
			if ((distant[j] < min1) && (pass[j] == false)) {
				pos = j; // ���������� ������ ������ �������
				// �� �� ����������� ����� ���������� ����� �� ��������� ������
			}
		}

	}
	return distant;

}