#pragma once
#include <string>

class MobiProgParser
{
public:
	typedef std::string String;
	static MobiProgParser* getInstance();
	static void initialize();
	static void destroy();

	void setScript(String fileDir);
	void compileScript();

private:
	MobiProgParser();
	~MobiProgParser();
	MobiProgParser(MobiProgParser const&) {};             // copy constructor is private
	MobiProgParser& operator=(MobiProgParser const&) {};  // assignment operator is private*/
	static MobiProgParser* sharedInstance;

	String openedFileDir;
};

