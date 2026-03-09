#include "Cannon.h"
#include "Math2D.h"
#include "Input.h"
#include "globals.h"
#include <DxLib.h>

Cannon::Cannon(const Vector2D& pos, unsigned int color)
	: Base(pos, { 0.0f, 0.0f }, color)
	, angle_(Math2D::PI / 4.0f)
	, angleSpeed_(0.02f)
	, barrelLength_(50.0f)
	, bulletSpeed_(15.0f)
	, bulletSpeedMin_(10.0f)
	, bulletSpeedMax_(25.0f)
	, bulletSpeedStep_(0.2f)
{
	objType = OBJ_TYPE::CANNON;
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	// 左キー: 角度を上げる（左回転）
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		angle_ += angleSpeed_;
		if (angle_ > Math2D::PI / 2.0f)
		{
			angle_ = Math2D::PI / 2.0f;
		}
	}
	
	// 右キー: 角度を下げる（右回転）
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		angle_ -= angleSpeed_;
		if (angle_ < 0.0f)
		{
			angle_ = 0.0f;
		}
	}

	// 上キー: 初速度を上げる
	if (Input::IsKeepKeyDown(KEY_INPUT_UP))
	{
		bulletSpeed_ += bulletSpeedStep_;
		if (bulletSpeed_ > bulletSpeedMax_)
		{
			bulletSpeed_ = bulletSpeedMax_;
		}
	}

	// 下キー: 初速度を下げる
	if (Input::IsKeepKeyDown(KEY_INPUT_DOWN))
	{
		bulletSpeed_ -= bulletSpeedStep_;
		if (bulletSpeed_ < bulletSpeedMin_)
		{
			bulletSpeed_ = bulletSpeedMin_;
		}
	}
}

void Cannon::Draw()
{
	Vector2D screenPos = Math2D::World2Screen(pos_);
	
	// 砲台本体（円）
	DrawCircle((int)screenPos.x, (int)screenPos.y, 20, Color_, TRUE);
	
	// 砲身（線）
	Vector2D tip = GetTipPosition();
	Vector2D screenTip = Math2D::World2Screen(tip);
	
	DrawLine((int)screenPos.x, (int)screenPos.y, 
	         (int)screenTip.x, (int)screenTip.y, 
	         GetColor(255, 255, 0), 5);
}

// ========================================
// TODO: ワークシート01 問題3
// 角度から方向ベクトルを作る
// ========================================
Vector2D Cannon::GetDirection() const
{
	// TODO: ここに実装を書く
	// Math2D には角度から方向ベクトルを作る関数がある
	//   return Math2D::角度変換関数(角度を表すメンバ変数);
	// ヒント: 単位ベクトル (cos θ, sin θ) を返す関数を使う
	
	return Vector2D{ 0.0f, 0.0f };  // 仮の値（要実装）
}

// ========================================
// TODO: ワークシート01 問題4
// 砲身の先端位置を計算
// ========================================
Vector2D Cannon::GetTipPosition() const
{
	// TODO: ここに実装を書く
	// ステップ1: 方向ベクトルを取得
	//   Vector2D dir = 方向を取得する関数();
	//
	// ステップ2: 方向ベクトル × 砲身の長さ = オフセット
	//   Vector2D offset = Math2Dのスカラー倍関数(方向ベクトル, 砲身の長さ);
	//   砲身の長さは barrelLength_ メンバ変数
	//
	// ステップ3: 中心位置 + オフセット = 先端位置
	//   return Math2Dのベクトル加算関数(中心位置, オフセット);
	//   中心位置は pos_ メンバ変数
	
	return pos_;  // 仮の値（中心位置を返している、要実装）
}
