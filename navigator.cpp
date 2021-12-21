#include <iostream>
#include <vector>
#include "navigator.h"
using namespace std;



Node::Node(int _x, int _y, char _name) {  // Конструктор инициализации.
	x = _x;
	y = _y;
	name = _name;
	visited = false;
	mark = -1;
}
int Node::getX() const {
	return x;
}
int Node::getY() const {
	return y;
}
char Node::getName() const {
	return name;
}
void Node::printInfo() const {
	std::cout << name << " " << x << "," << y << std::endl;
}
bool Node::isVisited() const {
	return visited;
}
int Node::getMark() const {
	return mark;
}
void Node::visit() {
	visited = true;
}
void Node::unvisit() {
	visited = false;
}
void Node::setMark(int _mark) {
	mark = _mark;
}

// Функция сложения маршрутов.
Route operator+(Route& leftRoute, Route& rightRoute) {
	Route tempRoute;
	for (int i = 0; i < leftRoute.roads.size(); i++) {
		tempRoute.roads.emplace_back(leftRoute.roads[i]);
	}
	for (int i = 0; i < rightRoute.roads.size(); i++) {
		tempRoute.roads.emplace_back(rightRoute.roads[i]);
	}
	return tempRoute;
}

vector<class Node> getInitialNodes(vector<vector<char>>& map) {
	vector<class Node> nodes;
	char c;
	for (int i = 0; c != '#' && c != EOF; i++) {
		c = 0;
		// cout << "test4" << endl;
		for (int j = 0; c != '\n' && c != EOF && c != '#'; j++) {
			// cout << "test3" << endl;
			c = map[i][j];
			if (c >= 'A' && c <= 'Z') {
				nodes.push_back(Node(i, j, c));
			}
		}
	}
	return nodes;
}

int getNumber(vector<class Node>& nodes, char name) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == name) return i;
	}
	return 0;
}

bool isNameValid(vector<class Node>& nodes, char c) {  // Проверка валидности имени узла
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].getName() == c) return true;
	}
	return false;
	// В случае успеха вернет переданный символ, в случае неудачи - 0
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

vector<vector<class Route>> getRoads(vector<vector<char>>& map, vector<class Node>& nodes) {
	vector<vector<class Route>> roads(nodes.size(), vector<class Route> (nodes.size(), Route(Road('0', 0))));
	// cout << "test1\n";
	// cout << "Test4" << endl;
	char c;
	for (int i = 0; i < nodes.size(); i++) {  // Проходим по всем узлам
		int currentX = nodes[i].getX();
		int currentY = nodes[i].getY();
		// cout << nodes[i].getName() << " " << nodes[i].getX() << " " << nodes[i].getY() << endl;
		char roadName;
		if (map[currentX][currentY+1] > 'a' && map[currentX][currentY+1] < 'z') {
			roadName = map[currentX][currentY+1];
			do {  // Идём до ближайшего узла справа
				currentY++;
				c = map[currentX][currentY];
				// cout << "tes2\n";
			} while (c == roadName);
			if (c >= 'A' && c <= 'Z') {
				int j = 0;
				// Следующий цикл делает j равным номеру встреченного узла.
				for (j = 0; j < nodes.size(); j++) if (c == nodes[j].getName()) break;
				roads[i][j] = Route(Road(roadName, abs(currentY - nodes[i].getY())));
				// cout << i << ';' << j << " " << roadName << " " << abs(currentY - nodes[i].getY()) << endl;
				roads[j][i] = roads[i][j];
				// cout << "Между пунктами " << nodes[i].getName() << " и " << nodes[j].getName() << " " << roads[i][j] << endl;
			}
		}
		// cout << roadName << endl;
		// cout << currentX << " " << currentY + 1 << endl;

		// cout << "Test5" << endl;
		currentX = nodes[i].getX();
		currentY = nodes[i].getY();
		if (map[currentX+1][currentY] > 'a' && map[currentX+1][currentY] < 'z') {
			roadName = map[currentX+1][currentY];
			do {  // Идём до ближайшего узла снизу
				currentX++;
				c = map[currentX][currentY];
			} while (c == roadName);
			if (c >= 'A' && c <= 'Z') {
				int j = 0;
				for (j = 0; j < nodes.size(); j++) if (c == nodes[j].getName()) break;
				roads[i][j] = Route(Road(roadName, abs(currentX - nodes[i].getX())));
				roads[j][i] = roads[i][j];
				// cout << "Между пунктами " << nodes[i].getName() << " и " << nodes[j].getName() << " " << roads[i][j] << endl;
				// cout << i << ';' << j << " " << roadName << " " << abs(currentX - nodes[i].getX()) << endl;
			}
		}
		// cout << roadName << endl;
		// cout << currentX + 1 << " " << currentY << endl;
	}
	// cout << "test3\n";
	return roads;
}

