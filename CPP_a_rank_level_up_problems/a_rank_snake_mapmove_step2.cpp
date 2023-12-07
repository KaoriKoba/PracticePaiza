#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>

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
		int dx_;
		int dy_;

		Caps(uint8_t ang, int dx, int dy) : angle_(ang), dx_(dx), dy_(dy) {}
	};

private:
	std::map<char, Caps> caps_;

public:
	DirUtil()
	{
		caps_.emplace('N', Caps(0, 0, -1));
		caps_.emplace('E', Caps(1, 1, 0));
		caps_.emplace('S', Caps(2, 0, 1));
		caps_.emplace('W', Caps(3, -1, 0));
	}
	~DirUtil() = default;

	static const DirUtil& Get()
	{
		static DirUtil dirutil;
		return dirutil;
	}
	
	Point getCaps(char dir) const
	{
		auto it = caps_.find(dir);
		Point cap;

		if (it != caps_.end())
		{
			cap.x = it->second.dx_;
			cap.y = it->second.dy_;
		}

		return cap;
	}

	char getDir(uint8_t angle) const
	{
		std::array <char, 4> dirmap = { 'N', 'E', 'S', 'W' };
		return dirmap[angle & 0b11];
	}

	uint8_t getAngle(char dir) const
	{
		auto it = caps_.find(dir);
		return ((it != caps_.end()) ? it->second.angle_ : 0);
	}

	int8_t getMoveDir(char ang) const
	{
		return ((ang == 'R') ? 1 : ((ang == 'L') ? - 1 : 0));
	}
};


class Map
{
private:
	std::vector < std::string > lines_;

public:
	Map() = default;
	~Map() = default;

	void Add(const std::string& line) { lines_.push_back(line); }
	bool checkRange(int x, int y) const
	{
		if (lines_.size() > y && 0 <= y)
		{
			if (lines_[y].length() > x && 0 <= x)
			{
				return true;
			}
		}
		return false;
	}
	bool chackValid(int x, int y) const;
	char getData(int x, int y) const
	{
		return lines_[y][x];
	}
};

bool Map::chackValid(int x, int y) const
{
	if (checkRange(x, y) && lines_[y][x] != MAP_NO_DATA)
	{
		return true;
	}

	return false;
}


class Character
{
private:
	uint8_t dir_{ 0 };
	Point   pos_;
public:
	void setDir(char dir) 
	{
		dir_ = DirUtil::Get().getAngle(dir);
	}
	void setPos(int x, int y) { pos_.x = x; pos_.y = y; }
	uint8_t getCrrDir() const { return dir_; }
	Point getCrrPos() const { return pos_; }
};


int main(void)
{
	Map map;
	Character snake;
	int H, W, sx, sy;
	char d, m;

	std::cin >> H >> W >> sy >> sx >> d >> m;

	snake.setDir(d);
	snake.setPos(sx, sy);

	for (int i = 0; i < H ; i++)
	{
		std::string line;
		std::cin >> line;
		map.Add(line);
	}
	
	auto util = DirUtil::Get();
	uint8_t dir = snake.getCrrDir() + util.getMoveDir(m);
	char checkDir = util.getDir(dir & 0b11);
	Point crrPos = snake.getCrrPos();
	Point caps = util.getCaps(checkDir);

	std::cout << (map.chackValid((crrPos.x + caps.x), (crrPos.y + caps.y)) ? "Yes" : "No");

	return 0;
}