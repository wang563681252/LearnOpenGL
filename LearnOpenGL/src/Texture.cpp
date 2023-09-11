#include "Texture.h"

#include "vendor/stb_image.h"

Texture::Texture(const std::string& path)
	: mFilePath(path), mLocalBuffer(nullptr), mWidth(0), mHeight(0), mBPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);
	GLCall(glGenTextures(1, &mRendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
}

Texture::~Texture()
{

}

void Texture::Bind(unsigned int slot) const
{

}

void Texture::Unbind() const
{

}