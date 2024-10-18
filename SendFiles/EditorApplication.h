#pragma once

#include "TextFileFactory.h"
#include <conio.h>
#include <windows.h>
#include <string>


class EditorApplication
{
private:
	FileEditor* file;

	bool edit_cicle;
	size_t write_position;
public:
	EditorApplication() : file{ nullptr }, edit_cicle{true}, write_position{ 0 } {};
	~EditorApplication() { if (file) delete file; }

	void deleteCharacter();
	void insertCharacter(char ch);

	void drawUI();
	void drawMenu();

	void nextLine();
	void pastLine();

	void draw();
	void update();
	void editFile();

	void loadFile();
	void createFile();
	void saveFile();
	void saveFileAs();

	void menu();
};

