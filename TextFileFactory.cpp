#include "TextFileFactory.h"


myFiles::FileInterface* myFiles::TextFileFactory::createFile(const char* pName)
{
    return new TextFile{pName, nullptr, 0};
}

myFiles::FileInterface* myFiles::TextFileFactory::openFile(const char* pName)
{
    FileInterface* textFile = new TextFile{ pName, nullptr, 0 };
    textFile->read();

    return textFile;
}


void myFiles::TextFileFactory::writeData(myFiles::FileInterface* fileEditor, const char* data, size_t size)
{
    fileEditor->setData(data, size);
}

bool myFiles::TextFileFactory::saveFile(myFiles::FileInterface* fileEditor)
{
    return fileEditor->save();
}

bool myFiles::TextFileFactory::saveFileAs(myFiles::FileInterface* fileEditor, const char* pName)
{
    fileEditor->setName(pName);
    return fileEditor->save();
}

void myFiles::TextFileFactory::close(myFiles::FileInterface* fileEditor)
{
    fileEditor->close();
}
