// cc-8-functional.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void cpp_14_impl() {

}

void functional() {

}

void fp(int** ppi) {
	int* pi = new int(2);
	*ppi = pi;
}

int main(int argc, char* argv[])
{
	int i = 3;
	int* pi = &i;
	int& ri = i;
	++i;
	++(*pi); string g;
	++ri;
	return 0;
}

