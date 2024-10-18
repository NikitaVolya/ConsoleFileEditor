#pragma once
#include <stdio.h>
#include <iostream>

namespace myFiles 
{
	class FileInterface
	{
	protected:
		char* fileName;
	public:
		FileInterface() : fileName(nullptr) {};
		FileInterface(const char* pFileName);
		~FileInterface();

		virtual FileInterface& operator=(FileInterface* other) = 0;

		const char* getName() const;
		virtual const char* getData() const = 0;
		virtual size_t getSize() const = 0;

		void setName(const char* pName);
		virtual void setData(const char* pData, size_t size) = 0;

		virtual bool save() = 0;
		virtual void close() = 0;
		virtual void read() = 0;
	};


	class TextFile : public FileInterface
	{
	private:
		char* data;
		size_t size;
	public:
		TextFile() : TextFile(nullptr, nullptr, 0) {};
		TextFile(const char* pName, const char* pData, size_t size);
		TextFile(const TextFile& other);
		~TextFile();

		FileInterface& operator=(FileInterface* other);

		const char* getData() const override;
		size_t getSize() const override;

		void setData(const char* pData, size_t size) override;

		bool save() override;
		void close() override;
		void read() override;
	};
}