// cc-4-sort.cpp : Defines the entry point for the console application.
//

#include "../helper.hpp"
#include <random>

typedef vector<uint32_t> vec_t;

void get_random_arr(vec_t& v) {
	mt19937 eng(823);
	uniform_int_distribution<int> dist(0, 1000);

	for (int i = 0; i < 100000; ++i)
		v.push_back(dist(eng));
}

template <typename T>
void merge_sort(vec_t& v) {

}


void quick_sort(vec_t& v, size_t b, size_t e) {

		uint32_t p = v[b];
		size_t minp = b;
		size_t maxp = e;

		while (minp < maxp ) {

			while (v[minp] < p) minp++;
			while (v[maxp] > p) maxp--;

			if (minp <= maxp) 
				swap(v[minp++], v[maxp--]);
		}

		if (b < maxp)
			quick_sort(v, b, maxp);

		if (e > minp)
			quick_sort(v, minp, e);
}

bool check_sorted(const vec_t& v) {


	for (size_t i = 1; i < v.size(); i++)
		if (v[i] < v[i - 1])
			return false;

	return true;
}

int main(int argc, char** argv)
{
	vec_t v;
	get_random_arr(v);
	bool r = check_sorted(v);
	quick_sort(v, 0, v.size() - 1);
	r = check_sorted(v);
	return 0;
}

