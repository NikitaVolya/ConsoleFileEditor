#pragma once

#include "FileInterface.h"

namespace myEditor {

	class FileEditorInterface
	{
	protected:
		myFiles::FileInterface* file;

		virtual void deleteCharacter() = 0;
		virtual void insertCharacter(char ch) = 0;

	public:
		FileEditorInterface() : file{ nullptr } {};

		virtual void drawUI() = 0;
		virtual void inputs() = 0;

		const myFiles::FileInterface* getFile() { return file; }

		virtual void loadFile() = 0;
		virtual void createFile() = 0;
		virtual void saveFile() = 0;
		virtual void saveFileAs() = 0;

		virtual void start() = 0;
	};
}