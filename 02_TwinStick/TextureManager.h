#pragma once
#include "Object.h"
class TextureManager : public Object
{
public:
  TextureManager(size_t _amountOfTextures);

  ~TextureManager();

protected:
  //Array of all Textures to load into Memeory.
  raylib::Texture* TextureArray;

  //How many Textures Is This Class Storing.
  size_t TEXTURE_COUNT;

public:
  //Takes in an index and Image to set a specific Texture.
  void SetTexture(raylib::Image _image, size_t _index);

  //Outputs the reference to the Texture, so it can be printed to screen.
  raylib::Texture& GetTexture(size_t _index);
};

