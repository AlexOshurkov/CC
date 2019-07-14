#pragma once

#include <ctime>
#include <cstdint>
#include <vector>
#include <random>
using namespace std;


//----------------------------------------------------------------------------
template <typename T>
uint16_t bits_count(T val) {

	uint16_t cnt = 0;

	for (; val; val &= val - 1)
		cnt++;

	return cnt;
}

//----------------------------------------------------------------------------
template <typename T>
void set_bit(T& val, uint16_t bit) {
	val |= (1 << bit);
}

//----------------------------------------------------------------------------
template <typename T>
bool get_bit(T& val, uint16_t& bit) {
	return (val & (1 << bit)) != 0;
}

//----------------------------------------------------------------------------
template <typename T>
void reset_bit(T& val, uint16_t bit) {
	val &= ~(1 << bit);
}

//----------------------------------------------------------------------------
template <typename T>
void flip_bit(T& val, uint16_t bit) {
	val ^= (1 << bit);
}


//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename T>
void swap_vals(T& a, T& b) {
	b = a ^ b;
	a = b ^ a;
	b = b ^ a;
}

//----------------------------------------------------------------------------
uint8_t flip_bits(uint8_t x);
bool is_littelendian();
int rand_int(int low, int high);
size_t br2num(char br);
bool check_braces(const string& exp);
void print_perm(string s, string pref = string());
bool next_perm(string& s);
void reverse_str(string& str);
void repl_str(char* str, char ch, const char* rep); 
void part(vector<int>& v, int el);
uint64_t fib(size_t max, size_t c = 0, uint64_t p1 = 0, uint64_t p2 = 0);
uint64_t fib2(size_t max);

