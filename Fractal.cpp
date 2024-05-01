#include "Fractal.h"

Fractal::Fractal() {
	x = y = size=new float;
	step = new float;
	*step = 0.15f;
	immaginary = real = 0;
	iterations = 0;
	type = 0;
	mainTexture.create(500, 300);
	sprite.setTexture(mainTexture);
}
Fractal::Fractal(float* X, float*Y, float*s, float* iterations, float* r, float* i,std::string dir) {
	dirS = dir;
	type = 1;
	color = nullptr;
	step = nullptr;
	shader.loadFromFile(dirS+"Resourses\\Shaders\\julia.frag", sf::Shader::Fragment);
	grad.loadFromFile(dirS + "Resourses\\Shaders\\shader.frag", sf::Shader::Fragment);
	shader.setUniform("step", 0.15f);

	x = X;
	y = Y;
	size = s;
	this->iterations = iterations;
	real = r;
	immaginary = i;
	mainTexture.create(500, 300);
	sprite.setTexture(mainTexture);
}
Fractal::Fractal(float* X, float* Y, float* s, float* iterations,std::string dir) {
	dirS = dir;
	type = 0;
	step = nullptr;
	color = nullptr;
	shader.loadFromFile(dirS + "Resourses\\Shaders\\mandelbrot.frag", sf::Shader::Fragment);
	grad.loadFromFile(dirS + "Resourses\\Shaders\\shader.frag", sf::Shader::Fragment);
	shader.setUniform("step", 0.15f);

	x = X;
	y = Y;
	size = s;
	this->iterations = iterations;
	real = 0;
	immaginary = 0;
	mainTexture.create(500, 300);
	sprite.setTexture(mainTexture);
}
void Fractal::SetStep(float* step) {
	this->step = step;
}
sf::Shader* Fractal::Draw() {
	shader.setUniform("x", *x);
	shader.setUniform("y", *y);
	shader.setUniform("size", *size);
	shader.setUniform("iterations", *iterations*maxIter);
	shader.setUniform("step", *step);
	shader.setUniform("color", *color);
	if (type) {
		shader.setUniform("i", *immaginary);
		shader.setUniform("r", *real);
	}
	return &shader;
}

void Fractal::SetType(bool type) {
	if(type)
		shader.loadFromFile(dirS+"Resourses\\Shaders\\julia.frag", sf::Shader::Fragment);
	else
		shader.loadFromFile(dirS+"Resourses\\Shaders\\mandelbrot.frag", sf::Shader::Fragment);
}
void Fractal::SetPos(float* x, float* y) {
	this->x = x;
	this->y = y;
}
void Fractal::SetSize(float*size) {
	this->size = size;
}
void Fractal::SetColor(String str) {
	sf::Image img;
	img.loadFromFile(str);
	sf::Vector3f mat[1000];
	for (int i = 0; i < 1000; i++) {
		mat[i].x = img.getPixel(999-i, 0).r;
		mat[i].y = img.getPixel(999 - i, 0).g;
		mat[i].z = img.getPixel(999 - i, 0).b;
	}

	shader.setUniformArray("colors", mat, 1000);
	grad.setUniformArray("colors", mat, 1000);
}
void Fractal::SetColor(sf::Vector3f* col) {
	
	color=col;
	
}

sf::Shader* Fractal::GetGradient() {
	grad.setUniform("step", *step);
	grad.setUniform("color", *color);
	return(&grad);
}