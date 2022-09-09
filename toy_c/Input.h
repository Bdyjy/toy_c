#pragma once

#include "Defines.h"
#include <string>

TC_NAMESPACE_START
	
class Input
{
public:
	// 字符串作为输入
	static Input* GenWithStr(const std::string& name, const std::string& str);

	// 文件作为输入
	static Input* GenWithFile(const std::string& fname);

	// 获取name
	std::string GetName() const { return m_name; }

	// 获取当前字符所在行号
	int GetLine() const { return m_curLine + 1; }

	// 获取一个字符
	int GetCh();

	// 回退一个字符
	void BackCh();

	// 回退num个字符
	void BackCh(int num)
	{
		for (int i = 0; i < num; ++i)
		{
			BackCh();
		}
	}
	
private:
	std::string m_name;
	std::string m_data;
	int m_index = 0;
	int m_curLine = 0;
};

TC_NAMESPACE_END