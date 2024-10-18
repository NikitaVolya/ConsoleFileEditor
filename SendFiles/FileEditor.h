#pragma once
#include <stdio.h>
#include <iostream>

class FileEditor
{
protected:
	char* fileName;
public:
	FileEditor() : fileName(nullptr) {};
	FileEditor(const char* pFileName);
	~FileEditor();

	virtual FileEditor& operator=(FileEditor* other) = 0;

	const char* getName() const { return fileName; }
	void setName(const char* pName);


	virtual const char* getData() const = 0;
	virtual size_t getSize() const = 0;	

	virtual bool save() = 0;
	virtual void close() = 0;

	virtual void read() = 0;
};



class TextFile : public FileEditor
{
private:
	char* data;
	size_t size;
public:
	TextFile() : TextFile(nullptr, nullptr, 0) {};
	TextFile(const char* pName, const char* pData, size_t size);
	TextFile(const TextFile& other);
	~TextFile();

	FileEditor& operator=(FileEditor* other);

	bool save();
	void close();

	void setData(const char* pData, size_t size);

	const char* getData() const { return data; }
	size_t getSize() const { return size; }

	void read();
};
