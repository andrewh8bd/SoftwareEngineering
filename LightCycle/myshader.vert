varying vec2 texcoord;
varying vec2 texcoord2;
void main()
{
  texcoord = vec2(gl_MultiTexCoord0);
  texcoord2 = vec2(gl_MultiTexCoord1);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
