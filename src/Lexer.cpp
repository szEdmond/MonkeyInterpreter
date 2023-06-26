#include "Lexer.h"
#include "Utility.h"

namespace interpreter
{
	Lexer::Lexer(std::string_view input) :
		m_input(input),
		m_position(m_input.begin()),
		m_readPosition(m_position + 1)
	{
		assert(!input.empty());

		if(m_position != m_input.end())
		{
			m_char = *m_position;
		}
		Tokenize();
	}

	void Lexer::readChar()
	{
		if (m_readPosition == m_input.end())
		{
			m_char = 0;
			return;
		}
		m_position = m_readPosition;
		++m_readPosition;
		m_char = *m_position;
	}

	void Lexer::skipWhitespace()
	{
		while (m_char == ' ' || m_char == '\t' || m_char == '\n' || m_char == '\r')
		{
			readChar();
		}
	}

	Token Lexer::nextToken()
	{
		Token token;

		skipWhitespace();

		switch (m_char)
		{
		case '=':
			if (peekChar() == '=') {
				token = { TokenType::EQ, "==" };
				readChar();
				break;
			}
			token = { TokenType::ASSIGN, m_char };
			break;
		case '!':
			if (peekChar() == '=') {
				token = { TokenType::NOT_EQ, "!=" };
				readChar();
				break;
			}
			token = { TokenType::BANG, m_char };
			break;
		case '(':
			token = { TokenType::LPAREN, m_char };
			break;
		case ')':
			token = { TokenType::RPAREN, m_char };
			break;
		case '{':
			token = { TokenType::LBRACE, m_char };
			break;
		case '}':
			token = { TokenType::RBRACE, m_char };
			break;
		case '+':
			token = { TokenType::PLUS, m_char };
			break;
		case '-':
			token = { TokenType::MINUS, m_char };
			break;
		case '/':
			token = { TokenType::SLASH, m_char };
			break;
		case '*':
			token = { TokenType::ASTERISK, m_char };
			break;
		case '<':
			token = { TokenType::LT, m_char };
			break;
		case '>':
			token = { TokenType::GT, m_char };
			break;
		case ',':
			token = { TokenType::COMMA, m_char };
			break;
		case ';':
			token = { TokenType::SEMICOLON, m_char };
			break;
		case 0:
			token.m_literal = "";
			token.m_type = TokenType::ENDF;
			break;
		default:
			if (utility::isLetter(m_char))
			{
				std::string identifier{ readIdentifier() };
				token = { utility::lookupIdent(identifier), std::string(identifier) };
				return token;
			}
			else if (utility::isDigit(m_char))
			{
				token = { TokenType::INT, std::string(readNumber()) };
				return token;
			}
			else {
				token = { TokenType::ILLEGAL, m_char };
			}
		}
		readChar();

		return token;
	}

	std::string_view Lexer::readNumber()
	{
		for (; m_readPosition != m_input.end() && utility::isDigit(*m_readPosition); m_readPosition++)
		{
		}

		std::string_view result{ m_position, m_readPosition };
		readChar();
		return result;
	}

	std::string_view Lexer::readIdentifier()
	{
		for (; m_readPosition != m_input.end() && utility::isLetter(*m_readPosition); m_readPosition++)
		{
		}

		std::string_view identifier{ m_position, m_readPosition };
		readChar();
		return identifier;
	}

	char Lexer::peekChar()
	{
		if (m_readPosition >= m_input.end())
		{
			return 0;
		}
		else 
		{
			return *m_readPosition;
		}
	}
	
	void Lexer::Tokenize()
	{
		Token token{ nextToken() };
		while (token.m_type != TokenType::ENDF)
		{
			m_tokens.push_back(token);
			token = nextToken();
		}
		m_tokens.push_back(token);
	}
}
