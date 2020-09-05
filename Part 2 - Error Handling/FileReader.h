#pragma once
#include <string>
class FileReader
{
public:
	typedef std::string String;
	FileReader(String directory);
	~FileReader();

	void readFromFile();

private:
	String directory;
};

