#pragma once

#include "utility.hpp"

//	This method returns new position of a Knight, after applying all moves. 
//  If there is illegal move, or attempt to go outside of the board 
//  method will return (-1, -1) as error indicating
point_t Level1(uint16_t board_size, point_t start, points_t moves);

//	Method returns list of valid moves from start (S) point to end (E) point
//  If error occurs: invalid start or end positions, or route cannot be found 
//  method returns empty list of moves
points_t FindPatch(const board_t&, point_t start, point_t dest);
