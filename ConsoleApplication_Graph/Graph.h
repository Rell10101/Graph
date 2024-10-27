#pragma once


#include <vector>
#include <stack>
#include <queue>
#include "LinkedList.h"

using namespace std;


// класс Графа
template <typename T>
class Graph
{
	private:
		// основные данные включают список вершин, матрицу смежности
		//и текущий размер (число вершин) графа
		LinkedList<T> vertexList; // список вершин
		// ** - двумерный массив(матрица). Указатель на указатель
		
		

		// методы для поиска вершины и указания ее позиции в списке
		int GetVertexPos(const T& vertex1) const;

public:
	int** edge;  // матрица смежности
	int graphsize; // число вершин в графе
	int maxGraphSize; // максимальное число вершин в графе
	// конструктор с заданием максимального числа вершин maxsize
	Graph(int maxsize = 1);

	// деструктор
	~Graph();

	// получение веса ребра
	int GetWeight(const T& vertex1, const T& vertex2) const;
	int GetWeightByInd(int ver1, int ver2) const;

	// получение списка из соседних вершин
	vector<T> GetNeighbors(const T& vertex) const;
	//vector<T> GetFolowers(const T& vertex) const;

	// количество вершин
	int NumberOfVertices() const;

	// количество рёбер
	int NumberOfEdges() const;

	// методы модификации графа

	// вставка вершины
	void InsertVertex(const T& vertex);

	// вставка ребра
	void InsertEdge(const T& vertex1, const T& vertex2, int weight);

	// удаление вершины
	void DeleteVertex(const T& vertex);

	// удаление ребра
	void DeleteEdge(const T& vertex1, const T& vertex2);

	// обход в глубину
	vector<T> DepthFirstSearch(const T& beginVertex) const;

	// обход в ширину
	vector<T> BreadthFirstSearch(const T& beginVertex) const;


	// алгоритм Дейкстры
	// возвращает вектор из кратчайших путей до каждой вершины из вершины beginVertex
	vector<T> dijkstra(const T& beginVertex) const;
};


// конструктор, обнуляет матрицу смежности и переменную graphsize
// выделяет память под матрицу смежности
template <typename T>
Graph<T>::Graph(int maxsize)
{
	edge = nullptr;

	if (maxsize <= 0) {
		throw invalid_argument("Wrong max size of graph");
	}
	maxGraphSize = maxsize;

	// выделение памяти под матрицу
	edge = new int* [maxGraphSize];
	for (int i = 0; i < maxGraphSize; i++) {
		edge[i] = new int[maxGraphSize];
	}

	// заполнение матрицы смежности нулями
	for (int i = 0; i < maxGraphSize; i++)
		for (int j = 0; j < maxGraphSize; j++)
			edge[i][j] = 0;

	// фактическое количество вершин в графе = 0
	graphsize = 0;
}

// деструктор
template <typename T>
Graph<T>::~Graph() {
	// освободить память, выделенную под матрицу
	// если эта память была выделенна
	if (edge != nullptr) {

		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}

		delete[] edge;
	}

}


// получение индекса вершины в списке
// если вершины нет, то возвращает -1
template <typename T>
int Graph<T>::GetVertexPos(const T& vertex1) const {
	return vertexList.searchNodeInd(vertex1);
}


// получение веса ребра
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

// получение веса ребра по индексам вершин
template <typename T>
int Graph<T>::GetWeightByInd(int ver1, int ver2) const {
	if ((ver1 == -1) || (ver2 == -1)) {
		throw invalid_argument("Vertex is not exist");
	}
	else
		return edge[ver1][ver2];
}

// количество вершин
template <typename T>
int  Graph<T>::NumberOfVertices() const {
	return graphsize;
}

// количество рёбер
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

// получение соседей
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



// метод вставки вершины
template <typename T>
void Graph<T>::InsertVertex(const T& vertex)
{
	// проверить, заполнен ли граф и, если да, увеличить maxGraphSize
	if ((graphsize + 1) == maxGraphSize) {

		int newmaxGraphSize = maxGraphSize * 2;

		// создадим новую матрицу смежности с увеличенным размером
		int** temp = new int* [newmaxGraphSize];
		for (int i = 0; i < newmaxGraphSize; i++) {
			temp[i] = new int[newmaxGraphSize];
		}

		// заполнение матрицы смежности нулями
		for (int i = 0; i < newmaxGraphSize; i++)
			for (int j = 0; j < newmaxGraphSize; j++)
				temp[i][j] = 0;

		// копирование значений из старой матрицы смежности в новую 
		for (int i = 0; i < maxGraphSize; i++)
		{
			for (int j = 0; j < maxGraphSize; j++)
			{
				temp[i][j] = edge[i][j];
			}
		}

		// освобождение памяти старой матрицы смежности
		for (int i = 0; i < maxGraphSize; i++) {
			delete[] edge[i];
		}
		delete[] edge;

		// обновляем поля класса
		edge = temp;
		maxGraphSize = newmaxGraphSize;
	}

	// добавление новой вершину в список вершин
	vertexList.addNode(vertex);

	// обновление поля количества вершин графа
	graphsize++;
}


