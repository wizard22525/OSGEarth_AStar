#include "myOSG.h"
myOSG::myOSG()
{
	mViewer = new osgViewer::Viewer();
	mRoot = new osg::Group();
	em = new osgEarth::Util::EarthManipulator();


}
myOSG::~myOSG()
{
	delete mViewer;
}

void myOSG::InitOSG()
{
	InitSceneGraph();
	InitCameraConfig();

	InitOsgEarth();
}
void myOSG::InitSceneGraph()
{
	mRoot->addChild(osgDB::readNodeFile("F:\\OSG\\OpenSceneGraph-Data\\cow.osg"));
}
void myOSG::InitCameraConfig()
{
	osg::ref_ptr<osg::GraphicsContext::Traits> trait = new osg::GraphicsContext::Traits();
	trait->x = 0;
	trait->y = 0;
	trait->width = 1280;
	trait->height = 720;
	trait->doubleBuffer = true;
	osg::GraphicsContext *gc = osg::GraphicsContext::createGraphicsContext(trait);

	osg::ref_ptr<osg::Camera> camera = new osg::Camera();
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport());

	//mViewer->setCamera(camera);
	//mViewer->setCameraManipulator(new osgEarth::Util::m());
	mViewer->setSceneData(mRoot.get());
	mViewer->realize();
}

void myOSG::InitOsgEarth()
{
	osg::ref_ptr<osg::Node> mp = osgDB::readNodeFile("F:\\OSGEarth\\osgearth-2.10.1\\tests\\myearth.earth");
	mRoot->addChild(mp);
	//mapNode = osgEarth::MapNode::get(mp.get());
	mMapNode = dynamic_cast<osgEarth::MapNode*>(mp.get());
	if (mMapNode.valid())
	{
		std::cout << "valid mapnode" << std::endl;
		em->setNode(mMapNode);
	}
	em->getSettings()->setArcViewpointTransitions(true);
	mViewer->setCameraManipulator(em);

	//Ìì¿ÕºÐ
	osgEarth::Config skyConf;
	osg::ref_ptr<osgEarth::Util::SkyNode> mSkyNode = osgEarth::Util::SkyNode::create(mMapNode);
	mSkyNode->attach(mViewer, 1);
	mRoot->addChild(mSkyNode);
}

void myOSG::PreFrameUpdate()
{

}
void myOSG::PostFrameUpdate()
{

}
void myOSG::Render()
{
	mViewer->run();
}
osgViewer::Viewer* myOSG::getViewer()
{
	return mViewer;
}