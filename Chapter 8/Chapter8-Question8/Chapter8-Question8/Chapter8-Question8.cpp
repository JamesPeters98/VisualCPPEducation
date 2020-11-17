// Chapter8-Question8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Chapter8-Question8.h"

int main()
{
	CTrace trace{ TRACE_TYPE::FUNC, "main" };

	if (true)
	{
		CTrace trace2{ TRACE_TYPE::IF };

		{
			int x{};
			CTrace whileTrace{ TRACE_TYPE::WHILE };
			while (x < 5)
			{
				CTrace innerWhile{ TRACE_TYPE::WHILE_INNER };
				if (x == 2) {
					CTrace ifTrace{ TRACE_TYPE::IF };
					test_func();
				}
				x++;
			}
		}
	}
}

CTrace::CTrace(TRACE_TYPE trace_type, const string& name)
{
	this->trace_type = trace_type;
	this->name = name;

	indentation();
	
	if (name.empty())
	{
		std::cout << "Entering '" << getTraceName(trace_type) << "'" << endl;
	} else
	{
		std::cout << "Entering " << getTraceName(trace_type) << " '" << name << "'" << endl;
	}

	indent++;
}

CTrace::~CTrace()
{
	indent--;

	indentation();
	
	if (name.empty())
	{
		std::cout << "Leaving '" << getTraceName(trace_type) << "'" << endl;
	}
	else
	{
		std::cout << "Leaving " << getTraceName(trace_type) << " '" << name << "'" << endl;
	}
}

void check_func()
{
	CTrace trace{ TRACE_TYPE::FUNC, "check_func" };
}

void test_func()
{
	CTrace trace{ TRACE_TYPE::FUNC, "test_func" };

	{
		CTrace forTrace{ TRACE_TYPE::FOR };
		for (int i{}; i < 3; i++)
		{
			CTrace innerTrace{ TRACE_TYPE::FOR_INNER };
			check_func();
		}
	}
}


