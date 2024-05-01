#pragma once
#include <vector>
struct Key
{
public:
	enum Type {
		Zoom, Coord, ZCoord, Color, Step, Iter, Const
	};
	static int GetValuesNum(Type type);
	Type type;
	int frame;
	std::vector<float> value;
	Key(Type t, int f, std::vector<float> val);
	Key();
};

