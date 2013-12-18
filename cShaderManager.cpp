#include "cShaderManager.h"
#include "cData.h"
#include <iostream>

using namespace std;

cShaderManager::cShaderManager(void){}

cShaderManager::~cShaderManager(void){}

GLuint cShaderManager::getFileLength(ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0, ios::end);
	unsigned long len = file.tellg();
	file.seekg(ios::beg);

	return (GLuint)len;
}

int cShaderManager::cargashader(char* filename, GLcharARB** ShaderSource, GLuint len)
{
	ifstream file;
	file.open(filename, ios::in); // opens as ASCII!
	if (!file.is_open()) return -1;

	len = getFileLength(file);

	if (len == 0) return -2;   // Error: Empty File 

	*ShaderSource = new GLcharARB[len + 1];
	//*ShaderSource = "void main (void){ gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);}";
	if (*ShaderSource == 0) return -3;   // can't reserve memory

	// len isn't always strlen cause some characters are stripped in ascii read...
	// it is important to 0-terminate the real length later, len is just max possible value... 
	(*ShaderSource)[len] = (GLcharARB)0;

	unsigned int i = 0;
	while (file.good())
	{
		(*ShaderSource)[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	(*ShaderSource)[i] = 0;  // 0-terminate it at the correct position

	file.close();

	return 0; // No Error
}

int cShaderManager::unloadshader(GLubyte** ShaderSource)
{
	if (*ShaderSource != 0)
		delete[] * ShaderSource;
	*ShaderSource = 0;

	return 0;
}

void cShaderManager::InitShaders(cData *Data)
{
	GLenum err = glewInit();

	glEnable(GL_TEXTURE_2D);

	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLcharARB * ShaderSource1;
	GLcharARB * ShaderSource2;
	const GLint len1 = 0;
	const GLint len2 = 0;

	cargashader("blinn.vert", &ShaderSource1, len1);

	glShaderSource(vertexShader, 1, (const GLcharARB **) &ShaderSource1, len1);
	glCompileShader(vertexShader);

	GLfloat compiled;

	glGetObjectParameterfvARB(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (compiled)
	{
		int j = 0; // yes it compiled!
	}
	
	cargashader("blinn.frag", &ShaderSource2, len2);

	glShaderSource(fragmentShader, 1, (const GLcharARB **)&ShaderSource2, len2);
	glCompileShader(fragmentShader);

	glGetObjectParameterfvARB(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (compiled)
	{
		int j = 0; // yes it compiled!
	}

	ProgramObject = glCreateProgram();

	glAttachShader(ProgramObject, vertexShader);
	glAttachShader(ProgramObject, fragmentShader);

	glLinkProgram(ProgramObject);

	GLint location = glGetUniformLocation(ProgramObject, "textureUnit");
	glUniform1i(location, 0);

	//glUseProgram(ProgramObject);

}

void cShaderManager::Begin(void)
{
	glUseProgram(ProgramObject);
}

void cShaderManager::End(void)
{
	glUseProgram(0);
}