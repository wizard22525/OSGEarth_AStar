#pragma once
//定义强枚举类型
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
//节点类
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
//自定义排序函数
bool compareNode(const myNode* node1, const myNode* node2);

class AStar
{
public:
	AStar();
	~AStar();

	//bool endNode(myNode* currentNode);    //是否到达终点
	void searchPath(myNode* startNode, myNode* endNode, std::vector<std::vector<myNode*>>& map);    //提供起点、终点，以及二维地图
	std::vector<std::vector<myNode*>> generateMap();

private:
	//用来寻找最终的路径
	myNode* startNode;
	myNode* endNode;
	std::vector<myNode*> openList;
	std::vector<myNode*> closeList;
	std::vector<myNode*> path;
	std::vector<std::vector<myNode*>> mapList;

	void pathDisplay();    //画出路径
	void calculateCost(myNode* neighborNode, myNode* parentNode);
	std::vector<myNode*> getNeighborsNode(myNode* currentNode);
	myNode* boundry(myNode* node);
	int getf(myNode* currentNode);
	int geth(myNode* currentNode);
	myNode* isOpenList(myNode* currentNode, std::vector<myNode*> open);
	myNode* isCloseList(myNode* currentNode, std::vector<myNode*> close);

};

