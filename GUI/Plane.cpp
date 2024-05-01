#include "Plane.h"
using namespace sf;
Plane::Plane(Color col,Vector2i pos,Vector2i size) {
	this->col = col;
	rect.left = pos.x;
	rect.top = pos.y;
	rect.width = size.x;
	rect.height = size.y;
	isEnable = true;
	bg.setSize(Vector2f(rect.width, rect.height));
	bg.setFillColor(col);
	rt.create(size.x,size.y);
	activated = nullptr;
}
Plane::Plane() {
	isEnable = false;
	activated = nullptr;
}

Sprite Plane::Draw() {
	Sprite s;
	
	s.setPosition(rect.left,rect.top);
	if (!isEnable) {
		rt.clear(Color(0, 0, 0, 0));
		s.setTexture(rt.getTexture());
			return s;
	}
	rt.clear(Color(0,0,0,0));
	rt.draw(bg);
	for (auto i : deco) {
		rt.draw(i);
	}
	for (auto i : cd) {
		
		rt.draw(i->Draw());

	}
	for (auto i : txt)
		rt.draw(i);
	rt.display();
	
	s.setTexture(rt.getTexture());
	if (hasMask) {
		s.setPosition(rect.left-maskP.left, rect.top - maskP.top);
		mask.clear(sf::Color(0, 0, 0, 0));
		mask.draw(s);
		mask.display();
		sf::Sprite sp;
		sp.setTexture(mask.getTexture());
		sp.setPosition(maskP.left, maskP.top);
		return sp;
	}
	return s;
}

bool Plane::IsClicked(Vector2i pos) {
	if (hasMask && !maskP.contains(pos)) return false;
	if (isEnable && rect.contains(pos)) {
		activated = nullptr;
		pos.x -= rect.left;
		pos.y -= rect.top;
		for (auto i : cd) {	
			if (i->OnMouseDown(pos)) {
				activated = i;
				break;
			}
		}
		return true;
	}
	return false;
}
