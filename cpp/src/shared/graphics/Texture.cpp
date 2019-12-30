#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GLuint createTexture(const std::string& fileName)
{
	int width, height, nrChannels;
	unsigned char* imgdata = stbi_load(fileName.data(), &width, &height, &nrChannels, 0);

	if (!imgdata){
		throw std::exception( ("Failed to load image: "+ fileName ).data());
	}

	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imgdata);
	return textureId;
}
