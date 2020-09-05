#include "ErrorInfo.h"

ErrorInfo::ErrorInfo()
{
}

ErrorInfo::~ErrorInfo()
{
}

int ErrorInfo::getLineNumber()
{
	return this->lineNumber;
}

void ErrorInfo::setLineNumber(int lineNo)
{
	this->lineNumber = lineNo;
}

int ErrorInfo::getCharNumber()
{
	return this->charNumber;
}

void ErrorInfo::setCharNum(int num)
{
	this->charNumber = num;
}
