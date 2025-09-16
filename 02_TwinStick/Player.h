#pragma once
#include "Entity.h"
#include "GlobalVariableObject.h"

enum EInputType
{
	E_IsKeyDown,
	E_IsKeyPressed,
	E_IsKeyPressedRepeat,
	E_IsKeyReleased,
	E_IsKeyUp
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
	//DEFAULT CONSTRUCTOR
	Player();

	/*Variable Constructors*/
	//SET Position Only
	Player(Driscoll::Vector2D _position);

	//SET Texture BY IMAGE Only
	Player(raylib::Image _texture);

	//SET Radius Only
	Player(float _radius);

	//Set Position & Texture BY IMAGE Only
	Player(Driscoll::Vector2D _position, raylib::Image _texture);

	//Set Position & Radius
	Player(Driscoll::Vector2D _position, float _radius);

	//Set Texture & Radius
	Player(raylib::Image _texture, float _radius);

	//Set Position, Texture, & Radius
	Player(Driscoll::Vector2D _position, raylib::Image _texture, float _radius);

	//COPY CONSTRUCTOR
	Player(const Player& _other);

	//COPY ASSIGNMENT
	Player operator =(const Player& _other);

	//DESTRUCTOR
	~Player();

protected:
	/* VARIABLES */
	//TURRET POINTER

	Driscoll::Vector2D MovementVector;

	float Speed;

	class GlobalVariableObject GVO;

	//Input Arrays:
		//Movement: (WASD), (ARROW KEYS)
		FInput MovementInput[8];


public:
	/* FUNCTIONS */

	/* OBJECT VIRTUAL FUNCTION OVERRIDES */
	//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
	virtual void BeginPlay() override;

	//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
	virtual void Update() override;

	//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
	virtual void Draw() override;

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER INPUT FUNCTIONS */
	FInputReturnStruct Input(FInput _input);
	
	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER SPECIFIC GET FUNCTIONS */


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER SPECIFIC SET FUNCTIONS */

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* PLAYER ONLY FUNCTIONS */
	void Move();

	Driscoll::Vector2D Wrap(Driscoll::Vector2D _currentVector, Driscoll::Vector2D _min, Driscoll::Vector2D _max);
};

