#include "FileInterface.h"

myFiles::FileInterface::FileInterface(const char* pFileName) : fileName{ nullptr }
{
	setName(pFileName);
}

myFiles::FileInterface::~FileInterface()
{
	if (fileName)
		delete[] fileName;
}

const char* myFiles::FileInterface::getName() const
{
	return fileName;
}

inline void myFiles::FileInterface::setName(const char* pName)
{
	if (!pName)
		return;

	if (fileName)
		delete[] fileName;

	long long size = 0;
	while (pName[size++] != '\0');

	fileName = new char[size + 1];
	for (int i = 0; i < size; i++)
		fileName[i] = pName[i];
}



myFiles::TextFile::TextFile(const char* pName, const char* pData, size_t pSize) : myFiles::FileInterface{ pName }
{
	if (size <= 0 || !pData)
	{
		data = nullptr;
		size = 0;
		return;
	}

	data = new char[pSize];
	for (int i = 0; i < pSize; i++)
		data[i] = pData[i];

	size = pSize;
}

myFiles::TextFile::TextFile(const myFiles::TextFile& other)
{
	setName(other.getName());
	setData(other.getData(), other.getSize());
}

myFiles::TextFile::~TextFile()
{
	close();
}

myFiles::FileInterface& myFiles::TextFile::operator=(myFiles::FileInterface* other)
{
	close();
	setName(other->getName());
	setData(other->getData(), other->getSize());
	return *this;
}

bool myFiles::TextFile::save()
{
	if (!fileName || !data)
		return false;

	FILE* file;
	if (fopen_s(&file, fileName, "wb") != 0)
		return false;
	fwrite(data, 1, size, file);
	fclose(file);

	return true;
}

void myFiles::TextFile::close()
{
	if (fileName)
	{
		delete[] fileName;
		fileName = nullptr;
	}
	if (data)
	{
		delete[] data;
		data = nullptr;
	}
	size = 0;
}

void myFiles::TextFile::setData(const char* pData, size_t pSize)
{
	if (data)
		delete[] data;

	data = new char[pSize];
	size = pSize;
	for (int i = 0; i < size; i++)
		data[i] = pData[i];
}

const char* myFiles::TextFile::getData() const
{
	return data;
}

size_t myFiles::TextFile::getSize() const
{
	return size;
}

void myFiles::TextFile::read()
{
	FILE* file;
	if (fopen_s(&file, fileName, "rb") != 0) {
		return;
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* data_buffer = new char[file_size];
	size_t bytes_read = fread(data_buffer, 1, file_size, file);

	if (bytes_read != file_size)
	{
		delete[] data_buffer;
		fclose(file);
		return;
	}
	fclose(file);

	setData(data_buffer, file_size);
}
