#pragma once
#include "Button.h"
#include<iostream>
//#include <thread>
class Slider:public ClickDetector
{
protected:
	sf::Vector2i position_;
	sf::RenderTexture texture;
	sf::RectangleShape handleShape;
	sf::RectangleShape background;
	sf::RectangleShape fillArea;
	sf::Color normalColor;
	sf::Color backgroundColor;
	sf::Color pressedColor;
	float handleShapeY = 0;
	int clickPos;
	int lastPos;
	bool isPressed;	
	virtual void Pressed();

public:
	enum HandleAligning { Center, Down };
	float value;
	Slider(int x, int y, int width, int height);
	Slider();
	bool OnMouseDown(sf::Vector2i clickPos);
	bool OnMouseUp(sf::Vector2i clickPos);
	void MouseUp();
	void SetHandleColors(sf::Color defaultColor,sf::Color pressedColor);
	void SetValue(float value);
	sf::Sprite Draw();
	void SetPosition(sf::Vector2i) override;
	void SetHandleProperties(sf::Vector2i hsize,int align);
	void SetHandleTexture(const sf::Texture*);
	void SetBackgroundTexture(const sf::Texture*);
	void SetBackgroundColor(sf::Color);
	void SetFillAreaTexture(const sf::Texture*);
	void SetFillAreaColor(sf::Color);	
};

