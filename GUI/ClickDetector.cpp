#include "ClickDetector.h"
#include <iostream>
ClickDetector::ClickDetector() {
	rect.left = rect.top = 0;
	rect.width = rect.height = 0;
	position = sf::Vector2i(0, 0);
	size = sf::Vector2i(0, 0);
	type = 0;
}
ClickDetector::ClickDetector(sf::Vector2i pos, sf::Vector2i size,int t) {
	rect.left = pos.x;
	rect.top = pos.y;
	rect.width = size.x;
	rect.height = size.y;
	position = pos;
	this->size = size;
	type = t;
	number = 0;
}
 bool ClickDetector::OnMouseDown(sf::Vector2i clickPos){
	if (rect.contains(clickPos)) {
		isMouseDown = 1;
		return 1;
	}
	return 0;
}
bool ClickDetector::OnMouseUp(sf::Vector2i clickPos) {
	if (isMouseDown&&rect.contains(clickPos))
			isMouseUp = 1;
	isMouseDown = 0;
	return 0;
}

sf::Sprite ClickDetector::Draw() {
	return sf::Sprite();
}
void ClickDetector::SetPosition(sf::Vector2i pos) {
	position = pos;
}
void ClickDetector::SetSize(sf::Vector2i sz) {
	size = sz;
}