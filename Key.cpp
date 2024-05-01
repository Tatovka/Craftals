#include "Key.h"
Key::Key(Type t, int f, std::vector<float> val) {
	type = t;
	frame = f;
	for (int i = 0; i < GetValuesNum(t); i++)
		value.push_back(val[i]);
}
Key::Key() {
	frame = 0;
	type = Type::Coord;
}
int Key::GetValuesNum(Type type) {
	if (type == ZCoord || type == Color)
		return 3;
	else if (type == Coord || type == Const) 
		return 2;
	else
		return 1;
}