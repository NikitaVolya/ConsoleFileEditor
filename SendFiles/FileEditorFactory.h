
#include <iostream>
#include "FileEditor.h"


class FileEditorFactory
{
public:
	virtual FileEditor* createFile(const char* pName) = 0;
	virtual FileEditor* openFile(const char* pName) = 0;

	virtual bool saveFile(FileEditor* fileEditor) = 0;
	virtual bool saveFileAs(FileEditor* fileEditor, const char* pName) = 0;

	virtual void close(FileEditor* fileEditor) = 0;

	virtual void display(const FileEditor* fileEditor) = 0;
};