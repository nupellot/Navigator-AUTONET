#include <iostream>
#include "navigator.h"
using namespace std;


int main() {
	vector<vector<char>> map;  // Вектор, хранящий вектора из символов.
	map = getMapFromFile((char*)"initialConfiguration");  // Получаем изначальную карту из файла.
	// printMap(map);  // Выводим считанные из файла данные.
	// printMap(map);
	vector<class Node> nodes;  // Создаем массив узлов.
	nodes = getInitialNodes(map);  // Записываем в nodes найденные в map узлы.
	// cout << "TEst1" << endl;
	// printNodes(nodes);  // Выводим обнаруженные узлы.

	vector<vector<class Route>> roads;
	// cout << "TEst2" << endl;  // Карта смежности узлов.
	roads = getRoads(map, nodes);  // Находим все расстояния между узлами.
	// cout << "TEst3" << endl;
	printRoads(roads, nodes);  // Выводим найденные расстояния.

	// vector<vector<vector<class Route>>> routes;  // Массив со всеми маршрутами.
	// vector<class Route> tempRoute;  // Вспомогательная переменная.
	// // cout << "Откуда и куда отправиться? (Пример: A D)" << endl;
	// char from, to;
	// cin >> from >> to;
	// getRoutes(nodes, roads, from, to, routes, tempRoute);  // Записываем в routes все маршруты.
	// printRoutes(routes);  // Выводим все обнаруженные маршруты.
	// printShortestRoute(routes, nodes, distances);  // Выводим самый короткий из найденных маршрутов.

	return 0;
}

