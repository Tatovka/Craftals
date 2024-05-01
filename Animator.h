#pragma once
#include <vector>
#include<iostream>
#include "Key.h"
class Animator
{
public:
	Key firstKey;
	Key secondKey;
	std::vector<float> currentValue;
	bool leadValue;
	int length;
	Key::Type type;
	Animator(Key first, Key last); 
	bool GetValue(int frame);
	float CountValue(int frame,int num);
	float CountExponentValue(int frame, int num);
	float CountDependedValue(int frame, int num);
};

