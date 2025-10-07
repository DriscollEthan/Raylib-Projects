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
	MenuObject
	(
		Driscoll::Vector2D _worldPosition = {},
		Driscoll::Vector2D _worldDimensions = {},
		Driscoll::Color _normalColor = Driscoll::BLACK,
		Driscoll::Color _hoveredColor = Driscoll::WHITE,
		Driscoll::Color _textNormalColor = Driscoll::WHITE,
		Driscoll::Color _textHoveredColor = Driscoll::BLACK,
		raylib::Text _text = raylib::Text()
		);

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

	Driscoll::Color NormalColor;

	Driscoll::Color HoveredColor;

	Driscoll::Color TextNormalColor;

	Driscoll::Color TextHoveredColor;

	raylib::Text Text;

	int AmountOfNewLinesInText;

	Driscoll::Vector2D TextOrigin;

	Driscoll::Vector2D DrawScale;

	Driscoll::Vector2D DrawPosition;

public:
	/* VIRTUAL FUNCTIONS */
	//Called Before the Start of the Main Game Loop, But after being Constructed. MUST be USER CALLED!
	virtual void BeginPlay();

	//Called Every Tick in the Update Section.
	virtual void Update();

	//Called Every Tick on the Draw Section.
	virtual void Draw();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* MENU OBJECT SPECIFIC SET FUNCTION */

	void SetDimensions(Driscoll::Vector2D _newDimensionsInPixels);

	void SetWorldPosition(Driscoll::Vector2D _newPosition);

	void SetTextFontSize(int _fontSize);

	void SetText(std::string& _newText);

	void SetNormalColor(Driscoll::Color _newNormalColor);

	void SetHoveredColor(Driscoll::Color _newHoveredColor);

	void SetTextNormalColor(Driscoll::Color _newTextNormalColor);

	void SetTextHoveredColor(Driscoll::Color _newTextHoveredColor);

	void SetTextOrigin(Driscoll::Vector2D _textOrigin);

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* OBJECT SPECIFC FUNCTIONS */

	bool CheckCollision(Driscoll::Vector2D _mousePosition, float _mouseHitboxRadius);
};

