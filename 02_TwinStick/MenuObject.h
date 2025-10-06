#pragma once
#include "Object.h"

#include <string.h>
#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP
#include "DriscollMathUtils.h"

#include "TextureManager.h"
#include "GlobalVariableObject.h"

class MenuObject : public Object
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	//Default Constructor
	MenuObject();

	//Copy Constructor
	MenuObject(const MenuObject& _other);

	//Copy Assignment
	MenuObject operator =(const MenuObject& _other);

	//Desctructor
	virtual ~MenuObject();

protected:
	/* VARIABLES */
	Driscoll::Vector2D WorldDimensions;

	Driscoll::Vector2D WorldPosition;

	bool MouseColliding;

	Driscoll::Color DrawColor;

	raylib::Text Text;

public:
	/* VIRTUAL FUNCTIONS */
	//Called Before the Start of the Main Game Loop, But after being Constructed. MUST be USER CALLED!
	virtual void BeginPlay();

	//Called Every Tick in the Update Section.
	virtual void Update();

	//Called Every Tick on the Draw Section.
	virtual void Draw();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* OBJECT SPECIFIC SET FUNCTION */
	void SetTextureManagerRef(TextureManager* _newRef);

	void SetTextureIndex(size_t _newIndex);

	void SetDimensions(Driscoll::Vector2D _newDimensionsInPixels);

	void SetWorldPosition(Driscoll::Vector2D _newPosition);

	void SetTextColor(Driscoll::Color _textColor);

	void SetTextFontSize(int _fontSize);

	void SetText(std::string& _newText);

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* OBJECT SPECIFC FUNCTIONS */
	TextureManager* GetTextureManagerRef();

	bool CheckCollision(Driscoll::Vector2D _mousePosition, float _mouseHitboxRadius);
};

