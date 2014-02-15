//
//  main.cpp
//  assert 2.0
//
//  Created by taowei on 14-2-8.
//  Copyright (c) 2014年 taowei. All rights reserved.
//

#include <iostream>
#include <exception>
#include <sstream>

class AssertException: public std::exception {
public:
	AssertException(const char *exp, const char *file, int line) {
		std::ostringstream out;
		out << "ensure failed :" << exp << "\n";
		out << file << " {" << line << "}" << "\n";
		out << "context variables:\n";
		m_what = out.str();
	}
	~AssertException() throw () {}

	template<typename T>
	AssertException& operator << (const std::pair<const char *, T>& p) {
		std::ostringstream out;
		out << "\t" << p.first << " : " << p.second << "\n";
		m_what += out.str();
		return *this;
	}
	AssertException& operator << (int) {
		return *this;
	}

	const char *what() const throw () {
		return m_what.c_str();
	}
private:
	mutable std::string m_what;
};

static int A = 0, B = 0;
#define AB(a, N) std::make_pair(#a, a) << N
#define A(a) AB(a, B)
#define B(a) AB(a, A)
#define ASSERT_2(b) if (b); else throw AssertException(#b, __FILE__, __LINE__) << A

int main(int argc, const char * argv[])
{
	try {
		int a = 2, b = 3;
		ASSERT_2(a > 1);
		ASSERT_2(a > 10)(a);
		ASSERT_2(a > 2 && b <= 3)(a)(b)(5);
	} catch (const AssertException& e) {
		std::cout << "catch exception:\n" << e.what() << "\n";
	}
    return 0;
}

