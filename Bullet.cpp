#include "Bullet.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Bullet::Bullet(const Vector2D& pos, const Vector2D& vel, unsigned int color, float radius)
	: Base(pos, vel, color)       // 親クラスを初期化（位置、速度、色）
	, radius_(radius)             // 弾の半径
	, isActive_(true)             // 生成時は有効（true）
	, gravity_(0.3f)              // 重力加速度（下向き = 負の値として使う）
{
	objType = OBJ_TYPE::BULLET;   // オブジェクトタイプを弾に設定
}

Bullet::~Bullet()
{
}

// ========================================
// TODO: ワークシート02 問題3
// 重力を考慮した放物線運動を実装
// ========================================
void Bullet::Update()
{
	// 無効な弾は更新しない
	if (!isActive_) return;

	// TODO: ステップ1: 重力を速度に加える
	// 
	// 重力ベクトルを作る
	//   Vector2D gravityVec = { x成分, y成分 };
	//   x成分: 横方向の重力はないので 0.0f
	//   y成分: 下向き = 負の値
	//          ワールド座標ではy軸が上向きなので、下向きは「-gravity_」
	//
	// 速度を更新する（速度 = 速度 + 重力）
	//   vel_ = Math2Dのベクトル加算関数(現在の速度, 重力ベクトル);
	//   現在の速度は vel_ メンバ変数（親クラスから継承）
	//   ヒント: 加算の関数名は「Add」
	
	// TODO: ステップ2: 速度を位置に加える
	//
	// 位置を更新する（位置 = 位置 + 速度）
	//   pos_ = Math2Dのベクトル加算関数(現在の位置, 更新された速度);
	//   現在の位置は pos_ メンバ変数（親クラスから継承）
	//
	// 重要: 必ず「速度を更新してから」位置を更新すること
	//       順序を間違えると物理計算がおかしくなる

	// 画面外判定（提供済み）
	// 画面外に出たら弾を無効にする
	if (pos_.x < 0 || pos_.x > WIN_WIDTH || 
	    pos_.y < 0 || pos_.y > WIN_HEIGHT)
	{
		isActive_ = false;
	}
}

void Bullet::Draw()
{
	// 無効な弾は描画しない
	if (!isActive_) return;

	// ワールド座標を画面座標に変換
	Vector2D screenPos = Math2D::World2Screen(pos_);
	
	// 弾を円として描画
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)radius_, Color_, TRUE);
}
