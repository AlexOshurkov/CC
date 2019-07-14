#include "precomp.hpp"

using std::list;
using std::queue;
using std::vector;

struct point_t
{
	int x = -1;
	int y = -1;

	point_t() = default;
	point_t(int x_, int y_) : x(x_), y(y_) {}

	bool operator== (const point_t& val) const
	{
		return x == val.x && y == val.y;
	}

	const point_t operator+(const point_t& val) const
	{
		point_t npos{ *this};
		npos.x += val.x;
		npos.y += val.y;
		return npos;
	}

	const point_t operator-(const point_t& val) const
	{
		point_t npos{ *this };
		npos.x -= val.x;
		npos.y -= val.y;
		return npos;
	}
};

typedef list<point_t>  points_t;

//	Class represents cell of the board
class cell_t
{
public:
	//  Type of cells
	enum class type_e : uint16_t {
		FREE,      //  Free cell
		WATER,     //  Water cell
		ROCK,      //  Rock cell
		BARRIER,   //  Barrier cell
		TELEPORT,  //  Teleport cell
		LAVA       //  Lava cell
	};

	static type_e CharToType(char ch)
	{
		switch (ch)
		{
			case 'W': return type_e::WATER;
			case 'R': return type_e::ROCK;
			case 'B': return type_e::BARRIER;
			case 'T': return type_e::TELEPORT;
			case 'L': return type_e::LAVA;
			default: return type_e::FREE;
		}
	}
private:
	point_t pos;
	type_e  type = type_e::FREE; //  Type of cell
	bool    visited = false;        //  Flag for check visiting
	cell_t* prev = nullptr;      //  the previous cell

public:
	cell_t() = default;
	cell_t(const point_t& pos_, type_e type_) :
		pos{ pos_ },
		type{ type_e::FREE }
	{}

	void set_visited()
	{
		visited = true;
	}

	point_t get_pos() const
	{
		return pos;
	}

	type_e get_type() const
	{
		return type;
	}

	cell_t* get_prev() const
	{
		return prev;
	}

	bool is_visited() const
	{
		return visited;
	}

	void set_prev(cell_t& val)
	{
		prev = &val;
	}

	bool operator=(const point_t& val)
	{
		return pos == val;
	}
};

//	Board matrix
typedef vector<vector<cell_t>> board_t;
