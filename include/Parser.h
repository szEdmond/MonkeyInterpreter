#pragma once
#include <vector>
#include <functional>

#include "Lexer.h"
#include "AbstractSyntaxTree.h"

typedef std::function<std::unique_ptr<Expression>()> prefixParseFnPtr;
typedef std::function<std::unique_ptr<Expression>(std::unique_ptr<Expression>)> infixParseFnPtr;

using namespace interpreter;

enum Precedence : int{
    _ = 0,
    LOWEST = 1,
    EQUALS = 2,
    LESSGREATER = 3,
    SUM = 4,
    PRODUCT = 5,
    PREFIX = 6,
    CALL = 7
};

static const std::unordered_map<TokenType, Precedence> precedences{
    {TokenType::EQ, EQUALS},
    {TokenType::NOT_EQ, EQUALS},
    {TokenType::LT, LESSGREATER},
    {TokenType::GT, LESSGREATER},
    {TokenType::PLUS, SUM},
    {TokenType::MINUS, SUM},
    {TokenType::SLASH, PRODUCT},
    {TokenType::ASTERISK, PRODUCT}
};


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
    std::unique_ptr<Expression> parseIntegerLiteral();
    std::unique_ptr<Expression> parsePrefixExpression();
    std::unique_ptr<Expression> parseInfixExpression(std::unique_ptr<Expression> left);

    void advanceToken();

    int peekPrecedence();
    int currPrecedence();

    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Expression> parseExpression(int precedence);

    std::unique_ptr<Expression> parseIdentifier();

};


