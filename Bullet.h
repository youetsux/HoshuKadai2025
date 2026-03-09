#pragma once
#include "Base.h"

class Bullet : public Base
{
public:
	Bullet(const Vector2D& pos, const Vector2D& vel, unsigned int color, float radius);
	~Bullet();

	void Update() override;
	void Draw() override;

	bool IsActive() const { return isActive_; }
	void SetInactive() { isActive_ = false; }
	float GetRadius() const { return radius_; }

private:
	float radius_;
	bool isActive_;
	float gravity_;
};
