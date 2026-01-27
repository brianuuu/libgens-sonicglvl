#include "ObjectLinkNode.h"
#include "EditorApplication.h"

ObjectLinkNode::ObjectLinkNode(Ogre::SceneManager* scene_manager, LibGens::Object* parent_p, set<LibGens::Object*> const& children_p)
{
	scene_node = scene_manager->getRootSceneNode()->createChildSceneNode();
	scene_node->setPosition(position);
	scene_node->setScale(scale);
	scene_node->getUserObjectBindings().setUserAny("EditorNodePtr", Ogre::Any((EditorNode*)this));

	lines = new DynamicLines(Ogre::RenderOperation::OT_LINE_LIST);
	lines->setMaterial("objectlink");
	scene_node->attachObject(lines);

	parent = parent_p;
	children = children_p;
	restart();
}

ObjectLinkNode::~ObjectLinkNode()
{
	delete lines;
}

void ObjectLinkNode::addChild(LibGens::Object* child)
{
	children.insert(child);
	restart();
}

void ObjectLinkNode::removeChild(LibGens::Object* child)
{
	children.erase(child);
	restart();
}

void ObjectLinkNode::clearChild()
{
	children.clear();
	restart();
}

void ObjectLinkNode::restart()
{
	ObjectNode* parent_node = editor_application->getObjectNodeManager()->findObjectNode(parent);

	lines->clear();
	for (LibGens::Object* child : children)
	{
		ObjectNode* child_node = editor_application->getObjectNodeManager()->findObjectNode(child);
		if (child_node)
		{
			lines->addPoint(parent_node->getPosition());
			lines->addPoint(child_node->getPosition());
		}
	}

	lines->update();
}
