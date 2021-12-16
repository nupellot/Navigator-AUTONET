#include <iostream>
#include "navigator.h"
using namespace std;


int main() {
	vector<vector<char>> map;  // Вектор, хранящий вектора из символов.
	map = getMapFromFile((char*)"initialConfiguration");  // Получаем изначальную карту из файла.
	// printMap(map);  // Выводим считанные из файла данные.

	vector<class node> nodes;  // Создаем массив узлов.
	nodes = getInitialNodes(map);  // Записываем в nodes найденные в map узлы.
	// printNodes(nodes);  // Выводим обнаруженные узлы.

	vector<vector<int>> distances;  // Карта смежности узлов.
	distances = getDistances(map, nodes);  // Находим все расстояния между узлами.
	printDistances(distances, nodes);  // Выводим найденные маршруты.

	vector<vector<class node>> routes;  // Массив со всеми маршрутами.
	vector<class node> tempRoute;  // Вспомогательная переменная.
	cout << "Откуда и куда отправиться? (Пример: A D)" << endl;
	char from, to;
	cin >> from >> to;
	getRoutes(nodes, distances, from, to, routes, tempRoute);  // Записываем в routes все маршруты.
	printRoutes(routes);  // Выводим все обнаруженные маршруты.
	printShortestRoute(routes, nodes, distances);  // Выводим самый короткий из найденных маршрутов.

	return 0;
}

