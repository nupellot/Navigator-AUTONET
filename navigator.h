#include <stdlib.h>
#include <vector>
using namespace std;

class node {  // Узел.
	private:
		int x;  // Координаты узла.
		int y;
		int mark;
		char name;  // Имя узла.
		bool visited;  // Вспомогательная переменная
	public:
		node(int _x, int _y, char _name);
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


vector<class node> getInitialNodes(vector<vector<char>>& map);

int getNumber(vector<class node>& nodes, char name);

void printMap(vector<vector<char>>& map);

vector<vector<char>> getMapFromFile(char* source);

vector<vector<int>> getDistances(vector<vector<char>>& map, vector<class node>& nodes);

void printDistances(vector<vector<int>>& distances, vector<class node>& nodes);

void printNodes(vector<class node>& nodes);

void getRoutes(vector<class node>& nodes, vector<vector<int>>& distances, char from, char to, vector<vector<class node>>& routes, vector<class node>& tempRoute);

bool isNameValid(vector<class node>&, char);

void printRoutes(vector<vector<class node>>&);

int getDistance(vector<class node>&, vector<class node>&, vector<vector<int>>&);

void printShortestRoute(vector<vector<class node>>&, vector<class node>&, vector<vector<int>>&);

void printRoute(vector<class node>);