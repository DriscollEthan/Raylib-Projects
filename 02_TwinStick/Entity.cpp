#include "Entity.h"
#include "DriscollMathUtils.h"
#include <iostream>

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed)
{
	LocalData = _localData;
	Origin = _origin;
	Hitbox = _other.Hitbox;
	MovementVector = Driscoll::Vector2D();
	Speed = _speed;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{
	LocalData = _other.LocalData;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	LocalData = _other.LocalData;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	return *this;
}

//Destructor
Entity::~Entity()
{

}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Entity::BeginPlay()
{
	Object::BeginPlay();
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Entity::Update()
{
	Object::Update();

	Hitbox.Position = { GetWorldMatrix().m7, GetWorldMatrix().m8 };
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Entity::Draw()
{
	if (bIsAlive)
	{
		Object::Draw();
		//Get World Data from World Matrix
			// World Matrix:
			Driscoll::Matrix3 WorldMatrix = GetWorldMatrix();
		//Get Position, Rotation, and Scale From World Matrix
			//World Position
			Driscoll::Vector2D WorldPosition = { WorldMatrix.m7, WorldMatrix.m8 };
			//World Rotation
			float WorldRotation = Driscoll::AngleFrom2DDeg(WorldMatrix.m1, WorldMatrix.m2);
			//World Scale
			Driscoll::Vector2D WorldScale = { WorldMatrix.axis[0].Magnitude(), WorldMatrix.axis[1].Magnitude() };


		GetTextureManagerRef()->GetTexture(TextureIndex).Draw(raylib::Rectangle(0, 0, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth(), (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetHeight()),						// SourceRec
			raylib::Rectangle(WorldPosition.x, WorldPosition.y, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth() * WorldScale.x, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetHeight() * WorldScale.y),	// DestRec
			Driscoll::Vector2D((float)GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth() * Origin.x * WorldScale.x, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetHeight() * Origin.y * WorldScale.y),		// Origin
			WorldRotation,	// Rotation
			Driscoll::Color::White() // Tint
		);
	}
}

void Entity::GotHit()
{
	std::cout << "thing \n";
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC GET FUNCTIONS */	

//Get Radius
HitboxData Entity::GetHitbox()
{
	return Hitbox;
}

bool Entity::CollisionCheck(HitboxData& _otherHitbox)
{
	return Hitbox.CheckCollision(_otherHitbox);
}

bool Entity::GetIsAlive()
{
	return bIsAlive;
}

Driscoll::Matrix3 Entity::GetLocalMatrix()
{
	return Driscoll::Matrix3().MakeTranslation(LocalData.LocalPosition)
		* Driscoll::Matrix3().MakeRotateZ(LocalData.LocalRotation)
		* Driscoll::Matrix3().MakeScale(LocalData.LocalPosition);
}

Driscoll::Matrix3 Entity::GetWorldMatrix()
{
	if (Parent == nullptr)
	{
		return GetLocalMatrix();
	}
	else
	{
		return Parent->GetWorldMatrix() * GetLocalMatrix();
	}
}


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC SET FUNCTIONS */


//Set Position
void Entity::SetLocalPosition(Driscoll::Vector2D _newPosition)
{
	LocalData.LocalPosition = _newPosition;
}

//Set Scale
void Entity::SetLocalScale(Driscoll::Vector2D _newScale)
{
	LocalData.LocalScale = _newScale;
}

//Set Radius
void Entity::SetHitboxRadius(float _newRadius)
{
	LocalData.LocalRotation = _newRadius;
}

void Entity::SetHitboxLocation(Driscoll::Vector2D _newPosition)
{
	Hitbox.Position = _newPosition;
}

void Entity::SetIsAlive(bool _isAlive)
{
	bIsAlive = _isAlive;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY ONLY FUNCTIONS */
//Move Entity
void Entity::Move()
{
	LocalData.LocalPosition += MovementVector.SafeNormalised() * (Speed * GetFrameTime() * 100.0f);
	LocalData.LocalPosition = Driscoll::Vector2D::WrapVector2D(LocalData.LocalPosition, Driscoll::Vector2D(0, 0), GlobalVariables.ScreenSize);
}

//Rotate Entity
void Entity::SetLocalRotation(float _newRotation)
{
	LocalData.LocalRotation = _newRotation;
}