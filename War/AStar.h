#pragma once

#include <exception>
#include <vector>
#include <stack>
#include <string>
#include "TileMap.h"

class AStarPath;

class AStar {
public:
	class AStarNode {
		friend class AStar;
	public:
		int getX() const { return x; }
		int getY() const { return y; }
	private:
		AStarNode* parent;
		int x, y;
		double g;
		double h;
		int weight;
		int list;
		bool isTraversable;
	};


	AStar(const TileMap<int>&);
	~AStar();
	bool findPath(int, int, int, int);
	AStarPath getPath() const;
	DWORD getLatency();

private:
	static const int OPEN_LIST = 1;
	static const int CLOSED_LIST = 2;

	int width, height;
	std::vector<std::vector<AStarNode>> nodes;
	AStarNode* endNode;
	DWORD latency;

	double manhattan(int, int, int, int);
	double euclidean(int, int, int, int);
	std::vector<AStarNode*> getNeighbors(AStarNode*);
};

class AStarPath {
public:
	AStarPath(std::stack<AStar::AStarNode>);
	~AStarPath();
	std::vector<AStar::AStarNode> getNodes() const;
	std::string toString() const;

private:
	std::vector<AStar::AStarNode> nodes;
};

class AStarMapIsEmptyException : std::exception {};
class AStarOutOfBoundsException : std::exception {};