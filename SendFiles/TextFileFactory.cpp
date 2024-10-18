
#include "TextFileFactory.h"


FileEditor* TextFileFactory::createFile(const char* pName)
{
    return new TextFile{pName, nullptr, 0};
}

FileEditor* TextFileFactory::openFile(const char* pName)
{
    FileEditor* textFile = new TextFile{ pName, nullptr, 0 };
    textFile->read();

    return textFile;
}


bool TextFileFactory::saveFile(FileEditor* fileEditor)
{
    return fileEditor->save();
}

bool TextFileFactory::saveFileAs(FileEditor* fileEditor, const char* pName)
{
    fileEditor->setName(pName);
    return fileEditor->save();
}

void TextFileFactory::close(FileEditor* fileEditor)
{
    fileEditor->close();
}

void TextFileFactory::display(const FileEditor* fileEditor)
{
    if (fileEditor->getData())
        std::cout << fileEditor->getData() << std::endl;
    else
        std::cout << "None" << std::endl;
}

