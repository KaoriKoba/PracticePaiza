#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>

constexpr auto MAP_NO_DATA = '#';
constexpr std::array<char, 4> DirectionAbsolute = { 'N', 'E', 'S', 'W'};

enum class DirectionRelative : char
{
	RIGHT = 'R',
	LEFT = 'L'
};

struct Point
{
	int x{ 0 };
	int y{ 0 };
};

struct Caps
{
	uint8_t angle;
	int8_t dx;
	int8_t dy;

	Caps(uint8_t ang, int8_t x, int8_t y) :angle(ang), dx(x), dy(y) { }
};

class Map
{
public:
	Map() = default;
	~Map() = default;

private:
	std::vector<std::string> lines_;

public:
	void Add(const std::string& line) { lines_.push_back(line); }
	char Get(int x, int y) const;
	char Get(const Point& p) const;
	int Modify(int x, int y, char newdata);
	int Modify(const Point& p, char newdata);
	void Print();

protected:
	bool CheckRange(int x, int y) const;
	bool CheckRange(const Point& p) const;

};

class Character
{
public:
	Character()
	{
		convm_.emplace(DirectionAbsolute[0], Caps(0, 0, -1)); // N  向いている方向にすすむ時の座標の増減値
		convm_.emplace(DirectionAbsolute[1], Caps(1, 1, 0));  // E
		convm_.emplace(DirectionAbsolute[2], Caps(2, 0, 1));  // S
		convm_.emplace(DirectionAbsolute[3], Caps(3, -1, 0)); // W
	};
	~Character() = default;

private:
	Point pos_;
	uint8_t angle_{ 0 };
	std::map<char, Caps> convm_;

public:
	void Move(DirectionRelative moveDir);
	void SetAng(char newDir);
	void SetPos(const Point& basePos);
	void SetPos(int x, int y);
	Point GetCrrPos();
	void PrintCrrPos();

private:
	char RotateAng(char dir);
};


bool Map::CheckRange(int x, int y) const
{
	if (0 <= y && lines_.size() > y)
	{
		if (0 <= x && lines_[y].length() > x)
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
		return lines_[y][x];
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
		lines_[y][x] = newdata;
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
	for (std::string l : lines_)
	{
		std::cout << l << std::endl;
	}
}

void Character::SetAng(char newDir)
{
	int i = 0;
	for (char dir : DirectionAbsolute )
	{
		if (newDir == dir) break;
		i++;
	}

	angle_ = i & 0b11;
}

void Character::SetPos(const Point& basePos)
{
	SetPos(basePos.x, basePos.y);
}

void Character::SetPos(int x, int y)
{
	pos_.x = x;
	pos_.y = y;
}

Point Character::GetCrrPos()
{
	return pos_;
}

void Character::Move(DirectionRelative moveDir)
{ 
	RotateAng((char)moveDir);
	
	auto it = convm_.find(DirectionAbsolute[angle_]);
	if (it != convm_.end())
	{
		pos_.x += it->second.dx;
		pos_.y += it->second.dy;
	}
}

void Character::PrintCrrPos()
{
	std::cout << pos_.y << ' ' << pos_.x << std::endl;
}

char Character::RotateAng(char dir)
{
	angle_ += ((dir == 'R') ? 1 : ((dir == 'L') ? -1 : 0));
	angle_ &= 0b11;

	return angle_;
}


int main()
{
	int X, Y;
	char D, d;
	Character snake;

	std::cin >> Y >> X >> D;

	snake.SetPos(X, Y);
	snake.SetAng(D);

	Point pos;
	std::cin >> d;

	snake.Move((DirectionRelative)d);
	pos = snake.GetCrrPos();

	std::cout << pos.y << ' ' << pos.x << std::endl;

	return 0;
}
