uniform sampler2D lctexture;
varying vec2 texcoord;

void main()
{
  vec4 tex = texture2D(lctexture, texcoord);
  
	gl_FragColor = tex;
}
