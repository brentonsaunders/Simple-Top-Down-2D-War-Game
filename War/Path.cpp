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

		this->nodes.push_back(Vector2(
			20 * nodes[i].getX() + 10,
			20 * nodes[i].getY() + 10
		));
	}
}

Path::Path(const Path& path) {
	this->nodes = path.nodes;
}

Path::Path(const std::vector<Vector2>& nodes) {
	int size = (int)nodes.size();

	for (int i = size - 1; i >= 0; --i) {
		this->nodes.push_back(nodes[i]);
	}
}

Path::Path(const Vector2& pos) {
	nodes.push_back(pos);
}

Path::~Path() {

}

Vector2 Path::nextNode(Vector2 pos, double turnRadius) {
	while (!nodes.empty()) {
		if (nodes.back().distance(pos) > turnRadius) {
			return nodes.back();
		}

		nodes.pop_back();
	}

	return pos;
}

bool Path::atEnd() {
	return nodes.empty();
}