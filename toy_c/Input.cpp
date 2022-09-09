#include "Input.h"
#include "Exception.h"
#include <fstream>
#include <sstream>

TC_NAMESPACE::Input* TC_NAMESPACE::Input::GenWithStr(const std::string& name, 
	const std::string& str)
{
	Input* input = new Input();
	input->m_name = name;
	input->m_data = str;

	return input;
}

TC_NAMESPACE::Input* TC_NAMESPACE::Input::GenWithFile(const std::string& fname)
{
	std::ifstream file(fname);
	if (!file)
	{
		GEN_EXCEPTION("¼ÓÔØ%sÎÄ¼þÊ§°Ü£¡", fname.c_str());
	}

	std::ostringstream temp;
	temp << file.rdbuf();
	std::string str = temp.str();

	if (str.length() > 3 && (char)0xef == str[0] && (char)0xbb == str[1] && (char)0xbf == str[2])
	{
		str = str.substr(3, str.length() - 3);
	}

	return GenWithStr(fname, str);
}

int TC_NAMESPACE::Input::GetCh()
{
	if (m_index + 1 <= m_data.length())
	{
		char ch = m_data[m_index++];

		if ('\n' == ch)
		{
			++m_curLine;
		}

		return ch;
	}

	return CH_EOF;
}

void TC_NAMESPACE::Input::BackCh()
{
	if (m_index > 0)
	{
		if ('\n' == m_data[--m_index])
		{
			--m_curLine;
		}
	}
}
