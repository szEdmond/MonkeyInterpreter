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
    
    while ((*m_currentToken).m_type != TokenType::ENDF)
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
    switch ((*m_currentToken).m_type)
    {
    case TokenType::LET:
        return parseLetStatement();
        break;
    case TokenType::RETURN:
        return parseReturnStatement();
        break;
    default:
        return nullptr;
        break;
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

    statement->identifier = *m_nextToken;
    advanceToken();

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
