#include "TextureManager.h"

TextureManager::TextureManager(size_t _amountOfTextures)
{
  TEXTURE_COUNT = _amountOfTextures;
  TextureArray = new raylib::Texture[TEXTURE_COUNT];
}

TextureManager::~TextureManager()
{
  delete[] TextureArray;
}

void TextureManager::SetTexture(raylib::Image _image, size_t _index)
{
  //Create more memeory if out of bounds.
  if (_index >= TEXTURE_COUNT)
  {
    //Create a tempArray that has access to the current memeory slot.
    raylib::Texture* tempArray = TextureArray;
    
    //Create a new TextureArray that has the bounds for the new Size.
    TextureArray = new raylib::Texture[_index + 1];

    //Set the Textures to the Images from the old Textures for the slots before the newly created slot.
    for (size_t i = 0; i < TEXTURE_COUNT; ++i)
    {
      if (tempArray->IsValid())
      {
        TextureArray[i].Load(tempArray[i].GetData());
      }
    }
    //Delete the old array
    delete[] tempArray;

    //Reset the TEXTURE_COUNT to the new count.
    TEXTURE_COUNT = _index + 1;
  }

  //Set the image in the new slot.
  TextureArray[_index].Load(_image);
}

raylib::Texture& TextureManager::GetTexture(size_t _index)
{
  //Return the Texture as an Image.
  return TextureArray[_index];
}
