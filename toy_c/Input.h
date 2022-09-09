#pragma once

#include "Defines.h"
#include <string>

TC_NAMESPACE_START
	
class Input
{
public:
	// �ַ�����Ϊ����
	static Input* GenWithStr(const std::string& name, const std::string& str);

	// �ļ���Ϊ����
	static Input* GenWithFile(const std::string& fname);

	// ��ȡname
	std::string GetName() const { return m_name; }

	// ��ȡ��ǰ�ַ������к�
	int GetLine() const { return m_curLine + 1; }

	// ��ȡһ���ַ�
	int GetCh();

	// ����һ���ַ�
	void BackCh();

	// ����num���ַ�
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