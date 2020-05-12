#include "myOSG.h"
void myOSG::InitOSG()
{
	InitSceneGraph();
	InitCameraConfig();

	InitOsgEarth();
}
void myOSG::InitSceneGraph()
{
	mRoot = new osg::Group();
}
void myOSG::InitCameraConfig()
{
	mViewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::GraphicsContext::Traits> trait = new osg::GraphicsContext::Traits();
	trait->x = 0;
	trait->y = 0;
	trait->width = 1280;
	trait->height = 720;
	trait->doubleBuffer = true;
	osg::GraphicsContext *gc = osg::GraphicsContext::createGraphicsContext(trait);

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport());
}
void myOSG::PreFrameUpdate()
{

}
void myOSG::PostFrameUpdate()
{

}
static void Render(void* ptr)
{

}

void myOSG::InitOsgEarth()
{

}