#include "precomp.hpp"
#include "utility.hpp"

using namespace std;


//	Level 1: Write a function that accepts a sequence of moves and reports
//  whether the sequence contains only valid knight moves.It should also
//  optionally print the state of the knight board to the terminal as shown
//  above after each move.The current position should be marked with a 'K'.
//  Assume inputs:
//  - Sqare board size
//  - Starting position of the Knight as X, Y coordinates
//  - Sequence (list) of moves (offsets) from last position
//  Also I assume: all coordinates have range: 1..MAX



//	This method returns new position of a Knight, after applying all moves. 
//  If there is illegal move, or attempt to go outside of the board 
//  method will return (-1,-1) as error indicating
point_t Level1(uint16_t board_size, point_t start, points_t moves)
{
	if (board_size < 3) // check the minimum possible board 
		return point_t();

	point_t dest = start;

	do
	{
		if (!moves.empty())
		{
			const point_t offset = moves.front();
			moves.pop_front();

			//  reducing compares
			const point_t abs_offset = point_t(abs(offset.x), abs(offset.y));

			if (abs_offset == point_t(1, 2) || abs_offset == point_t(2, 1))
			{
				dest.x += offset.x;
				dest.y += offset.y;

				if (!CheckBorder(board_size, dest))
					return point_t();
			}
			else
				return point_t();
		}

	} while (!moves.empty());

	return dest;
}

//	Method returns list of valid moves from start (S) point to end (E) point
//  If error occurs: invalid start or end positions, or route cannot be found 
//  method returns empty list of moves
points_t FindPatch(const board_t& cboard, point_t start, point_t dest)
{
	board_t board{ cboard };

	if (!CheckBorder(board, start) || !CheckBorder(board, dest))
		return points_t();

	const points_t teleports = GetTeleports(board);

	if (teleports.size() != 2)
		return points_t();

	//	allowed moves from current position
	const points_t steps{ { -2, -1 },{ -1, -2 },{ 1, -2 },{ 2, -1 },{ 2, 1 },{ 1, 2 },{ -1, 2 },{ -2, 1 } };

	// Two queries for handling passes through all the cells
	list<cell_t> q1;
	list<cell_t> q2;

	// Just joking :)
	// I understand, there is more readable format, 
	// but it also can work, so I won't be surprised if find something like this
	q1.push_back((board[start.x][start.y].set_visited(), board[start.x][start.y]));

	while (!q1.empty())
	{
		while (!q1.empty())
		{
			cell_t cell = q1.front();
			point_t pos = cell.get_pos();
			q1.pop_front();

			for (auto step : steps)
			{
				point_t npos = GetNextStep(board, teleports, pos, step);

				if (npos == point_t())
					continue;

				//	check if we found destination
				cell_t& ncell = board[npos.x][npos.y];

				if (ncell.is_visited())
					continue;
				else
				{
					ncell.set_visited();
					ncell.set_prev(board[pos.x][pos.y]);
					q2.push_back(ncell);
				}

				if (npos == dest)
				{
					points_t steps;

					do
					{
						steps.push_front(npos);
						npos = board[npos.x][npos.y].get_prev()->get_pos();
					} while (board[npos.x][npos.y].get_prev() != nullptr);

					return steps;
				}
			}
		}
		swap(q1, q2);
	}

	return points_t();
}
