#pragma once

#include <osgViewer/Viewer>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/Map>

class myOSG
{
public:
	void InitOSG();
	void InitSceneGraph();
	void InitCameraConfig();
	void PreFrameUpdate();
	void PostFrameUpdate();
	static void Render(void* ptr);

	void InitOsgEarth();
private:
	osgViewer::Viewer* mViewer;
	osg::ref_ptr<osg::Group> mRoot;
};

