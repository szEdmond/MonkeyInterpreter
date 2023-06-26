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

    if ((*m_nextToken).m_type != TokenType::IDENT)
    {
        return nullptr;
    }

    advanceToken(); //?
    auto identifier = std::make_unique<Identifier>();
    identifier->identifierToken = *m_currentToken;
    identifier->identifierValue = m_currentToken->m_literal;
    statement->name = std::move(identifier);
    //statement->name->identifierValue = t.m_literal;


    if ((*m_nextToken).m_type != TokenType::ASSIGN)
    {
        return nullptr;
    }

    while ((*m_currentToken).m_type != TokenType::SEMICOLON)
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
    while ((*m_currentToken).m_type != TokenType::SEMICOLON)
    {
        advanceToken();
    }
    return statement;
}

std::unique_ptr<Expression> Parser::parseExpression(int precedence)
{
    prefixParseFnPtr prefix = m_prefixParseFns[(*m_currentToken).m_type]; // get types corresponding prefixParseFunction
    if (prefix == nullptr)
        return nullptr;

    auto leftExpression = std::move(prefix());
    return leftExpression;
}

std::unique_ptr<ExpressionStatement> Parser::parseExpressionStatement()
{
    auto statement = std::make_unique<ExpressionStatement>();
    statement->expression = parseExpression(Precedence::LOWEST);

    if ((*m_nextToken).m_type == TokenType::SEMICOLON) {
        advanceToken();
    }

    return statement;
}
