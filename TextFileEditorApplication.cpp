#include "TextFileEditorApplication.h"


void myEditor::TextFileEditorApplication::inputs()
{
	char user_code = _getch();
	switch (user_code)
	{
	case 8: //backspace
		textField->left_cursor();
		deleteCharacter();
		break;
	case 9:
		for (int i = 0; i < 5; i++)
			insertCharacter(' ');
		break;
	case 13: //enter
		insertCharacter('\n');
		break;
	case 27: //ecs
		textField->stopEditing();
		break;
	case 19: // ctr + s
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) // ctr + shift + s
			saveFileAs();
		else
			saveFile();
		break;
	case -32: //arrows
		user_code = _getch();
		switch (user_code)
		{
		case 75: //left
			textField->left_cursor();
			break;
		case 77: //right
			textField->right_cursor();
			break;
		case 72: //up
			textField->up_cursor();
			break;
		case 80:  //down
			textField->down_cursor();
			break;
		case 83: // del
			deleteCharacter();
			break;
		}
		break;
	default: //others
		insertCharacter(user_code);
		break;
	}
}

void myEditor::TextFileEditorApplication::deleteCharacter()
{
	if (file->getSize() == 0)
		return;

	size_t write_position = textField->getIndexPosition();
	if (write_position == file->getSize())
		return;

	size_t newSize = file->getSize() - 1;
	const char* oldData = file->getData();
	
	char* newData = new char[newSize];

	for (int i = 0; i < newSize; i++)
		newData[i] = oldData[i + (i >= write_position ? 1 : 0)];

	myFiles::TextFileFactory().writeData(file, newData, newSize);

	delete[] newData;

	textField->update_scr();
}

void myEditor::TextFileEditorApplication::insertCharacter(char ch)
{
	size_t newSize = file->getSize() + 1;

	const char* oldData = file->getData();
	char* newData = new char[newSize];

	size_t write_position = textField->getIndexPosition();
	for (int i = 0; i < newSize; i++)
	{
		if (i == write_position)
			newData[i] = ch;
		else
			newData[i] = oldData[i - (i > write_position ? 1 : 0)];
	}
	myFiles::TextFileFactory().writeData(file, newData, newSize);
	textField->right_cursor();
	delete[] newData;

	textField->update_scr();
}

myEditor::TextFileEditorApplication::TextFileEditorApplication() : textField{nullptr}
{
	textField = new myEditor::TextField(this);

	header.appendElement("[ESC: Exit]", 12);
	header.appendElement("[ <= Left] [ => Right]", 11);
	header.appendElement("[Ctrl + S: Save]", 10);
	header.appendElement("[Ctrl + Shift + S: Save As]", 13);
}

myEditor::TextFileEditorApplication::~TextFileEditorApplication()
{
	delete textField;
}

void myEditor::TextFileEditorApplication::loadFile()
{
	std::string fileName;

	std::cout << "Enter file name: ";
	std::getline(std::cin, fileName);
	std::cout << fileName << std::endl;
	if (file)
		delete file;

	file = myFiles::TextFileFactory().openFile(fileName.c_str());
	if (file->getSize() == 0)
	{
		std::cout << "File not found!!! Create new file in procces... (press any key to continue)";
		_getch();
	}
}

void myEditor::TextFileEditorApplication::createFile()
{
	std::string fileName;

	std::cout << "Enter file name: ";
	std::getline(std::cin, fileName);

	file = myFiles::TextFileFactory().createFile(fileName.c_str());
}

void myEditor::TextFileEditorApplication::saveFile()
{
	system("cls");

	if (myFiles::TextFileFactory().saveFile(file))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		std::cout << "Saving successful!!!\npress any case to continue...";
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Error saving file.\npress any case to continue...";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_getch();
	textField->update_scr();
}

void myEditor::TextFileEditorApplication::saveFileAs()
{
	std::string fileName;

	system("cls");

	std::cout << "Enter file name to save: ";
	std::getline(std::cin, fileName);

	if (myFiles::TextFileFactory().saveFileAs(file, fileName.c_str()))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		std::cout << "Saving successful!!!\npress any case to continue...";
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Error saving file.\npress any case to continue...";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_getch();
	textField->update_scr();
}

void myEditor::TextFileEditorApplication::start()
{
	textField->startEditing();
}
