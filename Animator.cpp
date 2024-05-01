#include "Animator.h"
Animator::Animator(Key first, Key last) {
	firstKey = first;
	secondKey = last;
	type = first.type;
	length = secondKey.frame - firstKey.frame;
	if (type == Key::Type::ZCoord) {
		leadValue = true;
	}
	else
		leadValue = false;
	currentValue = first.value;
}

float Animator::CountValue(int frame,int num) {
	float delta = secondKey.value[num] - firstKey.value[num];
	return frame / (float)length * delta + firstKey.value[num];
	std::cout << delta;
		
	/*float a = (secondKey.value[num] - firstKey.value[num]) / (pow(secondKey.frame, 2) - pow(firstKey.frame, 2));
	if (secondKey.value[num] - firstKey.value[num] < 0) {
		frame = secondKey.frame - frame;
		a = (secondKey.value[num] - firstKey.value[num]) / (pow(secondKey.frame, 2) - pow(firstKey.frame, 2));
		a = -a;
	}
	return a * pow(frame,2);*/
}
float Animator::CountExponentValue(int frame, int num) {
	return exp(frame / (float)length * ((log(secondKey.value[num])) - log(firstKey.value[num])) + log(firstKey.value[num]));
}
float Animator::CountDependedValue(int frame, int num) {
	float firstValue = CountExponentValue(0, 0);
	float lastValue = CountExponentValue(length, 0);
	float value = CountExponentValue(frame, 0);
	if (lastValue == firstValue)
		return firstKey.value[num];
	float delta = (value-firstValue)/(lastValue - firstValue);

		return delta * (secondKey.value[num] - firstKey.value[num])+ (firstKey.value[num]);
}

bool Animator::GetValue(int frame) {
	

	if (frame<firstKey.frame || frame > secondKey.frame)
		return false;
	frame -= firstKey.frame;
	for (int i = 0; i < currentValue.size(); i++) {
		if (leadValue && i != 0)
			currentValue[i] = CountDependedValue(frame, i);
		else if (leadValue)
				currentValue[i] = CountExponentValue(frame, i);
		else
			currentValue[i] = CountValue(frame,i);
		
		//std::cout << currentValue[i]<<" ";
	}
	
	return true;
}