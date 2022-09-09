#pragma once

#include "Defines.h"
#include "Input.h"
#include <string>
#include <stack>
#include <map>

TC_NAMESPACE_START

#define FLAG_CH_INTER_TOKEN 1		// 间隔符
#define FLAG_CH_SINGLE_TOKEN 2		// 单字符token

enum TokenType
{
	TK_EOF = 0,		// 结束

	TK_NEW_LINE,	// \n
	TK_TAB,			// \t

	// 符号
	TK_ADD,			// +
	TK_ADD_ASSIGN,	// +=
	TK_SUB,			// -
	TK_SUB_ASSIGN,	// -=
	TK_MUL,			// *
	TK_MUL_ASSIGN,	// *=
	TK_DIV,			// /
	TK_DIV_ASSIGN,	// /=
	TK_MOD,			// %
	TK_MOD_ASSIGN,	// %=
	TK_INC,			// ++
	TK_DEC,			// -- 

	TK_AND,			// &
	TK_AND_ASSIGN,	// &=
	TK_OR,			// |
	TK_OR_ASSIGN,	// |=
	TK_NOT,			// ~
	TK_NOT_ASSIGN,	// ~=
	TK_XOR,			// ^
	TK_XOR_ASSIGN,	// ^=
	TK_SHIFT_LEFT,	// <<
	TK_SHIFT_LEFT_ASSIGN,	// <<=
	TK_SHIFT_RIGHT,	// >>
	TK_SHIFT_RIGHT_ASSIGN,	// >>=

	TK_LOGIC_AND,	// &&
	TK_LOGIC_OR,	// ||
	TK_LOGIC_NOT,	// !

	TK_ASSIGN,		// =
	TK_EQ,			// ==
	TK_NE,			// != 
	TK_LT,			// <
	TK_LE,			// <=
	TK_AT,			// >
	TK_AE,			// >=

	TK_CURLY_LEFT,	// {
	TK_CURLY_RIGHT, // }
	TK_SQUARE_LEFT, // [
	TK_SQUARE_RIGHT,// ]
	TK_PAR_LEFT,	// (
	TK_PAR_RIGHT,	// )
	//TK_ANGLE_LEFT,	// <
	//TK_ANGLE_RIGHT,	// >

	TK_SPACE,		// 空格
	TK_COMMA,		// ,
	TK_QUESTION,	// ?
	TK_COLON,		// :
	TK_SEMICOLON,	// ;
	TK_DOT,			// .
	TK_BACKSLASH,	// \

	TK_ARROW,		// ->

	TK_DOTS,		// ...

	// 关键字
	TK_KEY_WORD_START,

	TK_CHAR,
	TK_SHORT,
	TK_INT,
	TK_FLOAT,
	TK_DOUBLE,
	TK_LONG,
	TK_VOID,
	TK_UNSIGNED,
	TK_SIGNED,

	TK_IF,
	TK_ELSE,
	TK_FOR,
	TK_WHILE,
	TK_DO,
	TK_SWITCH,
	TK_CASE,
	TK_BREAK,
	TK_CONTINUE,
	TK_RETURN,
	TK_GOTO,

	TK_CONST,
	TK_STATIC,
	
	TK_ENUM,
	TK_UNION,
	TK_STRUCT,

	TK_EXTERN,
	TK_TYPEDEF,
	TK_SIZEOF,
	
	TK_CDECL,
	TK_STDCALL,

	TK_KEY_WORD_END,

	// 宏
	TK_MACRO_START,

	TK_MACRO_PRAGMA,	// #pragma
	TK_MACRO_INCLUDE,
	TK_MACRO_DEFINE,
	TK_MACRO_UNDEF,
	TK_MACRO_IF,
	TK_MACRO_IFDEF,
	TK_MACRO_IFNDEF,
	TK_MACRO_ENDIF,
	TK_MACRO_SHAP,		// #
	TK_MACRO_DSHAP,		// ##

	TK_MACRO_END,

	// 字面量
	TK_LITERAL_CHAR,
	TK_LITERAL_STR,
	TK_LITERAL_NUM,

	// 标识符
	TK_IDENT
};

struct Token
{
	TokenType type;		// token类型

	std::string fname;	// token所在文件名
	int line;			// token所在文件行

	std::string str;	// token字符串
};

class Lexer
{
public:
	Lexer();
	Lexer(const Lexer&) = delete;
	Lexer& operator = (const Lexer&) = delete;

	// 关联字符缓冲区
	void Attach(Input* input) { m_input = input; }

	// 设置单字符是否为token
	void SetChFlag(char ch, int flag = 0) { m_chFlag[ch] = flag; }

	// 获取token
	Token GetToken();

	// 回退一个token
	void BackToken(Token token);

private:
	// 获取token字符串，字符串末位返回空字符串，内部会处理字符、字符串和注释
	std::string GetTokenStr();

	// 获取字符常量
	std::string GetChar();
	
	// 获取字符串常量
	std::string GetStr();

	// 获取数字常量
	std::string GetNum(int ch);

	// 获取标识符
	std::string GetIdent(int ch);

	// 是否是某字符串开头
	bool StartWith(const std::string& str);

	// 跳过注释
	void SkipLineComment();
	void SkipChunkComment();

	Input* m_input = nullptr;
	
	int m_chFlag[256] = { 0 };		

	std::stack<Token> m_stack;

	std::map<std::string, TokenType> m_tokenMap;	
};

TC_NAMESPACE_END