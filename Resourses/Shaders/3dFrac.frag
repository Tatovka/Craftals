#define fragCoord gl_TexCoord[0]
#define fragColor gl_FragColor
#define len 1000
float n=8.;
uniform float time;
uniform float iterations;
uniform float deep;
uniform vec3 colors[len];
bool sqr(vec3 g1) {
float r=(g1.x*g1.x+g1.y*g1.y+g1.z*g1.z);
return(r>4.);
}
vec3 sqrf(vec3 g1,vec3 g2) {
float r=(g1.x*g1.x+g1.y*g1.y+g1.z*g1.z);
float O=atan(g1.y/g1.x);
r=pow(r,n/2.);
float o=atan(sqrt(g1.x*g1.x+g1.y*g1.y)/g1.z);
return(r*vec3(cos(n*O)*cos(n*o),cos(n*o)*sin(n*O),-sin(n*o))+g2);
}

bool graph(vec3 z){
vec3 z1;
z1=z;
//z1 = vec3(0.,-0.8,0.);
for (float its = 0.0; its <iterations; its+=1.0) {
if (sqr(z1))
return false;
z1 = sqrf(z1,z);
}
return true;
}

void main()
{
bool b=true;
for (float z=1.;z<3.;z+=deep)
{
float t=0.7;
float x=(fragCoord.x *3.0-2.0)/t;
float y=((fragCoord.y *2.0)-1.0)/t;
//float time=0;
float x1=(x*cos(time)+(z-2.)*sin(time));
float y1=y;
float z1=-x*sin(time)+(z-2.)*cos(time);

float tmp=y1;
y1=y1*cos(time)+z1*sin(time) ;
z1=-tmp*sin(time)+z1*cos(time) ;


if (graph(vec3(x1,y1,z1))){
fragColor=vec4(colors[int(z * (float(len) / 3.))]/256.,1);
b=false;
break;
}
}
if (b)
fragColor=vec4(0,0,0,1);

}