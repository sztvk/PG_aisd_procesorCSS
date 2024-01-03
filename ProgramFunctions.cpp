#include "ProgramFunctions.h"

ProgramFunctions::ProgramFunctions() : CSSinput(true), exitInput(false)
{

}

void ProgramFunctions::oneBlockInput(char* command, char* buf)
{
	int letterCounter = 0;
	Block* newBlock = new Block();

	do
	{
		scanf("%c", command);
	} while (*command <= ' ');

	if (*command != '{')
	{
		selectorsInput(&letterCounter, buf, command, newBlock);
		attributesInput(command, buf, newBlock);
	}
	else
	{
		attributesInput(command, buf, newBlock);
	}

	if (newBlock->attributesList.head != nullptr) blockList.addNewBlock(newBlock);
	CSSinput = checkIfCSSinput(command);
}

void ProgramFunctions::selectorsInput(int* letterCounter, char* buf, char* command, Block* newBlock)
{
	bool selectorsDuplicate = false;

	while (*command != '{')
	{
		if (*command == ',')
		{
			scanf("%c", command);
			if (*command == ' ') scanf("%c", command);
		}
		while (*command != ',' && *command != '{')
		{
			if (*command != '\n')
			{
				buf[*letterCounter] = *command;
				(*letterCounter)++;
			}
			scanf("%c", command);
		}
		buf[*letterCounter] = '\0';
		if (buf[*letterCounter - 1] <= ' ') buf[*letterCounter - 1] = '\0';

		selectorsDuplicate = newBlock->selectorsList.checkDuplicates(buf);
		if (selectorsDuplicate == false) newBlock->selectorsList.addElementAtTheEnd(buf, *letterCounter);

		*letterCounter = 0;
		buf[*letterCounter] = '\0';
	}
}

void ProgramFunctions::attributesInput(char* command, char* buf, Block* newBlock)
{
	char buf2[MAX_COMMAND_SIZE];
	int letterCounter = 0;
	int letterCounter2 = 0;
	bool attributesDuplicate = false;

	while (true)
	{
		// parsing name of attribute
		while (true)
		{
			if (*command != '}') scanf("%c", command);
			if (*command == ':' || *command == '}') break;
			if (*command == ' ' && letterCounter2 == 0) continue;
			if (*command >= ' ')
			{
				buf[letterCounter] = *command;
				(letterCounter)++;
			}
		}
		buf[letterCounter] = '\0';
		if (*command == '}') break;

		// parsing value of attribute
		*command = ' ';
		while (true)
		{
			scanf("%c", command);
			if (*command == ';' || *command == '}') break;
			if (*command == ' ' && letterCounter2 == 0) continue;
			if (*command >= ' ')
			{
				buf2[letterCounter2] = *command;
				letterCounter2++;
			}
		}
		buf2[letterCounter2] = '\0';

		if (newBlock != nullptr)
		{
			attributesDuplicate = newBlock->attributesList.checkDuplicates(buf, buf2);
		}
		if (attributesDuplicate == false && newBlock!=nullptr) newBlock->attributesList.addElementAtTheEnd(buf, buf2, letterCounter, letterCounter2);

		letterCounter = 0;
		letterCounter2 = 0;
		buf[letterCounter] = '\0';
		buf2[letterCounter2] = '\0';
	}
}

bool ProgramFunctions::checkIfCSSinput(char* command)
{
	int commandCounter = 0;

	// do-while: handling whitespaces and end of file
	do
	{
		scanf("%c", command);
		if (feof(stdin) != 0)
		{
			exitInput = true;
			return CSSinput = true;
		}
	} while (*command <= ' ');


	if (CSSinput == true)
	{
		if (*command != '?')
		{
			ungetc(*command, stdin);
			return true;
		}
		else
		{
			commandCounter++;
			while (*command == '?')
			{
				scanf("%c", command);
				if (*command == '?') commandCounter++;
				if (commandCounter == NUMBER_OF_SYMBOLS_CHANGING_INPUT) return false;
			}
		}
	}
	else if (CSSinput == false)
	{
		if (*command != '*')
		{
			ungetc(*command, stdin);
			return false;
		}
		else
		{
			commandCounter++;
			while (*command == '*')
			{
				scanf("%c", command);
				if (*command == '*') commandCounter++;
				if (commandCounter == NUMBER_OF_SYMBOLS_CHANGING_INPUT) return true;
			}
		}
	}
	return true;
}

