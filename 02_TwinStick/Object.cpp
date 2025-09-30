#include "Object.h"

Object::Object()
{
	TextureManagerRef = nullptr;
	TextureIndex = 0;
	GlobalVariables = {};
}

Object::Object(const Object& _other)
{
	TextureManagerRef = _other.TextureManagerRef;
	TextureIndex = _other.TextureIndex;
	GlobalVariables = {};
}

Object Object::operator=(const Object& _other)
{
	TextureManagerRef = _other.TextureManagerRef;
	TextureIndex = _other.TextureIndex;
	GlobalVariables = {};
	return *this;
}

Object::~Object()
{

}

void Object::BeginPlay()
{

}

void Object::Update()
{

}

void Object::Draw()
{

}

void Object::SetTextureManagerRef(TextureManager* _newRef)
{
	TextureManagerRef = _newRef;
}

void Object::SetTextureIndex(size_t _newIndex)
{
	TextureIndex = _newIndex;
}

TextureManager* Object::GetTextureManagerRef()
{
	if (!TextureManagerRef)
	{
		std::cout << "[1;31mWARNING: NO TEXTURE MANAGER REF SET IN ENTITY: RETURN NULLPTR \033[0m" << std::endl;
	}
	return TextureManagerRef;
}
