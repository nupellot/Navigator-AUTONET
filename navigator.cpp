#include <iostream>
#include <vector>
#include "navigator.h"
using namespace std;



node::node(int _x, int _y, char _name) {  // Конструктор инициализации.
	x = _x;
	y = _y;
	name = _name;
	visited = false;
	mark = -1;
}
int node::getX() const {
	return x;
}
int node::getY() const {
	return y;
}
char node::getName() const {
	return name;
}
void node::printInfo() const {
	std::cout << name << " " << x << "," << y << std::endl;
}
bool node::isVisited() const {
	return visited;
}
int node::getMark() const {
	return mark;
}
void node::visit() {
	visited = true;
}
void node::unvisit() {
	visited = false;
}
void node::setMark(int _mark) {
	mark = _mark;
}



vector<class node> getInitialNodes(vector<vector<char>>& map) {
	vector<class node> nodes;
	char c;
	for (int i = 0; c != '#' && c != EOF; i++) {
		c = 0;
		// cout << "test4" << endl;
		for (int j = 0; c != '\n' && c != EOF && c != '#'; j++) {
			// cout << "test3" << endl;
			c = map[i][j];
			if (c >= 'A' && c <= 'Z') {
				nodes.push_back(node(i, j, c));
			}
		}
	}
	return nodes;
}

int getNumber(vector<class node>& nodes, char name) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == name) return i;
	}
	return 0;
}

void printMap(vector<vector<char>>& map) {
	cout << "Считанная карта:" << endl;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			cout << map[i][j];
		}
	}
	cout << endl;
}

vector<vector<char>> getMapFromFile(char* source) {
	FILE* initialConfiguration = fopen(source, "r+");
	if (initialConfiguration == NULL) {
		printf("Couldn't open file\n");
		exit(1);
	}

	vector<vector<char>> map;
	char c = 0;
	for (int i = 0; c != '#' && c != EOF; i++) {  // Пока не кончится карта.
		c = 0;
		map.push_back(vector<char> ());  // Записываем в конец ещё один вектор.
		for (int j = 0; c != '#' && c != EOF && c != '\n'; j++) {  // Пока не кончится строка.
			c = fgetc(initialConfiguration);
			map[i].push_back(c);  // Записываем в конец вектора ещё один символ.
		}
	}
	fclose(initialConfiguration);
	return map;
}

vector<vector<int>> getDistances(vector<vector<char>>& map, vector<class node>& nodes) {
	vector<vector<int>> distances(nodes.size(), vector<int> (nodes.size(), 0));
	// cout << "test1\n";
	char c;
	for (int i = 0; i < nodes.size(); i++) {  // Проходим по всем узлам
		int currentX = nodes[i].getX();
		int currentY = nodes[i].getY();
		do {  // Идём до ближайшего узла справа
			currentX++;
			c = map[currentX][currentY];
			// cout << "tes2\n";
		} while (c == '+');
		if (c >= 'A' && c <= 'Z') {
			int j = 0;
			// Следующий цикл делает j равным номеру встреченного узла.
			for (j = 0; j < nodes.size(); j++) if (c == nodes[j].getName()) break;
			distances[i][j] = currentX - nodes[i].getX();
			distances[j][i] = distances[i][j];
			// cout << "Между пунктами " << nodes[i].getName() << " и " << nodes[j].getName() << " " << distances[i][j] << endl;
		}

		currentX = nodes[i].getX();
		currentY = nodes[i].getY();
		do {  // Идём до ближайшего узла снизу
			currentY++;
			c = map[currentX][currentY];
		} while (c == '+');
		if (c >= 'A' && c <= 'Z') {
			int j = 0;
			for (j = 0; j < nodes.size(); j++) if (c == nodes[j].getName()) break;
			distances[i][j] = currentY - nodes[i].getY();
			distances[j][i] = distances[i][j];
			// cout << "Между пунктами " << nodes[i].getName() << " и " << nodes[j].getName() << " " << distances[i][j] << endl;
		}
	}
	// cout << "test3\n";
	return distances;
}

