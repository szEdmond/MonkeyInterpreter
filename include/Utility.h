#pragma once
#include <string>
#include "Token.h"
#include <assert.h>


namespace interpreter
{
	namespace utility
	{
		bool isLetter(char character);
		bool isDigit(char character);
		TokenType lookupIdent(std::string_view);
	}
}

