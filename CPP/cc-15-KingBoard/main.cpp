#include "precomp.hpp"

#include "utility.hpp"
#include "levels.hpp"

using namespace std;

void TestLevel1()
{
	cout << endl << "===   Test Level 1  ===" << endl;

	point_t dest1 = Level1(7, { 2, 3 }, { { 1, 2 },{ 1, -2 } });
	cout << "Test case 1: " << dest1.x << ", " << dest1.y << endl;

	point_t dest2 = Level1(20, { 11, 3 }, { { 2, 1 },{ 1,2 },{ -2, 1 },{ 2, -1 } });
	cout << "Test case 2: " << dest2.x << ", " << dest2.y << endl;
}

void TestLevel3()
{
	board_t board = FillBoard(10);

	cout << endl << "===   Test Level 3  ===" << endl;

	PrintRoute(FindPatch(board, point_t(3, 3), point_t(5, 5)));
	PrintRoute(FindPatch(board, point_t(1, 1), point_t(5, 5)));
	PrintRoute(FindPatch(board, point_t(1, 1), point_t(1, 2)));
	PrintRoute(FindPatch(board, point_t(0, 0), point_t(98, 98)));
}

void TestLevel4()
{
	board_t board = FillBoard(32);

	cout << endl << "===   Test Level 4  ===" << endl;

	PrintRoute(FindPatch(board, point_t(3, 3), point_t(5, 5)));
	PrintRoute(FindPatch(board, point_t(1, 1), point_t(5, 5)));
	PrintRoute(FindPatch(board, point_t(1, 1), point_t(1, 2)));
	PrintRoute(FindPatch(board, point_t(0, 0), point_t(9, 9)));
}

int main() {

	TestLevel1();
	TestLevel3();
	//TestLevel4();

	return 0;
}
