#pragma once
#include "Common.h"
#include "EditorNode.h"
#include "ObjectNode.h"

class ObjectLinkNode : public EditorNode
{
private:
	DynamicLines* lines;

	EditorNode* parent;
	set<EditorNode*> children;

public:
	ObjectLinkNode(Ogre::SceneManager* scene_manager, EditorNode* parent_p, set<EditorNode*> const& children_p);
	~ObjectLinkNode();

	void addChild(EditorNode* child);
	void removeChild(EditorNode* child);
	void clearChild();

	void restart();
};
