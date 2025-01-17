#pragma once
#include <antlr4-runtime.h>

using namespace antlr4;
class MobiErrorListener: public ANTLRErrorListener
{
    void syntaxError(Recognizer* recognizer, Token* offendingSymbol, size_t line,
        size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override;
    
    void reportAmbiguity(Parser* recognizer, const dfa::DFA& dfa, size_t startIndex, size_t stopIndex, bool exact,
        const antlrcpp::BitSet& ambigAlts, atn::ATNConfigSet* configs) override {};

    void reportAttemptingFullContext(Parser* recognizer, const dfa::DFA& dfa, size_t startIndex, size_t stopIndex,
        const antlrcpp::BitSet& conflictingAlts, atn::ATNConfigSet* configs) override {};

    void reportContextSensitivity(Parser* recognizer, const dfa::DFA& dfa, size_t startIndex, size_t stopIndex,
        size_t prediction, atn::ATNConfigSet* configs) override {};
};

