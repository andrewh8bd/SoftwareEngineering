#include "renderer.h"
#include "soil/src/SOIL.h"
#include "ogl-math/glm/gtc/type_ptr.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Renderer* Renderer::m_instance = NULL;
Renderer::Renderer() : m_staticvertexbufferobject(0), m_dynamicvertexbufferobject(0),
                       m_staticindexbufferobject(0), m_dynamicindexbufferobject(0),
                       m_numstaticindices(0), m_numdynamicindices(0)
{
}

Renderer::~Renderer()
{
  for(std::vector<GraphicsComponent*>::iterator it = m_graphicscomponents.begin(); it != m_graphicscomponents.end(); it++)
  {
    delete (*it);
  }
}

Renderer* Renderer::getInstance()
{
  if(m_instance == NULL)
    m_instance = new Renderer;
  return m_instance;
}

//Initializes the renderer, gives us 2 different patches (static and dynamic)
//both of 2Meg size in the form of OpenGL's Vertex Buffer Objects.
void Renderer::initialize()
{
  glGenBuffers(1, &m_staticvertexbufferobject);
  
  glBindBuffer(GL_ARRAY_BUFFER, m_staticvertexbufferobject);
  glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glGenBuffers(1, &m_dynamicvertexbufferobject);
  glBindBuffer(GL_ARRAY_BUFFER, m_dynamicvertexbufferobject);
  glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glGenBuffers(1, &m_staticindexbufferobject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticindexbufferobject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  glGenBuffers(1, &m_dynamicindexbufferobject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicindexbufferobject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//This allows us to create a graphic component from specified vertices, normals
//and texture coordinates. A pointer to the specific component is returned for
//control by the programmer, and the renderer keeps a pointer to it to do it's
//rendering. This is added to the static patch in that it's vertex information
//does not change over the course of rendering.
GraphicsComponent* Renderer::createStaticGraphicsComponent(const std::vector<glm::vec3>& vs, const std::vector<glm::vec3>& ns,
                                                         const std::vector<glm::vec2>& ts)
{
  std::vector<VertexInformation> vertices;
  std::vector<unsigned int> indices;
  GraphicsComponent* gc = new GraphicsComponent;
  gc->setVBOBegin(m_numstaticindices);
  gc->setGraphicsState(STATIC);
  
  std::vector<glm::vec3>::const_iterator vt;
  std::vector<glm::vec3>::const_iterator nt;
  std::vector<glm::vec2>::const_iterator tt;
  int currindex;
  for(vt = vs.begin(), nt = ns.begin(), tt = ts.begin(), currindex = m_numstaticindices;
      vt != vs.end(), nt != ns.end(), tt != ts.end();
      vt++, nt++, tt++, currindex++)
  {
    indices.push_back(currindex);
    VertexInformation temp;
    temp.px = (*vt)[0];
    temp.py = (*vt)[1];
    temp.pz = (*vt)[2];
    temp.nx = (*nt)[0];
    temp.ny = (*nt)[1];
    temp.nz = (*nt)[2];
    temp.tx = (*tt)[0];
    temp.ty = (*tt)[1];
    vertices.push_back(temp);
  }
    
  gc->setVBOEnd(gc->getVBOBegin() + vertices.size() - 1);
  
  
  glBindBuffer(GL_ARRAY_BUFFER, m_staticvertexbufferobject);
  glBufferSubData(GL_ARRAY_BUFFER, m_numstaticindices*32, vertices.size()*32, &vertices[0].px);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticindexbufferobject);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_numstaticindices*4, indices.size()*4, &indices[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  m_numstaticindices += vertices.size();
  m_graphicscomponents.push_back(gc);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return gc;
}

//This allows us to create a graphic component from specified vertices, normals
//and texture coordinates. A pointer to the specific component is returned for
//control by the programmer, and the renderer keeps a pointer to it to do it's
//rendering. This is added to the dynamic patch in that it's vertex information
//can change over the course of rendering.
GraphicsComponent* Renderer::createDynamicGraphicsComponent(const std::vector<glm::vec3>& vs, const std::vector<glm::vec3>& ns,
                                                            const std::vector<glm::vec2>& ts)
{
  std::vector<VertexInformation> vertices;
  std::vector<unsigned int> indices;
  GraphicsComponent* gc = new GraphicsComponent;
  gc->setVBOBegin(m_numdynamicindices);
  gc->setGraphicsState(DYNAMIC);
  std::vector<glm::vec3>::const_iterator vt;
  std::vector<glm::vec3>::const_iterator nt;
  std::vector<glm::vec2>::const_iterator tt;
  int currindex;
  for(vt = vs.begin(), nt = ns.begin(), tt = ts.begin(), currindex = m_numdynamicindices;
      vt != vs.end(), nt != ns.end(), tt != ts.end();
      vt++, nt++, tt++, currindex++)
  {
    indices.push_back(currindex);
    VertexInformation temp;
    temp.px = (*vt)[0];
    temp.py = (*vt)[1];
    temp.pz = (*vt)[2];
    temp.nx = (*nt)[0];
    temp.ny = (*nt)[1];
    temp.nz = (*nt)[2];
    temp.tx = (*tt)[0];
    temp.ty = (*tt)[1];
    vertices.push_back(temp);
  }
  
  gc->setVBOEnd(gc->getVBOBegin() + vertices.size() - 1);
  
  gc->setVertexInformation(vertices);
  gc->setVBOHandle(m_dynamicvertexbufferobject);
  
  glBindBuffer(GL_ARRAY_BUFFER, m_dynamicvertexbufferobject);
  glBufferSubData(GL_ARRAY_BUFFER, m_numdynamicindices*32, vertices.size()*32, &vertices[0]);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicindexbufferobject);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_numdynamicindices*4, vertices.size()*4, &indices[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  m_numdynamicindices += vertices.size();
  m_graphicscomponents.push_back(gc);
  return gc;
}

//This lets us load a shader to be applied to a graphics component to give a
//high level of precision and control over the way it looks in the end.
//Vname is the filename of the vertex shader and fname is the filename of the
//fragment shader. An opengl shader id is returned.

unsigned int Renderer::loadAndGetShader(const std::string vname, const std::string fname)
{
  unsigned int vertexshader;
  unsigned int fragmentshader;
  
  //VERTEX SHADER LOAD
	std::ifstream v(vname.c_str());
	char c;
	std::vector<std::string> lines;
	std::vector<int> sizes;
	std::string in;
	int size = 0;
	int maxsize = 0;
	int infologlength = 0;
	char infolog[1024];
	if(v.is_open() == false) throw "Vertex Shader file could not be opened!";
	while(!v.eof())
	{
		c = v.get();
		if(v.good())
		{
			if(c != '\n')
			{
				in+=c;
				size++;
			}
			else
			{
				if(size > maxsize) maxsize = size;
				sizes.push_back(size);
				size = 0;
				lines.push_back(in);
				in = "";
			}		
		}
	}
	v.close();
	
  vertexshader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
	const char* actuallines[lines.size()];
	for(int i = 0; i<lines.size(); i++)
	{
		actuallines[i] = lines[i].c_str();
	}
	glShaderSource(vertexshader, sizes.size(), (const char**)actuallines, &sizes[0]);
	glCompileShader(vertexshader);
		
	glGetInfoLogARB(vertexshader, 1024, &infologlength, infolog);
  std::cout<<"Vert"<<std::endl;
  std::cout<<infolog<<std::endl;
  
  //FRAGMENT SHADER LOAD
	std::ifstream f(fname.c_str());
	c = 0;
	lines.clear();
	sizes.clear();
	in = "";
	size = 0;
	maxsize = 0;
	infologlength = 0;
	if(f.is_open() == false) throw "Fragment Shader file could not be opened!";
	while(!f.eof())
	{
		c = f.get();
		if(f.good())
		{
			if(c != '\n')
			{
				in+=c;
				size++;
			}
			else
			{
				if(size > maxsize) maxsize = size;
				sizes.push_back(size);
				size = 0;
				lines.push_back(in);
				in = "";
			}		
		}
	}
	f.close();
	
  fragmentshader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
	const char* actuallines2[lines.size()];
	for(int i = 0; i<lines.size();i++)
	{
		actuallines2[i] = lines[i].c_str();
	}
	glShaderSource(fragmentshader, sizes.size(), (const char**)actuallines2, &sizes[0]);
	glCompileShader(fragmentshader);
		
	glGetInfoLogARB(fragmentshader, 1024, &infologlength, infolog);
  
  std::cout<<"Frag"<<std::endl;
  std::cout<<infolog<<std::endl;
  
  //SHADER PROGRAM CREATE
  infologlength = 0;
  unsigned int program = 0;
  
  program = glCreateProgramObjectARB();
  
  glAttachShader(program, vertexshader);
  glAttachShader(program, fragmentshader);
  
  
  glLinkProgram(program);
  
  glGetInfoLogARB(program, 1024, &infologlength, infolog);
  
  std::cout<<"Prog"<<std::endl;
  std::cout<<infolog<<std::endl;
  
  return program;
}

//This allows us to load a texture from file using SOIL. A opengl texture unit
//is returned.
unsigned int Renderer::loadAndGetTexture(const std::string filename)
{
  unsigned int tex = 0;
  tex = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
  if(tex == 0)
  {
    std::cout<<"SOIL loading error: "<<SOIL_last_result()<<std::endl;
  }
  return tex;
}

//This is called once every frame, and updates the graphics shown on the screen
void Renderer::render()
{
  //For every graphic component the renderer knows about
  for(std::vector<GraphicsComponent*>::iterator it = m_graphicscomponents.begin();
                                                      it != m_graphicscomponents.end(); it++)
  {
    //Check if it's visible
    if((*it)->isVisible())
    {
      //Save the matrix (which should be holding camera information currently)
      glPushMatrix();
      //Multiply the graphics component's transformation matrix by the 
      //current top matrix.
      glMultMatrixf(glm::value_ptr((*it)->getTransformation()));
      
      //Check to see if the shader program provided with the graphicscomponent
      //actually exists
      if(glIsProgram((*it)->getShaderProgram()))
      {
        int prog;
        glGetIntegerv(GL_CURRENT_PROGRAM, &prog);
        if(prog != (*it)->getShaderProgram())
          //If so, connect the program
          glUseProgram((*it)->getShaderProgram());
        for(std::map<unsigned int, glm::vec4>::iterator at = (*it)->getUniforms().begin();
                                                        at != (*it)->getUniforms().end(); at++)
        {
          glUniform4fv(at->first, 1, glm::value_ptr(at->second));
        }
      }
      else
      {
        //If not, don't use a shader
        glUseProgram(0);
      }
       
      //If it's a dynamic graphics component use the dynamic patch (vbo)       
      if((*it)->getGraphicsState() == DYNAMIC)
        glBindBuffer(GL_ARRAY_BUFFER, m_dynamicvertexbufferobject);
      //Otherwise use the static patch
      else
        glBindBuffer(GL_ARRAY_BUFFER, m_staticvertexbufferobject);
      
      //Start vertices
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, 32, BUFFER_OFFSET(0));
      //Start normals
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT, 32, BUFFER_OFFSET(12));
      
      //For each possible texture start the texture coordinates
      //and turn on the respective texture unit. Also send texture
      //information to the shader(if it exists).
      for(int a = 0; a < (*it)->getTextures().size(); a++)
      {
        glActiveTexture(GL_TEXTURE0 + a);
        glBindTexture(GL_TEXTURE_2D, (*it)->getTextures()[a]);
        if(glIsProgram((*it)->getShaderProgram()))
        {
          glUniform1i((*it)->getSamplerLocation(a), a);
        }
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 32, BUFFER_OFFSET(24));
      }
      
      //If it's on the dynamic patch start the dynamic index array
      //and draw this patch.
      if((*it)->getGraphicsState() == DYNAMIC)
      {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicindexbufferobject);
        glDrawRangeElements(GL_TRIANGLES, 0, m_numdynamicindices, (*it)->getVBOEnd() - (*it)->getVBOBegin() + 1, GL_UNSIGNED_INT, BUFFER_OFFSET(4*(*it)->getVBOBegin()));
      }
      //Else start the static index array and draw the patch.
      else
      {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticindexbufferobject);
        glDrawRangeElements(GL_TRIANGLES, 0, m_numstaticindices, (*it)->getVBOEnd() - (*it)->getVBOBegin() + 1, GL_UNSIGNED_INT, BUFFER_OFFSET(4*(*it)->getVBOBegin()));
      }
      
      //Turn everything off, and pop the matrix off.
      for(int i=(*it)->getTextures().size() - 1; i >= 0; i--)
      {
        glClientActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      }
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
      
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glPopMatrix();
    }
  }
}