// удалить вершину из списка вершин и скорректировать матрицу
// смежности, удалив принадлежащие этой вершине ребра
template <typename T>
void Graph<T>::DeleteVertex(const T& vertex)
{
	// получить позицию вершины в списке вершин
	int pos = GetVertexPos(vertex);
	//int row, col;
	// если такой вершины нет, сообщить об этом и вернуть управление
	if (pos == -1)
	{
		throw invalid_argument("Vertex is not exist");
	}

	// удалить вершину и уменьшить graphsize
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


// вставка ребра
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

// удаление ребра
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



// Обходы графа

// обход в глубину(на основе стека)
template <typename T>
vector<T> Graph<T>::DepthFirstSearch(const T& beginVertex) const {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("Vertex is not exist");
	}

	// стек для временного хранения вершин, ожидающих обработки
	stack<T> st;

	// pass - список пройденных вершин. 
	// neighbours содержит вершины, смежные с текущей
	vector<T> pass = {}, neighbours = {};

	T vertex1;

	st.push(beginVertex);

	// продолжать обход, пока не опустеет стек
	while (!st.empty()) {
		// сохранение самого верхнего элемента
		vertex1 = st.top();
		// его удаление
		st.pop();
		// если вершина ещё не была пройдена (не находится в списке пройденных вершин pass)
		// Функция std::find() ищет на определенном диапазоне элементов определенное значение.
		// std::begin возвращает указатель на начало массива, а std::end указатель на воображаемый элемент за концом массива
		// Для установки диапазона в функцию передаются итератор на начало и конец диапазона и значение, которое надо найти. Результат функции - итератор на найденное значение. 
		// Если же значение не найдено, то возвращаемый итератор указывает на конец диапазона. 
		if (find(pass.begin(), pass.end(), vertex1) == pass.end()) {
			//включить вершину в pass
			pass.push_back(vertex1);

			//а также получить все смежные с ней вершины
			neighbours = GetNeighbors(vertex1);

			// поместить все смежные вершины в стек
			for (T item : neighbours) {
				st.push(item);
			}
		}
	}
	// возвратить выходной список
	return pass;
}




// обход в ширину(на основе очереди)
template <typename T>
vector<T> Graph<T>::BreadthFirstSearch(const T& beginVertex) const {

	if (GetVertexPos(beginVertex) == -1) {
		throw invalid_argument("Vertex is not exist");
	}

	// очередь для временного хранения вершин, ожидающих обработки
	queue<T> qu;

	// pass - список пройденных вершин
	// neighbours содержит вершины, смежные с текущей
	vector<T> pass = {}, neighbours = {};

	T vertex1;

	qu.push(beginVertex);

	// продолжать обход, пока не опустеет очередь
	while (!qu.empty()) {
		// сохранение первого элемента
		vertex1 = qu.front();
		// его удаление, чтобы на следующей итерации можно было получить следующий(i+1) элемент
		qu.pop();
		// если вершина ещё не была пройдена (не находится в списке пройденных вершин pass)
		if (find(pass.begin(), pass.end(), vertex1) == pass.end()) {
			//включить вершину в pass
			pass.push_back(vertex1);

			//а также получить все смежные с ней вершины
			neighbours = GetNeighbors(vertex1);

			// поместить все смежные вершины в очередь(в конец)
			for (T item : neighbours) {
				qu.push(item);
			}
		}
	}
	// возвратить выходной список
	return pass;
}



// алгоритм Дейкстры
// возвращает вектор из кратчайших путей до каждой вершины из вершины beginVertex
template <typename T>
vector<T> Graph<T>::dijkstra(const T& beginVertex) const {
	int pos = GetVertexPos(beginVertex);
	if (pos == -1) {
		throw invalid_argument("Vertex is not exist");
	}

	vector<int> distant; // вектор кратчайших растояний
	vector<bool> pass; // вектор посещений

	// Каждой вершине из V сопоставим метку — минимальное 
	// известное расстояние от этой вершины до a.
	// Метка самой вершины a полагается равной 0, 
	// метки остальных вершин — бесконечности
	// 
	// изначально расстояния до вершин неизвестны (INT_MAX)
	// все вершины не посещены (false)
	for (int i = 0; i < NumberOfVertices(); i++) {
		distant.push_back(INT_MAX);
		pass.push_back(false);
	}
	distant[pos] = 0; // расстояние из вершины до самой себя равно 0

	// повторяем для всех вершин графа
	for (int k = 0; k < NumberOfVertices(); k++) {
		// для каждой вершины смотрим расстояние до всех других вершин по матрице смежности
		for (int i = 0; i < NumberOfVertices(); i++) {
			int weight = GetWeightByInd(pos, i);

			if (weight < 0) {
				throw invalid_argument("Dijkstra’s algorithm don't support weight < 0");
			}

			// если путь до вершины есть, если вершина ещё не была посещена и
			// если найдено меньшее расстояние до данной вершины
			if ((weight != 0) && (pass[i] == false) && ((distant[pos] + weight) < distant[i])) {
				distant[i] = distant[pos] + weight; // записываем новое значение кратчайшего пути
			}
		}
		// вершина пройдена, когда по матрице смежности были проверены все вершины относительно данной
		pass[pos] = true;

		// находим индекс с минимальным значением расстояния на данный момент
		// (из непросмотренных вершин)
		int min1 = INT_MAX;
		for (int j = 0; j < NumberOfVertices(); j++) {
			if ((distant[j] < min1) && (pass[j] == false)) {
				pos = j; // запоминаем индекс данной вершины
				// от неё продолжится поиск кратчайших путей до остальных вершин
			}
		}

	}
	return distant;

}