void printDistances(vector<vector<int>>& distances, vector<class node>& nodes) {
	cout << "########### Карта смежности узлов ###########" << endl;
	cout << "  ";
	for (int i = 0; i < distances.size(); i++) printf("%3c ", nodes[i].getName());
	cout << endl;
	for (int i = 0; i < distances.size(); i++) {
		cout << nodes[i].getName() << " ";
		for (int j = 0; j < distances.size(); j++) {
			if (distances[i][j] != 0) {
				printf("\033[42m%3d\033[0m ", distances[i][j]);
			} else {
				printf("%3d ", distances[i][j]);
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printNodes(vector<class node>& nodes) {
	cout << "Обнаружено " << nodes.size() << " узлов" << endl;
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].printInfo();
	}
}

void getRoutes(vector<class node>& nodes, vector<vector<int>>& distances, char from, char to, vector<vector<class node>>& routes, vector<class node>& tempRoute) {
	bool isNameValid(vector<class node>& nodes, char c);  // Объявление вспомогательной функции.

	if (!isNameValid(nodes, from) || !isNameValid(nodes, to)) {  // Проверка имен.
		cout << "Передано неверное имя узла" <<  endl;
		exit(2);
	}
	if (from == to) {  // Проверка несовпадения имён.
		cout << "Имя начального и конечного узлов не должны совпадать" << endl;
		exit(3);
	}

	tempRoute.push_back(nodes[getNumber(nodes, from)]);
	nodes[getNumber(nodes, from)].visit();
	// cout << "Вызов от " << from << " до " << to << endl;
	
	for (int i = 1; i < nodes.size(); i++) {  // Перебираем все пункты.
		// Этот небольшой блок отвечает за то, чтобы был выбран правильный номер узла.
		int n = getNumber(nodes, from) + i;
		if (n > nodes.size() - 1) {
			n = n - nodes.size();  // Теперь n - номер рассматриваемого элемента.
		}
		// cout << "n = " << n << endl;
		if (!nodes[n].isVisited() && distances[getNumber(nodes, from)][n] != 0) {  // Если данный пункт ещё не был посещён.
			if (nodes[n].getName() == to) {  // Если оказалось, что мы пришли в нужный пункт.
				nodes[n].visit();
				tempRoute.push_back(nodes[n]);
				// cout << "Найден маршрут: ";
				// for (int j = 0; j < nodes.size(); j++) {
				// 	if (nodes[j].isVisited()) cout << nodes[j].getName();
				// }
				// cout << endl;
				nodes[n].unvisit();
				routes.push_back(tempRoute);
				tempRoute.pop_back();
			}
			if (nodes[n].getName() != to) {
				// nodes[n].visit();
				getRoutes(nodes, distances, nodes[n].getName(), to, routes, tempRoute);
			}
		}
	}
	// cout << "Вернулись" << endl;
	nodes[getNumber(nodes, from)].unvisit();
	tempRoute.pop_back();
}

bool isNameValid(vector<class node>& nodes, char c) {  // Проверка валидности имени узла
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == c) return true;
	}
	return false;
	// В случае успеха вернет переданный символ, в случае неудачи - 0
}

void printRoutes(vector<vector<class node>>& routes) {
	if (routes.size() != 0) {
		cout << "\033[46mОбнаруженные маршруты (" << routes.size() << ")\033[0m:" << endl << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
	} else if (routes.size() == 0) {
		cout << "\033[46mМаршрутов не обнаружено ;(\033[0m" << endl;
		exit(4);
	}

	for (int i = 0; i < routes.size(); i++) {  // Пока не кончатся маршруты.
		for (int j = 0; j < routes[i].size(); j++) {  // Пока не кончатся узлы в маршруте.
			cout << routes[i][j].getName();
		}
		cout << endl;
	}
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

int getDistance(vector<class node>& globalNodes, vector<class node>& localNodes, vector<vector<int>>& distances) {
	int getNumber(vector<class node>& nodes, char name);
	int length = 0;
	for (int i = 0; i < localNodes.size() - 1; i++) {
		length += distances[getNumber(globalNodes, localNodes[i].getName())][getNumber(globalNodes, localNodes[i+1].getName())];
		// cout << "+" << distances[getNumber(globalNodes, localNodes[i].getName())][getNumber(globalNodes, localNodes[i+1].getName())] << endl;
	}
	return length;
}

void printShortestRoute(vector<vector<class node>>& routes, vector<class node>& globalNodes, vector<vector<int>>& distances) {
	// if (routes.size() == 0);
	void printRoute(vector<class node> route);
	int getDistance(vector<class node>& globalNodes, vector<class node>& localNodes, vector<vector<int>>& distances);
	int minDistance = getDistance(globalNodes, routes[0], distances);
	vector<class node> shortestRoute = routes[0];
	for (int i = 1; i < routes.size(); i++) {
		if (getDistance(globalNodes, routes[i], distances) < minDistance) {
			minDistance = getDistance(globalNodes, routes[i], distances);
			shortestRoute = routes[i];
		}
	}
	cout << "\033[45mРекомендуемый маршрут\033[0m: ";
	printRoute(shortestRoute);
	cout << "\033[46mДлина данного пути\033[0m: " << minDistance << endl;
	
}

void printRoute(vector<class node> route) {
	for (int i = 0; i < route.size(); i++) {
		cout << route[i].getName();
	}
	cout << endl;
}