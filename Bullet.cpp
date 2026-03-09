#include "Bullet.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Bullet::Bullet(const Vector2D& pos, const Vector2D& vel, unsigned int color, float radius)
	: Base(pos, vel, color)
	, radius_(radius)
	, isActive_(true)
	, gravity_(0.3f)
{
	objType = OBJ_TYPE::BULLET;
}

Bullet::~Bullet()
{
}

// ========================================
// TODO: ワークシート02 問題3
// 放物線運動を実装する
// ========================================
void Bullet::Update()
{
	if (!isActive_) return;

	// TODO: ステップ1: 重力を速度に加える
	// 重力ベクトルを作る
	//   Vector2D gravityVec = { x成分, y成分 };
	//   x成分: 横方向の重力はないので 0.0f
	//   y成分: 下向きなので -gravity_（負の値）
	//
	// 速度を更新する
	//   vel_ = Math2Dのベクトル加算関数(現在の速度, 重力ベクトル);
	
	// TODO: ステップ2: 速度を位置に加える
	// 位置を更新する
	//   pos_ = Math2Dのベクトル加算関数(現在の位置, 更新された速度);

	// 画面外判定（提供済み）
	if (pos_.x < 0 || pos_.x > WIN_WIDTH || 
	    pos_.y < 0 || pos_.y > WIN_HEIGHT)
	{
		isActive_ = false;
	}
}

void Bullet::Draw()
{
	if (!isActive_) return;

	Vector2D screenPos = Math2D::World2Screen(pos_);
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)radius_, Color_, TRUE);
}
