#pragma once
#include "TextFileFactory.h"
#include "PythonFile.h"

namespace myFiles
{
	class PythonFileFactory : public TextFileFactory
	{
	public:
		void execute(FileInterface* file);
	};
}



