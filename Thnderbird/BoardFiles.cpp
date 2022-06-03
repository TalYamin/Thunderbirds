#include "BoardFiles.h"

BoardFiles::~BoardFiles()
{
}

ifstream& BoardFiles::getStepsIn() 
{
	return stepsIn;
}

ifstream& BoardFiles::getReusltIn()
{
	return resultIn;
}

ofstream& BoardFiles::getStepsOut()
{
	return stepsOut;
}

ofstream& BoardFiles::getResultOut()
{
	return resultOut;
}

void BoardFiles::stepsInOpener(string fileName)
{
	stepsIn.open(fileName);
}

void BoardFiles::stepsOutOpener(string fileName)
{
	stepsOut.open(fileName);

}

void BoardFiles::resultInOpener(string fileName)
{
	resultIn.open(fileName);

}

void BoardFiles::resultOutOpener(string fileName)
{
	resultOut.open(fileName);

}

void BoardFiles::closeAllFiles()
{
	stepsInCloser();
	stepsOutCloser();
	resultInCloser();
	resultOutCloser();
}

void BoardFiles::stepsInCloser()
{
	stepsIn.close();

}

void BoardFiles::stepsOutCloser()
{
	stepsOut.close();

}

void BoardFiles::resultInCloser()
{
	resultIn.close();
}

void BoardFiles::resultOutCloser()
{
	resultOut.close();

}
