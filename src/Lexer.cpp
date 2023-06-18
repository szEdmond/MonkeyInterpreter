#include "Lexer.h"
#include "Utility.h"

namespace interpreter
{
	Lexer::Lexer(std::string_view input) :
		_input(input),
		_position(_input.begin()),
		_readPosition(_position + 1)
	{
		assert(!input.empty());
		if (_position != _input.end())
		{
			_ch = *_position;
		}
	}

	void Lexer::readChar()
	{
		if (_readPosition == _input.end())
		{
			_ch = 0;
			return;
		}

		_ch = *_readPosition;

		_position = _readPosition;
		++_readPosition;
	}

	void Lexer::skipWhitespace()
	{
		while (_ch == ' ' || _ch == '\t' || _ch == '\n' || _ch == '\r')
		{
			readChar();
		}
	}

	Token Lexer::nextToken()
	{
		Token token;

		skipWhitespace();

		switch (_ch)
		{
		case '=':
			token = { TokenType::ASSIGN, _ch };
			break;
		case ';':
			token = { TokenType::SEMICOLON, _ch };
			break;
		case '(':
			token = { TokenType::LPAREN, _ch };
			break;
		case ')':
			token = { TokenType::RPAREN, _ch };
			break;
		case '{':
			token = { TokenType::LBRACE, _ch };
			break;
		case '}':
			token = { TokenType::RBRACE, _ch };
			break;
		case '+':
			token = { TokenType::PLUS, _ch };
			break;
		case ',':
			token = { TokenType::COMMA, _ch };
			break;
		case 0:
			token._literal = "";
			token._type = TokenType::ENDF;
			break;
		default:
			if (utility::isLetter(_ch))
			{
				std::string_view identifier{ readIdentifier() };
				token = { utility::lookupIdent(identifier), std::string(identifier) };
				return token;
			}
			else if (utility::isDigit(_ch))
			{
				token = { TokenType::INT, std::string(readNumber()) };
				return token;
			}
			else {
				token = { TokenType::ILLEGAL, _ch };
			}
		}
		readChar();

		return token;
	}

	std::string_view Lexer::readNumber()
	{
		for (; _readPosition != _input.end() && utility::isDigit(*_readPosition); _readPosition++)
		{
		}

		std::string_view result{ _position, _readPosition };
		readChar();
		return result;
	}

	std::string_view Lexer::readIdentifier()
	{
		for (; _readPosition != _input.end() && utility::isLetter(*_readPosition); _readPosition++)
		{
		}

		std::string_view identifier{ _position, _readPosition };
		readChar();
		return identifier;
	}
}
