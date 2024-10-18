#pragma once

#include "FileEditorInterface.h"
#include "TextFileFactory.h"
#include "TextField.h"
#include <conio.h>
#include <windows.h>
#include <string>

namespace myEditor
{

	class TextFileEditorApplication : public FileEditorInterface
	{
	protected:
		myEditor::TextField* textField;

		virtual void drawUI();
		virtual void inputs();

		void deleteCharacter();
		void insertCharacter(char ch);
	public:
		TextFileEditorApplication();
		~TextFileEditorApplication();

		void loadFile();
		void createFile();
		void saveFile();
		void saveFileAs();

		void start();
	};

}



