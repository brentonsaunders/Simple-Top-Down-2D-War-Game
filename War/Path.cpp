#include <Windows.h>
#include <iostream>
#include "Path.h"

using namespace std;

Path::Path() {}

Path::Path(AStarPath path) {
	std::vector<AStar::AStarNode> nodes = path.getNodes();
	int size = (int)nodes.size();

	for (int i = size - 1; i >= 0; --i) {
		int x = 20 * nodes[i].getX() + 10;
		int y = 20 * nodes[i].getY() + 10;

		this->nodes.push(Vector2(
			20 * nodes[i].getX() + 10,
			20 * nodes[i].getY() + 10
		));
	}
}

Path::~Path() {

}

Vector2 Path::nextNode(Vector2 pos) {
	while (!nodes.empty()) {
		if (nodes.top().distance(pos) > 10) {
			return nodes.top();
		}

		nodes.pop();
	}

	return pos;
}

bool Path::atEnd() {
	return nodes.empty();
}