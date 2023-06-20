#include "Utility.h"
namespace interpreter 
{
	namespace utility 
	{
		bool isLetter(char ch)
		{
			return ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_');
		}

		bool isDigit(char ch)
		{
			return '0' <= ch && ch <= '9';
		}

		TokenType lookupIdent(std::string_view literal)
		{
			std::string word{ literal };
			if (const auto keywordIter{ sKeyWordsMap.find(word) }; keywordIter != sKeyWordsMap.end())
			{
				return keywordIter->second;
			}
			return TokenType::IDENT;
		}

		std::string stringFromFile(std::string_view fileName)
		{
			assert(!fileName.empty());
			std::ifstream f(fileName.data());
			std::stringstream buffer;
			buffer << f.rdbuf();
			return buffer.str();
		}
	}
}
