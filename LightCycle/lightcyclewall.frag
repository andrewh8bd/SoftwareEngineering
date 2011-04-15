uniform vec4 wallcolor;
varying float multiplier;

void main()
{
	gl_FragColor = wallcolor * multiplier;
}
