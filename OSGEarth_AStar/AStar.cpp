#include "AStar.h"

bool compareNode(const myNode* node1, const myNode* node2)
{
	return node1->f < node2->f;
}
myNode::myNode() :x(0), y(0), myState(NodeState::UNKNOW), f(0), g(0), h(0), parentNode(nullptr)
{
}
myNode::~myNode()
{

}
AStar::AStar()
{
	startNode = nullptr;
	endNode = new myNode;

}
AStar::~AStar()
{
	delete endNode;
	openList.shrink_to_fit();
	closeList.shrink_to_fit();
	path.shrink_to_fit();
}
//获取当前点周围的八个点，此时拿到的只有xy坐标，将坐标点加入到vector数组中
std::vector<myNode*> AStar::getNeighborsNode(myNode* currentNode)
{
	std::vector<myNode*> neighborsNode;
	//将该点周围的八个点加入临接点中，临界点在这里只有坐标被确定，相关的代价值还无法被确定，需要等到具体执行的时候
	myNode* left_bottom = new myNode();
	left_bottom->x = currentNode->x - 1;
	left_bottom->y = currentNode->y - 1;
	left_bottom = boundry(left_bottom);
	if (left_bottom != nullptr)
	{
		neighborsNode.push_back(left_bottom);
	}

	myNode* left_top = new myNode();
	left_top->x = currentNode->x - 1;
	left_top->y = currentNode->y + 1;
	left_top = boundry(left_top);
	if (left_top != nullptr)
	{
		neighborsNode.push_back(left_top);
	}

	myNode* right_bottom = new myNode();
	right_bottom->x = currentNode->x + 1;
	right_bottom->y = currentNode->y - 1;
	right_bottom = boundry(right_bottom);
	if (right_bottom != nullptr)
	{
		neighborsNode.push_back(right_bottom);
	}

	myNode* right_top = new myNode();
	right_top->x = currentNode->x + 1;
	right_top->y = currentNode->y + 1;
	right_top = boundry(right_top);
	if (right_top != nullptr)
	{
		neighborsNode.push_back(right_top);
	}

	myNode* right = new myNode();
	right->x = currentNode->x + 1;
	right->y = currentNode->y;
	right = boundry(right);
	if (right != nullptr)
	{
		neighborsNode.push_back(right);
	}

	myNode* left = new myNode();
	left->x = currentNode->x - 1;
	left->y = currentNode->y;
	left = boundry(left);
	if (left != nullptr)
	{
		neighborsNode.push_back(left);
	}

	myNode* top = new myNode();
	top->x = currentNode->x;
	top->y = currentNode->y + 1;
	top = boundry(top);
	if (top != nullptr)
	{
		neighborsNode.push_back(top);
	}

	myNode* bottom = new myNode();
	bottom->x = currentNode->x;
	bottom->y = currentNode->y - 1;
	bottom = boundry(bottom);
	if (bottom != nullptr)
	{
		neighborsNode.push_back(bottom);
	}

	return neighborsNode;
}

