#pragma once
#include <vector>

#include "Lexer.h"
#include "AbstractSyntaxTree.h"

using namespace interpreter;

class Parser
{
private:
    std::unique_ptr<Lexer> m_lexer;
    std::vector<Token>::const_iterator m_currentToken;
    std::vector<Token>::const_iterator m_nextToken;
    std::vector<Token>::const_iterator m_endToken;

public:
    Parser(std::unique_ptr<Lexer> _lexer);
    std::unique_ptr<Program> parseProgram();

private:
    std::unique_ptr<LetStatement> parseLetStatement();
    std::unique_ptr<ReturnStatement> parseReturnStatement();

    void advanceToken();
    std::unique_ptr<Statement> parseStatement();
};


