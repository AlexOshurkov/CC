#pragma once

#include <iomanip>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class RPNCalc
{
	static bool isnum(const string& str)
	{
		bool digfound = false;
		bool dotfound = false;

		for (string::const_iterator it = str.cbegin(); it != str.cend(); ++it)
		{
			if (it == str.begin() && (*it == '+' || *it == '-'))
				continue;

			else if (isdigit(*it))
				digfound = true;

			else if (*it == '.')
			{
				if (dotfound)
					return false;
				else
					dotfound = true;
			}
			else
				return false;
		}

		return digfound;
	}

	static bool isop(const string& str)
	{
		if (str.empty() || str.size() > 1)
			return false;

		char ch = str[0];

		switch (ch)
		{
		case '-':
		case '+':
		case '*':
		case '/': return true;
		default: return false;
		}
	}

	static bool check_range(double num)
	{
		return num >= -1000000 && num <= 1000000;
	}

	static double makeop(double a, double b, const string& op)
	{
		if (op == "+")
			return a + b;

		if (op == "-")
			return a - b;

		if (op == "*")
			return a * b;

		if (op == "/")
			return a / b;

		return 0;
	}

	static double ErrVal()
	{
		return nan(nullptr);
	}

public:

	static double Calculate(vector<string> tokens)
	{
		if (tokens.size() < 3 || tokens.size() > 1000000)
			return ErrVal();

		const size_t len = tokens.size();
		size_t posop = 0;
		size_t posnum = 0;
		stack <double> res;

		// goto first operations
		for (; posop < len; posop++)
		{
			const string& tok = tokens[posop];

			if (isop(tok))
			{
				if (res.empty())
					return ErrVal();

				double b = res.top();
				res.pop();

				if (res.empty())
					return ErrVal();

				double a = res.top();
				res.pop();

				if (b == 0 && tok == "/")
					return ErrVal();

				res.push(makeop(a, b, tok));
			}
			else if (isnum(tok))
			{
				double val = stod(tokens[posop]);

				if (check_range(val))
					res.push(val);
				else
					return ErrVal();
			}
		}

		return res.empty() ? ErrVal() : res.top();
	}
};
