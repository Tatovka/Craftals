#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
class Fractal
{
public:
	float maxIter = 500;
	bool type;
	float* step;
	float* x, *y,*size;
	float* iterations;
	sf::Vector3f* color;
	float* real, *immaginary;
	sf::Shader shader;
	sf::Shader grad;
	Texture mainTexture;
	Sprite sprite;
	std::string dirS;
	Fractal();
	Fractal(float* X, float* Y, float* s, float* iterations, float* r, float* i, std::string dirS);
	Fractal(float* X, float* Y, float* s, float* iterations, std::string dirS);
	void SetType(bool type);
	void SetPos(float*x, float*y);
	void SetSize(float* size);
	void SetColor(String str);
	void SetColor(sf::Vector3f* col);
	void SetColorType(int type);
	void SetStep(float *step);
	sf::Shader* GetGradient();
	sf::Shader* Draw();
};

