#include "Button.h"
using namespace sf;
Button::Button(sf::Vector2f pos, sf::Vector2f size, std::function<void()> method_ ):ClickDetector(sf::Vector2i(pos), sf::Vector2i(size),1){
	method = method_;
	isActive = 1;
	buttonTexture = sf::Texture();
	isPressed = false;
	position = sf::Vector2i(pos);
	rt.create(size.x,size.y);
	this->size = sf::Vector2i(size);
	//Vector2f size = buttonShape.getSize();
	buttonShape.setOrigin(size.x / 2, size.y / 2);
	buttonShape.setPosition(size.x / 2, size.y / 2);
	//buttonShape.setPosition(0,0);
	buttonShape.setSize(size);
	mainColor = sf::Color::White;
	buttonShape.setFillColor(mainColor);
	buttonShape.setOutlineThickness(0);
	buttonShape.setOutlineColor(sf::Color::Black);
	selectColor = sf::Color(220,220,220);
}

Button::~Button() {
	method=nullptr;
}
void Button::SetColor(sf::Color color) {
	mainColor = color;
	buttonShape.setFillColor(color);
}
void Button::SetSelectColor(sf::Color color) {
	selectColor = color;
}
void Button::Rotate(float angle) {
	buttonShape.rotate(angle);
}
void Button::SetRotation(float angle) {
	buttonShape.setRotation(angle);
}
bool Button::OnMouseDown(sf:: Vector2i clickPos){
	if (isActive && rect.contains(clickPos)) {
		isMouseDown = 1;
		buttonShape.setFillColor(selectColor);
		
		return 1;
	}
	return 0;
}
bool Button::OnMouseUp(sf::Vector2i clickPos) {
	if (!isActive) return 0;

	buttonShape.setFillColor(mainColor);
	
	if (isMouseDown && rect.contains(clickPos)) {
		method();
	}
isMouseDown = 0;
return 0;
}

void Button::SetTexture(sf::Texture texture) {
	buttonTexture = texture;
	buttonShape.setTexture(&buttonTexture);
}
sf::Sprite Button::Draw() {
	Sprite s;
	rt.clear(Color(0, 0, 0, 0));
	if (isActive) {
		rt.draw(buttonShape);
		rt.display();
		s.setOrigin(size.x / 2, size.y / 2);
		s.setPosition(position.x + size.x / 2, position.y + size.y / 2);
	}
	s.setTexture(rt.getTexture());
	return s;
}