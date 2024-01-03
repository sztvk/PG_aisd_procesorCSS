#pragma once
#include "MainList.h"

#define MAX_COMMAND_SIZE 200
#define QUESTION_MARK '?'
#define STAR_SYMBOL '*'
#define NUMBER_OF_SYMBOLS_CHANGING_INPUT 4
#define ZERO_CHAR '0'
#define NINE_CHAR '9'
#define S_STRING  "S"
#define A_STRING "A"
#define D_STRING "D"
#define E_STRING "E"
#define STAR_STRING "*"
#define QUESTION_MARK_STRING "?"

#pragma warning(disable : 4996)

class ProgramFunctions
{
public:
	MainList blockList;
	bool CSSinput;
	bool exitInput;

	ProgramFunctions();

	void oneBlockInput(char* command, char* buf);
	void selectorsInput(int* letterCounter, char* buf, char* command, Block* newBlock);
	void attributesInput(char* command, char* buf, Block* newBlock);
	bool commandsInput(char* command);
	bool checkIfCSSinput(char* command);

	Block* searchForSectionWithGivenNumber(int sectionNumber);
	char* findSelectorOfGivenNumber(int selectorNumber, Block currentBlock);
	int countAllOccurencesOfElement(char* elementName, char* typeOfElement) const;
	char* findLastOccurence(char* selectorName, char* attributeName);

	MainNode* findCurrentNode(int sectionNumber);

	bool deleteGivenSection(int blockNumber);
	bool deleteGivenAttributeFromSection(int sectionNumber, char* attributeName);
};

