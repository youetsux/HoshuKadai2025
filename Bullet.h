#pragma once
#include "Base.h"

// ========================================
// TODO: ワークシート02 問題1
// Bulletクラスの定義
// ========================================
// ヒント:
// ①親クラスは Cannon と同じクラスを継承する
//   Cannon.h を見て確認しよう
// ②有効・無効を管理するフラグ変数は英語で "is active"
//   bool型で、true=有効、false=無効 を表す

class Bullet : public /* TODO: ①親クラス名を書く */
{
public:
	// コンストラクタ: 弾の初期位置、初速度、色、半径を設定
	Bullet(const Vector2D& pos, const Vector2D& vel, unsigned int color, float radius);
	~Bullet();

	// 毎フレーム呼ばれる更新処理（重力を加えて放物線運動）
	void Update() override;
	
	// 毎フレーム呼ばれる描画処理（円として描画）
	void Draw() override;

	// 弾が有効かどうかを取得
	// 画面外に出たり、的に当たったら false になる
	bool IsActive() const { return /* TODO: ②有効フラグの変数名を書く */; }
	
	// 弾を無効にする（画面外や的に当たったときに呼ばれる）
	void SetInactive() { /* TODO: ②有効フラグの変数名を書く */ = false; }
	
	// 弾の半径を取得（当たり判定で使用）
	float GetRadius() const { return radius_; }

private:
	// ========================================
	// メンバ変数（弾の状態を管理）
	// ========================================
	
	float radius_;   // 弾の半径（ピクセル）
	
	bool /* TODO: ②有効フラグの変数名を書く（bool型）*/;  // 弾が有効かどうか（true=有効、false=無効）
	
	float gravity_;  // 重力加速度（毎フレーム速度のy成分に加算される値）
	                 // ワールド座標では下向き = 負の値
};
