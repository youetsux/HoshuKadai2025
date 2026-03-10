#pragma once
#include "Base.h"

// ========================================
// TODO: ワークシート02 問題1
// Bulletクラスの定義
// ========================================
// ヒント:
// ①親クラスは Cannon と同じクラスを継承する
// ②有効・無効を管理するフラグ変数は英語で "is active"

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
