//=========================================================================
//	  Copyright (c) 2016 SonicGLvl
//
//    This file is part of SonicGLvl, a community-created free level editor 
//    for the PC version of Sonic Generations.
//
//    SonicGLvl is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    SonicGLvl is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//    
//
//    Read AUTHORS.txt, LICENSE.txt and COPYRIGHT.txt for more details.
//=========================================================================

#include "EditorApplication.h"
#include "ObjectNodeHistory.h"
#include "ObjectSet.h"

// Create
void HistoryActionCreateObjectNode::undo() {
	if (!object) return;
	junk_state = true;

	LibGens::ObjectSet *object_set = object->getParentSet();

	if (object_set) {
		object_set->eraseObject(object);
		editor_application->updateLayerControlGUI();
	}

	if (object_node_manager) {
		object_node_manager->hideObjectNode(object, true);
	}
}

void HistoryActionCreateObjectNode::redo() {
	if (!object) return;
	junk_state = false;

	LibGens::ObjectSet *object_set = object->getParentSet();

	if (object_set) {
		object_set->addObject(object);
		editor_application->updateLayerControlGUI();
	}

	if (object_node_manager) {
		object_node_manager->showObjectNode(object);
	}
}

HistoryActionCreateObjectNode::~HistoryActionCreateObjectNode() {
	if (junk_state) {
		if (object) {
			delete object;
			if (object_node_manager) {
				object_node_manager->deleteObjectNode(object);
			}
		}
	}
}

// Delete
void HistoryActionDeleteObjectNode::undo() {
	if (!object) return;
	junk_state = false;

	LibGens::ObjectSet *object_set = object->getParentSet();

	if (object_set) {
		object_set->addObject(object);
		editor_application->updateLayerControlGUI();
	}

	if (object_node_manager) {
		object_node_manager->showObjectNode(object);
	}
}

void HistoryActionDeleteObjectNode::redo() {
	if (!object) return;
	junk_state = true;

	LibGens::ObjectSet *object_set = object->getParentSet();

	if (object_set) {
		object_set->eraseObject(object);
		editor_application->updateLayerControlGUI();
	}

	if (object_node_manager) {
		object_node_manager->hideObjectNode(object, true);
	}
}

HistoryActionDeleteObjectNode::~HistoryActionDeleteObjectNode() {
	if (junk_state) {
		if (object) {
			delete object;
			if (object_node_manager) {
				object_node_manager->deleteObjectNode(object);
			}
		}
	}
}

// Move objects to layer
void HistoryActionMoveObjectToLayer::undo() {
	if (!object) return;

	to_set->eraseObject(object);
	from_set->addObject(object);

	editor_application->updateLayerControlGUI();
}

void HistoryActionMoveObjectToLayer::redo() {
	if (!object) return;

	from_set->eraseObject(object);
	to_set->addObject(object);

	editor_application->updateLayerControlGUI();
}

// Edit Bool
void HistoryActionEditObjectElementBool::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

void HistoryActionEditObjectElementBool::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}


// Edit Integer
void HistoryActionEditObjectElementInteger::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index, false);
}

void HistoryActionEditObjectElementInteger::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index, false);
}

// Edit Float
void HistoryActionEditObjectElementFloat::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index, false);
}

void HistoryActionEditObjectElementFloat::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index, false);
}


// Edit String
void HistoryActionEditObjectElementString::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index, false);
}

void HistoryActionEditObjectElementString::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index, false);
}

// Edit ID
void HistoryActionEditObjectElementID::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		ObjectNode* this_node = object_node_manager->findObjectNode(object);
		if (this_node)
		{
			ObjectNode* old_node = editor_application->getObjectNodeFromID(previous_value);
			if (old_node) old_node->addReference(this_node);
			ObjectNode* new_node = editor_application->getObjectNodeFromID(new_value);
			if (new_node) new_node->removeReference(this_node);
		}

		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

void HistoryActionEditObjectElementID::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		ObjectNode* this_node = object_node_manager->findObjectNode(object);
		if (this_node)
		{
			ObjectNode* old_node = editor_application->getObjectNodeFromID(previous_value);
			if (old_node) old_node->removeReference(this_node);
			ObjectNode* new_node = editor_application->getObjectNodeFromID(new_value);
			if (new_node) new_node->addReference(this_node);
		}

		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

// Edit ID List
void HistoryActionEditObjectElementIDList::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		ObjectNode* this_node = object_node_manager->findObjectNode(object);
		if (this_node)
		{
			for (size_t id : previous_value)
			{
				ObjectNode* old_node = editor_application->getObjectNodeFromID(id);
				if (old_node) old_node->addReference(this_node);
			}
			for (size_t id : new_value)
			{
				ObjectNode* new_node = editor_application->getObjectNodeFromID(id);
				if (new_node) new_node->removeReference(this_node);
			}
		}

		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

void HistoryActionEditObjectElementIDList::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		ObjectNode* this_node = object_node_manager->findObjectNode(object);
		if (this_node)
		{
			for (size_t id : previous_value)
			{
				ObjectNode* old_node = editor_application->getObjectNodeFromID(id);
				if (old_node) old_node->removeReference(this_node);
			}
			for (size_t id : new_value)
			{
				ObjectNode* new_node = editor_application->getObjectNodeFromID(id);
				if (new_node) new_node->addReference(this_node);
			}
		}

		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

// Edit Vector
void HistoryActionEditObjectElementVector::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

void HistoryActionEditObjectElementVector::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

// Edit Vector List
void HistoryActionEditObjectElementVectorList::undo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = previous_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}

void HistoryActionEditObjectElementVectorList::redo() {
	if (!object) return;
	if (!object_element) return;

	object_element->value = new_value;

	if (object_node_manager) {
		object_node_manager->reloadObjectNode(object);
	}

	editor_application->updateObjectPropertyIndex(selection_index);
}