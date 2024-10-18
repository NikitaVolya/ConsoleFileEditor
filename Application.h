#pragma once

#include "PythonFileEditorApplication.h"


class Application
{
private:
	myEditor::FileEditorInterface* editor;
public:
	Application() {};
	~Application() {
		if (editor)
			delete editor;
	}

	void createTextFileEditorApplication();
	void createPythonFileEditorApplication();

	void drawMenu();
	void menu();
};