void Renderer::dump()
{
  delete m_instance;
}


GraphicsComponent* Renderer::createStaticGraphicsComponentFromFile(const std::string s)
{
  std::ifstream infile(s.c_str());
  std::string buffer;
  std::string temp;
  std::string temp2;
  std::vector<glm::vec3> rawvs;
  std::vector<glm::vec3> rawns;
  std::vector<glm::vec2> rawts;
  std::vector<glm::vec3> vs;
  std::vector<glm::vec3> ns;
  std::vector<glm::vec2> ts;
  if(!infile.is_open())
  {
    std::cout<<"File could not be opened."<<std::endl;
    return NULL;
  }
  
  int i = 0;
  while(!infile.eof())
  {
    getline(infile, buffer);
    std::istringstream line(buffer);
    if(buffer.substr(0, 6) == "mtllib")
    {
        line >> temp >> temp2;
        //o.IsMaterial = true;
        //o.AddMaterial(Material(temp2));
    }
    if(buffer.substr(0, 2) == "vt")
    {
      double f1, f2;
      line >> temp >> f1 >> f2;
      rawts.push_back(glm::vec2(static_cast<float>(f1), static_cast<float>(f2)));
    }
    else if(buffer.substr(0, 2) == "vn")
    {
      double f1, f2, f3;
      line >> temp >> f1 >> f2 >> f3;
      rawns.push_back(glm::vec3(static_cast<float>(f1), static_cast<float>(f2),
                                static_cast<float>(f3)));
    }
    else if(buffer.substr(0, 1) == "v" && buffer.substr(0, 2) != "vn" && buffer.substr(0, 2) != "vt")
    {
      double f1, f2, f3;
      line >> temp >> f1 >> f2 >> f3;
      rawvs.push_back(glm::vec3(static_cast<float>(f1), static_cast<float>(f2),
                                static_cast<float>(f3)));
    }
    else if(buffer.substr(0, 1) == "f")
    {
      char buffer[100];
      std::string s1, s2, s3;
      int len1, len2, len3;
      int vertices[3];
      int normals[3];
      int texcoords[3];
      line >> temp >> s1 >> s2 >> s3;
      len1 = s1.find_first_of('/');
      
      vertices[0] = atoi((s1.substr(0, len1)).c_str());
      std::cout<<vertices[0]<<std::endl;
      len2 = s1.find_last_of('/');
      if(len2 > len1 + 1)
        texcoords[0] = atoi((s1.substr(len1 + 1, len2 - len1 - 1)).c_str());
      else
        texcoords[0] = -1;
      len3 = s1.size();
      normals[0] = atoi((s1.substr(len2 + 1, len3 - len2).c_str()));
      
      len1 = s2.find_first_of('/');
      
      vertices[1] = atoi((s2.substr(0, len1)).c_str());
      std::cout<<vertices[1]<<std::endl;
      
      len2 = s2.find_last_of('/');
      if(len2 > len1 + 1)
        texcoords[1] = atoi((s2.substr(len1 + 1, len2 - len1 - 1)).c_str());
      else
        texcoords[1] = -1;
        
      len3 = s2.size();
      
      normals[1] = atoi((s2.substr(len2 + 1, len3 - len2).c_str()));
      len1 = s3.find_first_of('/');
      vertices[2] = atoi((s3.substr(0, len1)).c_str());
      std::cout<<vertices[2]<<std::endl;
      
      len2 = s3.find_last_of('/');
      if(len2 > len1 + 1)
        texcoords[2] = atoi((s3.substr(len1 + 1, len2 - len1 - 1)).c_str());
      else
        texcoords[2] = -1;
      len3 = s3.size();
      normals[2] = atoi((s3.substr(len2 + 1, len3 - len2).c_str()));
      
      vs.push_back(rawvs[vertices[0]-1]);
      vs.push_back(rawvs[vertices[1]-1]);
      vs.push_back(rawvs[vertices[2]-1]);
      ns.push_back(rawns[normals[0]-1]);
      ns.push_back(rawns[normals[1]-1]);
      ns.push_back(rawns[normals[2]-1]);
      if(texcoords[0] > 0)
        ts.push_back(rawts[texcoords[0]-1]);
      else
        ts.push_back(glm::vec2(0.0, 0.0));
      if(texcoords[1] > 0)
        ts.push_back(rawts[texcoords[1]-1]);
      else
        ts.push_back(glm::vec2(0.0, 0.0));
      if(texcoords[2] > 0)
        ts.push_back(rawts[texcoords[2]-1]);
      else
        ts.push_back(glm::vec2(0.0, 0.0));
    }
    else if(buffer.substr(0, 1) == "s")
    {
    }
  }
  infile.close();
  
  for(std::vector<glm::vec3>::iterator it = vs.begin(); it!=vs.end(); it++)
  {
    std::cout<<(*it)[0]<<" "<<(*it)[1]<<" "<<(*it)[2]<<" "<<std::endl;
  }
  
  /*ts.clear();
  
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));
  
  ts.push_back(glm::vec2(0.0, 0.0));
  ts.push_back(glm::vec2(0.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 1.0));
  ts.push_back(glm::vec2(1.0, 0.0));
  ts.push_back(glm::vec2(0.0, 0.0));*/
  
  /*infile.clear();
  if(o.IsMaterial)
  {
      std::ifstream infile2(o.GetMaterial().GetFilename().c_str());
      Material tmpMat;
      if(!infile2.is_open())
      {
          MessageBox(NULL, ".mtl Failed to Open", "ERROR!", MB_ICONEXCLAMATION);
          return;
      }
      while(!infile2.eof())
      {
          getline(infile2, buffer);
          std::istringstream line(buffer);
          std::string temp;
          float f1, f2, f3;
          if(buffer.substr(0, 5) == "illum")
          {
              tmpMat.SpecularOn = true;
          }
          else if(buffer.substr(0, 2) == "Ka")
          {
              line >> temp >> f1 >> f2 >> f3;
              tmpMat.Ambient.x = f1;
              tmpMat.Ambient.y = f2;
              tmpMat.Ambient.z = f3;
          }
          else if(buffer.substr(0, 2) == "Kd")
          {
              line >> temp >> f1 >> f2 >> f3;
              tmpMat.Diffuse.x = f1;
              tmpMat.Diffuse.y = f2;
              tmpMat.Diffuse.z = f3;
          }
          else if(buffer.substr(0, 2) == "Ks")
          {
              line >> temp >> f1 >> f2 >> f3;
              tmpMat.Specular.x = f1;
              tmpMat.Specular.y = f2;
              tmpMat.Specular.z = f3;
          }
          else if(buffer.substr(0, 2) == "Ns")
          {
              line >> temp >> f1;
              tmpMat.Shininess = f1;
          }
          else if(buffer.substr(0, 2) == "Tr" || buffer.substr(0, 1) == "d")
          {
              line >> temp >> f1;
              tmpMat.Transparency = f1;
          }
          else if(buffer.substr(0, 6) == "map_Kd")
          {
          }
          else if(buffer.substr(0, 2) == "Tf")
          {
              line >> temp >> f1 >> f2 >> f3;
              tmpMat.TransmissionFilter.x = f1;
              tmpMat.TransmissionFilter.y = f2;
              tmpMat.TransmissionFilter.z = f3;
          }
      }
      o.AddMaterial(tmpMat);
      infile2.close();
      infile2.clear();
  }*/
  
  return createStaticGraphicsComponent(vs, ns, ts);
}
