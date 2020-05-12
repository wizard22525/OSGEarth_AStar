#pragma once
//����ǿö������
#include<iostream>
#include<algorithm>
#include<vector>

#define MAX_MAP 20


enum class NodeState
{
	UNKNOW,
	OBSTACLE,
	CLOSELIST,
	OPENLIST
};
//�ڵ���
class myNode
{
public:
	myNode();
	~myNode();
	int x;
	int y;
	NodeState myState;
	int f;
	int g;
	int h;
	myNode* parentNode;
	bool operator==(const myNode& node)
	{
		if (x == node.x && y == node.y)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const myNode& node)
	{
		if (x == node.x && y == node.y)
		{
			return false;
		}
		return true;
	}
};
//�Զ���������
bool compareNode(const myNode* node1, const myNode* node2);

class AStar
{
public:
	AStar();
	~AStar();

	//bool endNode(myNode* currentNode);    //�Ƿ񵽴��յ�
	void searchPath(myNode* startNode, myNode* endNode, std::vector<std::vector<myNode*>>& map);    //�ṩ��㡢�յ㣬�Լ���ά��ͼ
	std::vector<std::vector<myNode*>> generateMap();

private:
	//����Ѱ�����յ�·��
	myNode* startNode;
	myNode* endNode;
	std::vector<myNode*> openList;
	std::vector<myNode*> closeList;
	std::vector<myNode*> path;
	std::vector<std::vector<myNode*>> mapList;

	void pathDisplay();    //����·��
	void calculateCost(myNode* neighborNode, myNode* parentNode);
	std::vector<myNode*> getNeighborsNode(myNode* currentNode);
	myNode* boundry(myNode* node);
	int getf(myNode* currentNode);
	int geth(myNode* currentNode);
	myNode* isOpenList(myNode* currentNode, std::vector<myNode*> open);
	myNode* isCloseList(myNode* currentNode, std::vector<myNode*> close);

};

