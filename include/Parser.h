#pragma once
#include <vector>
#include <functional>

#include "Lexer.h"
#include "AbstractSyntaxTree.h"

typedef std::function<std::unique_ptr<Expression>()> prefixParseFnPtr;
typedef std::function<std::unique_ptr<Expression>(std::unique_ptr<Expression>)> infixParseFnPtr;

using namespace interpreter;

class Parser
{
private:
    std::unique_ptr<Lexer> m_lexer;
    std::vector<Token>::const_iterator m_currentToken;
    std::vector<Token>::const_iterator m_nextToken;
    std::vector<Token>::const_iterator m_endToken;

    std::unordered_map<TokenType, prefixParseFnPtr> m_prefixParseFns;
    std::unordered_map<TokenType, infixParseFnPtr> m_infixParseFns;

public:
    Parser(std::unique_ptr<Lexer> _lexer);
    std::unique_ptr<Program> parseProgram();


private:
    std::unique_ptr<LetStatement> parseLetStatement();
    std::unique_ptr<ReturnStatement> parseReturnStatement();
    std::unique_ptr<ExpressionStatement> parseExpressionStatement();

    void advanceToken();
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Expression> parseExpression(int precedence);

    std::unique_ptr<Expression> parseIdentifier() {
        auto exp = std::make_unique<Identifier>();
        exp->identifierToken = *m_currentToken;
        exp->identifierValue = (*m_currentToken).m_literal;
        
        return exp;
    }

};


