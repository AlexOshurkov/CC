#include "stdafx.h"
#pragma hdrstop

#include "RPNCalc.hpp"

void RpnCalcTest()
{
	vector<string> seq1 = { "3","4","5","*","-" };
	vector<string> seq2 = split_str("5 1 2 + 4 * +  3   -");
	vector<string> seq3 = { "5", "1", "2", "+", "4", "/", "+", "3", "-" };
	vector<string> seq4 = { 
		"-4 5 +",
		"5 3 /",
		"5 2.5 /",
		"5 1 2 + 4 * 3 - +",
		"4 2 5 * + 1 3 2 * + /",
		"12 8 3 * 6 / - 2 + -20.5 "
	};

	for (auto str : seq4)
	{
		const double res = RPNCalc::Calculate(split_str(str));
		cout << setprecision(5) << str << " " << string(50 - str.size(), '_') << " " << res << endl;
	}
}
