#include "MenuObject.h"

MenuObject::MenuObject()
{
  TextureManagerRef = nullptr;
  TextureIndex = 0;
  WorldDimensions = Driscoll::Vector2D();
  WorldPosition = Driscoll::Vector2D();
  DrawColor = Driscoll::BLACK;
  MouseColliding = false;
  Text = raylib::Text();
}

MenuObject::MenuObject(const MenuObject& _other)
{
  TextureManagerRef = _other.TextureManagerRef;
  TextureIndex = _other.TextureIndex;
  WorldDimensions = _other.WorldDimensions;
  WorldPosition = _other.WorldPosition;
  DrawColor = _other.DrawColor;
  MouseColliding = _other.MouseColliding;
  Text = _other.Text;
}

MenuObject MenuObject::operator=(const MenuObject& _other)
{
  TextureManagerRef = _other.TextureManagerRef;
  TextureIndex = _other.TextureIndex;
  WorldDimensions = _other.WorldDimensions;
  WorldPosition = _other.WorldPosition;
  DrawColor = _other.DrawColor;
  MouseColliding = _other.MouseColliding;
  Text = _other.Text;
  return *this;
}

MenuObject::~MenuObject()
{
  
}

void MenuObject::BeginPlay()
{
  Text.SetSpacing(5.f);
}

void MenuObject::Update()
{
  if (MouseColliding)
  {
    //Set Hover Color if Mouse Colliding;
    DrawColor = Driscoll::GREY;
  }
  else
  {
    DrawColor = Driscoll::BLACK;
  }
}

void MenuObject::Draw()
{
  raylib::Texture& imageTexture = TextureManagerRef->GetTexture(TextureIndex);

  Driscoll::Vector2D scale = WorldDimensions / (Driscoll::Vector2D)imageTexture.GetSize();
  Driscoll::Vector2D position = WorldPosition - (scale * 0.5f);

  imageTexture.Draw(
    raylib::Rectangle(0, 0, (float)imageTexture.GetWidth(), (float)imageTexture.GetHeight()),																						    // SourceRec
    raylib::Rectangle(position.x, position.y, (float)imageTexture.GetWidth() * scale.x, (float)imageTexture.GetHeight() * scale.y),	        // DestRec
    raylib::Vector2((float)imageTexture.GetWidth() * 0.5f * scale.x, (float)imageTexture.GetHeight() * 0.5f * scale.y),										  // Origin
    0.0f,	// Rotation
    DrawColor // Tint
  );

  int textWidth = Text.Measure();

  Text.Draw(position - Driscoll::Vector2D(textWidth / 2, Text.GetFontSize() / 2));
}

void MenuObject::SetTextureManagerRef(TextureManager* _newRef)
{
  TextureManagerRef = _newRef;
}

void MenuObject::SetTextureIndex(size_t _newIndex)
{
  TextureIndex = _newIndex;
}

void MenuObject::SetDimensions(Driscoll::Vector2D _newDimensionsInPixels)
{
  WorldDimensions = _newDimensionsInPixels;
}

void MenuObject::SetWorldPosition(Driscoll::Vector2D _newPosition)
{
  WorldPosition = _newPosition;
}

void MenuObject::SetTextColor(Driscoll::Color _textColor)
{
  Text.SetColor(_textColor);
}

void MenuObject::SetTextFontSize(int _fontSize)
{
  Text.SetFontSize(_fontSize);
}

void MenuObject::SetText(std::string& _newText)
{
  Text.SetText(_newText);
}

TextureManager* MenuObject::GetTextureManagerRef()
{
  return TextureManagerRef;
}

bool MenuObject::CheckCollision(Driscoll::Vector2D _mousePosition, float _mouseHitboxRadius)
{
  Driscoll::Vector2D scale = WorldDimensions / (Driscoll::Vector2D)TextureManagerRef->GetTexture(TextureIndex).GetSize();
  Driscoll::Vector2D position = (WorldPosition - (WorldDimensions * 0.5f));
  position -= Driscoll::Vector2D(12.5f, 12.5f);

  raylib::Rectangle hitbox = raylib::Rectangle(position, WorldDimensions);

  MouseColliding = CheckCollisionCircleRec(_mousePosition, _mouseHitboxRadius, hitbox);
  return MouseColliding;
}
