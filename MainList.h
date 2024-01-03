#pragma once
#include "MainNode.h"

class MainList
{
public:
	MainNode* head;
	MainNode* tail;
	int size;
	int numberOfCSSsections;

	MainList();

	void addNewMainNode();
	void addNewBlock(Block* block);

	void deleteGivenMainNode(MainNode* currentMainNode);
	void deleteGivenBlock(Block* blockToDelete);
};

