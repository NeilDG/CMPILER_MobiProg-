#include "MobiErrorListener.h"
#include "Debug.h"
#include <sstream>

void MobiErrorListener::syntaxError(Recognizer* recognizer, Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string& msg, std::exception_ptr e)
{
	std::stringstream buffer;
	buffer << "Parser error caught by MobiErrorListener: " << msg << std::endl;
	Debug::Log(buffer.str());
}
