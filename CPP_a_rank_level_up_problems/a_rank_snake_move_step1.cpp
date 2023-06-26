#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

#define MAP_NO_DATA '#'

struct Point
{
	int x;
	int y;
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
	char dir;

public:

	Character() = default;
	~Character() = default;

};

int main()
{
	int H, W;
	Map map;

	std::cin >> H >> W;

	for (int i = 0; i < H; i++)
	{
		std::string line;

		std::cin >> line;
		map.Add(line);
	}

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (map.Get(j, i) == '#')
			{
				std::cout << i << ' ' << j << std::endl;
				return 0;
			}
		}

	}

	return 0;
}
