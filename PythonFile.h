#pragma once
#include "FileInterface.h"

class PythonFile : public myFiles::TextFile
{
public:
	PythonFile() : TextFile(nullptr, nullptr, 0) {};
	PythonFile(const char* pName, const char* pData, size_t size) : myFiles::TextFile{ pName, pData, size } {};
	PythonFile(const TextFile& other) : myFiles::TextFile{ other } {};

	void execute() const;
};

