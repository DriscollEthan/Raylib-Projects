#include "MenuObject.h"

MenuObject::MenuObject(Driscoll::Vector2D _worldPosition, 
  Driscoll::Vector2D _worldDimensions, 
  Driscoll::Color _normalColor, 
  Driscoll::Color _hoveredColor,
  Driscoll::Color _textNormalColor,
  Driscoll::Color _textHoveredColor,
  raylib::Text _text)
{
  WorldPosition = _worldPosition;
  WorldDimensions = _worldDimensions;
  NormalColor = _normalColor;
  HoveredColor = _hoveredColor;
  DrawColor = NormalColor;
  TextNormalColor = _textNormalColor;
  TextHoveredColor = _textHoveredColor;
  Text = _text;
  MouseColliding = false;
  AmountOfNewLinesInText = 1;

  for (int i = 0; i < Text.GetText().length(); ++i)
  {
    if (Text.GetText().at(i) == '\n')
    {
      ++AmountOfNewLinesInText;
    }
  }
  TextOrigin = { 0.5f, 0.5f };
}

MenuObject::MenuObject(const MenuObject& _other)
{
  WorldPosition = _other.WorldPosition;
  WorldDimensions = _other.WorldDimensions;
  NormalColor = _other.NormalColor;
  HoveredColor = _other.HoveredColor;
  DrawColor = NormalColor;
  TextNormalColor = _other.TextNormalColor;
  TextHoveredColor = _other.TextHoveredColor;
  Text = _other.Text;
  AmountOfNewLinesInText = _other.AmountOfNewLinesInText;
  MouseColliding = false;
  DrawScale = _other.DrawScale;
  DrawPosition = _other.DrawPosition;
}

MenuObject MenuObject::operator=(const MenuObject& _other)
{
  WorldPosition = _other.WorldPosition;
  WorldDimensions = _other.WorldDimensions;
  NormalColor = _other.NormalColor;
  HoveredColor = _other.HoveredColor;
  DrawColor = NormalColor;
  TextNormalColor = _other.TextNormalColor;
  TextHoveredColor = _other.TextHoveredColor;
  Text = _other.Text;
  AmountOfNewLinesInText = _other.AmountOfNewLinesInText;
  MouseColliding = false;
  return *this;
}

MenuObject::~MenuObject()
{
  
}

void MenuObject::BeginPlay()
{
  raylib::Texture& imageTexture = TextureManagerRef->GetTexture(TextureIndex);

  DrawScale = WorldDimensions / (Driscoll::Vector2D)imageTexture.GetSize();
  DrawPosition = WorldPosition - (DrawScale * 0.5f);
}

void MenuObject::Update()
{
  if (MouseColliding)
  {
    //Set Hover Color if Mouse Colliding;
    DrawColor = HoveredColor;
    Text.SetColor(TextHoveredColor);
  }
  else
  {
    DrawColor = NormalColor;
    Text.SetColor(TextNormalColor);
  }
}

void MenuObject::Draw()
{
  raylib::Texture& imageTexture = TextureManagerRef->GetTexture(TextureIndex);

  imageTexture.Draw(
    raylib::Rectangle(0, 0, (float)imageTexture.GetWidth(), (float)imageTexture.GetHeight()),																						                  // SourceRec
    raylib::Rectangle(DrawPosition.x, DrawPosition.y, (float)imageTexture.GetWidth() * DrawScale.x, (float)imageTexture.GetHeight() * DrawScale.y),       // DestRec
    raylib::Vector2((float)imageTexture.GetWidth() * 0.5f * DrawScale.x, (float)imageTexture.GetHeight() * 0.5f * DrawScale.y),									          // Origin
    0.0f,	// Rotation
    DrawColor // Tint
  );

  int textWidth = Text.Measure();
  Text.Draw(DrawPosition - Driscoll::Vector2D(textWidth * TextOrigin.x, (Text.GetFontSize() * AmountOfNewLinesInText) * TextOrigin.y));
}

void MenuObject::SetDimensions(Driscoll::Vector2D _newDimensionsInPixels)
{
  WorldDimensions = _newDimensionsInPixels;
}

void MenuObject::SetWorldPosition(Driscoll::Vector2D _newPosition)
{
  WorldPosition = _newPosition;
}

void MenuObject::SetTextFontSize(int _fontSize)
{
  Text.SetFontSize(_fontSize);
}

void MenuObject::SetText(std::string& _newText)
{
  Text.SetText(_newText);

  AmountOfNewLinesInText = 1;

  for (int i = 0; i < Text.GetText().length(); ++i)
  {
    if (Text.GetText().at(i) == '\n')
    {
      ++AmountOfNewLinesInText;
    }
  }
}

void MenuObject::SetNormalColor(Driscoll::Color _newNormalColor)
{
  NormalColor = _newNormalColor;
}

void MenuObject::SetHoveredColor(Driscoll::Color _newHoveredColor)
{
  HoveredColor = _newHoveredColor;
}

void MenuObject::SetTextNormalColor(Driscoll::Color _newTextNormalColor)
{
  TextNormalColor = _newTextNormalColor;
}

void MenuObject::SetTextHoveredColor(Driscoll::Color _newTextHoveredColor)
{
  TextHoveredColor = _newTextHoveredColor;
}

void MenuObject::SetTextOrigin(Driscoll::Vector2D _textOrigin)
{
  TextOrigin = _textOrigin;
}

bool MenuObject::CheckCollision(Driscoll::Vector2D _mousePosition, float _mouseHitboxRadius)
{
  Driscoll::Vector2D position = (WorldPosition - (WorldDimensions * 0.5f));
  position -= Driscoll::Vector2D(_mouseHitboxRadius, _mouseHitboxRadius);

  raylib::Rectangle hitbox = raylib::Rectangle(position, WorldDimensions);

  MouseColliding = CheckCollisionCircleRec(_mousePosition, _mouseHitboxRadius, hitbox);
  return MouseColliding;
}
