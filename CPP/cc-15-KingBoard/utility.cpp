#include "precomp.hpp"

#include "utility.hpp"

using namespace std;

static const char* board_templ =
"\
		. . . . . . . . B . . . L L L . . . . . . . . . . . . . . . . .\
		. . . . . . . . B . . . L L L . . . . . . . . . . . . . . . . .\
		. . . . . . . . B . . . L L L . . . L L L . . . . . . . . . . .\
		. . . . . . . . B . . . L L L . . L L L . . . R R . . . . . . .\
		. . . . . . . . B . . . L L L L L L L L . . . R R . . . . . . .\
		. . . . . . . . B . . . L L L L L L . . . . . . . . . . . . . .\
		. . . . . . . . B . . . . . . . . . . . . R R . . . . . . . . .\
		. . . . . . . . B B . . . . . . . . . . . R R . . . . . . . . .\
		. . . . . . . . W B B . . . . . . . . . . . . . . . . . . . . .\
		. . . R R . . . W W B B B B B B B B B B . . . . . . . . . . . .\
		. . . R R . . . W W . . . . . . . . . B . . . . . . . . . . . .\
		. . . . . . . . W W . . . . . . . . . B . . . . . . T . . . . .\
		. . . W W W W W W W . . . . . . . . . B . . . . . . . . . . . .\
		. . . W W W W W W W . . . . . . . . . B . . R R . . . . . . . .\
		. . . W W . . . . . . . . . . B B B B B . . R R . W W W W W W W\
		. . . W W . . . . . . . . . . B . . . . . . . . . W . . . . . .\
		W W W W . . . . . . . . . . . B . . . W W W W W W W . . . . . .\
		. . . W W W W W W W . . . . . B . . . . . . . . . . . . B B B B\
		. . . W W W W W W W . . . . . B B B . . . . . . . . . . B . . .\
		. . . W W W W W W W . . . . . . . B W W W W W W B B B B B . . .\
		. . . W W W W W W W . . . . . . . B W W W W W W B . . . . . . .\
		. . . . . . . . . . . B B B . . . . . . . . . . B B . . . . . .\
		. . . . . R R . . . . B . . . . . . . . . . . . . B . . . . . .\
		. . . . . R R . . . . B . . . . . . . . . . . . . B . T . . . .\
		. . . . . . . . . . . B . . . . . R R . . . . . . B . . . . . .\
		. . . . . . . . . . . B . . . . . R R . . . . . . . . . . . . .\
		. . . . . . . . . . . B . . . . . . . . . . R R . . . . . . . .\
		. . . . . . . . . . . B . . . . . . . . . . R R . . . . . . . .";

const char* GetBoardTempl()
{
	return board_templ;
}

//	Fills board by initial values
board_t FillBoard(size_t size, const char* board_templ)
{
	board_t board;

	for (size_t i = 0; i < size; ++i)
		board.push_back(vector<cell_t>(size));

	for (size_t row = 0; row < size; ++row)
		for (size_t col = 0; col < size; ++col)
		{
			const int irow = static_cast<int>(row);
			const int icol = static_cast<int>(col);

			if (board_templ == nullptr)
				board[row][col] = cell_t(point_t(irow, icol), cell_t::type_e::FREE);
			else
			{
				while (*board_templ > 0 && *board_templ <= ' ')
					++board_templ;

				board[row][col] = cell_t(point_t(irow, icol), cell_t::CharToType(*board_templ++));
			}
		}

	return board;
}

// check the coordinate and one relative step. 
// The position (-1,-1) is indicating nonexisting location
bool CheckBorder(size_t bsize, point_t pos)
{
	return pos.x >= 0 && pos.y >= 0 && pos.x < bsize && pos.y < bsize;
}

bool CheckBorder(const board_t& board, point_t pos)
{
	return CheckBorder(board.size(), pos);
}

// Return teleports of the board
points_t GetTeleports(const board_t& board)
{
	points_t vals;

	for (auto row : board)
		for (auto col : row)
			if (col.get_type() == cell_t::type_e::TELEPORT)
				vals.push_back(col.get_pos());

	return vals;
}

point_t CheckStep(const cell_t& cell, const points_t& tels)
{
	if (tels.size() != 2)
		return point_t();

	//	teleport oofset
	point_t tel_offs = *tels.rbegin() - *tels.begin();

	if ((cell.get_type() == cell_t::type_e::ROCK) ||
		(cell.get_type() == cell_t::type_e::BARRIER))
		return point_t();

	//	Check the teleport cell and make the movement if it necessary
	else if (cell.get_type() == cell_t::type_e::TELEPORT)
	{
		if (cell.get_pos() == *tels.begin())
			return cell.get_pos() + tel_offs;
		else
			return cell.get_pos() - tel_offs;
	}
	
	return cell.get_pos();
}

// Returns the next step, returns point_t() if it no allowed
point_t GetNextStep(const board_t& board, const points_t& tels, point_t start, point_t step)
{
	const int step_x = step.x > 0 ? 1 : -1;
	const int step_y = step.y > 0 ? 1 : -1;

	point_t beg = start;
	point_t end = beg + step;
	point_t pos;

	for (pos = beg; pos.x < end.x; pos.x += step_x)
	{
		pos = CheckStep(board[pos.x][pos.y], tels);
	}

	return pos;
}

void PrintRoute(const points_t& steps, uint32_t count)
{
	cout << endl << "Found: " << (count == 0 ? steps.size() : count)
		<< " steps, route trace: " << (steps.empty() ? "empty" : "");

	bool isFirst = true;

	for(auto step : steps)
	{
		if (isFirst)
			isFirst = false;
		else
			cout << ", ";

		cout << "{" << step.x << ", " << step.y << "}";
	}
}

//	Calculates the steps depending on cell type
uint32_t CalcSteps(const board_t& board, const points_t& steps)
{
	return 0;
}