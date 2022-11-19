#include <Windows.h>
#include "Path.h"

using namespace std;

Path::Path(AStarPath path) {
	vector<AStar::AStarNode> aStarNodes = path.getNodes();
	int size = (int)aStarNodes.size();

	for (int i = 0; i < size; ++i) {
		nodes.push_back(Vector2(20 * aStarNodes[i].getX(), 20 * aStarNodes[i].getY()));
	}
}

Path::~Path() {

}
