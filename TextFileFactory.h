#pragma once

#include "FileFactory.h";


namespace myFiles
{

	class TextFileFactory : public FileFactory
	{
	public:
		FileInterface* createFile(const char* pName);
		FileInterface* openFile(const char* pName);

		void writeData(FileInterface* fileEditor, const char* data, size_t size);
		bool saveFile(FileInterface* fileEditor);
		bool saveFileAs(FileInterface* fileEditor, const char* pName);

		void close(FileInterface* fileEditor);
	};
}
