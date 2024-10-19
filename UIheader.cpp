#include "UIheader.h"

size_t UIheader::getWidth()
{
	size_t rep = 0;
	for (const UIelement* element : elements)
	{
		rep += std::strlen(element->text);
		rep += 1;
	}

	return rep;
}

UIheader::~UIheader()
{
	for (UIelement* element : elements)
	{
		delete[] element->text;
		delete element;
	}
	elements.clear();
}

size_t UIheader::getSize()
{
	return elements.size();
}

size_t UIheader::getHeight()
{
	size_t rep = 0;

	CONSOLE_SCREEN_BUFFER_INFO csbi_new;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi_new);

	size_t console_width = csbi_new.srWindow.Right - csbi_new.srWindow.Left;
	size_t elements_width = getWidth();

	rep += elements_width / console_width + (elements_width % console_width != 0 ? 1 : 0);
	return rep;
}

void UIheader::appendElement(const char* text, short color)
{	
	size_t size = std::strlen(text);
	UIelement* newElement = new UIelement{ new char[size + 1], color };
	
	for (int i = 0; i < size; i++)
		newElement->text[i] = text[i];
	newElement->text[size] = '\0';
	elements.push_back(newElement);
}

void UIheader::draw()
{
	for (const UIelement* element : elements)
	{
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), element->color);
		std::cout << ' ' << element->text;
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
