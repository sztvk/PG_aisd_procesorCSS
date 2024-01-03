#include "MainList.h"

MainList::MainList() : head(nullptr), tail(nullptr), size(0), numberOfCSSsections(0)
{
}

void MainList::addNewMainNode()
{
	if (size == 0)
	{
		head = new MainNode();
		head->next = nullptr;
		head->previous = nullptr;
		tail = head;
		size++;
	}
	else
	{
		MainNode* temp = tail;
		tail = new MainNode();
		temp->next = tail;
		tail->previous = temp;
		tail->next = nullptr;
		size++;
	}
}

void MainList::addNewBlock(Block* block)
{
	// checking if there are some spots in the array that were never used
	int notTakenSpotsCounter = 0;
	if (tail != nullptr)
	{
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			if (tail->blockArray[i].permamentlyTaken == false) notTakenSpotsCounter++;
		}
	}
	
	if (size == 0 || notTakenSpotsCounter == 0)
	{
		addNewMainNode();
		addNewBlock(block);
	}
	else
	{
		int indexToAdd = tail->takenSpots;

		while (tail->blockArray[indexToAdd].permamentlyTaken == true)
		{
			indexToAdd++;
		}

		tail->blockArray[indexToAdd] = *block;
		tail->takenSpots++;
		numberOfCSSsections++;
		tail->blockArray[indexToAdd].permamentlyTaken = true;
	}
}

void MainList::deleteGivenMainNode(MainNode* currentMainNode)
{
	if(size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		MainNode* temp = currentMainNode;

		if (currentMainNode->previous == nullptr) head = currentMainNode->next;
		else if (currentMainNode->next == nullptr) tail = currentMainNode->previous;

		if(currentMainNode->previous != nullptr) currentMainNode->previous->next = currentMainNode->next;
		else if (currentMainNode->next != nullptr)currentMainNode->next->previous = currentMainNode->previous;
		delete temp;
	}
	size--;
}

void MainList::deleteGivenBlock(Block* blockToDelete)
{
	blockToDelete->attributesList.deleteAllAttributes();
	blockToDelete->selectorsList.deleteAllSelectors();
	numberOfCSSsections--;
}
