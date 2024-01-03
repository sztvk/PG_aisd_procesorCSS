#pragma once
#include "Block.h"

#define ARRAY_SIZE 10

class MainNode
{
public:
	MainNode* next;
	MainNode* previous;
	int takenSpots;

	Block blockArray[ARRAY_SIZE];

	MainNode();
};

