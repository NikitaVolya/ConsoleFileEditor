#pragma once

#include "TextField.h"

class FileApplicationInterface
{
protected:
	myFiles::FileEditorInterface* file;

	virtual void drawUI() = 0;
	virtual void inputs() = 0;

	virtual void deleteCharacter() = 0;
	virtual void insertCharacter(char ch) = 0;

public:
	virtual void loadFile() = 0;
	virtual void createFile() = 0;
	virtual void saveFile() = 0;
	virtual void saveFileAs() = 0;

	virtual void start() = 0;
};