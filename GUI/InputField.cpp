#include "InputField.h"
InputField::InputField( sf::Vector2i pos, sf::Vector2i size,float fontSize, sf::Font font_):ClickDetector(pos,size,3) {
	//this->type = type;
	isActive = 1;
	ifType = Float;
	position = pos;
	scrollK = new float;
	*scrollK = 1;
	strPos = 0;
	this->fontSize = fontSize;
	cursorPos = 0;
	cursor.setFillColor(sf::Color(0,0,0,0));
	cursor.setPosition(0,size.y/2.f);
	cursor.setSize(sf::Vector2f(1, size.y/1.5f));
	cursor.setOrigin(0, 0.5f * cursor.getSize().y);
	texture.create(size.x,size.y);
	sprite.setPosition(sf::Vector2f(pos));
	rectangle.setPosition(0,0);
	rectangle.setSize(sf::Vector2f(size.x,size.y));
	rectangle.setFillColor(sf::Color(70,70,70,255));
	font=font_;
	charSize = 0;
	textBorders = sf::Vector2i(6, size.x - 6);
	txt.setFont(font);
	txt.setOrigin(0, 0);
	txt.setCharacterSize(fontSize);
	txt.setPosition(0,0);
	txt.setFillColor(sf::Color::Black);
	txt.setString(str);
	textMask.create(textBorders.y - textBorders.x, size.y);
	maskSprite.setTexture(textMask.getTexture());
	maskSprite.setPosition(textBorders.x, 0);
	texture.clear(sf::Color(0, 0, 0, 0));
	texture.draw(rectangle);
	sprite.setTexture(texture.getTexture());
}
InputField::InputField() {

}
void InputField::Erase() {

	if (str.getSize() > 0 && cursorPos>0) {

		MoveCursor(-1);
		str.erase(cursorPos, 1);
	}
	
}
void InputField::SetType(Type t) {
	ifType = t;
}
void InputField::MoveCursor(int dir) {
	float glyphSize=0;
	if (cursorPos + dir <= 0) {
		cursorPos = 0;
		strPos = 0;
		txt.setPosition(0, 0);
		cursor.setPosition(GetPos(cursorPos), cursor.getPosition().y);
	}
	else if (cursorPos + dir > 0 && cursorPos + dir <= str.getSize()) {
		cursorPos += dir;
		if (dir > 0) {



			if (textBorders.y - textBorders.x - (GetPos(cursorPos) + strPos) < 0) {
				MoveStr(textBorders.y - textBorders.x - (GetPos(cursorPos) + strPos));
				if (str.getSize() > cursorPos) {
					glyphSize = font.getGlyph(str[cursorPos], fontSize, 0).advance;
					MoveStr(-glyphSize / 2.f);
				}
			}
		
		}
		
		else if (dir < 0) {
			glyphSize = font.getGlyph(str[cursorPos], fontSize, 0).advance;

			if (- GetPos(cursorPos) - strPos > 0) {
				MoveStr(-GetPos(cursorPos) - strPos);
				if (cursorPos > 0) {
					glyphSize = font.getGlyph(str[cursorPos - 1], fontSize, 0).advance;
					MoveStr(glyphSize / 2.f);
				}
			}
		}
		if (dir>0)
			cursor.setPosition(GetPos(cursorPos)+strPos-1, cursor.getPosition().y);
		else
			cursor.setPosition(GetPos(cursorPos) + strPos, cursor.getPosition().y);

	}

}
void InputField::Input(sf::String str) {
	if (str != '.' || this->str.find('.') == sf::String::InvalidPos)
		this->str.insert(cursorPos, str);
		MoveCursor(1);
}

void InputField::MoveStr(int dir) {
	txt.setPosition(txt.getPosition().x + dir, txt.getPosition().y);
	strPos += dir;
}
float InputField::GetPos(int pos) {
	float res = 0;
	for (int i=0;i<pos;i++) 
		res+= font.getGlyph(str[i], fontSize, 0).advance;
	return res;
}

