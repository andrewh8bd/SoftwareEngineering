uniform sampler2D my_texture;
uniform sampler2D my_texture2;
varying vec2 texcoord;
varying vec2 texcoord2;

void main()
{
	gl_FragColor = (texture2D(my_texture2, texcoord) + texture2D(my_texture, texcoord))/2.0;
}
