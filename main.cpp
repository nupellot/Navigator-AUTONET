#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

class node {  // Узел.
	private:
		int x;  // Координаты узла.
		int y;
		char name;
	public:
		node(int _x, int _y, char _name) {  // Конструктор инициализации.
			x = _x;
			y = _y;
			name = _name;
		}
		int getX() {
			return x;
		}
		int getY() {
			return y;
		}
		char getName() {
			return name;
		}
		void printInfo() {
			cout << name << " " << x << "," << y << endl;
		}
};

int main() {
  vector<class node> nodes;

	FILE* initialConfiguration = fopen("initialConfiguration", "r+");
	
	char c;
	int amountOfNodes = 0;
	for (int i = 1; i < 25; i++) {
		c = 0;
		for (int j = 1; c != '\n' && c != EOF; j++) {
			c = fgetc(initialConfiguration);
			if (c >= 'A' && c <= 'Z') {
				amountOfNodes++;
				nodes.push_back(node(i, j, c));
			}
		}
	}

	for (int i = 0; i < amountOfNodes; i++) {
		nodes[i].printInfo();
	}

	// TODO: реализовать распознавание путей между узлами. Например, идти в 4 стороны от каждого узла до того, пока не встретишь новый узел или пустоту.

	fclose(initialConfiguration);
}