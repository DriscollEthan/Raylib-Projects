#pragma once

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

public:
	/* VIRTUAL FUNCTIONS */
	//Called Before the Start of the Main Game Loop, But after being Constructed. MUST be USER CALLED!
	virtual void BeginPlay();

	//Called Every Tick in the Update Section.
	virtual void Update();

	//Called Every Tick on the Draw Section.
	virtual void Draw();
};

