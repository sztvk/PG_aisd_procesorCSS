#include <iostream>
#include "DoublyLinkedList.h"
#include "ProgramFunctions.h"

using namespace std;

int main()
{
	ProgramFunctions currentProgram;
	char buf[MAX_COMMAND_SIZE];
	char command = ' ';
	bool finishProgram = false;
	
	while (finishProgram == false)
	{
		if (currentProgram.CSSinput)
		{
			while (currentProgram.CSSinput) currentProgram.oneBlockInput(&command, buf);
		}
		else
		{
			while (currentProgram.CSSinput == false) finishProgram=currentProgram.commandsInput(&command);
		}
	}

	return 0;
}
