#pragma once

#include "FileInterface.h"
#include "UIheader.h"

namespace myEditor {

	class FileEditorInterface
	{
	protected:
		myFiles::FileInterface* file;
		UIheader header;

		virtual void deleteCharacter() = 0;
		virtual void insertCharacter(char ch) = 0;

	public:
		FileEditorInterface() : file{ nullptr } {};

		virtual void drawUI() { header.draw(); };
		virtual size_t getHeaderHeight() { return header.getHeight(); };
		virtual void inputs() = 0;

		const myFiles::FileInterface* getFile() { return file; }

		virtual void loadFile() = 0;
		virtual void createFile() = 0;
		virtual void saveFile() = 0;
		virtual void saveFileAs() = 0;

		virtual void start() = 0;
	};
}