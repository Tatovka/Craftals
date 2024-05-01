#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class ClickDetector
{
public:
	bool isActive;
	sf::Vector2i position;
	sf::Vector2i size;
	sf::IntRect rect;
	int number;
	int type;
	bool isMouseUp = 0;
	bool isMouseDown = 0;
	ClickDetector();
	ClickDetector(sf::Vector2i pos, sf::Vector2i size, int t);
	virtual bool OnMouseDown(sf::Vector2i clickPos);
	virtual bool OnMouseUp(sf::Vector2i clickPos);
	virtual sf::Sprite Draw();
	virtual void SetPosition(sf::Vector2i);
	virtual void SetSize(sf::Vector2i);
};

