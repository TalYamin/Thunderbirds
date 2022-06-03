#pragma once

#include <fstream>

using namespace std;

class BoardFiles {

	ifstream stepsIn;
	ofstream stepsOut;
	ifstream resultIn;
	ofstream resultOut;

	BoardFiles();
	~BoardFiles();


public:
	ifstream& getStepsIn();
	ifstream& getReusltIn();
	ofstream& getStepsOut();
	ofstream& getResultOut();

	void stepsInOpener(string fileName);
	void stepsOutOpener(string fileName);
	void resultInOpener(string fileName);
	void resultOutOpener(string fileName);
	void closeAllFiles();

private:
	void stepsInCloser();
	void stepsOutCloser();
	void resultInCloser();
	void resultOutCloser();
};