myNode* AStar::boundry(myNode* node)
{
	if (node->x < 0 || node->y < 0 || node->x > MAX_MAP || node->y > MAX_MAP)
	{
		node = nullptr;
	}
	else if (isOpenList(node, openList) != nullptr)
	{
		node = isOpenList(node, openList);
	}
	else if (isCloseList(node, closeList) != nullptr)
	{
		node = isCloseList(node, closeList);
	}
	return node;
}
//生成地图，地图的每个点都是myNode类型，只有x，y，和状态被初始化，状态只被初始化成UNKNOW和OBSTACLE两种状态
std::vector<std::vector<myNode*>> AStar::generateMap()
{
	std::vector<std::vector<myNode*>> map;
	for (int i = 0; i < MAX_MAP; i++)
	{
		std::vector<myNode*> xCoord;
		for (int j = 0; j < MAX_MAP; j++)
		{
			myNode* yCoord = new myNode();
			yCoord->x = i;
			yCoord->y = j;
			xCoord.push_back(yCoord);
		}
		map.push_back(xCoord);
	}
	return map;
}
void AStar::searchPath(myNode* startNode, myNode* endNode, std::vector<std::vector<myNode*>>& map)
{
	this->startNode = startNode;    //此时操作this->startNode和startNode都一样
	this->endNode = endNode;
	this->startNode->parentNode = nullptr;
	openList.push_back(startNode);
	//单独计算起点的代价值
	startNode->g = 0;
	startNode->h = geth(startNode);
	startNode->f = getf(startNode);
	startNode->myState = NodeState::OPENLIST;
	while (!openList.empty())
	{
		//取出当前openlist中的最小节点，将其放入封闭列表
		sort(openList.begin(), openList.end(), compareNode);
		myNode* minCostNode = openList.at(0);
		if (minCostNode->x == endNode->x && minCostNode->y == endNode->y)
		{
			std::cout << "searth the shortest path" << std::endl;
			this->endNode = minCostNode;
			pathDisplay();
			break;
		}
		//对最小节点周围的节点进行判断，并设置周围节点的父节点为这个最小节点
		std::vector<myNode*> neighborNodes = getNeighborsNode(minCostNode);
		closeList.push_back(minCostNode);
		minCostNode->myState = NodeState::CLOSELIST;
		openList.erase(openList.begin());
		//开始判断该点周围的八个点（或更少的点）
		for (int i = 0; i < neighborNodes.size(); i++)
		{
			//循环判断当前临接点的状态
			myNode* tempNode = neighborNodes.at(i);
			//若当前点在封闭列表中或者是障碍物，则直接忽略
			if (tempNode->myState == NodeState::CLOSELIST || tempNode->myState == NodeState::OBSTACLE)
			{
				continue;
			}
			else
			{
				//若当前点不在开放列表中，将当前点加入到开放列表中，并更新节点相关代价值
				if (tempNode->myState != NodeState::OPENLIST)
				{
					tempNode->parentNode = minCostNode;
					calculateCost(tempNode, tempNode->parentNode);
					tempNode->myState = NodeState::OPENLIST;
					openList.push_back(tempNode);
				}
				//当前点已经存在于开放列表中，只需要重新计算代价值即可
				else
				{
					calculateCost(tempNode, minCostNode);
				}
			}
		}
	}
}

void AStar::calculateCost(myNode* neighborNode, myNode* parentNode)
{
	//不在openlist中可以直接计算该点的代价值，若在openlist中就需要判断是否经过父节点来到达该临接点可以最优
	if (neighborNode->myState != NodeState::OPENLIST)
	{
		if (abs(neighborNode->x - parentNode->x) != abs(neighborNode->y - parentNode->y))
		{
			neighborNode->g = parentNode->g + 10;
			neighborNode->h = geth(neighborNode);
			neighborNode->f = getf(neighborNode);
			neighborNode->myState = NodeState::OPENLIST;
		}
		else
		{
			neighborNode->g = parentNode->g + 14;
			neighborNode->h = geth(neighborNode);
			neighborNode->f = getf(neighborNode);
		}
	}
	else
	{
		//当临接点在openlist中的处理
		if (abs(neighborNode->x - parentNode->x) != abs(neighborNode->y - parentNode->y))
		{
			if (neighborNode->g < parentNode->g + 10)
			{
				//此时不做处理
			}
			else
			{
				//通过parentNode到达neighbornode代价会更小，此时更改neighbornode的父节点，并重新计算代价,f值不需要更新
				neighborNode->parentNode = parentNode;
				neighborNode->g = parentNode->g + 10;
				neighborNode->h = getf(neighborNode);
				neighborNode->f = getf(neighborNode);
			}
		}
		else
		{
			if (neighborNode->g > parentNode->g + 14)
			{
				neighborNode->parentNode = parentNode;
				neighborNode->g = parentNode->g + 14;
				neighborNode->h = getf(neighborNode);
				neighborNode->f = getf(neighborNode);
			}
		}

	}
}

void AStar::pathDisplay()
{
	myNode* tempNode = endNode;
	while (tempNode->parentNode != nullptr)
	{
		std::cout << "x坐标：" << tempNode->x << "y坐标：" << tempNode->y << std::endl;
		tempNode = tempNode->parentNode;
	}
}

int AStar::getf(myNode* currentNode)
{
	return currentNode->g + currentNode->h;
}
//使用曼哈顿距离来计算当前点的估算值
int AStar::geth(myNode* currentNode)
{
	return (abs(endNode->x - currentNode->x) + abs(endNode->y - currentNode->y));
}
myNode* AStar::isOpenList(myNode* currentNode, std::vector<myNode*> open)
{
	for (int i = 0; i < open.size(); i++)
	{
		if (currentNode->x == open.at(i)->x && currentNode->y == open.at(i)->y)
		{
			return open.at(i);
		}
	}
	return nullptr;
}
myNode* AStar::isCloseList(myNode* currentNode, std::vector<myNode*> close)
{
	for (int i = 0; i < close.size(); i++)
	{
		if (currentNode->x == close.at(i)->x && currentNode->y == close.at(i)->y)
		{
			return close.at(i);
		}
	}
	return nullptr;
}