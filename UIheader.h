#pragma once

#include "vector"
#include "Windows.h"
#include "iostream"

class UIheader
{
private:
	struct UIelement
	{
		char* text;
		short color;
	};

	std::vector<UIelement*> elements;

	size_t getWidth();
public:
	UIheader() {};
	~UIheader();

	size_t getSize();
	size_t getHeight();

	void appendElement(const char* text, short color);

	void draw();
};

