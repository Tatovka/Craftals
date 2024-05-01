#pragma once
#include <functional>
#include"ClickDetector.h"
#include "Button.h"
#include "Slider.h"
#include "InputField.h"
#include "Plane.h"
#include "ScrollBar.h"
class UiController {
private:
	sf::RenderTexture rt;
	ClickDetector* activated;
	InputField* enterText;
	int activatedLayer;
	sf::Font ifFont;
public:
	std::string dirS;
	int windowW=1920;
	int windowH = 1080;
	std::vector <Plane*> layers;
	UiController(int width,int height) {
		ifFont.loadFromFile("Resourses/Fonts/Inter-Medium.ttf");
		activatedLayer =0;
		windowH = height;
		windowW = width;
		layers.push_back(new Plane( sf::Color(0,0,0,0), sf::Vector2i(0,0), sf::Vector2i(1920,1080) ) );
		rt.create(1920, 1080);
		activated = nullptr;
	}
	UiController() {
	}
	void Create(int width, int height) {
		ifFont.loadFromFile(dirS+"Resourses\\Fonts\\Inter-Medium.ttf");
		activatedLayer = 0;
		windowH = height;
		windowW = width;
		layers.push_back(new Plane(sf::Color(0, 0, 0, 0), sf::Vector2i(0, 0), sf::Vector2i(1920, 1080)));
		rt.create(1920, 1080);
		activated = nullptr;
	}
	Plane* CreatePlane(Color col, Vector2i pos, Vector2i size) {
		Plane* p = new Plane(col, pos,size);
		p->id = layers.size();
		layers.push_back(p);
		return p;
	}
	Button* CreateButton(sf::Vector2f pos, sf::Vector2f size, std::function<void()> func,int layer) {
		if (layer >= layers.size())
			return 0;
		Button* b = new Button(pos,size,func);
		//b->number = buttons.size();
		//clickDetectors.push_back(b);
		//buttons.push_back(b);
		layers[layer]->AddObject(b);
		return b;
	}
	Slider* CreateSlider(int x, int y, int width, int height, int layer) {
		if (layer >= layers.size())
			return 0;
		Slider* b = new Slider(x,y, width,height);
		//b->number = sliders.size();
		//clickDetectors.push_back(b);
		//sliders.push_back(b);
		layers[layer]->AddObject(b);
		return b;
	}
	ScrollBar* CreateScrollBar(int x, int y, int width, int height, int layer){
		if (layer >= layers.size())
			return 0;
		ScrollBar* b = new ScrollBar(x, y, width,height);
		//b->number = sliders.size();
		//clickDetectors.push_back(b);
		//sliders.push_back(b);
		layers[layer]->AddObject(b);
		//scrollBars.push_back(b);
		return b;
	}
	InputField* CreateInputField(sf::Vector2i pos, sf::Vector2i size, float fontSize, int layer) {
		if (layer >= layers.size())
			return 0;
		InputField *b = new InputField(pos,size,fontSize,ifFont);
		b->number = layers[layer]->iF.size();
		b->windowW = windowW;
		b->windowH = windowH;
		//clickDetectors.push_back(b);
		//inputFields.push_back(b);
		layers[layer]->AddObject(b);
		return b;
	}
	Button* CreateButton(sf::Vector2f pos, sf::Vector2f size, std::function<void()> func) {
		Button* b = new Button(pos, size, func);
		//b->number = buttons.size();
		//clickDetectors.push_back(b);
		//buttons.push_back(b);
		layers[0]->AddObject(b);
		return b;
	}
	Slider* CreateSlider(int x, int y, int width, int height) {
		Slider* b = new Slider(x, y, width, height);
		//b->number = sliders.size();
		//clickDetectors.push_back(b);
		//sliders.push_back(b);
		layers[0]->AddObject(b);
		return b;
	}
	ScrollBar* CreateScrollBar(int x, int y, int width, int height) {
		ScrollBar* b = new ScrollBar( x,  y,  width,  height);
		//b->number = sliders.size();
		//clickDetectors.push_back(b);
		//sliders.push_back(b);
		layers[0]->AddObject(b);
		//scrollBars.push_back(b);
		return b;
	}
	InputField* CreateInputField(sf::Vector2i pos, sf::Vector2i size, float fontSize) {
		InputField* b = new InputField(pos, size, fontSize,ifFont);
		b->number = layers[0]->iF.size();
		b->windowW = windowW;
		b->windowH = windowH;
		//clickDetectors.push_back(b);
		//inputFields.push_back(b);
		layers[0]->AddObject(b);
		return b;
	}
	sf::Sprite Draw() {
		float w = windowW / 1920.f;
		float h = windowH / 1080.f;
		rt.clear(sf::Color(0, 0, 0, 0));
		for (auto i : layers) {
			rt.draw(i->Draw());
		}
		rt.display();
		sf::Sprite s;
		s.setTexture(rt.getTexture());
		s.setScale(w,h);
		return s;
	}
	void OnMouseDown(sf::Vector2i clickPos) {
		if (enterText) {
			enterText->Deactivate();
			enterText = nullptr;
		}
		for (auto i = layers.end()-1; i >= layers.begin();--i) {
			if ((*i)->IsClicked(clickPos)) {
				activated = (*i)->activated;
				(*i)->activated = nullptr;
				activatedLayer = (*i)->id;
				break;
			}
			
		}
		
	}
	void OnMouseUp(sf::Vector2i clickPos) {
		if (activated) {
		
			clickPos.x -= layers[activatedLayer]->rect.left;
			clickPos.y -= layers[activatedLayer]->rect.top;
			if (activated->OnMouseUp(clickPos))
				enterText = layers[activatedLayer]->iF[activated->number];
			activated = nullptr;
		}
	}
	
	void OnEvent(sf::Event event) {
		float w = windowW / 1920.f;
		float h = windowH / 1080.f;
		if (event.type == sf::Event::MouseButtonPressed) {
			OnMouseDown(sf::Vector2i(event.mouseButton.x / w, event.mouseButton.y / h));
		}
		if (event.type == sf::Event::MouseButtonReleased)
			OnMouseUp(sf::Vector2i(event.mouseButton.x / w, event.mouseButton.y / h));

		if (event.type == sf::Event::TextEntered) {
			if (enterText)
				if (enterText->OnKeyDown(event.text.unicode))
					enterText = nullptr;
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (enterText) {
				if (event.key.code == sf::Keyboard::Left)
					enterText->OnKeyDown(1);
				if (event.key.code == sf::Keyboard::Right)
					enterText->OnKeyDown(2);

			}
		}
		else if (event.type == sf::Event::KeyPressed) {
		}
	}

};