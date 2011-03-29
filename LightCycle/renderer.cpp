#include "renderer.h"
#include "soil/src/SOIL.h"
#include "ogl-math/glm/gtc/type_ptr.hpp"
#include <fstream>
#include <iostream>

Renderer::Renderer() : m_staticvertexbufferobject(0), m_dynamicvertexbufferobject(0),
                       m_staticindexbufferobject(0), m_dynamicindexbufferobject(0),
                       m_numstaticindices(0), m_numdynamicindices(0)
{
}

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

void Renderer::render()
{
  for(std::vector<GraphicsComponent*>::iterator it = m_graphicscomponents.begin();
                                                      it != m_graphicscomponents.end(); it++)
  {
    if((*it)->isVisible())
    {
      glLoadMatrixf(glm::value_ptr((*it)->getTransformation()));
      
      if(glIsProgram((*it)->getShaderProgram()))
      {
        int prog;
        glGetIntegerv(GL_CURRENT_PROGRAM, &prog);
        if(prog != (*it)->getShaderProgram())
          glUseProgram((*it)->getShaderProgram());
      }
      else
      {
        glUseProgram(0);
      }
          
      if((*it)->getGraphicsState() == DYNAMIC)
        glBindBuffer(GL_ARRAY_BUFFER, m_dynamicvertexbufferobject);
      else
        glBindBuffer(GL_ARRAY_BUFFER, m_staticvertexbufferobject);
      
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_FLOAT, 32, BUFFER_OFFSET(0));
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT, 32, BUFFER_OFFSET(12));
      for(int a = 0; a < (*it)->getTextures().size(); a++)
      {
        glActiveTexture(GL_TEXTURE0 + a);
        glBindTexture(GL_TEXTURE_2D, (*it)->getTextures()[a]);
        glUniform1i((*it)->getSamplerLocation(a), a);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 32, BUFFER_OFFSET(24));
      }
      
      if((*it)->getGraphicsState() == DYNAMIC)
      {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicindexbufferobject);
        glDrawRangeElements(GL_TRIANGLES, 0, m_numdynamicindices, (*it)->getVBOEnd() - (*it)->getVBOBegin() + 1, GL_UNSIGNED_INT, BUFFER_OFFSET(4*(*it)->getVBOBegin()));
      }
      else
      {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticindexbufferobject);
        glDrawRangeElements(GL_TRIANGLES, 0, m_numstaticindices, (*it)->getVBOEnd() - (*it)->getVBOBegin() + 1, GL_UNSIGNED_INT, BUFFER_OFFSET(4*(*it)->getVBOBegin()));
      }
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
    }
  }
}
