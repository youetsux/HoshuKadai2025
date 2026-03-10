#pragma once
#include "Base.h"

// ========================================
// TODO: ワークシート03 問題1
// Targetクラスの定義
// ========================================
// ヒント:
// ①親クラスは他のゲームオブジェクトと同じ
//   Cannon.h や Bullet.h を見て確認しよう
// ②当たったかどうかのフラグは英語で "is hit"
//   bool型で、true=当たった、false=当たっていない を表す
// ③半径を格納する変数は英語で "radius"
//   float型で、円の半径を表す

class Target : public Base
{
public:
	// コンストラクタ: 的の位置、半径、色を設定
	Target(const Vector2D& pos, float radius, unsigned int color);
	~Target();

	// 毎フレーム呼ばれる更新処理
	// 的は動かないので、実装は空でOK
	void Update() override;
	
	// 毎フレーム呼ばれる描画処理（3重の円で的を表現）
	void Draw() override;

	// 的に当たったかどうかを取得
	bool IsHit() const { return isHit_; }
	
	// 的を「当たった」状態にする（当たり判定で呼ばれる）
	void SetHit() { isHit_ = true; }
	
	// 的の半径を取得（当たり判定で使用）
	// 弾との距離がこの値以下なら当たり
	float GetRadius() const { return radius_; }

private:
	// ========================================
	// メンバ変数（的の状態を管理）
	// ========================================
	
	float radius_;  // 的の半径（ピクセル）
	
	bool isHit_;  // 的に当たったかどうか（true=当たった、false=当たっていない）
	                                                      // 当たるとグレーアウトして表示される
};
