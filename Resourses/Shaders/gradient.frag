
uniform float r1;
uniform float g1;
uniform float b1;

uniform float r2;
uniform float g2;
uniform float b2;

void main( )
{

vec3 color1=vec3(r1,g1,b1);
vec3 color2=vec3(r2,g2,b2);
vec3 color=color1+(color2-color1)*gl_TexCoord[0].x;
gl_FragColor=vec4(color,1.);

}