#pragma once
#include"SFML/Graphics.hpp"
using namespace sf;
class NewColor
{
public:
	Color color;
	Texture r,g,b;
	Vector3f col;
	Shader shader;
	RenderTexture texture;
	NewColor(std::string dirS) {
		r.create(200, 20);
		g.create(200, 20);
		b.create(200, 20);
		color = sf::Color::Black;
		col = Vector3f(0, 0, 0);
		shader.loadFromFile(dirS+"Resourses\\Shaders\\gradient.frag", sf::Shader::Fragment);
		texture.create(200, 20);
	}
	void SetColor(Vector3f c) {
		col = c;
		float r, g, b;
		r = c.x/256.f;
		g = c.y / 256.f;
		b = c.z / 256.f;
		r = (0.5 + 0.5 * cos(3.f + r)) * 256.f;
		g = (0.5 + 0.5 * cos(3.f + g)) * 256.f;
		b = (0.5f + 0.5f * cos(3.f + b)) * 256.f;
		color = Color(r*20.f, g*20.f, b*20.0f);
		GetTexture(1); GetTexture(2); GetTexture(3);
	}
	Texture* GetTexture(int c) {
		Texture t;
		t.create(200, 20);
		Sprite s;
		s.setTexture(t);
		Vector3f color0 = col;
		Vector3f color1=col;
		if (c == 1) { color0.x = 0; color1.x = 1.f; }
		if (c == 2) { color0.y = 0; color1.y = 1.f; }
		if (c == 3) { color0.z = 0; color1.z =1.f; }
		shader.setUniform("r1", color0.x);
		shader.setUniform("g1", color0.y );
		shader.setUniform("b1", color0.z );
		shader.setUniform("r2", color1.x);
		shader.setUniform("g2", color1.y );
		shader.setUniform("b2", color1.z );
		texture.clear(Color(0, 0, 0, 0));
		texture.draw(s, &shader);
		texture.display();
		if (c == 1) { r = texture.getTexture(); return &r; }
		if(c == 2) { g = texture.getTexture(); return &g; }
		b = texture.getTexture(); return &b;
	}
};

