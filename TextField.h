#pragma once

#include "FileEditorInterface.h"
#include <windows.h>
#include <conio.h>


namespace myEditor {

	class TextField
	{
	protected:
		FileEditorInterface* owner;

		bool edit_circle;
		COORD screen_position;
		COORD position;

		size_t getIndexPosition(COORD coord);

		size_t getSizeOfLine(size_t n);
		size_t getStartOfLine(size_t n);
		size_t getEndOfLine(size_t n);

		void move_screen();

		COORD getConsoleSize();

		void draw();
		void update();

	public:
		TextField(FileEditorInterface* pOwner) : owner{pOwner}, edit_circle { true },
			screen_position{ 0, 0 }, position{ 0, 0 } {};

		size_t getIndexPosition();

		void left_cursor();
		void right_cursor();

		
		void up_cursor();
		void down_cursor();

		void startEditing();
		void stopEditing();
	};

}
