#pragma once

using std::string;
using std::endl;

enum class TRACE_TYPE { FUNC, IF, WHILE, FOR, FOR_INNER, WHILE_INNER };

string getTraceName(TRACE_TYPE trace_type);
void check_func();
void test_func();

string getTraceName(TRACE_TYPE trace_type)
{
	switch (trace_type)
	{
	case TRACE_TYPE::FUNC:
		return "function";
	case TRACE_TYPE::IF:
		return "if";
	case TRACE_TYPE::WHILE:
		return "while";
	case TRACE_TYPE::FOR:
		return "for";
	case TRACE_TYPE::FOR_INNER:
		return "inner-for";
	case TRACE_TYPE::WHILE_INNER:
		return "inner-while";

	default:
		return "";
	}
}


class CTrace
{
private:
	static int indent;

	string name;
	TRACE_TYPE trace_type;

	static void indentation();

public:
	CTrace(TRACE_TYPE trace_type, const string& name = "");
	~CTrace();
};

// Initial indent
int CTrace::indent = 0;

void CTrace::indentation()
{
	int i{};
	while (i++ < indent)
		std::cout << "\t";
}