void printRoads(vector<vector<class Route>>& roads, vector<class Node>& nodes) {
	cout << "########### Карта смежности узлов ###########" << endl;
	cout << "  ";
	for (int i = 0; i < roads.size(); i++) printf("%3c ", nodes[i].getName());
	cout << endl;
	for (int i = 0; i < roads.size(); i++) {
		cout << nodes[i].getName() << " ";
		for (int j = 0; j < roads.size(); j++) {
			if (roads[i][j].getRoads()[0].getName() != '0') {
				printf("\033[42m%3c\033[0m ", roads[i][j].getRoads()[0].getName());
			} else {
				printf("%3c ", roads[i][j].getRoads()[0].getName());
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printNodes(vector<class Node>& nodes) {
	cout << "Обнаружено " << nodes.size() << " узлов" << endl;
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].printInfo();
	}
}



void getRoutes(vector<class Node>& nodes, vector<vector<class Route>>& roads, char from, char to, vector<class Route>& routes, Route& tempRoute) {
	if (!isNameValid(nodes, from) || !isNameValid(nodes, to)) {  // Проверка имен.
		cout << "Передано неверное имя узла" <<  endl;
		exit(2);
	}
	if (from == to) {  // Проверка несовпадения имён.
		cout << "Имя начального и конечного узлов не должны совпадать" << endl;
		exit(3);
	}

	// tempRoute.push_back(nodes[getNumber(nodes, from)]);
	nodes[getNumber(nodes, from)].visit();
	// cout << "Вызов от " << from << " до " << to << endl;
	
	for (int i = 1; i < nodes.size(); i++) {  // Перебираем все пункты.
		// Этот небольшой блок отвечает за то, чтобы был выбран правильный номер узла.
		int n = getNumber(nodes, from) + i;
		if (n > nodes.size() - 1) {
			n = n - nodes.size();  // Теперь n - номер рассматриваемого элемента.
		}
		// cout << "n = " << n << endl;
		if (!nodes[n].isVisited() && roads[getNumber(nodes, from)][n].getRoads()[0].getName() != '0') {  // Если данный пункт ещё не был посещён.
			if (nodes[n].getName() == to) {  // Если оказалось, что мы пришли в нужный пункт.
				nodes[n].visit();
				// tempRoute.push_back(nodes[n]);
				tempRoute = tempRoute + roads[getNumber(nodes, from)][n];
				// cout << "Найден маршрут: ";
				// for (int j = 0; j < nodes.size(); j++) {
				// 	if (nodes[j].isVisited()) cout << nodes[j].getName();
				// }
				// cout << endl;
				nodes[n].unvisit();
				routes.push_back(tempRoute);
				tempRoute.getRoads().pop_back();
			}
			if (nodes[n].getName() != to) {
				// nodes[n].visit();
				getRoutes(nodes, roads, nodes[n].getName(), to, routes, tempRoute);
			}
		}
	}
	// cout << "Вернулись" << endl;
	nodes[getNumber(nodes, from)].unvisit();
	tempRoute.getRoads().pop_back();
}

void printRoute(Route route) {
	for (int i = 0; i < route.getRoads().size(); i++) {
		cout << route.getRoads()[i].getName();
	}
	cout << endl;
}

void printRoutes(vector<class Route>& routes) {
	if (routes.size() != 0) {
		cout << "\033[46mОбнаруженные маршруты (" << routes.size() << ")\033[0m:" << endl << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
	} else if (routes.size() == 0) {
		cout << "\033[46mМаршрутов не обнаружено ;(\033[0m" << endl;
		exit(4);
	}

	for (int i = 0; i < routes.size(); i++) {  // Пока не кончатся маршруты.
		printRoute(routes[i]);
	}
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

// int getDistance(vector<class Node>& globalNodes, vector<class Node>& localNodes, vector<vector<int>>& roads) {
// 	int getNumber(vector<class Node>& nodes, char name);
// 	int length = 0;
// 	for (int i = 0; i < localNodes.size() - 1; i++) {
// 		length += roads[getNumber(globalNodes, localNodes[i].getName())][getNumber(globalNodes, localNodes[i+1].getName())];
// 		// cout << "+" << roads[getNumber(globalNodes, localNodes[i].getName())][getNumber(globalNodes, localNodes[i+1].getName())] << endl;
// 	}
// 	return length;
// }

// void printShortestRoute(vector<vector<class Node>>& routes, vector<class Node>& globalNodes, vector<vector<int>>& roads) {
// 	// if (routes.size() == 0);
// 	void printRoute(vector<class Node> route);
// 	int getDistance(vector<class Node>& globalNodes, vector<class Node>& localNodes, vector<vector<int>>& roads);
// 	int minDistance = getDistance(globalNodes, routes[0], roads);
// 	vector<class Node> shortestRoute = routes[0];
// 	for (int i = 1; i < routes.size(); i++) {
// 		if (getDistance(globalNodes, routes[i], roads) < minDistance) {
// 			minDistance = getDistance(globalNodes, routes[i], roads);
// 			shortestRoute = routes[i];
// 		}
// 	}
// 	cout << "\033[45mРекомендуемый маршрут\033[0m: ";
// 	printRoute(shortestRoute);
// 	cout << "\033[46mДлина данного пути\033[0m: " << minDistance << endl;
	
// }

