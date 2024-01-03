#pragma once
#include "DoublyLinkedList.h"

struct Attribute
{
	char* name;
	char* value;

	Attribute* next;
	Attribute* previous;
};

struct Selector
{
	char* name;
	Selector* next;
	Selector* previous;
};

class Block
{
public:
	DoublyLinkedList<Attribute> attributesList;
	DoublyLinkedList<Selector> selectorsList;
	bool permamentlyTaken;

	Block();
};

