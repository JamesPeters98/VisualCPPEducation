// Chapter9-Question3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class CBase
{
protected:
    int m_anInt;
public:
    CBase(int n) : m_anInt{ n } { std::cout << "Base constructor\n"; }
    virtual void print() const = 0;
};

class CExtendedBase : public CBase
{
public:
	CExtendedBase(int n) : CBase(n){}
	
	void print() const override
	{
		std::cout << "m_anInt = " << m_anInt;
	}
};



int main()
{
	CExtendedBase c_extended_base{ 5 };
	c_extended_base.print();

	CBase* cbase{};
	cbase = &c_extended_base;
	
	cbase->print();
}

