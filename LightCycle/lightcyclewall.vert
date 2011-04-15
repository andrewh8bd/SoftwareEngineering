varying float multiplier;
void main()
{
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  
  multiplier = gl_Vertex.y * 2.0;

}
