#pragma once

#include "defs.hpp"

//	Fills board by initial values
board_t FillBoard(size_t size, const char* board_templ = nullptr);

// Checks the coordinate and one relative step. It assumes board size: 1...BoardSize
// the position (0,0) is reserved for indication nonexisting location
bool CheckBorder(size_t bsize, point_t);
bool CheckBorder(const board_t&, point_t pos);

// Return teleports of the board
points_t GetTeleports(const board_t&);

// Returns the next step, returns point_t() if it no allowed
point_t GetNextStep(const board_t&, const points_t& teleports, point_t start, point_t step);

//	Calculates the steps depending on cell type
uint32_t CalcSteps(const board_t& board, const points_t& steps);

//	Prints the steps of route to the destination
void PrintRoute(const points_t& steps, uint32_t count = 0);

