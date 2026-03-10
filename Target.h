#pragma once
#include "Base.h"

// ========================================
// TODO: ワークシート03 問題1
// Targetクラスの定義
// ========================================
// ヒント:
// ①親クラスは他のゲームオブジェクトと同じ
// ②当たったかどうかのフラグは英語で "is hit"
// ③半径を格納する変数は英語で "radius"

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
