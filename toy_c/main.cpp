#include "Lexer.h"
#include "Input.h"
#include <iostream>
#include <fstream>

using namespace TC_NAMESPACE;

int main(int argc, char* argv[])
{
	try
	{
		auto* input = Input::GenWithFile(argv[1]);
		std::ofstream output(argv[2]);

		Lexer lexer;
		lexer.Attach(input);

		while (true)
		{
			Token token = lexer.GetToken();
			if (TK_EOF == token.type)
			{
				break;
			}

			// 宏
			if (TK_MACRO_START < token.type && token.type < TK_MACRO_END)
			{
				output << token.str;

				// 间隔符token
				lexer.SetChFlag(' ', FLAG_CH_SINGLE_TOKEN);
				lexer.SetChFlag('\t', FLAG_CH_SINGLE_TOKEN);

				while (true)
				{
					token = lexer.GetToken();

					if (TK_BACKSLASH == token.type)
					{
						output << token.str;

						token = lexer.GetToken();
						if (TK_NEW_LINE == token.type)
						{
							output << token.str;
						}

						continue;
					}

					if (TK_NEW_LINE == token.type || TK_EOF == token.type) { break; }

					output << token.str;
				}

				// 恢复间隔符
				lexer.SetChFlag(' ', FLAG_CH_INTER_TOKEN);
				lexer.SetChFlag('\t', FLAG_CH_INTER_TOKEN);
			}

			if ("\n" != token.str)
			{
				output << token.str << " ";
			}
			else
			{
				output << std::endl;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;

		return -1;
	}
}


