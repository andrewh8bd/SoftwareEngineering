varying vec2 texcoord;
void main()
{
  texcoord = vec2(gl_MultiTexCoord0);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
