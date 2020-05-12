#pragma once

#include <osgViewer/Viewer>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/Map>
#include <osgDB/readFile>
#include <osgEarthUtil/sky>

class myOSG
{
public:
	myOSG();
	~myOSG();
	void InitOSG();
	void InitSceneGraph();
	void InitCameraConfig();
	void PreFrameUpdate();
	void PostFrameUpdate();
	void Render();
	osgViewer::Viewer* getViewer();

	void InitOsgEarth();
private:
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot;
	osg::ref_ptr<osgEarth::MapNode> mMapNode;
	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;
};

