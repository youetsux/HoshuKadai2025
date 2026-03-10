#include "Cannon.h"
#include "Math2D.h"
#include "Input.h"
#include "globals.h"
#include <DxLib.h>

Cannon::Cannon(const Vector2D& pos, unsigned int color)
	: Base(pos, { 0.0f, 0.0f }, color)        // 親クラスを初期化（速度は0）
	, angle_(Math2D::PI / 4.0f)               // 初期角度45°（π/4 ラジアン）
	, angleSpeed_(0.02f)                      // 角度変化の速さ
	, barrelLength_(50.0f)                    // 砲身の長さ
	, bulletSpeed_(15.0f)                     // 弾の初速度（初期値）
	, bulletSpeedMin_(10.0f)                  // 弾の初速度の最小値
	, bulletSpeedMax_(25.0f)                  // 弾の初速度の最大値
	, bulletSpeedStep_(0.2f)                  // 速度変化の刻み幅
{
	objType = OBJ_TYPE::CANNON;               // オブジェクトタイプを砲台に設定
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
		// 角度の上限は90°（π/2 ラジアン）
		if (angle_ > Math2D::PI / 2.0f)
		{
			angle_ = Math2D::PI / 2.0f;
		}
	}
	
	// 右キー: 角度を下げる（右回転）
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		angle_ -= angleSpeed_;
		// 角度の下限は0°（0 ラジアン）
		if (angle_ < 0.0f)
		{
			angle_ = 0.0f;
		}
	}

	// 上キー: 初速度を上げる
	if (Input::IsKeepKeyDown(KEY_INPUT_UP))
	{
		bulletSpeed_ += bulletSpeedStep_;
		// 速度の上限チェック
		if (bulletSpeed_ > bulletSpeedMax_)
		{
			bulletSpeed_ = bulletSpeedMax_;
		}
	}

	// 下キー: 初速度を下げる
	if (Input::IsKeepKeyDown(KEY_INPUT_DOWN))
	{
		bulletSpeed_ -= bulletSpeedStep_;
		// 速度の下限チェック
		if (bulletSpeed_ < bulletSpeedMin_)
		{
			bulletSpeed_ = bulletSpeedMin_;
		}
	}
}

void Cannon::Draw()
{
	// ワールド座標を画面座標に変換
	Vector2D screenPos = Math2D::World2Screen(pos_);
	
	// 砲台本体（円）を描画
	DrawCircle((int)screenPos.x, (int)screenPos.y, 20, Color_, TRUE);
	
	// 砲身（線）を描画
	Vector2D tip = GetTipPosition();                    // 砲身の先端位置を取得
	Vector2D screenTip = Math2D::World2Screen(tip);     // 画面座標に変換
	
	// 砲台の中心から先端まで線を引く
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
	//         関数名は「FromAngle」（角度から作る、という意味）
	
	return Vector2D{ 0.0f, 0.0f };  // 仮の値（プレースホルダー）
}

// ========================================
// TODO: ワークシート01 問題4
// 砲身の先端位置を計算
// ========================================
Vector2D Cannon::GetTipPosition() const
{
	// TODO: ここに実装を書く
	// 計算手順:
	// ステップ1: 方向ベクトルを取得
	//   Vector2D dir = 方向を取得する関数();
	//
	// ステップ2: 方向ベクトル × 砲身の長さ = オフセット
	//   Vector2D offset = Math2Dのスカラー倍関数(方向ベクトル, 砲身の長さ);
	//   砲身の長さは barrelLength_ メンバ変数
	//   ヒント: スカラー倍の関数名は「Mul」（Multiply: 掛け算）
	//
	// ステップ3: 中心位置 + オフセット = 先端位置
	//   return Math2Dのベクトル加算関数(中心位置, オフセット);
	//   中心位置は pos_ メンバ変数（親クラスから継承）
	//   ヒント: 加算の関数名は「Add」（Addition: 足し算）
	
	return pos_;  // 仮の値（中心位置を返しているが、プレースホルダー）
}
