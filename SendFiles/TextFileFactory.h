#pragma once


#include "FileEditorFactory.h";


class TextFileFactory : public FileEditorFactory
{
public:
	FileEditor* createFile(const char* pName);
	FileEditor* openFile(const char* pName);

	bool saveFile(FileEditor* fileEditor);
	bool saveFileAs(FileEditor* fileEditor, const char* pName);

	void close(FileEditor* fileEditor);
	void display(const FileEditor* fileEditor);
};

