#pragma once
#include "Entity.h"

enum EInputType
{
	E_IsKeyDown,
	E_IsKeyPressed,
	E_IsKeyPressedRepeat,
	E_IsKeyReleased,
	E_IsKeyUp,
	E_IsMouseButtonPressed,
	E_IsMouseButtonDown,
	E_IsMouseButtonReleased,
	E_IsMouseButtonUp
};

struct FInputReturnStruct
{
	bool bIsInput = false;
	int Index = -1;
};

//To be Defined in BeginPlay, After creating the Array for each Input Type.
struct FInput
{
	FInput() {}

	FInput(EInputType _inputType, int _key, int _inputReturnIndex)
	{
		InputType = _inputType;
		Key = _key;
		InputIndex = _inputReturnIndex;
	}

	//Raylib Input Type, Default: "E_IsKeyDown"
	EInputType InputType = E_IsKeyDown;
	//Key To Check, Use Raylib MACROS for Key int, Default: 0 / NULL
	int Key = 0;
	//Index for Input Return, Default: -1
	int InputIndex = -1;
};

class Player : public Entity
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	/**
		* DEFAULT CONSTRUCTOR:
		* Parameters:
		* LocalData as a Driscoll::LocalData	| Default: Pos = 0,0; Rot = 0; Scale = 1,1;
		* Texture as an Image									| Default: Default Constructor
		* Hitbox as a HitboxData							| Default: Position = 0, Radius = 0;
		* Speed as a float										| Default: 1.0
		*/
	Player (LocalData2D _localData = {}, size_t _texturePosition = 0, Driscoll::Vector2D _origin = { 0,0 }, HitboxData _hitbox = {}, float _speed = 1.0f);

	Player(const Player& _other);

	Player operator=(const Player& _other);

	//DESTRUCTOR
	~Player();

protected:
	/* VARIABLES */

	//Input Arrays:

public:
	/* FUNCTIONS */

	/* OBJECT VIRTUAL FUNCTION OVERRIDES */
	//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
	virtual void BeginPlay() override;

	//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
	virtual void Update() override;

	//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
	virtual void Draw() override;

	//Collided: Called when Collision is detected.
	virtual void GotHit() override;

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER INPUT FUNCTIONS */
	FInputReturnStruct Input(FInput _input);
	
	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER SPECIFIC GET FUNCTIONS */


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER SPECIFIC SET FUNCTIONS */

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER ONLY FUNCTIONS */
};

