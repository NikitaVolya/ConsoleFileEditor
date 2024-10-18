#include "PythonFileFactory.h"

void myFiles::PythonFileFactory::execute(myFiles::FileInterface* file)
{
	file->save();
	((PythonFile*)file)->execute();
}
