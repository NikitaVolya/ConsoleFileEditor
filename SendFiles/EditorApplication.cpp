#include "EditorApplication.h"


void EditorApplication::deleteCharacter()
{
	size_t newSize = file->getSize() - 1;
	char* newData = new char[newSize];
	const char* oldData = file->getData();

	for (int i = 0; i <= newSize; i++)
	{
		if (i != write_position - 1)
			newData[(i < write_position ? i : i - 1)] = oldData[i];
	}

	((TextFile*)file)->setData(newData, newSize);
	delete[] newData;

	write_position -= 1;
}

void EditorApplication::insertCharacter(char ch)
{
	size_t newSize = file->getSize() + 1;
	char* newData = new char[newSize];
	const char* oldData = file->getData();
	
	for (int i = 0; i < newSize; i++)
	{
		if (i == write_position)
			newData[i] = ch;
		else
			newData[i] = oldData[(i < write_position ? i : i - 1)];
	}

	((TextFile*)file)->setData(newData, newSize);
	delete[] newData;

	write_position += 1;
}

void EditorApplication::drawUI()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "Controls: ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	std::cout << "[ESC: Exit] ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "[ <= Left] [ => Right] ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "[Ctrl + S: Save] ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	std::cout << "[Ctrl + Shift + S: Save As]";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	std::cout << std::endl;
}

void EditorApplication::drawMenu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "Main Menu:" << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "1. Open File" << std::endl;
	std::cout << "2. Create File" << std::endl;
	std::cout << "3. Exit" << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void EditorApplication::nextLine()
{
	const char* data = file->getData();
	size_t size = file->getSize();


	size_t start_line = write_position - 1;
	while (data[start_line] != '\n' && start_line != 0) 
		start_line -= 1;
	if (start_line != 0) 
		start_line += 1;

	size_t next_line = write_position;
	while (data[next_line] != '\n')
	{
		if (next_line >= size)
			return;
		next_line += 1;
	}
	next_line += 1;

	if (write_position == 0)
	{
		write_position = next_line;
		return;
	}

	size_t end_line = next_line;
	while (data[end_line] != '\n')
	{
		if (end_line > size)
		{
			end_line = size;
			break;
		}
		end_line += 1;
	}

	write_position = next_line + write_position - start_line;
	if (write_position > end_line)
		write_position = end_line;
}

void EditorApplication::pastLine()
{
	if (write_position == 0)
		return;

	const char* data = file->getData();
	size_t size = file->getSize();

	size_t start_line = write_position - 1;
	while (data[start_line] != '\n') 
	{
		if (start_line <= 0)
			return;
		start_line -= 1;
	}
	if (start_line != 0) start_line += 1;

	size_t past_line_end = start_line - 1;
	size_t past_line_start = past_line_end - 1;

	while (data[past_line_start] != '\n' && past_line_start != 0) past_line_start -= 1;
	if (past_line_start != 0) past_line_start += 1;

	write_position = past_line_start + write_position - start_line;
	if (write_position > past_line_end)
		write_position = past_line_end;
}

void EditorApplication::draw()
{
	system("cls");
	size_t file_size = file->getSize();
	const char* data = file->getData();
	drawUI();
	for (int i = 0; i < file_size + 1; i++)
	{
		if (i == write_position)
			std::cout << '_';
		else
			std::cout << data[(i < write_position ? i : i - 1)];
	}
}

void EditorApplication::update()
{
	char user_code = _getch();
	switch (user_code)
	{
	case 8: //backspace
		if (write_position > 0)
			deleteCharacter();
		break;
	case 13: //backspace
		insertCharacter('\n');
		break;
	case 27: //ecs
		edit_cicle = false;
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
			if (write_position > 0) 
				write_position -= 1;
			break;
		case 77: //right
			if (write_position < file->getSize())  
				write_position += 1;
			break;
		case 72: //up
			pastLine();
			break;
		case 80:  //down
			nextLine();
			break;
		case 83: // del
			if (write_position < file->getSize())
			{
				write_position += 1;
				deleteCharacter();
			}
			break;
		}
		break;
	default: //others
		insertCharacter(user_code);
		break;
	}

	
}

void EditorApplication::editFile()
{
	edit_cicle = true;
	write_position = 0;

	while (edit_cicle)
	{
		draw();
		update();
	}
	TextFileFactory().close(file);
} 

void EditorApplication::loadFile()
{
	std::string fileName;

	std::cout << "Enter file name: ";
	std::getline(std::cin, fileName);
	std::cout << fileName << std::endl;
	if (file)
		delete file;
	file = TextFileFactory().openFile(fileName.c_str());
	if (file->getSize() == 0)
	{
		std::cout << "File not found!!! Create new file in procces... (press any key to continue)";
		_getch();
	}
}

void EditorApplication::createFile()
{
	std::string fileName;

	std::cout << "Enter file name: ";
	std::getline(std::cin, fileName);

	file = TextFileFactory().createFile(fileName.c_str());
}

void EditorApplication::saveFile()
{
	system("cls");
	if (TextFileFactory().saveFile(file))
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
}

void EditorApplication::saveFileAs()
{
	std::string fileName;

	system("cls");

	std::cout << "Enter file name to save: ";
	std::getline(std::cin, fileName);

	if (TextFileFactory().saveFileAs(file, fileName.c_str()))
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
}

void EditorApplication::menu()
{
	while (true)
	{
		system("cls");
		drawMenu();
		
		switch (_getch())
		{
			case '1':
				loadFile();
				editFile();
				break;
			case '2':
				createFile();
				editFile();
				break;
			case '3':
				return;
		}
	}
}
