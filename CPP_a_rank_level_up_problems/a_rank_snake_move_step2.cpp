#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

constexpr auto MAP_NO_DATA = '#';
constexpr auto DIR_NORTH = 'N';
constexpr auto DIR_SOUTH = 'S';
constexpr auto DIR_EAST = 'E';
constexpr auto DIR_WEST = 'W';

enum class Direction : char
{
	North = 'N',
	South = 'S',
	East = 'E',
	West = 'W'
};

struct Point
{
	int x{ 0 };
	int y{ 0 };
};

class Map
{
public:
	Map() = default;
	~Map() = default;

private:
	std::vector<std::string> lines;

public:
	void Add(const std::string& line) { lines.push_back(line); }
	char Get(int x, int y) const;
	char Get(const Point& p) const;
	int Modify(int x, int y, char newdata);
	int Modify(const Point& p, char newdata);
	void Print();

protected:
	bool CheckRange(int x, int y) const;
	bool CheckRange(const Point& p) const;
};

bool Map::CheckRange(int x, int y) const
{
	if (0 <= y && lines.size() > y)
	{
		if (0 <= x && lines[y].length() > x)
		{
			return true;
		}
	}

	return false;
}

bool Map::CheckRange(const Point& p) const
{
	return CheckRange(p.x, p.y);
}

char Map::Get(int x, int y) const
{
	if (CheckRange(x, y))
	{
		return lines[y][x];
	}

	return MAP_NO_DATA;
}

char Map::Get(const Point& p) const
{
	return Get(p.x, p.y);
}

int Map::Modify(int x, int y, char newdata)
{
	if (CheckRange(x, y))
	{
		lines[y][x] = newdata;
		return 0;
	}

	return	-1;
}

int Map::Modify(const Point& p, char newdata)
{
	return Modify(p.x, p.y, newdata);
}

void Map::Print()
{
	for (std::string l : lines)
	{
		std::cout << l << std::endl;
	}
}

class Character
{
private:
	Point pos;
	Direction dir{ Direction::North };

public:
	void SetPos(const Point& basePos);
	void SetPos(int x, int y);
	Point GetCrrPos();
	void Move(Direction moveDir);
};

void Character::SetPos(const Point& basePos)
{
	SetPos(basePos.x, basePos.y);
}

void Character::SetPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

Point Character::GetCrrPos()
{
	return pos;
}

void Character::Move(Direction moveDir)
{
	switch (moveDir)
	{
	case Direction::North:
		pos.y--;
		break;
	case Direction::South:
		pos.y++;
		break;
	case Direction::East:
		pos.x++;
		break;
	case Direction::West:
		pos.x--;
		break;
	default:
		break;
	}
}

int main()
{
	int X, Y, N;
	Character snake;

	std::cin >> Y >> X >> N;

	snake.SetPos(X, Y);

	for (int i = 0; i < N; i++)
	{
		char dir;
		Point pos;
		std::cin >> dir;

		snake.Move((Direction)dir);
		pos = snake.GetCrrPos();

		std::cout << pos.y << ' ' << pos.x << std::endl;
	}

	return 0;
}
