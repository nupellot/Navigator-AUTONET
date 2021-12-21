#include <stdlib.h>
#include <vector>
using namespace std;

class Node {  // Узел.
private:
		int x;  // Координаты узла.
		int y;
		int mark;
		char name;  // Имя узла.
		bool visited;  // Вспомогательная переменная.
public:
		Node(int _x, int _y, char _name);
		int getX() const;
		int getY() const;
		char getName() const;
		void printInfo() const;
		bool isVisited() const;
		int getMark() const;
		void visit();
		void unvisit();
		void setMark(int _mark);
};

class Road {  // Дорога. К примеру, d
private:
	char name;  // Имя дороги (Символ, из которого она состоит).
	int length;
public:
	Road(char _name, int _length) {
		name = _name;
		length = _length;
	}
	int getLength() const {
		return length;
	}
	char getName() const {
		return name;
	}
};

class Route {  // Маршрут. К примеру, abcd
private:
	vector<class Road> roads;  // Дороги, из которых состоит маршрут.
public:
	Route () {;}
	Route (Road road) {
		roads.emplace_back(road);
	}
	int getLength() const {
		int length = 0;
		for (int i = 0; i < roads.size(); i++) {
			length += roads[i].getLength();
		}
		return length;
	}
	int getAmountOfRoads() const {
		return roads.size();
	}
	vector<class Road>& getRoads() {
		return roads;
	}
	friend Route operator+(Route& leftRoute, Route& rightRoute);
};



// class route {
// private:
// 	vector<class road> roads;
// public:

// };

// Функция получения номера узла по его имени.
int getNumber(vector<class Nodes>& nodes, char name);

// Проверка корректности имени узла.
bool isNameValid(vector<class Nodes>&, char);

// Функция получения карты из файла
vector<vector<char>> getMapFromFile(char* source);

// Получение списка узлов из считанной карты.
vector<class Node> getInitialNodes(vector<vector<char>>& map);

// Функция печати карты.
void printMap(vector<vector<char>>& map);

// Получение матрицы смежности из карты и списка узлов.
vector<vector<class Route>> getRoads(vector<vector<char>>& map, vector<class Node>& nodes);

// Печать матрицы смежности.
void printRoads(vector<vector<class Route>>& roads, vector<class Node>& nodes);

// Функция печати списка узлов.
void printNodes(vector<class Node>& nodes);
 
void getRoutes(vector<class Node>& nodes, vector<vector<int>>& roads, char from, char to, vector<vector<class Node>>& routes, vector<class Node>& tempRoute);

void printRoutes(vector<vector<class Node>>&);

int getDistance(vector<class Node>&, vector<class Nodes>&, vector<vector<int>>&);

void printShortestRoute(vector<vector<class Node>>&, vector<class Nodes>&, vector<vector<int>>&);

void printRoute(Route route);