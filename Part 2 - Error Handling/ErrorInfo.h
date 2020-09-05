#pragma once
#include <string>
//Represents an error encountered by the error listener.
//Used for printing error messages in the console
//By: NeilDG
class MobiErrorListener;
class Debug;
class ErrorInfo
{
public:
	typedef std::string String;
	
	enum ErrorType {
		NO_VIABLE_ALTERNATIVE = 0,
		MISSING = 1,
		MISMATCHED_INPUT = 2,
		EXTRANEOUS_INPUT = 3,
		TOKEN_RECOGNITION = 4
	};

	ErrorInfo();
	~ErrorInfo();

	int getLineNumber();
	void setLineNumber(int lineNo);
	int getCharNumber();
	void setCharNum(int num);

private:
	const String NO_VIABLE_ALT_KEY = "no viable alternative at input";
	const String MISSING_KEY = "missing";
	const String MISMATCHED_INPUT_KEY = "mismatched input";
	const String EXTRANEOUS_INPUT_KEY = "extraneous input";
	const String TOKEN_RECOGNITION_KEY = "token recognition error";

	friend MobiErrorListener;
	friend Debug;

	int lineNumber = -1;
	int charNumber = -1;
	ErrorType type;
};

