#include "Parser.h"

Parser::Parser(std::unique_ptr<Lexer> _lexer)
    : m_lexer(std::move(_lexer))
{
    if (!m_lexer->m_tokens.empty())
    {
        m_currentToken = m_lexer->m_tokens.begin();
        m_nextToken = m_currentToken + 1;
        m_endToken = m_lexer->m_tokens.end();
    }
    
    m_prefixParseFns.emplace(TokenType::IDENT, std::bind(&Parser::parseIdentifier, this));
    m_prefixParseFns.emplace(TokenType::INT, std::bind(&Parser::parseIntegerLiteral, this));
    m_prefixParseFns.emplace(TokenType::BANG, std::bind(&Parser::parsePrefixExpression, this));
    m_prefixParseFns.emplace(TokenType::MINUS, std::bind(&Parser::parsePrefixExpression, this));

    m_infixParseFns.emplace(TokenType::PLUS, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
    m_infixParseFns.emplace(TokenType::MINUS, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
    m_infixParseFns.emplace(TokenType::SLASH, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
    m_infixParseFns.emplace(TokenType::ASTERISK, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
    m_infixParseFns.emplace(TokenType::EQ, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
    m_infixParseFns.emplace(TokenType::NOT_EQ, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
    m_infixParseFns.emplace(TokenType::LT, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
    m_infixParseFns.emplace(TokenType::GT, std::bind(&Parser::parseInfixExpression, this, std::placeholders::_1));
}

void Parser::advanceToken()
{
    if (m_nextToken == m_endToken)
    {
        return;
    }

    m_currentToken = m_nextToken;
    ++m_nextToken;
}

int Parser::peekPrecedence()
{
    if (const auto precedenceIt = precedences.find(m_nextToken->m_type); precedenceIt != precedences.end())
    {
        return precedenceIt->second;
    }
    return LOWEST;

}

int Parser::currPrecedence()
{    
    if (const auto precedenceIt = precedences.find(m_currentToken->m_type); precedenceIt != precedences.end())
    {
        return precedenceIt->second;
    }
    return LOWEST;
}

std::unique_ptr<Program> Parser::parseProgram() {
    auto program = std::make_unique<Program>();
    
    while (m_currentToken->m_type != TokenType::ENDF)
    {
        auto statement{ parseStatement() };
        if (statement != nullptr)
        {
            program->statements.push_back(std::move(statement));
        }
        advanceToken();
    }
    return program;
}

std::unique_ptr<Statement> Parser::parseStatement() {
    switch (m_currentToken->m_type)
    {
    case TokenType::LET:
        return parseLetStatement();
    case TokenType::RETURN:
        return parseReturnStatement();
    default:
        return parseExpressionStatement();
    }
    return nullptr;
}

std::unique_ptr<LetStatement> Parser::parseLetStatement() {
    auto statement = std::make_unique<LetStatement>();
    statement->token = *m_currentToken;

    if (m_nextToken->m_type != TokenType::IDENT)
    {
        return nullptr;
    }

    advanceToken();
    auto identifier = std::make_unique<Identifier>();
    identifier->identifierToken = *m_currentToken;
    identifier->identifierValue = m_currentToken->m_literal;
    statement->name = std::move(identifier);

    if (m_nextToken->m_type != TokenType::ASSIGN)
    {
        return nullptr;
    }

    while (m_currentToken->m_type != TokenType::SEMICOLON)
    {
        advanceToken();
    }

    return statement;
}

std::unique_ptr<ReturnStatement> Parser::parseReturnStatement()
{
    auto statement = std::make_unique<ReturnStatement>();
    statement->token = *m_currentToken;

    advanceToken();
    while (m_currentToken->m_type != TokenType::SEMICOLON)
    {
        advanceToken();
    }
    return statement;
}

std::unique_ptr<Expression> Parser::parseExpression(int precedence)
{
    if (m_prefixParseFns.find(m_currentToken->m_type) == m_prefixParseFns.end())
    {
        //error msg;
        return nullptr;
    }
    prefixParseFnPtr prefix = m_prefixParseFns[m_currentToken->m_type]; // get types corresponding prefixParseFunction

    auto leftExp = prefix();

    while (m_nextToken->m_type != TokenType::SEMICOLON && precedence < peekPrecedence())
    {
        // if nexttoken not infix return else infix
        if (m_infixParseFns.find(m_nextToken->m_type) == m_infixParseFns.end())
        {
            return leftExp;
        }
        infixParseFnPtr infix = m_infixParseFns[m_nextToken->m_type];
        
        //if (infix = nullptr)
        //    return leftExp;
        advanceToken();
        leftExp = infix(std::move(leftExp));
    }

    return leftExp;
}

std::unique_ptr<ExpressionStatement> Parser::parseExpressionStatement()
{
    auto statement = std::make_unique<ExpressionStatement>();
    statement->token = *m_currentToken; //
    statement->expression = parseExpression(Precedence::LOWEST);

    if (m_nextToken->m_type == TokenType::SEMICOLON) {
        advanceToken();
    }

    return statement;
}

std::unique_ptr<Expression> Parser::parseIntegerLiteral()
{
    auto intLiteral = std::make_unique<IntegerLiteral>();
    int val = std::stoi(m_currentToken->m_literal);
    
    intLiteral->value = val;
    return intLiteral;

}

std::unique_ptr<Expression> Parser::parsePrefixExpression()
{
    auto prefixExpression = std::make_unique<PrefixExpression>();
    prefixExpression->token = *m_currentToken;
    prefixExpression->op = m_currentToken->m_literal;

    advanceToken();
    prefixExpression->right = parseExpression(PREFIX);
    return prefixExpression;
}

std::unique_ptr<Expression> Parser::parseInfixExpression(std::unique_ptr<Expression> _left)
{
    auto expression = std::make_unique<InfixExpression>();
    expression->token = *m_currentToken;
    expression->op = m_currentToken->m_literal;
    expression->left = std::move(_left);

    int precedence = currPrecedence();
    advanceToken();
    expression->right = parseExpression(precedence);

    return expression;
}

std::unique_ptr<Expression> Parser::parseIdentifier() {
    auto exp = std::make_unique<Identifier>();
    exp->identifierToken = *m_currentToken;
    exp->identifierValue = (*m_currentToken).m_literal;

    return exp;
}

