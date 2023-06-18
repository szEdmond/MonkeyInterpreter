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

	private:
		std::string _input;
		std::string::iterator _position;
		std::string::iterator _readPosition;
		char _ch;

		void readChar();
		void skipWhitespace();
		std::string_view readIdentifier();
		std::string_view readNumber();
	};
}

