#include "Lexer.h"
#include "Exception.h"
#include <stdio.h>

// �ؼ���
#define REGISTER_TOKEN(tokenType, tokenStr) m_tokenMap[tokenStr] = tokenType

TC_NAMESPACE::Lexer::Lexer()
{
	SetChFlag('(', FLAG_CH_SINGLE_TOKEN);
	SetChFlag(')', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('[', FLAG_CH_SINGLE_TOKEN);
	SetChFlag(']', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('{', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('}', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('<', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('>', FLAG_CH_SINGLE_TOKEN);
	SetChFlag(',', FLAG_CH_SINGLE_TOKEN);
	SetChFlag(';', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('.', FLAG_CH_SINGLE_TOKEN);
	SetChFlag(':', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('?', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('&', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('|', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('!', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('~', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('^', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('#', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('+', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('-', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('*', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('/', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('\\', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('%', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('=', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('\n', FLAG_CH_SINGLE_TOKEN);
	SetChFlag('"', FLAG_CH_SINGLE_TOKEN);

	SetChFlag(' ', FLAG_CH_INTER_TOKEN);
	SetChFlag('\t', FLAG_CH_INTER_TOKEN);
	SetChFlag('\r', FLAG_CH_INTER_TOKEN);

	REGISTER_TOKEN(TK_NEW_LINE, "\n");
	REGISTER_TOKEN(TK_TAB, "\t");

	REGISTER_TOKEN(TK_ADD, "+");
	REGISTER_TOKEN(TK_ADD_ASSIGN, "+=");
	REGISTER_TOKEN(TK_SUB, "-");
	REGISTER_TOKEN(TK_SUB_ASSIGN, "-=");
	REGISTER_TOKEN(TK_MUL, "*");
	REGISTER_TOKEN(TK_MUL_ASSIGN, "*=");
	REGISTER_TOKEN(TK_DIV, "/");
	REGISTER_TOKEN(TK_DIV_ASSIGN, "/=");
	REGISTER_TOKEN(TK_MOD, "%");
	REGISTER_TOKEN(TK_MOD_ASSIGN, "%=");
	REGISTER_TOKEN(TK_INC, "++");
	REGISTER_TOKEN(TK_DEC, "--");

	REGISTER_TOKEN(TK_AND, "&");
	REGISTER_TOKEN(TK_AND_ASSIGN, "&=");
	REGISTER_TOKEN(TK_OR, "|");
	REGISTER_TOKEN(TK_OR_ASSIGN, "|=");
	REGISTER_TOKEN(TK_NOT, "~");
	REGISTER_TOKEN(TK_NOT_ASSIGN, "~=");
	REGISTER_TOKEN(TK_XOR, "^");
	REGISTER_TOKEN(TK_XOR_ASSIGN, "^=");
	REGISTER_TOKEN(TK_SHIFT_LEFT, "<<");
	REGISTER_TOKEN(TK_SHIFT_LEFT_ASSIGN, "<<=");
	REGISTER_TOKEN(TK_SHIFT_RIGHT, ">>");
	REGISTER_TOKEN(TK_SHIFT_RIGHT_ASSIGN, ">>=");

	REGISTER_TOKEN(TK_LOGIC_AND, "&&");
	REGISTER_TOKEN(TK_LOGIC_OR, "||");
	REGISTER_TOKEN(TK_LOGIC_NOT, "!");

	REGISTER_TOKEN(TK_ASSIGN, "=");
	REGISTER_TOKEN(TK_EQ, "==");
	REGISTER_TOKEN(TK_NE, "!=");
	REGISTER_TOKEN(TK_LT, "<");
	REGISTER_TOKEN(TK_LE, "<=");
	REGISTER_TOKEN(TK_AT, ">");
	REGISTER_TOKEN(TK_AE, ">=");

	REGISTER_TOKEN(TK_CURLY_LEFT, "{");
	REGISTER_TOKEN(TK_CURLY_RIGHT, "}");
	REGISTER_TOKEN(TK_SQUARE_LEFT, "[");
	REGISTER_TOKEN(TK_SQUARE_RIGHT, "]");
	REGISTER_TOKEN(TK_PAR_LEFT, "(");
	REGISTER_TOKEN(TK_PAR_RIGHT, ")");

	REGISTER_TOKEN(TK_SPACE, " ");
	REGISTER_TOKEN(TK_COMMA, ",");
	REGISTER_TOKEN(TK_QUESTION, "?");
	REGISTER_TOKEN(TK_COLON, ":");
	REGISTER_TOKEN(TK_SEMICOLON, ";");
	REGISTER_TOKEN(TK_BACKSLASH, "\\");
	REGISTER_TOKEN(TK_DOT, ".");

	REGISTER_TOKEN(TK_ARROW, "->");

	REGISTER_TOKEN(TK_DOTS, "...");

	REGISTER_TOKEN(TK_CHAR, "char");
	REGISTER_TOKEN(TK_SHORT, "short");
	REGISTER_TOKEN(TK_INT, "int");
	REGISTER_TOKEN(TK_FLOAT, "float");
	REGISTER_TOKEN(TK_LONG, "long");
	REGISTER_TOKEN(TK_VOID, "void");
	REGISTER_TOKEN(TK_UNSIGNED, "unsigned");
	REGISTER_TOKEN(TK_SIGNED, "signed");

	REGISTER_TOKEN(TK_IF, "if");
	REGISTER_TOKEN(TK_ELSE, "else");
	REGISTER_TOKEN(TK_FOR, "for");
	REGISTER_TOKEN(TK_WHILE, "while");
	REGISTER_TOKEN(TK_DO, "do");
	REGISTER_TOKEN(TK_SWITCH, "switch");
	REGISTER_TOKEN(TK_CASE, "case");
	REGISTER_TOKEN(TK_BREAK, "break");
	REGISTER_TOKEN(TK_CONTINUE, "continue");
	REGISTER_TOKEN(TK_RETURN, "return");
	REGISTER_TOKEN(TK_GOTO, "goto");

	REGISTER_TOKEN(TK_CONST, "const");
	REGISTER_TOKEN(TK_STATIC, "static");

	REGISTER_TOKEN(TK_ENUM, "enum");
	REGISTER_TOKEN(TK_UNION, "union");
	REGISTER_TOKEN(TK_STRUCT, "struct");

	REGISTER_TOKEN(TK_EXTERN, "extern");
	REGISTER_TOKEN(TK_TYPEDEF, "typedef");
	REGISTER_TOKEN(TK_SIZEOF, "sizeof");

	REGISTER_TOKEN(TK_CDECL, "_cdecl");
	REGISTER_TOKEN(TK_STDCALL, "_stdcall");

	REGISTER_TOKEN(TK_MACRO_PRAGMA, "#pragma");
	REGISTER_TOKEN(TK_MACRO_INCLUDE, "#include");
	REGISTER_TOKEN(TK_MACRO_DEFINE, "#define");
	REGISTER_TOKEN(TK_MACRO_UNDEF, "#undef");
	REGISTER_TOKEN(TK_MACRO_IF, "#if");
	REGISTER_TOKEN(TK_MACRO_IFDEF, "#ifdef");
	REGISTER_TOKEN(TK_MACRO_IFNDEF, "#ifndef");
	REGISTER_TOKEN(TK_MACRO_ENDIF, "#endif");
	REGISTER_TOKEN(TK_MACRO_SHAP, "#");
	REGISTER_TOKEN(TK_MACRO_DSHAP, "##");
}

TC_NAMESPACE::Token TC_NAMESPACE::Lexer::GetToken()
{
	Token token;

	if (!m_stack.empty())
	{
		token = m_stack.top();
		m_stack.pop();

		return token;
	}

	std::string tokenStr = GetTokenStr();
	token.str = tokenStr;
	token.fname = m_input->GetName();
	token.line = m_input->GetLine();

	if (tokenStr.empty())
	{
		token.type = TK_EOF;

		return token;
	}

	if (m_tokenMap.find(tokenStr) != m_tokenMap.end())
	{
		token.type = m_tokenMap[tokenStr];

		return token;
	}

	if ('\'' == tokenStr[0])
	{
		token.type = TK_LITERAL_CHAR;

		return token;
	}

	if ('"' == tokenStr[0])
	{
		token.type = TK_LITERAL_STR;

		return token;
	}

	if (tokenStr[0] >= '0' && tokenStr[0] <= '9')
	{
		token.type = TK_LITERAL_NUM;

		return token;
	}

	if ('_' == tokenStr[0] || (tokenStr[0] >= 'a' && tokenStr[0] <= 'z') ||
		(tokenStr[0] >= 'A' && tokenStr[0] <= 'Z'))
	{
		token.type = TK_IDENT;

		return token;
	}

	GEN_EXCEPTION("[%s-%d]: δ֪token %s", token.fname.c_str(), token.line, token.str.c_str());
}

void TC_NAMESPACE::Lexer::Lexer::BackToken(Token token)
{
	m_stack.push(token);
}

std::string TC_NAMESPACE::Lexer::GetTokenStr()
{
	if (!m_input)
	{
		GEN_EXCEPTION("Lexerδ�������룡");
	}

	while (true)
	{
		int ch = m_input->GetCh();

		// ����
		if (CH_EOF == ch) { return std::string(); }

		// �����
		if (FLAG_CH_INTER_TOKEN == m_chFlag[ch]) { continue; }

		// ����
		if (ch >= '0' && ch <= '9') { return GetNum(ch); }

		// ��ʶ��
		if ('_' == ch || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) { return GetIdent(ch); }

		m_input->BackCh();

		// ��ע��
		if (StartWith("//")) { SkipLineComment(); continue; }

		// ��ע��
		if (StartWith("/*")) { SkipChunkComment(); continue; }

		// �ַ�����
		if (StartWith("'")) { return GetChar(); }

		// �ַ�������
		if (StartWith("\"")) { return GetStr(); }

		// ���ַ�������
		if (StartWith("...")) { return "..."; }
		if (StartWith(">>=")) { return ">>="; }
		if (StartWith("<<=")) { return "<<="; }
		if (StartWith(">>")) { return ">>"; }
		if (StartWith("<<")) { return "<<"; }
		if (StartWith("+=")) { return "+="; }
		if (StartWith("-=")) { return "-="; }
		if (StartWith("*=")) { return "*="; }
		if (StartWith("/=")) { return "/="; }
		if (StartWith("%=")) { return "%="; }
		if (StartWith("|=")) { return "|="; }
		if (StartWith("&=")) { return "&="; }
		if (StartWith("~=")) { return "~="; }
		if (StartWith("^=")) { return "^="; }
		if (StartWith("++")) { return "++"; }
		if (StartWith("--")) { return "--"; }
		if (StartWith("&&")) { return "&&"; }
		if (StartWith("||")) { return "||"; }
		if (StartWith("==")) { return "=="; }
		if (StartWith("!=")) { return "!="; }
		if (StartWith(">=")) { return ">="; }
		if (StartWith("<=")) { return "<="; }
		if (StartWith("##")) { return "##"; }
		if (StartWith("->")) { return "->"; }

		// ��
		if (StartWith("#pragma") || StartWith("# pragma")) { return "#pragma"; }
		if (StartWith("#define") || StartWith("# define")) { return "#define"; }
		if (StartWith("#include") || StartWith("# include")) { return "#include"; }
		if (StartWith("#ifdef") || StartWith("# ifdef")) { return "#ifdef"; }
		if (StartWith("#ifndef") || StartWith("# ifndef")) { return "#ifndef"; }
		if (StartWith("#if") || StartWith("# if")) { return "#if"; }
		if (StartWith("#endif") || StartWith("# endif")) { return "#endif"; }

		// ���ַ�
		if (m_input->GetLine() == 261)
		{
			int a = 10;
		}

		ch = m_input->GetCh();
		if (FLAG_CH_SINGLE_TOKEN == m_chFlag[ch]) { return std::string() + (char)ch; }
		
		GEN_EXCEPTION("[%s-%d]: �Ƿ��ַ�!", m_input->GetName().c_str(), m_input->GetLine());
	}
}

std::string TC_NAMESPACE::Lexer::GetChar()
{
	std::string token("'");

	int ch = m_input->GetCh();

	if ('\\' == ch)
	{
		token += '\\';

		ch = m_input->GetCh();

		if ('\n' == ch)
		{
			GEN_EXCEPTION("[%s-%d]: �����ַ�����ʧ�ܣ������лس����з���", m_input->GetName().c_str(), m_input->GetLine());
		}

		if ('\'' == m_input->GetCh())
		{
			token += (char)ch;
			token += '\'';

			return token;
		}
	}
	else if (CH_EOF != ch)
	{
		if ('\n' == ch)
		{
			GEN_EXCEPTION("[%s-%d]: �����ַ�����ʧ�ܣ������лس����з���", m_input->GetName().c_str(), m_input->GetLine());
		}

		if ('\'' == ch)
		{
			GEN_EXCEPTION("[%s-%d]: �����ַ�����ʧ�ܣ���������������һ���ַ��ҡ�'���ַ���ʹ�á�\'��", m_input->GetName().c_str(), m_input->GetLine());
		}

		if ('\'' == m_input->GetCh())
		{
			token += (char)ch;
			token += '\'';

			return token;
		}
	}

	GEN_EXCEPTION("[%s-%d]: �����ַ�����ʧ�ܣ�", m_input->GetName().c_str(), m_input->GetLine());
}

std::string TC_NAMESPACE::Lexer::GetStr()
{
	std::string token("\"");

	while (true)
	{
		int ch = m_input->GetCh();

		if (CH_EOF == ch)
		{
			GEN_EXCEPTION("[%s-%d]: �����ַ�������ʧ�ܣ�û�гɶԵ�˫���ţ�", m_input->GetName().c_str(), m_input->GetLine());
		}
		else if ('"' == ch)
		{
			token += '"';

			if (2 == token.length() ||
				'\\' != token[token.length() - 2])
			{
				return token;
			}
		}
		else
		{
			token += (char)ch;
		}
	}
}

std::string TC_NAMESPACE::Lexer::GetNum(int ch)
{
	std::string token;
	token += (char)ch;

	while (true)
	{
		ch = m_input->GetCh();
		
		if (CH_EOF == ch)
		{
			GEN_EXCEPTION("[%s-%d]: ��������ʧ�ܣ��Ѿ���EOF��", m_input->GetName().c_str(), m_input->GetLine());
		}
		else if ('.' == ch)
		{
			token += '.';
		}
		else if (FLAG_CH_INTER_TOKEN == m_chFlag[ch])
		{
			return token;
		}
		else if (FLAG_CH_SINGLE_TOKEN == m_chFlag[ch])
		{
			m_input->BackCh();

			return token;
		}
		else
		{
			token += (char)ch;
		}
	}
}

std::string TC_NAMESPACE::Lexer::GetIdent(int ch)
{
	std::string token;
	token += (char)ch;

	while (true)
	{
		ch = m_input->GetCh();

		if (CH_EOF == ch)
		{
			GEN_EXCEPTION("[%s-%d]: ������ʶ��ʧ�ܣ��Ѿ���EOF��", m_input->GetName().c_str(), m_input->GetLine());
		}
		else if (FLAG_CH_INTER_TOKEN == m_chFlag[ch])
		{
			return token;
		}
		else if (FLAG_CH_SINGLE_TOKEN == m_chFlag[ch])
		{
			m_input->BackCh();

			return token;
		}
		else
		{
			token += (char)ch;
		}
	}
}

void TC_NAMESPACE::Lexer::SkipLineComment()
{
	int ch = 0;
	
	do
	{
		ch = m_input->GetCh();
	} while (ch != '\n' && ch != CH_EOF);

	// ������һ��
	if ('\n' == ch)
	{
		m_input->BackCh();
	}
}

void TC_NAMESPACE::Lexer::SkipChunkComment()
{
	while (true)
	{
		if (StartWith("*/")) 
		{ 
			return; 
		}

		if (CH_EOF == m_input->GetCh())
		{
			GEN_EXCEPTION("[%s-%d]: ��ע��û��'*/'��β��", m_input->GetName().c_str(), 
				m_input->GetLine());
		}
	}
}

bool TC_NAMESPACE::Lexer::StartWith(const std::string& str)
{
	int len = (int)str.length();

	// �Ƚ�ǰlen���ַ�
	int backNum = 0;
	for (int i = 0; i < len; ++i)
	{
		int ch = m_input->GetCh();

		++backNum;

		if (ch != str[i])
		{
			if (CH_EOF == ch) { --backNum; }

			// �����ַ�
			m_input->BackCh(backNum);

			return false;
		}
	}

	return true;
}