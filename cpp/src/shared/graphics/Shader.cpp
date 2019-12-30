#include "Shader.h"

GLuint createShaderProgram(const ShaderList& vertShaders, const ShaderList& fragShaders)
{
	//Generate program
	GLuint programId = glCreateProgram();

	for(auto iter = vertShaders.begin(); iter != vertShaders.end(); iter++){
		createShader(programId, GL_VERTEX_SHADER, iter->c_str() );
	}

	for(auto iter = fragShaders.begin(); iter != fragShaders.end(); iter++){
		createShader(programId, GL_FRAGMENT_SHADER, iter->c_str() );
	}
	glLinkProgram(programId);

	// Check the program
	GLint result = GL_FALSE;
	int infoLogLength;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		char* infoLog = new char[ infoLogLength ];
		glGetProgramInfoLog(programId, infoLogLength, NULL, infoLog);
		SDL_Log( "GL Program status: %d, log: %s\n", result, infoLog );
		delete[] infoLog;
	}

	return programId;
}

void createShader(GLuint programId, GLenum shaderType, const char* shaderSource){

	GLuint shaderId = glCreateShader(shaderType);

	glShaderSource( shaderId, 1, &shaderSource, NULL );

	//Compile vertex source
	glCompileShader( shaderId );

	//Attach vertex shader to program
	glAttachShader( programId, shaderId );

	GLint compiled = GL_FALSE;
	glGetShaderiv( shaderId, GL_COMPILE_STATUS, &compiled );
	if( compiled != GL_TRUE )
	{

		int infoLogLength = 0;
		int maxLength = 0;

		//Get info string length
		glGetShaderiv( shaderId, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate stringq
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetShaderInfoLog( shaderId, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 ) {
			SDL_Log( "Unable to compile shader: %s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}

}
