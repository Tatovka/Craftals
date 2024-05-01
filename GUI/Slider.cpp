#include "Slider.h"
Slider::Slider(int x,int y,int width,int height) :ClickDetector(sf::Vector2i(x,y), sf::Vector2i(height, height ), 2) {
	isPressed = false;
	isActive = 1;
	value = 0;
	lastPos = x;
	clickPos = 0;
	position_ = position;
	size = sf::Vector2i(width, height);
	normalColor = sf::Color(100, 100, 100);
	pressedColor = sf::Color(50, 50, 50);
	handleShape.setFillColor(normalColor);
	background.setFillColor(sf::Color(150, 150, 150));
	background.setSize(sf::Vector2f(width , height));
	fillArea.setFillColor(sf::Color(200, 200, 200));
	fillArea.setSize(sf::Vector2f(1,height));
	SetHandleProperties(sf::Vector2i(height, height), 0);
	texture.clear(sf::Color(0,0,0,1));
	texture.draw(background);
	texture.draw(fillArea);
	texture.draw(handleShape);
	texture.display();
}

Slider::Slider() {
}

void Slider::SetHandleColors(sf::Color defaultColor,sf::Color pressedColor) {
	normalColor = defaultColor;
	this->pressedColor = pressedColor;
	handleShape.setFillColor(normalColor);
}

bool Slider::OnMouseUp(sf::Vector2i clickPos) {
	isMouseDown = 0;
	handleShape.setFillColor(normalColor);
	return 0;
}

bool Slider::OnMouseDown(sf::Vector2i clickPos) {
	if (rect.contains(clickPos)) {
		this->clickPos = sf::Mouse::getPosition().x;
		lastPos = rect.left;
		isMouseDown = true;
		handleShape.setFillColor(pressedColor);
		return 1;
	}
	
	return 0;
}

void Slider::Pressed() {
		rect.left = lastPos + sf::Mouse::getPosition().x - clickPos;
		if (rect.left > position_.x + size.x)
			rect.left = position_.x + size.x;
		if (rect.left < position_.x)
			rect.left = position_.x;
		handleShape.setPosition(rect.left - position_.x, handleShapeY);
		value = (rect.left - position_.x) / (float)(size.x);
		fillArea.setSize(sf::Vector2f(size.x * value+size.y, size.y));
}

sf::Sprite Slider::Draw() {
	SetValue(value);
	//std::cout << clickPos.x << " " << clickPos.y << " ";
	if(isMouseDown)
		Pressed();
	texture.clear(sf::Color(0,0,0,0));
	texture.draw(background);
	texture.draw(fillArea);
	texture.draw(handleShape);
	texture.display();
	sf::Sprite sprite;
	sprite.setPosition(position.x, position.y);
	sprite.setTexture(texture.getTexture());
	return sprite;
}

void Slider::SetValue(float value) {
	value =__min(1, value);
	this->value = value;
	rect.left = value * size.x + position_.x;
	fillArea.setSize(sf::Vector2f(size.x * value + size.y, size.y));
	handleShape.setPosition(value * size.x, handleShapeY);
}

void Slider::SetPosition(sf::Vector2i pos) {
	position = pos;
}

void Slider::SetHandleProperties(sf::Vector2i hsize, int align) {
	sf::Vector2i size=this->size;
	handleShape.setSize(sf::Vector2f(hsize));
	if (align == 0) {
		if (hsize.y > size.y) {
			size.y = hsize.y;
		}
		size.x = size.x + hsize.x;
		handleShape.setOrigin(0, 0);
		handleShapeY = 0;
		background.setOrigin(0, this->size.y/2);
		fillArea.setOrigin(0, this->size.y/2);
		fillArea.setPosition(0, size.y/2);
		background.setPosition(0, size.y/2);
		rect.top = 0;
	}
	else if (align == 1) {
		size.y += hsize.y;
		size.x = size.x + hsize.x;
		handleShape.setOrigin(0, 0);
		handleShapeY = this->size.y;
		background.setOrigin(0, 0);
		fillArea.setOrigin(0, 0);
		fillArea.setPosition(0, 0);
		background.setPosition(0, 0);
		rect.top = 0;
	}	
	texture.create(size.x, size.y);
	rect.top+=handleShapeY+position.y;
	rect.height = hsize.y;
	rect.width = hsize.x;
	handleShape.setPosition(handleShape.getPosition().x, handleShapeY);
}

void Slider::SetHandleTexture(const sf::Texture* tex) {
	handleShape.setTexture(tex);
}

void Slider::SetBackgroundTexture(const sf::Texture* tex) {
	background.setTexture(tex);
}

void Slider::SetBackgroundColor(sf::Color col) {
	background.setFillColor(col);
}

void Slider::SetFillAreaTexture(const sf::Texture* tex) {
	fillArea.setTexture(tex);
}

void Slider::SetFillAreaColor(sf::Color col) {
	fillArea.setFillColor(col);
}