#include "Application.h"


void Application::createTextFileEditorApplication()
{
	if (editor)
		delete editor;
	editor = new myEditor::TextFileEditorApplication();
}

void Application::createPythonFileEditorApplication()
{
	if (editor)
		delete editor;
	editor = new myEditor::PythonFileEditorApplication();
}

void Application::drawMenu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "Main Menu:" << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "1. Open Text File" << std::endl;
	std::cout << "2. Create Text File" << std::endl;
	std::cout << "3. Open Python File" << std::endl;
	std::cout << "4. Create Python File" << std::endl;
	std::cout << "5. Exit" << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void Application::menu()
{
	
	while (true)
	{
		system("cls");
		drawMenu();
		
		switch (_getch())
		{
			case '1':
				createTextFileEditorApplication();
				editor->loadFile();
				editor->start();
				break;
			case '2':
				createTextFileEditorApplication();
				editor->createFile();
				editor->start();
				break;
			case '3':
				createPythonFileEditorApplication();
				editor->loadFile();
				editor->start();
				break;
			case '4':
				createPythonFileEditorApplication();
				editor->createFile();
				editor->start();
				break;
			case '5':
				return;
		}
	}
}
