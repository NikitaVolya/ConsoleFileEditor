#include "TextField.h"


size_t myEditor::TextField::getIndexPosition(COORD coord)
{
	const char* data = owner->getFile()->getData();
	size_t size = owner->getFile()->getSize();
 
	size_t i = 0;
	while (coord.Y > 0)
	{
		if (i >= size)
			return size;
		if (data[i] == '\n')
			coord.Y -= 1;
		i++;
	}
	i += coord.X;

	return i;
}

size_t myEditor::TextField::getSizeOfLine(size_t n)
{
	return getEndOfLine(n) - getStartOfLine(n);
}

size_t myEditor::TextField::getStartOfLine(size_t n)
{
	return getIndexPosition(COORD{0, short(n)});
}

size_t myEditor::TextField::getEndOfLine(size_t n)
{
	size_t size = owner->getFile()->getSize();

	size_t end_of_line = getStartOfLine(n + 1);
	if (end_of_line == size)
		return size;
	return end_of_line - 1;
}

void myEditor::TextField::move_screen()
{
	COORD consoleSize = getConsoleSize();
	consoleSize.Y -= owner->getHeaderHeight() + 1;
	consoleSize.X -= owner->getHeaderHeight() + 1;

	if (position.Y < screen_position.Y)
	{
		update_screen = true;
		screen_position.Y = position.Y;
	}
	if (position.Y > screen_position.Y + consoleSize.Y)
	{
		update_screen = true;
		screen_position.Y = position.Y - consoleSize.Y;
	}

	if (position.X < screen_position.X)
	{
		update_screen = true;
		screen_position.X = position.X;
	}
	if (position.X > screen_position.X + consoleSize.X)
	{
		update_screen = true;
		screen_position.X = position.X - consoleSize.X;
	}
}


COORD myEditor::TextField::getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		return COORD{ static_cast<short>(csbi.srWindow.Right - csbi.srWindow.Left + 1),
			          static_cast<short>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)};
	}
	return COORD{ 0, 0 };
}

void myEditor::TextField::left_cursor()
{
	if (getIndexPosition(position) == 0)
		return;
	
	if (position.X > 0)
		position.X -= 1;
	else
	{
		position.Y -= 1;
		position.X = getSizeOfLine(position.Y);
	}
}

void myEditor::TextField::right_cursor()
{
	if (getIndexPosition() == owner->getFile()->getSize())
		return;

	size_t line_size = getSizeOfLine(position.Y);
	if (position.X < line_size)
		position.X += 1;
	else {
		position.Y += 1;
		position.X = 0;
	}
}

void myEditor::TextField::down_cursor()
{
	if (getEndOfLine(position.Y) == getEndOfLine(position.Y + 1))
		return;

	if (position.X <= getSizeOfLine(position.Y + 1))
		position.Y += 1;
	else
	{
		position.Y += 1;
		position.X = getSizeOfLine(position.Y);
	}
}

void myEditor::TextField::up_cursor()
{
	if (position.Y == 0)
		return;
	
	if (position.X <= getSizeOfLine(position.Y - 1))
	{
		position.Y -= 1;
	}
	else
	{
		position.Y -= 1;
		position.X = getSizeOfLine(position.Y);
	}
}

void myEditor::TextField::draw()
{
	COORD size = getConsoleSize();
	if (update_screen || last_screen_size.X != size.X || last_screen_size.Y != size.Y)
	{
		system("cls");

		size_t file_size = owner->getFile()->getSize();
		const char* data = owner->getFile()->getData();

		owner->drawUI();

		for (size_t i = 0; i < size.Y - owner->getHeaderHeight(); i++)
		{
			size_t row = i + screen_position.Y;
			if (getStartOfLine(row) ==
				getSizeOfLine(row - 1))
				break;

			size_t line_start = getStartOfLine(row);
			size_t line_size = getSizeOfLine(row);
			if (line_size > screen_position.X)
				for (size_t j = 0; j < size.X; j++)
				{
					if (line_start + screen_position.X + j >= file_size)
						break;

					char ch = data[line_start + screen_position.X + j];
					if (ch == '\n')
						break;
					std::cout << ch;
				}
			if (i < size.Y - owner->getHeaderHeight() - 1)
				std::cout << '\n';
		}

	}
	update_screen = false;

	COORD cursor_display_position{0, 0};
	cursor_display_position.Y = position.Y - screen_position.Y + owner->getHeaderHeight();
	cursor_display_position.X = position.X - screen_position.X;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_display_position);
}

void myEditor::TextField::update()
{
	owner->inputs();
}

size_t myEditor::TextField::getIndexPosition()
{
	return getIndexPosition(position);
}

void myEditor::TextField::startEditing()
{
	edit_circle = true;
	position.X = 0;
	position.Y = 0;
	screen_position.X = 0;
	screen_position.Y = 0;

	while ( edit_circle)
	{
		
		draw();
		
		update();
		
		move_screen();
		last_screen_size = getConsoleSize();
	}
}

void myEditor::TextField::stopEditing()
{
	edit_circle = false;
}

void myEditor::TextField::update_scr()
{
	update_screen = true;
}
