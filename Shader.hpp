#ifndef SHADER_H
#define SHADER_H

/* --- Includes --- */

// Standard libraries
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Include glew to get all the required OpenGL headers
#include <GL/glew.h>

/* === Shader class === */

class Shader
{
public:
  	/* --- Variables --- */

	// Program ID
	GLuint program;

	/* --- Methods --- */

	// Constructor
	Shader (const GLchar*, const GLchar*);

  	// Use shader
  	void use();
};

#endif /* end of include guard: SHADER_H */