bool ProgramFunctions::commandsInput(char* command)
{
	// handling whitespaces
	do
	{
		scanf("%c", command);
		if (feof(stdin) != 0)
		{
			exitInput = true;
			return CSSinput = true;
		}
	} while (*command <= ' ');

	char s1[MAX_COMMAND_SIZE], s2[MAX_COMMAND_SIZE], s3[MAX_COMMAND_SIZE];
	int sectionNumber = 0;

	if (*command == QUESTION_MARK) printf("%c == %d\n", *command, blockList.numberOfCSSsections); // ? command
	else
	{
		ungetc(*command, stdin);
		scanf("%[^,],", s1);
		scanf("%[^,],", s2);
		scanf("%[^\n],", s3);

		if (s1[0] > '0' && s1[0] <= '9')
		{
			sectionNumber = atoi(s1);
			Block* returnedBlock = searchForSectionWithGivenNumber(sectionNumber);

			if (strcmp(s2, "S") == 0)
			{
				if (strcmp(s3, "?") == 0)
				{
					// i,S,? command - number of selectors for i-th CSS section
					if (returnedBlock != nullptr) printf("%s,%s,%s == %d\n", s1, s2, s3, returnedBlock->selectorsList.size);
				}
				else if (s3[0] > '0' && s3[0] <= '9')
				{
					// i,S,j command - name of j-th selector for i-th CSS section
					int selectorNumber = atoi(s3);
					char* nameOfSelector = nullptr;

					if (returnedBlock != nullptr) nameOfSelector = findSelectorOfGivenNumber(selectorNumber, *returnedBlock);
					if (returnedBlock != nullptr && nameOfSelector != nullptr) printf("%s,%s,%s == %s\n", s1, s2, s3, nameOfSelector);
				}
			}
			else if (strcmp(s2, "A") == 0)
			{
				if (strcmp(s3, "?") == 0)
				{
					// i,A,? command - number of attributes for i-th CSS section
					if (returnedBlock != nullptr) printf("%s,%s,%s == %d\n", s1, s2, s3, returnedBlock->attributesList.size);
				}
				else
				{
					// i,A,n command - print value of attribute with name n for i-th CSS section
					char* valueOfAttribute = nullptr;

					if (returnedBlock != nullptr) valueOfAttribute = returnedBlock->attributesList.findValueOfGivenAttribute(s3);
					if (returnedBlock != nullptr && valueOfAttribute != nullptr)
					{
						printf("%s,%s,%s == %s\n", s1, s2, s3, valueOfAttribute);
					}
				}
			}
			else if (strcmp(s2, "D") == 0)
			{
				int sectionNumber = atoi(s1);
				if (strcmp(s3, "*") == 0)
				{
					// i,D,* command - delete i-th CSS section
					bool successfulDelete = deleteGivenSection(sectionNumber);
					if (successfulDelete == true) printf("%s,%s,%s == deleted\n", s1, s2, s3);
				}
				else
				{
					// i,D,n command - delete attribute with name n from i-th CSS section
					bool successfulDelete = deleteGivenAttributeFromSection(sectionNumber, s3);
					if(successfulDelete == true) printf("%s,%s,%s == deleted\n", s1, s2, s3);
				}
			}
		}
		else
		{
			// n,A,? and z,S,? commands - total sum of occurences of given attribute or selector
			if ((strcmp(s2, "A") == 0 || (strcmp(s2, "S") == 0)) && strcmp(s3, "?") == 0)
			{
				int sumOfOccurences = countAllOccurencesOfElement(s1, s2);
				printf("%s,%s,%s == %d\n", s1, s2, s3, sumOfOccurences);
			}
			else if (strcmp(s2, "E") == 0)
			{
				// z,E,n command - find value of attribute n for selector z
				char* returnedValue = findLastOccurence(s1, s3);
				if (returnedValue != nullptr) printf("%s,%s,%s == %s\n", s1, s2, s3, returnedValue);
			}
		}
	}
	CSSinput = checkIfCSSinput(command);
	if (exitInput == true) return true;
	return false;
}

