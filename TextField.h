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
		bool update_screen;
		COORD screen_position;
		COORD position;
		COORD last_screen_size;

		size_t getIndexPosition(COORD coord);

		size_t getSizeOfLine(size_t n);
		size_t getStartOfLine(size_t n);
		size_t getEndOfLine(size_t n);

		void move_screen();

		COORD getConsoleSize();

		void draw();
		void update();

	public:
		TextField(FileEditorInterface* pOwner) : owner{ pOwner }, update_screen{true}, edit_circle{ true },
			screen_position{ 0, 0 }, position{ 0, 0 }, last_screen_size{getConsoleSize()} {};

		size_t getIndexPosition();

		void left_cursor();
		void right_cursor();
		
		void up_cursor();
		void down_cursor();

		void startEditing();
		void stopEditing();

		void update_scr();
	};

}
