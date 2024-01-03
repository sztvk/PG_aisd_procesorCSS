#pragma once
#include <iostream>
#include <string.h>

#define MAX_NAME_SIZE 200

//class Block;

template <class T> class DoublyLinkedList
{
public:
	int size;

	T* head;
	T* tail;

	DoublyLinkedList()
	{
		this->size = 0;
		this->head = nullptr;
		this->tail = nullptr;
	}

	void addElementAtTheEnd(char* name, int letterCounter)
	{
		char* oneWord = new char[letterCounter];
		strcpy(oneWord, name);

		if (size == 0)
		{
			head = new T();
			head->next = nullptr;
			head->previous = nullptr;
			head->name = oneWord;
			tail = head;
			size++;
		}
		else
		{
			T* temp = tail;
			tail = new T();
			temp->next = tail;
			tail->previous = temp;
			tail->next = nullptr;
			tail->name = oneWord;
			size++;
		}
	}
	void addElementAtTheEnd(char* name, char* value, int letterCounter, int letterCounter2)
	{
		char* attributeName = new char[letterCounter];
		strcpy(attributeName, name);
		char* attributeValue = new char[letterCounter2];
		strcpy(attributeValue, value);

		if (size == 0)
		{
			head = new T();
			head->next = nullptr;
			head->previous = nullptr;
			head->name = attributeName;
			head->value = attributeValue;
			tail = head;
			size++;
		}
		else
		{
			T* temp = tail;
			tail = new T();
			temp->next = tail;
			tail->previous = temp;
			tail->next = nullptr;
			tail->name = attributeName;
			tail->value = attributeValue;
			size++;
		}
	}

	bool checkDuplicates(char* name, char* value) const
	{
		T* temp = head;
		int sizeOfNewValue = strlen(value);

		if (value == nullptr) return false;
		if (head != nullptr && value!= nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				if (strcmp(temp->name, name) == 0)
				{
					char* newValue = new char[sizeOfNewValue];
					strcpy(newValue, value);
					temp->value = newValue;

					return true;
				}
				temp = temp->next;
			}
		}

		return false;
	}
	bool checkDuplicates(char* name) const
	{
		T* temp = head;

		for (int i = 0; i < size; i++)
		{
			if (strcmp(temp->name, name) == 0) return true;

			temp = temp->next;
		}
		return false;
	}

	char* findNameOfElementWithNumber(int numberOfElement)
	{
		if (numberOfElement > size) return nullptr;

		T* currentNode = head;

		for (int i = 0; i < numberOfElement - 1; i++)
		{
			currentNode = currentNode->next;
		}
		return currentNode->name;
	}
	char* findValueOfGivenAttribute(char* nameOfAttribute)
	{
		T* currentNode = head;

		for (int i = 0; i < size; i++)
		{
			if (strcmp(currentNode->name, nameOfAttribute) == 0) return currentNode->value;
			currentNode = currentNode->next;
		}
		return nullptr;
	}
	bool findSelectorOfGivenName(char* selectorName) const
	{
		T* currentNode = head;

		for (int i = 0; i < size; i++)
		{
			if (strcmp(currentNode->name, selectorName) == 0) return true;
			currentNode = currentNode->next;
		}

		return false;
	}

	int countOccurencesOfElementInBlock(char* elementName) const
	{
		T* currentNode = head;

		if (head != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				if (strcmp(currentNode->name, elementName) == 0) return 1;
				currentNode = currentNode->next;
			}
		}
		return 0;
	}

	void deleteFirstSelector()
	{
		if (size == 1)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			T* temp = head;
			head = temp->next;
			delete temp;
		}
		size--;
	}
	void deleteFirstAttribute()
	{
		if (size == 1)
		{
			head->value = nullptr;
			head->name = nullptr;
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			T* temp = head;
			head = temp->next;
			head->previous = nullptr;
			delete temp;
		}
		size--;
	}
	
	void deleteAllAttributes()
	{
		int initialSize = size;

		for (int i = 0; i < initialSize; i++)
		{
			deleteFirstAttribute();
		}
	}
	void deleteAllSelectors()
	{
		int initialSize = size;

		for (int i = 0; i < initialSize; i++)
		{
			deleteFirstSelector();
		}
	}

	bool deleteAttributeOfGivenName(char* attributeName)
	{
		T* currentNode = head;
		bool attributeDeleted = false;

		for (int i = 0; i < size; i++)
		{
			if (strcmp(attributeName, currentNode->name) == 0)
			{
				if (size == 1)
				{
					head = nullptr;
					tail = nullptr;
				}
				else if (currentNode == head)
				{
					head = currentNode->next;
					head->previous = nullptr;
				}
				else if (currentNode == tail)
				{
					tail = currentNode->previous;
					tail->next = nullptr;
				}
				else
				{
					currentNode->previous->next = currentNode->next;
					currentNode->next->previous = currentNode->previous;
				}
				delete currentNode;
				size--;
				attributeDeleted = true;
				break;
			}
			currentNode = currentNode->next;
		}
		return attributeDeleted;
	}
};