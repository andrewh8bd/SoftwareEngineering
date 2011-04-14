uniform sampler2D lctexture;
uniform vec4 lccolor;
varying vec2 texcoord;

void main()
{
  vec4 tex = texture2D(lctexture, texcoord);
  if(tex.r > 0.95 && tex.g > 0.95 && tex.b > 0.95)
  {
    tex = lccolor;
  }
  
	gl_FragColor = tex;
}
