#pragma once
#include "Common.h"
#include "EditorNode.h"
#include "ObjectNode.h"

class ObjectLinkNode : public EditorNode
{
private:
	DynamicLines* lines;

	LibGens::Object* parent;
	set<LibGens::Object*> children;

public:
	ObjectLinkNode(Ogre::SceneManager* scene_manager, LibGens::Object* parent_p, set<LibGens::Object*> const& children_p);
	~ObjectLinkNode();

	void addChild(LibGens::Object* child);
	void removeChild(LibGens::Object* child);
	void clearChild();

	void restart();
};
