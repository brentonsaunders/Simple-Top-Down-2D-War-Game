#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include <sstream>
#include "AStar.h"

using namespace std;

AStar::AStar(const TileMap& tileMap) {
	latency = 0;

	width = tileMap.getWidth();
	height = tileMap.getHeight();

	if (width <= 0 || height <= 0) {
		throw AStarMapIsEmptyException();
	}

	for (int y = 0; y < height; ++y) {
		vector<AStarNode> row;

		for (int x = 0; x < width; ++x) {
			AStarNode node;

			node.x = x;
			node.y = y;
			node.weight = tileMap.get(x, y);
			node.isTraversable = node.weight >= 0;

			row.push_back(node);
		}

		nodes.push_back(row);
	}
}

AStar::~AStar() {

}

bool AStar::findPath(int xStart, int yStart, int xEnd, int yEnd) {
	if (xStart < 0 || yStart < 0 || xEnd < 0 || yEnd < 0 ||
		xStart >= width || yStart >= height || xEnd >= width || yEnd >= height) {
		throw AStarOutOfBoundsException();
	}

	DWORD then = timeGetTime();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			nodes[y][x].g = 0;
			nodes[y][x].h = euclidean(x, y, xEnd, yEnd);
			nodes[y][x].list = 0;
			nodes[y][x].parent = NULL;
		}
	}

	vector<AStarNode*> openList;

	AStarNode *startNode = &nodes[yStart][xStart];

	endNode = NULL;

	startNode->list = OPEN_LIST;

	openList.push_back(startNode);

	struct AStarNodeCompare {
		inline bool operator()(const AStarNode* a, const AStarNode* b) {
			return (a->g + a->h) < (b->g + b->h);
		}
	};

	bool foundPath = false;

	while (!foundPath && openList.size() > 0) {
		sort(openList.begin(), openList.end(), AStarNodeCompare());

		AStarNode* node = openList[0];

		if (node->x == xEnd && node->y == yEnd) {
			endNode = &nodes[yEnd][xEnd];

			foundPath = true;

			continue;
		}

		node->list = CLOSED_LIST;

		openList.erase(remove(openList.begin(), openList.end(), node), openList.end());

		vector<AStarNode*> neighbors = getNeighbors(node);
		int size = (int)neighbors.size();

		for (int i = 0; i < size; ++i) {
			AStarNode* neighbor = neighbors[i];

			if (neighbor->list == OPEN_LIST && node->x < neighbor->g) {
				neighbor->parent = node;
				neighbor->g = node->g + neighbor->weight;
			}
			else if(neighbor->list == 0) {
				neighbor->parent = node;
				neighbor->g = node->g + neighbor->weight;
				neighbor->list = OPEN_LIST;

				openList.push_back(neighbor);
			}
		}
	}

	DWORD now = timeGetTime();

	latency = now - then;

	return foundPath;
}

AStarPath AStar::getPath() const {
	AStarNode* node = endNode;
	stack<AStarNode> nodes;

	while (node) {
		nodes.push(*node);

		node = node->parent;
	}

	return AStarPath(nodes);
}

DWORD AStar::getLatency() {
	return latency;
}

double AStar::manhattan(int xStart, int yStart, int xEnd, int yEnd) {
	return abs(xStart - xEnd) + abs(yStart - yEnd);
}

double AStar::euclidean(int xStart, int yStart, int xEnd, int yEnd) {
	return sqrt(pow(xStart - xEnd, 2) + pow(yStart - yEnd, 2));
}

vector<AStar::AStarNode*> AStar::getNeighbors(AStarNode* node) {
	vector<AStarNode*> neighbors;
	int x = node->x;
	int y = node->y;

	for (int yy = y - 1; yy <= y + 1; ++yy) {
		for (int xx = x - 1; xx <= x + 1; ++xx) {
			if (xx < 0 || yy < 0 || xx >= width || yy >= height) {
				continue;
			}

			if (!nodes[yy][xx].isTraversable) {
				continue;
			}

			neighbors.push_back(&nodes[yy][xx]);
		}
	}


	return neighbors;
}

AStarPath::AStarPath(stack<AStar::AStarNode> nodes) {
	while (!nodes.empty()) {
		this->nodes.push_back(nodes.top());

		nodes.pop();
	}
}

AStarPath::~AStarPath() {}

std::vector<AStar::AStarNode> AStarPath::getNodes() const {
	return nodes;
}

string AStarPath::toString() const {
	stringstream ss;
	int size = (int)nodes.size();

	for (int i = 0; i < size; ++i) {
		ss << nodes[i].getX() << "," << nodes[i].getY() << endl;
	}

	return ss.str();
}
