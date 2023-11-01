#include<iostream>
#include<string>
#include<array>
#include<vector>
#include<map>

constexpr auto MAP_NO_DATA = '#';
enum class DirectionRelative : char
{
	RIGHT = 'R',
	LEFT = 'L'
};

struct Point
{
	int x{ 0 }; // Member initializer
	int y{ 0 };
};

class DirUtil
{
public:
	struct Caps
	{
		char dir_;
		int dx_;
		int dy_;

		Caps(char dir, int dx, int dy) : dir_(dir), dx_(dx), dy_(dy) {};
	};

public:
	DirUtil() = default;

	static const DirUtil& Get()
	{
		static DirUtil util; // staticをつけることで多重に実体化しない
		return util;
	}

	int8_t getMoveAngle(char dir) const
	{
		return (dir == 'R') ? 1 : ((dir == 'L') ? -1 : 0);
	}

	char getDir(uint8_t dir) const
	{
		return caps_[dir & 0b11].dir_;
	}

	Point getCaps(uint8_t ang) const
	{
		Point caps;
		caps.x = caps_[ang & 0b11].dx_;
		caps.y = caps_[ang & 0b11].dy_;
		return caps;
	}

private:
	std::array<Caps, 4> caps_ = {
		Caps('N', 0, -1), // 右が正、下が正
		Caps('E', 1, 0),
		Caps('S', 0, 1),
		Caps('W', -1, 0) };
};


class Character
{
public:
	Character() = default;
	Character(uint8_t dir, int x, int y) : dir_(dir), pos_{ x, y } {};

public:
	void setPos(const Point& basePos) { setPos(basePos.x, basePos.y); };
	void setPos(int x, int y) { pos_.x = x; pos_.y = y; };
	Point getCrrPos() { return pos_; };
	void rotateAng(char dir);
	void moveForward();

private:
	uint8_t dir_{ 0 };
	Point pos_{ 0, 0 };
};

void Character::rotateAng(char dir)
{
	int8_t ang = DirUtil::Get().getMoveAngle(dir);
	dir_ += ang;
}

void Character::moveForward()
{
	Point caps = DirUtil::Get().getCaps(dir_);
	pos_.x += caps.x;
	pos_.y += caps.y;
}



int main()
{
	int X, Y, N;

	std::cin >> X >> Y >> N;

	Character snake(0, X, Y);

	int rotateFlag = 0;
	uint8_t cntRotFlag = 0;
	int add = 1;

	for (int i = 0; i < N; i++)
	{
		if (i == rotateFlag)
		{
			snake.rotateAng('R');

			if ((i != 0) && ((cntRotFlag & 0b1) == 0)) //偶数回のみaddを更新
			{
				add++;
			}
			rotateFlag += add;
			cntRotFlag++;
		}

		snake.moveForward();
	}

	std::cout << snake.getCrrPos().x << ' ' << snake.getCrrPos().y;
	return 0;
}
