
#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "ClickDetector.h"
class Button :public ClickDetector
{
public:

	std::function<void()> method;

	//sf::IntRect buttonRect;
	sf::RenderTexture rt;
	//sf::Vector2f position, size;
	sf::Color color;
	sf::Color mainColor;
	sf::Color selectColor;
	sf::Texture buttonTexture;
	sf::RectangleShape buttonShape;
	bool isPressed;
	Button(sf::Vector2f pos, sf::Vector2f size, std::function<void()> method_);
	Button(sf::Vector2f pos, sf::Vector2f size);
	Button() {}
	~Button();
	void SetFunction(std::function<void()> f) {
		method = f;
	};
	bool OnMouseDown(sf::Vector2i clickPos) override;
	bool OnMouseUp(sf::Vector2i clickPos) override;
	void SetColor(sf::Color color);
	void SetSelectColor(sf::Color color);
	void SetTexture(sf::Texture texture);
	void Rotate(float angle);
	void SetRotation(float angle);
	//void SetOrigin(sf::Vector2f origin);
	sf::Sprite Draw() override;
};