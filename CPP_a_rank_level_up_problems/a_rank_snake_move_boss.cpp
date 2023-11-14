#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <string>

constexpr auto MAP_NO_DATA = '#';

enum class DerectionRelative : char
{
	RIGHT = 'R',
	LEFT  = 'L'
};

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
	
		Caps(uint8_t angle, int dx, int dy): angle_(angle), dx_(dx), dy_(dy) {} // constructor initialization list
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

	static const DirUtil& Get()
	{
		static DirUtil util;
		return util;
	}

	int8_t getMoveAngle(char dir) const // ‘Š‘Î ¶‰E
	{
		return (dir == 'R') ? 1 : ((dir == 'L') ? -1 : 0);
	}

	uint8_t getAngle(char dir) const // â‘Î •ûŠp
	{
		auto it = caps_.find(dir);
		return (it != caps_.end()) ? it->second.angle_ : 0;
	}
	
	char getDir(uint8_t angle) const
	{
		constexpr std::array<char, 4> dirmap = { 'N', 'E', 'S', 'W' };
		return dirmap[angle & 0b11];
	}

	Point getCaps(char dir) const // •ûŠp
	{
		auto it = caps_.find(dir);
		Point cap = {0,0};
		
		if (it != caps_.end())
		{
			cap.x = it->second.dx_;
			cap.y = it->second.dy_;
			return cap;
		}

		return cap;
	}
};


class Map
{
public:
	Map() = default;
	~Map() = default;
private:
	std::vector<std::string > line_;
};

class Character
{
public:
	Character() = default;
	~Character() = default;

private:
	uint8_t dir_{ 0 };
	Point pos_{ 0, 0 };

public:
	void Move(char dir);
	void setChDir(uint8_t dir) { dir_ = dir; }
	void setChDir(char dir);
	void setChPos(int x, int y) { pos_ = { x, y }; }
	void setChPos(Point pos) { pos_ = pos; }
	uint8_t getDir() const { return (dir_ & 0b11); }
	Point getCrrPos() const { return pos_; }
};

void Character::setChDir(char dir)
{
	const DirUtil& utl = DirUtil::Get();

	dir_ = utl.getAngle(dir);

}

void Character::Move(char dir)
{
	const DirUtil& utl = DirUtil::Get();
	
	dir_ += utl.getMoveAngle(dir);

	char newDir = utl.getDir(dir_ & 0b11);

	const Point cups = utl.getCaps(newDir);

	pos_.x += cups.x;
	pos_.y += cups.y;

}


int main()
{
	Character snakeBoss;
	int X, Y, N;

	std::cin >> X >> Y >> N;

	snakeBoss.setChDir('N');
	snakeBoss.setChPos(X, Y);

	for (int i = 0; i < N; i++)
	{
		char dir;
		std::cin >> dir;
		
		snakeBoss.Move(dir);

		Point pt = snakeBoss.getCrrPos();
		std::cout << pt.x << ' ' << pt.y << std::endl;

	}

	return 0;
}
