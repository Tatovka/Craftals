
uniform vec3 color;
uniform float step;
void main( )
{
float col =gl_TexCoord[0].x*5.;

	vec3 c=0.5+0.5*cos(3. +col + color);
	gl_FragColor =vec4(c,1.);
	

}