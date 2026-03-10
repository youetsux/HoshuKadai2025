#pragma once
#include "Base.h"

// ========================================
// TODO: ワークシート01 問題1
// Cannonクラスの定義
// ========================================
// ヒント:
// ①すべてのゲームオブジェクトは共通の親クラスを継承している
// ②角度を格納する変数名は英語で "angle"

class Cannon : public Base
{
public:
	Cannon(const Vector2D& pos, unsigned int color);
	~Cannon();

	void Update() override;
	void Draw() override;

	float GetAngle() const { return angle_; }
	float GetSpeed() const { return bulletSpeed_; }
	Vector2D GetDirection() const;
	Vector2D GetTipPosition() const;

private:
	float angle_;
	float angleSpeed_;
	float barrelLength_;
	float bulletSpeed_;
	float bulletSpeedMin_;
	float bulletSpeedMax_;
	float bulletSpeedStep_;
};
