
#include <iostream>
#include "FileInterface.h"

namespace myFiles
{
	class FileFactory
	{
	public:
		virtual FileInterface* createFile(const char* pName) = 0;
		virtual FileInterface* openFile(const char* pName) = 0;

		virtual void writeData(FileInterface* fileEditor, const char* data, size_t size) = 0;
		virtual bool saveFile(FileInterface* fileEditor) = 0;
		virtual bool saveFileAs(FileInterface* fileEditor, const char* pName) = 0;
		virtual void close(FileInterface* fileEditor) = 0;
	};
}

