#include "MobiErrorListener.h"
#include "Debug.h"
#include <sstream>
#include "ErrorInfo.h"
#include "StringUtils.h"
#include <vector>

typedef std::vector<String> List;
void MobiErrorListener::syntaxError(Recognizer* recognizer, Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e)
{
	std::stringstream buffer;
	ErrorInfo errorInfo;

	//has found substring
	if (msg.find(errorInfo.NO_VIABLE_ALT_KEY) != String::npos) {
		errorInfo.setLineNumber(line);

		buffer << "Error line #" << errorInfo.getLineNumber() << ": Could not resolve the token " << offendingSymbol->getText();
		Debug::Log(buffer.str());
	}

	if (msg.find(errorInfo.MISSING_KEY) != String::npos) {
		errorInfo.setLineNumber(line);
		List wordList = StringUtils::split(msg, ' ');
		buffer << "Error line #" << errorInfo.getLineNumber() << ": Missing: " << wordList[1] <<". Try adding this token just before " << wordList[3];
		Debug::Log(buffer.str());
	}
}
