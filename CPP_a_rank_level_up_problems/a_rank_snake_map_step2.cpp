#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

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

};

char Map::Get(int x, int y) const
{
	try
	{
		return lines.at(y).at(x);
	}
	catch (std::out_of_range&)
	{
		return '#';
	}
}

char Map::Get(const Point& p) const
{
	return Get(p.x, p.y);
}

int Map::Modify(int x, int y, char newdata)
{
	try
	{
		lines.at(y).at(x) = newdata;
		return 0;
	}
	catch (std::out_of_range&)
	{
		return -1;
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


int main()
{
	int H, W, N;
	Map map;

	std::cin >> H >> W >> N;

	for ( int i = 0; i < H; i++ )
	{
		std::string line;
		
		std::cin >> line;
		map.Add(line);
	}

	for (int i = 0; i < N; i++)
	{
		Point p;
		std::cin >> p.y >> p.x;

		map.Modify(p, '#');
	}

	map.Print();

	return 0;
}
