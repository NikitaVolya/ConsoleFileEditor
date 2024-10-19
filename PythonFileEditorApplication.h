#pragma once

#include "TextFileEditorApplication.h"
#include "PythonFileFactory.h"

namespace myEditor
{
	class PythonFileEditorApplication : public  TextFileEditorApplication
	{
	private:
		bool validSyb(char symb);
	public:
		PythonFileEditorApplication();

		void inputs();
	};
}

