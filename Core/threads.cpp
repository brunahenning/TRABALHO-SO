#include <program1.h>
#include <program2.h>
#include <iostream>

int main()
{
	int choose;

	std::cout << "Escolha o programa\n1 - Programa um\n2 - Programa dois" << std::endl;
	std::cin >> choose;

	switch (choose)
	{
		case 1:
			ProgramOne();
			std::cout << std::endl;
			break;
		case 2:
			ProgramTwo();
			std::cout << std::endl;
			break;
		default:
			break;
	}

	return 0;
}