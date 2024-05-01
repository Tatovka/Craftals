
uniform float iterations;
uniform float time;
uniform float size;
uniform float x;
uniform float y;
uniform float r;
uniform float i;

uniform vec3 color;
uniform float step;
bool isBail(vec2 z) {
float r = z.x * z.x -z.y * z.y;
float b = 2.0 * z.x * z.y;
return(r * r + b * b >= 2048.);
}

vec2 sqr(vec2 z) {
float r = z.x * z.x - z.y * z.y;
float b = 2.0 *z.x * z.y;
return vec2(r,b);
}

float graph(vec2 z){
	vec2 c=vec2(r,i);
	for (float i = 0.0; i < iterations; i+=1.0) {
		if (isBail(z)){
			//float col=colors[int(i * (float(len) /iterations))]
			return float(i)-log2(log2((z.x*z.x+z.y*z.y)));
			//vec3 col=vec3(1,1,1);
		}
		z = sqr(z)+c;
	}
	return 0;

}

void main()
{
float col = graph(vec2((gl_TexCoord[0].x)*3.0f*size+x, -((gl_TexCoord[0].y)*2.0*size )+y));
	vec3 c=0.5+0.5*cos(3. +col*step + color);
	gl_FragColor =vec4(c,1.);
}