#include "ObjectLinkNode.h"
#include "EditorApplication.h"

ObjectLinkNode::ObjectLinkNode(Ogre::SceneManager* scene_manager, EditorNode* parent_p, set<EditorNode*> const& children_p)
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

void ObjectLinkNode::addChild(EditorNode* child)
{
	children.insert(child);
	restart();
}

void ObjectLinkNode::removeChild(EditorNode* child)
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
	lines->clear();
	for (EditorNode* child : children)
	{
		if (child)
		{
			lines->addPoint(parent->getPosition());
			lines->addPoint(child->getPosition());
		}
	}

	lines->update();
}
