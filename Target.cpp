#include "Target.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Target::Target(const Vector2D& pos, float radius, unsigned int color)
	: Base(pos, { 0.0f, 0.0f }, color)
	, radius_(radius)
	, isHit_(false)
{
	objType = OBJ_TYPE::TARGET;
}

Target::~Target()
{
}

void Target::Update()
{
}

void Target::Draw()
{
	Vector2D screenPos = Math2D::World2Screen(pos_);

	unsigned int drawColor = isHit_ ? GetColor(100, 100, 100) : Color_;
	
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)radius_, drawColor, FALSE);
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)(radius_ * 0.6f), drawColor, FALSE);
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)(radius_ * 0.3f), drawColor, FALSE);
}
