#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <string>

#define MAP_NO_DATA '#'

struct Point
{
	int x{ 0 };
	int y{ 0 };
};

class DirUtil
{
public:
	struct Caps
	{
		uint8_t angle_;
		int x_;
		int y_;

		Caps(uint8_t ang, int x, int y) : angle_(ang), x_(x), y_(y) {}
	};

private:
	std::map<char, Caps> caps_;

public:
	DirUtil()
	{
		caps_.emplace('N', Caps( 0, 0, -1 ));
		caps_.emplace('E', Caps( 1, 1, 0 ));
		caps_.emplace('S', Caps( 2, 0, 1 ));
		caps_.emplace('W', Caps( 3, -1, 0 ));
	}
	~DirUtil() = default;

	static const DirUtil& Get()
	{
		static DirUtil util;
		return util;
	}
	
	uint8_t getAngle(char dir) const
	{
		auto it = caps_.find(dir);
		return (it != caps_.end()) ? it->second.angle_ : 0;
	}

	char getDie(uint8_t angle) const
	{
		const std::array<char, 4> dirmap = { 'N', 'E', 'S', 'W' };
		return dirmap[angle & 0b011];
	}

	Point getCaps(char dir) const
	{
		auto it = caps_.find(dir);
		Point cap;

		if (it != caps_.end())
		{
			cap.x = it->second.x_;
			cap.y = it->second.y_;
		}
		return cap;
	}

private:
	
};

class Map
{
private:
	std::vector < std::string> line_;

public:
	Map() = default;
	~Map() = default;

public:
	void Add(const std::string& line) { line_.push_back(line); }
	char Get(int x, int y) const;
	char Get(const Point& pos) const;
	bool checkRange(int x, int y) const;
	bool checkValid(int x, int y) const;
};

char Map::Get(const Point& pos) const
{
	return Get(pos.x, pos.y);
}

char Map::Get(int x, int y) const
{
	if (checkRange(x, y))
	{
		return line_[y][x];
	}

	return MAP_NO_DATA;
}

bool Map::checkRange(int x, int y) const
{
	if (0 <= y && line_.size() > y)
	{
		if (0 <= x && line_[y].length() > x)
		{
			return true;
		}
	}

	return false;
}

bool Map::checkValid(int x, int y) const
{
	if (checkRange(x , y) && line_[y][x] != MAP_NO_DATA) return true;	
	return false;
}


class Character
{
private:
	uint8_t dir_{0};
	Point   pos_;

public:
	Character() = default;
	~Character() = default;

	void SetPos(int x, int y) { pos_.x = x; pos_.y = y; }
	void SetDir(char dir) 
	{
		uint8_t ang = DirUtil::Get().getDie(dir);
		dir_ = ang;
	}
	Point GetCrrPos() const { return pos_; }
	Point GetForward(char dir) const;
	bool Move(int x, int y);
};

Point Character::GetForward(char dir) const
{
	Point cap = DirUtil::Get().getCaps(dir);
	Point pos;

	pos.x = pos_.x + cap.x;
	pos.y = pos_.y + cap.y;

	return pos;
}

bool Character::Move(int x, int y)
{
	return false;
}


int main()
{
	Map map;
	Character snake;
	int H, W, sy, sx;
	char m;

	std::cin >> H >> W >> sy >> sx >> m;

	snake.SetDir('N');
	snake.SetPos(sx, sy);

	for (int i = 0; i < H; i++)
	{
		std::string line;

		std::cin >> line;
		map.Add(line);
	}

	Point nextPos = snake.GetForward(m);

	std::cout << ((map.checkValid(nextPos.x, nextPos.y)) ? "Yes" : "No") << std::endl;


	return 0;
}