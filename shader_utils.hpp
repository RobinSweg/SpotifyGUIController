#pragma once
#include <GLES2/gl2.h>
#include <string>
#include <fstream>
#include <sstream> 

std::string loadShaderSource(const std::string& filePath);
GLuint compileShader(GLenum type, const char* source);
GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource);
void checkShaderCompile(GLuint shader);
void checkProgramLink(GLuint program);
