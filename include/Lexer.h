#pragma once
#include "Token.h"
#include <string_view>
#include <iostream>

namespace interpreter
{
	class Lexer {
	public:
		Lexer(std::string_view);
		Token nextToken();
		std::vector<Token> getTokens() { return _tokens; };

	private:
		std::string _input;
		std::string::iterator _position;
		std::string::iterator _readPosition;
		char _ch;
		std::vector<Token> _tokens;

		void readChar();
		void skipWhitespace();
		char peekChar();
		std::string_view readIdentifier();
		std::string_view readNumber();

		void Tokenize();
	};
}

