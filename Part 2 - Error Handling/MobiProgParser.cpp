#include "MobiProgParser.h"
#include <iostream>
#include <antlr4-runtime.h>
#include "CLexer.h"
#include "CParser.h"
#include "CBaseListener.h"
#include "Debug.h"
#include "MobiErrorListener.h"

using namespace antlr4;
typedef std::fstream StreamReader;

MobiProgParser* MobiProgParser::sharedInstance = NULL;
MobiProgParser* MobiProgParser::getInstance()
{
	return sharedInstance;
}

void MobiProgParser::initialize()
{
	sharedInstance = new MobiProgParser();
}

void MobiProgParser::destroy()
{
	delete sharedInstance;
}

void MobiProgParser::setScript(String fileDir)
{
	this->openedFileDir = fileDir;
}

void MobiProgParser::compileScript()
{
	StreamReader  sourceFile;
	sourceFile.open(this->openedFileDir, std::ios::in);

	ANTLRInputStream input(sourceFile);
	CLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	CParser parser(&tokens);
	parser.removeErrorListeners();
	MobiErrorListener errorListener;
	parser.addErrorListener(&errorListener);

	CBaseListener listener;
	tree::ParseTree* tree = parser.compilationUnit();
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	Debug::Log("Successfully parsed mobiprog file.");
}

MobiProgParser::MobiProgParser()
{
}

MobiProgParser::~MobiProgParser()
{
}
