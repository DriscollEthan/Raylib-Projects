#include "Entity.h"
#include "DriscollMathUtils.h"
#include <iostream>

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed)
{
	Parent = nullptr;
	bIsAlive = true;
	LocalData = _localData;
	TextureIndex = _textureLocation;
	Origin = _origin;
	Hitbox = _hitbox;
	MovementVector = Driscoll::Vector2D();
	Speed = _speed;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{
	Parent = _other.Parent;
	LocalData = _other.LocalData;
	TextureIndex = _other.TextureIndex;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	Parent = _other.Parent;
	LocalData = _other.LocalData;
	TextureIndex = _other.TextureIndex;
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
	LocalMatrix = GetLocalMatrix();
	WorldMatrix = GetWorldMatrix();
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Entity::Update()
{
	Object::Update();

	Hitbox.Position = GetWorldPosition();

	LocalMatrix = GetLocalMatrix();
	WorldMatrix = GetWorldMatrix();
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Entity::Draw()
{
	if (bIsAlive)
	{
		Object::Draw();

		raylib::Texture& texture = GetTextureManagerRef()->GetTexture(TextureIndex);

		//Draw Texture:
		texture.Draw
		(
			raylib::Rectangle(0, 0, (float)texture.GetWidth(), (float)texture.GetHeight()),																																								// SourceRec
			raylib::Rectangle(GetWorldPosition().x, GetWorldPosition().y, (float)texture.GetWidth() * GetWorldScale().x, (float)texture.GetHeight() * GetWorldScale().y),	// DestRec
			raylib::Vector2((float)texture.GetWidth() * Origin.x * GetWorldScale().x, (float)texture.GetHeight() * Origin.y * GetWorldScale().y),											// Origin
			GetWorldRotation(),	// Rotation
			Driscoll::WHITE // Tint
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
HitboxData& Entity::GetHitbox()
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
		* Driscoll::Matrix3().MakeScale(LocalData.LocalScale);
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

Driscoll::Vector2D Entity::GetWorldPosition()
{
	//World Position
	return Driscoll::Vector2D(WorldMatrix.m7, WorldMatrix.m8);
}

float Entity::GetWorldRotation()
{
	//World Rotation
	return (Driscoll::AngleFrom2DDeg(WorldMatrix.m1, WorldMatrix.m2));
}

Driscoll::Vector2D Entity::GetWorldScale()
{
	//World Scale
	return Driscoll::Vector2D(WorldMatrix.axis[0].Magnitude(), WorldMatrix.axis[1].Magnitude());
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

//Rotate Entity
void Entity::SetLocalRotation(float _newRotation)
{
	LocalData.LocalRotation = _newRotation;
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

void Entity::SetParent(Entity* _newParent)
{
	Parent = _newParent;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY ONLY FUNCTIONS */
//Move Entity
void Entity::Move()
{
	LocalData.LocalPosition += MovementVector.SafeNormalised() * (Speed * GetFrameTime() * 100.0f);
	LocalData.LocalPosition = Driscoll::Vector2D::WrapVector2D(LocalData.LocalPosition, Driscoll::Vector2D(0, 0), GlobalVariables.ScreenSize);
}