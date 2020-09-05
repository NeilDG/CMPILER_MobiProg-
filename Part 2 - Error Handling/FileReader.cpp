#include "FileReader.h"
#include "MobiProgParser.h"

FileReader::FileReader(String directory)
{
	this->directory = directory;
}

FileReader::~FileReader()
{
}

void FileReader::readFromFile()
{
	String fileDir = this->directory + ".mobiprog";
	if (this->directory.find(".mobiprog") != String::npos) {
		fileDir = this->directory;
	}

	MobiProgParser::getInstance()->setScript(fileDir);
}