Block* ProgramFunctions::searchForSectionWithGivenNumber(int sectionNumber)
{
	if (sectionNumber > blockList.numberOfCSSsections) return nullptr;

	MainNode* currentNode = blockList.head;

	while (currentNode->takenSpots < sectionNumber)
	{
		sectionNumber -= currentNode->takenSpots;
		currentNode = currentNode->next;
	}

	int counter = 0;
	int i = 0;

	for (i = 0; i < ARRAY_SIZE; i++)
	{
		if (currentNode != nullptr)
		{
			
			if (currentNode->blockArray[i].attributesList.head != nullptr) counter++;
			if (counter == sectionNumber) break;
		}
	}

	return &currentNode->blockArray[i];
}

char* ProgramFunctions::findSelectorOfGivenNumber(int selectorNumber, Block currentBlock)
{
	if (selectorNumber > currentBlock.selectorsList.size) return nullptr;

	return currentBlock.selectorsList.findNameOfElementWithNumber(selectorNumber);
}

int ProgramFunctions::countAllOccurencesOfElement(char* elementName, char* typeOfElement) const
{
	int occurencesOfElementSum = 0;
	MainNode* currentMainNode = blockList.head;
	char elementType = ' ';

	if (strcmp(typeOfElement, "A") == 0) elementType = 'A';
	else if (strcmp(typeOfElement, "S") == 0) elementType = 'S';

	for (int i = 0; i < blockList.size; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
		{
			if (elementType == 'A') occurencesOfElementSum += currentMainNode->blockArray[j].attributesList.countOccurencesOfElementInBlock(elementName);
			else if (elementType == 'S') occurencesOfElementSum += currentMainNode->blockArray[j].selectorsList.countOccurencesOfElementInBlock(elementName);
		}
		currentMainNode = currentMainNode->next;
	}
	return occurencesOfElementSum;
}

char* ProgramFunctions::findLastOccurence(char* selectorName, char* attributeName)
{
	MainNode* currentMainNode = blockList.tail;
	bool selectorFound = false;

	for (int i = 0; i < blockList.size; i++)
	{
		for (int j = ARRAY_SIZE; j > 0; j--)
		{
			selectorFound = currentMainNode->blockArray[j - 1].selectorsList.findSelectorOfGivenName(selectorName);

			if (selectorFound == true) return currentMainNode->blockArray[j - 1].attributesList.findValueOfGivenAttribute(attributeName);
		}
		currentMainNode = currentMainNode->previous;
	}
	return nullptr;
}

MainNode* ProgramFunctions::findCurrentNode(int sectionNumber)
{
	if (sectionNumber > blockList.numberOfCSSsections) return nullptr;

	MainNode* currentNode = blockList.head;

	while (currentNode->takenSpots < sectionNumber)
	{
		sectionNumber -= currentNode->takenSpots;
		currentNode = currentNode->next;
	}

	return currentNode;
}

bool ProgramFunctions::deleteGivenSection(int blockNumber)
{
	MainNode* currentMainNode = findCurrentNode(blockNumber);
	Block* blockToDelete = searchForSectionWithGivenNumber(blockNumber);

	if (blockToDelete != nullptr)
	{
		blockList.deleteGivenBlock(blockToDelete);
		currentMainNode->takenSpots--;

		if (currentMainNode->takenSpots == 0)
		{
			blockList.deleteGivenMainNode(currentMainNode);
		}
		return true;
	}
	return false;
}

bool ProgramFunctions::deleteGivenAttributeFromSection(int sectionNumber, char* attributeName)
{
	MainNode* currentMainNode = findCurrentNode(sectionNumber);
	Block* currentBlock = searchForSectionWithGivenNumber(sectionNumber);

	if (currentBlock != nullptr)
	{
		bool attributeDeleted = currentBlock->attributesList.deleteAttributeOfGivenName(attributeName);
		
		if (attributeDeleted == true)
		{
			if (currentBlock->attributesList.head == nullptr)
			{
				currentBlock->selectorsList.deleteAllSelectors();
				blockList.numberOfCSSsections--;
				currentMainNode->takenSpots--;

				if (currentMainNode->takenSpots == 0)
				{
					blockList.deleteGivenMainNode(currentMainNode);
				}
			}
			return true;
		}
	}
	return false;
}
