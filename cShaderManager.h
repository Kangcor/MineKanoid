#pragma once
#include "Globals.h"
#include "cData.h"
#include <fstream>
using namespace std;

class cShaderManager
{
public:
	cShaderManager(void);
	virtual ~cShaderManager(void);

	void InitShaders(cData *Data);
	void Begin(void);
	void End(void);
	int cargashader(char* filename, GLchar** ShaderSource, GLuint len);
	int unloadshader(GLubyte** ShaderSource);
	GLuint getFileLength(ifstream& file);

private:
	
	
	GLuint ProgramObject;
};