
#ifndef FILE_FUNCTION_H
#define FILE_FUNCTION_H

#include <mutex>

#include "..\image\CImg.h"
#include "..\core\tinydir.h"

void processReadIntoArrayFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty1 = gStore->get(statement);

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty2 = gStore->get(statement);

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty3 = gStore->get(statement);

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty4 = gStore->get(statement);

	bool createdArg4 = false;

	if (argProperty4 == nullptr)
	{
		createdArg4 = true;

		argProperty4 = createNewInt(statement);
	}

	Array<int>* vRight = dynamic_cast<Array<int>*>(argProperty1);
	TypedProperty<int>* numOne = dynamic_cast<TypedProperty<int>*>(argProperty2);
	TypedProperty<int>* numTwo = dynamic_cast<TypedProperty<int>*>(argProperty3);
	TypedProperty<int>* numThree = dynamic_cast<TypedProperty<int>*>(argProperty4);

	std::string filename = v->getValue();

	cimg_library::CImg<int> src(filename.c_str());

	int width = src.width();
	int height = src.height();
	const int numberOfChannels = numThree->getValue();

	numOne->setValue(width);
	numTwo->setValue(height);

	const int arraySize = width * height * numberOfChannels;

	int* arrayData = new int[arraySize];

	int count = 0, temp1, temp2, temp3, grayValue;

	for (int r = 0; r < height; ++r)
	{
		for (int c = 0; c < width; ++c)
		{
			if (numberOfChannels == 1)
			{
				temp1 = src(c, r, 0);
				temp2 = src(c, r, 1);
				temp3 = src(c, r, 2);

				grayValue = (int)((0.33 * temp1) + (0.33 * temp2) + (0.33 * temp3));

				arrayData[count] = grayValue;
				count++;

				continue;
			}

			arrayData[count] = src(c, r, 0);
			count++;

			arrayData[count] = src(c, r, 1);
			count++;

			arrayData[count] = src(c, r, 2);
			count++;
		}
	}

	vRight->setValue(arrayData, arraySize);

	if (createdArg4)
		delete argProperty4;
}

void processWriteArrayToFileFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty1 = gStore->get(statement);

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty2 = gStore->get(statement);

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty3 = gStore->get(statement);

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty4 = gStore->get(statement);

	bool createdArg4 = false;

	if (argProperty4 == nullptr)
	{
		createdArg4 = true;

		argProperty4 = createNewInt(statement);
	}

	Array<int>* vRight = dynamic_cast<Array<int>*>(argProperty1);
	TypedProperty<int>* numOne = dynamic_cast<TypedProperty<int>*>(argProperty2);
	TypedProperty<int>* numTwo = dynamic_cast<TypedProperty<int>*>(argProperty3);
	TypedProperty<int>* numThree = dynamic_cast<TypedProperty<int>*>(argProperty4);

	std::string filename = v->getValue();

	int width = numOne->getValue();
	int height = numTwo->getValue();
	int* imageData = vRight->getValue();
	const int numberOfChannels = numThree->getValue();

	int arraySize = width * height * numberOfChannels;
	int *imageDataCopy = new int[arraySize];

	if (arraySize < vRight->getSize())
	{
		int index = 0, temp1, temp2, temp3, grayValue;

		for (int i = 0; i < arraySize; ++i)
		{
			temp1 = imageData[index];
			index++;
			temp2 = imageData[index];
			index++;
			temp3 = imageData[index];
			index++;

			grayValue = (int)((0.33 * temp1) + (0.33 * temp2) + (0.33 * temp3));

			imageDataCopy[i] = grayValue;
		}
	}
	else if (numberOfChannels == 1)
	{
		for (int i = 0; i < arraySize; ++i)
			imageDataCopy[i] = imageData[i];
	}
	else
	{
		int index = 0, i;

		for (i = 0; i < arraySize; i += 3)
		{
			imageDataCopy[index] = imageData[i];
			index++;
		}
		for (i = 1; i < arraySize; i += 3)
		{
			imageDataCopy[index] = imageData[i];
			index++;
		}
		for (i = 2; i < arraySize; i += 3)
		{
			imageDataCopy[index] = imageData[i];
			index++;
		}
	}

	cimg_library::CImg<int> image(width, height, 1, numberOfChannels);
	image._data = imageDataCopy;
	image.save(filename.c_str());

	if (createdArg4)
		delete argProperty4;
}

void processFileExistFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);

	TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(argProperty);

	std::ifstream myFile(v->getValue());

	vRight->setValueNoRef(myFile.good());
}

void processFileRemoveFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);

	TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(argProperty);
	vRight->setValueNoRef(!std::remove(v->getValue().c_str()));
}

void processFileOpenFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);

	TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(argProperty);

	const std::string filename = v->getValue();

	FileStore* fileStore = acquireFileStore();
	fileStore->add(filename);
	fileStore->open(filename);
	std::ofstream* myFile = fileStore->get(filename);
	gFileStoreMutex.unlock();

	vRight->setValueNoRef(myFile->is_open());
}

void processFileCloseFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);

	TypedProperty<bool>* vRight = dynamic_cast<TypedProperty<bool>*>(argProperty);

	const std::string filename = v->getValue();

	FileStore* fileStore = acquireFileStore();
	fileStore->close(filename);
	std::ofstream* myFile = fileStore->get(filename);
	gFileStoreMutex.unlock();

	vRight->setValueNoRef(!myFile->is_open());

	fileStore = acquireFileStore();
	fileStore->remove(filename);
	gFileStoreMutex.unlock();
}

void processGetFilesInDirFunction(Property *basicProperty, std::queue<std::string> &mArgumentQueue)
{
	TypedProperty<std::string>* v = dynamic_cast<TypedProperty<std::string>*>(basicProperty);

	std::string statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	Property *argProperty = gStore->get(statement);

	Array<std::string>* vRight = dynamic_cast<Array<std::string>*>(argProperty);
	std::vector<std::string> filenameVector;

	statement = mArgumentQueue.front();
	mArgumentQueue.pop();

	argProperty = gStore->get(statement);

	TypedProperty<int>* vSize = dynamic_cast<TypedProperty<int>*>(argProperty);

	tinydir_dir dir;
	tinydir_open(&dir, v->getValue().c_str());

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		if (file.is_reg)
			filenameVector.push_back(file.name);

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	std::string *filenameArray = new std::string[filenameVector.size()];

	const int numberOfFiles = filenameVector.size();
	for (std::vector<std::string>::size_type i = 0; i != numberOfFiles; ++i) 
		filenameArray[i] = filenameVector[i];
	
	filenameVector.clear();

	vRight->setValue(filenameArray, numberOfFiles);
	vSize->setValueNoRef(numberOfFiles);
}

#endif