void InputField::MouseDown() {
	rectangle.setFillColor(sf::Color(0,113,188));
	value = sf::Mouse::getPosition().x - clickPosition.x;
}
void InputField::OnEnter() {
	rectangle.setFillColor(sf::Color(70, 70, 70));
	cursor.setFillColor(sf::Color(0, 0, 0, 0));
	cursorPos = 0;
	MoveCursor(0);
	value = 0;
	isMouseUp = 0;
	if (str.getSize() != 0) {
		if (str.find('.') == sf::String::InvalidPos)
		{
			int startPos = 0;
			if (str[0] == '-')
				int startPos = 1;
				for (int i = startPos; i < str.getSize(); i++)
					if (str[i] != '-')
						value += (float)(str[i] - 48) * pow(10, str.getSize() - i -1);
		}
		else {
			for (int i = 0; i < str.find('.'); i++)
				if (str[i] != '-')
					value += (str[i] - 48) * pow(10, str.find('.') - 1 - i);
			for (int i = str.find('.') + 1; i < str.getSize(); i++)
				if (str[i] != '-')
					value += (double)(str[i] - 48) * pow(10.0, -((double)i - (double)str.find('.')));
		}
		if (str[0] == '-')
			value *= -1.f;
		SetValue(value);
	}
}
sf::Text InputField::GetText() {
	return txt;
}
void InputField::SetK(float* k) {
	scrollK = k;
}
bool InputField::OnKeyDown(char c) {
	if (!isActive) return 0;
	if (c == 13) {
		OnEnter();
		return 1;
	}
	if (c == 8)
		Erase();
	else if (c < 58 && c >= 48)
		Input(c);
	else if (c == 46)
		Input('.');
	else if (c == 1)
		MoveCursor(-1);
	else if (c == 2)
		MoveCursor(1);
	else if (c == '-')
		Input('-');
	return 0;
	
}
bool InputField::OnMouseDown(sf::Vector2i clickPos) {
	if (!isActive) return 0;
	rectangle.setFillColor(sf::Color(70, 70, 70));
	cursor.setFillColor(sf::Color(0, 0, 0, 0));
	if (rect.contains(clickPos)) {
		lastPos = sf::Mouse::getPosition().x;
		isMouseDown = 1;
		clickPosition = clickPos;
		rectangle.setFillColor(sf::Color(30,30,30));
		return 1;
	}
	return 0;
}

void InputField::SetValue(float value) {
	this->value = value;
	str = std::to_string(value);
	if (ifType == Integer)
		str = std::to_string((int)value);
	for (int i = str.getSize()-1; i > 0; i--) {
		if (str[i] != '0' || str.find('.')==sf::String::InvalidPos)
		{
			if (str[i] == '.')
				str.erase(str.getSize() - 1, 1);
			break;
		}
		str.erase(str.getSize()-1, 1);
	}
}
bool InputField::OnMouseUp(sf::Vector2i clickPos) {
	if (!isActive) return 0;
	if (isMouseDown && rect.contains(clickPos)) {
		cursorPos = 0;
		cursorPos = 0;
		MoveCursor(0);
		isMouseUp = 1;
		rectangle.setFillColor(sf::Color(0, 113, 188));
		cursor.setFillColor(sf::Color::Black);
		isMouseDown = 0;
		oldString = str;
		return 1;
	}
	rectangle.setFillColor(sf::Color(70,70,70));
	isMouseDown = 0;
	return 0;	
}

void InputField::Pressed() {
	float delta = sf::Mouse::getPosition().x - lastPos;
	float koef = 1000.f;
	if (ifType == Integer)
		koef = 500.f;
	SetValue(value+delta / koef*abs(*scrollK));
	if (sf::Mouse::getPosition().x == 0 || sf::Mouse::getPosition().x == windowW-1)
		sf::Mouse::setPosition(sf::Vector2i(windowW - sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
	lastPos = sf::Mouse::getPosition().x;
	cursorPos = str.getSize();
}

void InputField::SetValue() {

	if(ifType==Integer)
	str = std::to_string((int)value);
	str = std::to_string(value);
}

sf::Sprite InputField::Draw() {
	//sf::Sprite sprite;
	sprite.setPosition(sf::Vector2f(position));
	texture.clear(sf::Color(0, 0, 0, 0));
	if (isActive) {
		if (isMouseDown)
			Pressed();
		if (isMouseUp) {
			frameCounter %= 60;
			if (frameCounter == 0)
				cursor.setFillColor(sf::Color::Black);
			else if (frameCounter == 30)
				cursor.setFillColor(sf::Color(0, 0, 0, 0));
			frameCounter++;
		}
		txt.setString(str);
		textMask.clear(sf::Color(255, 255, 0, 0));
		textMask.draw(txt);
		textMask.display();
		maskSprite.setTexture(textMask.getTexture());
		texture.draw(rectangle);
		textMask.draw(cursor);
		texture.draw(maskSprite);
		texture.display();
	}
	return(sprite);
}

void InputField::SetTexture(sf::Texture *t) {
	rectangle.setTexture(t);
}

void InputField::SetPosition(sf::Vector2i pos) {
	sprite.setPosition(sf::Vector2f(pos));
	position = pos;
}

void InputField::Deactivate() {
	rectangle.setFillColor(sf::Color(70, 70, 70));
	cursor.setFillColor(sf::Color(0, 0, 0, 0));
	isMouseUp = 0;
	str = oldString;
	cursorPos = 0;
	MoveCursor(0);
}

InputField::~InputField() {
	delete scrollK;
}