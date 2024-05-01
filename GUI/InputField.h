#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ClickDetector.h"
class InputField:public ClickDetector
{
private:
	sf::RenderTexture texture;
	sf::String oldString;
	sf::Sprite maskSprite;
	sf::RenderTexture textMask;
public:
	enum Type {
		Float = 0,
		Integer = 1
	};
	Type ifType;
	int windowW=1920;
	int windowH=1080;
	float lastPos;
	float *scrollK;
	int strPos;
	float charSize;
	int frameCounter;
	float fontSize;
	size_t cursorPos;
	sf::RectangleShape cursor;
sf::Sprite sprite;
	sf::Vector2i clickPosition;
	sf::Font font;
	sf::RectangleShape rectangle;
	sf::Text txt;
	int type; 
float value;
	sf::String str;
	sf::Vector2i textBorders;
	InputField( sf::Vector2i pos, sf::Vector2i size_,float fontSize,sf::Font font);
	InputField();
	~InputField();
	void SetValue(float value);
	void SetValue();
	void SetType(Type t);
	bool OnKeyDown(char c);
	void Input(sf::String str);
	void OnEnter();
	float GetPos(int pos);
	void MoveStr(int dir);
	void Erase();
	bool OnMouseDown(sf::Vector2i clickPos);
	bool OnMouseUp(sf::Vector2i clickPos);
	sf::Text GetText();
	void MouseDown();
	sf::Sprite Draw();
	void MoveCursor(int x);
	void Pressed();
	void SetK(float* k);
	void SetTexture(sf::Texture*);
	void SetPosition(sf::Vector2i) override;
	void Deactivate();
};

