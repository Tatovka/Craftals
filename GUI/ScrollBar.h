#pragma once
#include "Slider.h"
#include "Plane.h"
#include "vector"
#include <math.h>
class ScrollBar:public Slider 
{
public:
	float length, nullCoord;
	  int x, y;
	  ScrollBar(int x, int y, int width, int height):Slider( x,y, width,height){
		  length = 0;
		  this->x = x;
		  this->y = y;

	  }
	  Plane *plane;
	  void AddObject(Plane* obj) {
		  plane = obj;
		  length = plane->rect.width;
		  nullCoord = plane->rect.left;
	  }
	  void Move() {

		  plane->rect.left = nullCoord - value * (plane->rect.width - size.x);
	  }
	  void NewLen() {
		  if (plane->rect.width - size.x <= 0)value = 0;
		  value = -(plane->rect.left - nullCoord) / (plane->rect.width - size.x);
		  value = std::min(1.f,std::max(0.f, value));

		  SetValue(value);
		  Move();
	  }
	   void Pressed()override {
		  Move();
		
		  rect.left = lastPos + sf::Mouse::getPosition().x - clickPos;
		  if (rect.left > position_.x + size.x)
			  rect.left = position_.x + size.x;
		  if (rect.left < position_.x)
			  rect.left = position_.x;
		  handleShape.setPosition(rect.left - position_.x, handleShapeY);
		  value = (rect.left - position_.x) / (float)(size.x);
		  fillArea.setSize(sf::Vector2f(size.x * value + size.y, size.y));
	  }
	
sf::Sprite Draw() {
		   //SetValue(value);
		   //std::cout << clickPos.x << " " << clickPos.y << " ";
		   if (isMouseDown)
			   Pressed();
		   texture.clear(sf::Color(0, 0, 0, 0));
		   texture.draw(background);
		   texture.draw(fillArea);
		   texture.draw(handleShape);
		   texture.display();
		   sf::Sprite sprite;
		   sprite.setPosition(position.x, position.y);
		   sprite.setTexture(texture.getTexture());
		   return sprite;
	   }

void Close() {
	plane->isEnable = 0;
	value = 0;
}
void Open() {
	plane->isEnable = 1;
	value = 0;
}
};

