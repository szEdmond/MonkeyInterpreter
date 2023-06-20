#pragma once
#include <string>
#include <assert.h>
#include <fstream>
#include <sstream>

#include "Token.h"

namespace interpreter
{
	namespace utility
	{
		bool isLetter(char character);
		bool isDigit(char character);
		TokenType lookupIdent(std::string_view);
		std::string stringFromFile(std::string_view fileName);
	}
}

