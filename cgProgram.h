#pragma once

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

#include <GL/glew.h>

#include <string>
using std::string;
#include <map>

#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

#include <stdexcept>

class cgProgramException : public std::runtime_error
{
public:
	cgProgramException(const string & msg) : std::runtime_error(msg) { }
};

namespace cgShader
{
	enum cgShaderType
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};
};

class cgProgram
{
public:
	cgProgram();
	~cgProgram();

public:
	void   CompileShader(const char *fileName) throw (cgProgramException);
	void   CompileShader(const char * fileName, cgShader::cgShaderType type) throw (cgProgramException);
	void   CompileShader(const string & source, cgShader::cgShaderType type, const char *fileName = NULL) throw (cgProgramException);

	void   Link() throw (cgProgramException);
	void   Validate() throw(cgProgramException);
	void   Use() throw (cgProgramException);
	void   Unuse();

	int    GetHandle();
	bool   IsLinked();

	void   BindAttribLocation(GLuint location, const char * name);
	void   BindFragDataLocation(GLuint location, const char * name);

	void   SetUniform(const char *name, float x, float y, float z);
	void   SetUniform(const char *name, const vec2 & v);
	void   SetUniform(const char *name, const vec3 & v);
	void   SetUniform(const char *name, const vec4 & v);
	void   SetUniform(const char *name, const mat4 & m);
	void   SetUniform(const char *name, const mat3 & m);
	void   SetUniform(const char *name, float val);
	void   SetUniform(const char *name, int val);
	void   SetUniform(const char *name, bool val);
	void   SetUniform(const char *name, GLuint val);

	void   PrintActiveUniforms();
	void   PrintActiveUniformBlocks();
	void   PrintActiveAttribs();

	const char * GetTypeString(GLenum type);

	void SetName(string name);
	string GetName();
private:
	int  m_iHandle;

	bool m_bLinked;
	std::map<string, int> m_vUniformLocations;

	GLint  GetUniformLocation(const char * name);
	bool FileExists(const string & fileName);
	string GetExtension(const char * fileName);

	// Make these private in order to make the object non-copyable
	cgProgram(const cgProgram & other) { }
	cgProgram & operator=(const cgProgram &other) { return *this; }

	string m_name;
};

