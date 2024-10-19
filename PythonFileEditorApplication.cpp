#include "PythonFileEditorApplication.h"

bool myEditor::PythonFileEditorApplication::validSyb(char symb)
{
	if ((symb >= 65 && symb <= 90) ||
		(symb >= 97 && symb <= 122) ||
		(symb >= 48 && symb <= 57) ||
		symb == 32)
		return true;

	char punctuationAndSymbols[] = {
	'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'
	};

	for (int i = 0; i < 32; i++)
		if (symb == punctuationAndSymbols[i])
			return true;

	return false;
}

myEditor::PythonFileEditorApplication::PythonFileEditorApplication() : TextFileEditorApplication{}
{
	header.appendElement("[ execute F10 ]", 2);
}

void myEditor::PythonFileEditorApplication::inputs()
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
	case 68:
		system("cls");
		myFiles::PythonFileFactory().execute(file);
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
		if (validSyb(user_code))
			insertCharacter(user_code);
		break;
	}
}