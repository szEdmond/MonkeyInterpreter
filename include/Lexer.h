#pragma once
#include <string_view>
#include <iostream>

#include "Token.h"

namespace interpreter
{
	class Lexer {
	public:
		Lexer(std::string_view);
		Token nextToken();
		std::vector<Token> m_tokens;
		std::vector<Token> getTokens() { return m_tokens; };

	private:
		std::string m_input;
		std::string::iterator m_position;
		std::string::iterator m_readPosition;
		char m_char;

		void readChar();
		void skipWhitespace();
		char peekChar();
		std::string_view readIdentifier();
		std::string_view readNumber();

		void Tokenize();
	};
}

