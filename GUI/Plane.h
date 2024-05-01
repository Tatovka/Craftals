#pragma once
#include "InputField.h"
using namespace sf;
class Plane
{
public:
	bool hasMask;
	sf::RenderTexture mask;
	IntRect maskP;
	ClickDetector* activated;
	sf::RenderTexture rt;
	sf::Color col;
	sf::IntRect rect;
	bool isEnable;
	sf::RectangleShape bg;
	std::vector<sf::RectangleShape> deco;
	std::vector<ClickDetector*> cd;
	std::vector<InputField*> iF;
	std::vector<sf::Text> txt;
	int id;
	//std::vector<ScrollBar> sbs;
	void AddObject(ClickDetector* cld) {
		cd.push_back(cld);
	}
	void AddObject(InputField* cld) {
		cd.push_back(cld);
		iF.push_back(cld);
	}
	Plane(sf::Color,sf::Vector2i,sf::Vector2i);
	Plane();
	~Plane() {
		cd.~vector();
	}
	bool IsClicked(sf::Vector2i);
	sf::Sprite Draw();
	void write(sf::Text text, String str, Vector2f pos) {
		text.setString(str);
		text.setPosition(pos);
		txt.push_back(text);
	}
	void write(sf::Text text, String str, Vector2f pos, float size) {

		text.setCharacterSize(size);
		text.setString(str);
		text.setPosition(pos);
		txt.push_back(text);
	}
	void Clear() {
		for (auto i : cd) {
			if (i->type!=3)
			delete i;
		}
		for (auto i : iF) delete i;
		cd.clear();
		iF.clear();
		deco.clear();
		txt.clear();
	}
	void AddMask(IntRect maskProperties) {
		maskP = maskProperties;
		hasMask = 1;
		mask.create(maskP.width, maskP.height);
		mask.clear(Color(0, 0, 0,0));
	}
	void AddDeco(sf::RectangleShape d) {
		deco.push_back(d);
	}
	void SetSize(int width,int height) {
		rt.create(width,height);
		bg.setSize(sf::Vector2f(width, height));
		rect.width = width;
		rect.height = height;
	}
};

