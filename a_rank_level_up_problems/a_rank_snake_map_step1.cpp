#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <exception>

struct Point
{
	int x;
	int y;
};

class Map
{
public:
	Map();
	~Map();

private:
	std::vector<std::string> lines;

public:
	void Add(std::string line) { lines.push_back(line); }
	char Get(int x, int y);
	char Get(Point p);

};

Map::Map()
{
}

Map::~Map()
{
}

char Map::Get(int x, int y)
{
	try
	{
		return lines[y][x];
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return '#';
	}
}

char Map::Get(Point p)
{
	return Get(p.x, p.y);
}


int main( void )
{
	int H, W, N;
	Map map;

	std::cin >> H >> W >> N;

	for (int i = 0; i < H; i++)
	{
		std::string str;
		std::cin >> str;
		map.Add(str);
	}

	for (int i = 0; i < N; i++)
	{
		Point p;

		std::cin >> p.y >> p.x;
		std::cout <<  map.Get(p.x, p.y) << std::endl;
	}

	return 0;
}
