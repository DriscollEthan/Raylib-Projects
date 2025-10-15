#pragma once
#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP
#include "DriscollMathUtils.h"

#include "TextureManager.h"
#include "GlobalVariableObject.h"

class Object
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	//Default Constructor
	Object();

	//Copy Constructor
	Object(const Object& _other);

	//Copy Assignment
	Object operator =(const Object& _other);

	//Desctructor
	virtual ~Object();

protected:
	/* VARIABLES */
	TextureManager* TextureManagerRef;

	size_t TextureIndex;

	GlobalVariables GlobalVariables;

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

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/
	
	/* OBJECT SPECIFIC Get FUNCTION */
	size_t GetTextureIndex();

	TextureManager* GetTextureManagerRef();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* OBJECT SPECIFC FUNCTIONS */
	
};

