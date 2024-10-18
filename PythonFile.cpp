#include "PythonFile.h"

void PythonFile::execute() const
{
	std::string comand = std::string{ "py " } + std::string{ fileName };
	int result = system(comand.c_str());
	system("pause");
}
