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
//��ȡ��ǰ����Χ�İ˸��㣬��ʱ�õ���ֻ��xy���꣬���������뵽vector������
std::vector<myNode*> AStar::getNeighborsNode(myNode* currentNode)
{
	std::vector<myNode*> neighborsNode;
	//���õ���Χ�İ˸�������ٽӵ��У��ٽ��������ֻ�����걻ȷ������صĴ���ֵ���޷���ȷ������Ҫ�ȵ�����ִ�е�ʱ��
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
//���ɵ�ͼ����ͼ��ÿ���㶼��myNode���ͣ�ֻ��x��y����״̬����ʼ����״ֻ̬����ʼ����UNKNOW��OBSTACLE����״̬
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
	this->startNode = startNode;    //��ʱ����this->startNode��startNode��һ��
	this->endNode = endNode;
	this->startNode->parentNode = nullptr;
	openList.push_back(startNode);
	//�����������Ĵ���ֵ
	startNode->g = 0;
	startNode->h = geth(startNode);
	startNode->f = getf(startNode);
	startNode->myState = NodeState::OPENLIST;
	while (!openList.empty())
	{
		//ȡ����ǰopenlist�е���С�ڵ㣬����������б�
		sort(openList.begin(), openList.end(), compareNode);
		myNode* minCostNode = openList.at(0);
		if (minCostNode->x == endNode->x && minCostNode->y == endNode->y)
		{
			std::cout << "searth the shortest path" << std::endl;
			this->endNode = minCostNode;
			pathDisplay();
			break;
		}
		//����С�ڵ���Χ�Ľڵ�����жϣ���������Χ�ڵ�ĸ��ڵ�Ϊ�����С�ڵ�
		std::vector<myNode*> neighborNodes = getNeighborsNode(minCostNode);
		closeList.push_back(minCostNode);
		minCostNode->myState = NodeState::CLOSELIST;
		openList.erase(openList.begin());
		//��ʼ�жϸõ���Χ�İ˸��㣨����ٵĵ㣩
		for (int i = 0; i < neighborNodes.size(); i++)
		{
			//ѭ���жϵ�ǰ�ٽӵ��״̬
			myNode* tempNode = neighborNodes.at(i);
			//����ǰ���ڷ���б��л������ϰ����ֱ�Ӻ���
			if (tempNode->myState == NodeState::CLOSELIST || tempNode->myState == NodeState::OBSTACLE)
			{
				continue;
			}
			else
			{
				//����ǰ�㲻�ڿ����б��У�����ǰ����뵽�����б��У������½ڵ���ش���ֵ
				if (tempNode->myState != NodeState::OPENLIST)
				{
					tempNode->parentNode = minCostNode;
					calculateCost(tempNode, tempNode->parentNode);
					tempNode->myState = NodeState::OPENLIST;
					openList.push_back(tempNode);
				}
				//��ǰ���Ѿ������ڿ����б��У�ֻ��Ҫ���¼������ֵ����
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
	//����openlist�п���ֱ�Ӽ���õ�Ĵ���ֵ������openlist�о���Ҫ�ж��Ƿ񾭹����ڵ���������ٽӵ��������
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
		//���ٽӵ���openlist�еĴ���
		if (abs(neighborNode->x - parentNode->x) != abs(neighborNode->y - parentNode->y))
		{
			if (neighborNode->g < parentNode->g + 10)
			{
				//��ʱ��������
			}
			else
			{
				//ͨ��parentNode����neighbornode���ۻ��С����ʱ����neighbornode�ĸ��ڵ㣬�����¼������,fֵ����Ҫ����
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
		std::cout << "x���꣺" << tempNode->x << "y���꣺" << tempNode->y << std::endl;
		tempNode = tempNode->parentNode;
	}
}

int AStar::getf(myNode* currentNode)
{
	return currentNode->g + currentNode->h;
}
//ʹ�������پ��������㵱ǰ��Ĺ���ֵ
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