#pragma once
#include "Base.h"

class Target : public Base
{
public:
	Target(const Vector2D& pos, float radius, unsigned int color);
	~Target();

	void Update() override;
	void Draw() override;

	bool IsHit() const { return isHit_; }
	void SetHit() { isHit_ = true; }
	float GetRadius() const { return radius_; }

private:
	float radius_;
	bool isHit_;
};
