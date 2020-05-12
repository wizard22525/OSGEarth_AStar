#include <iostream>
#include <osgViewer/viewer>
#include <osgDB/readfile>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarth/Metrics>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/ExampleResources>
//#include "Astar.h"

using namespace osgEarth::Util;
using namespace osgUtil;
using namespace osgDB;
using namespace osg;
using namespace osgViewer;

int main(int argc, char** argv) {
	/*myNode* startNode = new myNode();
	myNode* endNode = new myNode();
	3
	startNode->x = 2;
	startNode->y = 2;

	endNode->x = 6;
	endNode->y = 5;
	AStar astar;
	vector<vector<myNode*>> map = astar.generateMap();
	astar.searchPath(startNode, endNode, map);*/
	/*return 0;*/

	ArgumentParser arguments(&argc, argv);
	Viewer viewer(arguments);
	viewer.setCameraManipulator(new EarthManipulator(arguments));
	viewer.getCamera()->setNearFarRatio(0.0001);
	Node* node = MapNodeHelper().load(arguments, &viewer);
	if (node)
	{
		viewer.setSceneData(node);
		Metrics::run(viewer);
	}
	while (!viewer.done())
	{
		viewer.frame();
	}
	return 0;
}