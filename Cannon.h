#pragma once
#include "Base.h"

// ========================================
// TODO: ワークシート01 問題1
// Cannonクラスの定義
// ========================================
// ヒント:
// ①すべてのゲームオブジェクトは共通の親クラスを継承している
//   Base.h を見て、どのクラスを継承すべきか確認しよう
// ②角度を格納する変数名は英語で "angle"
//   アンダースコア(_)で終わる命名規則を使っている

class Cannon : public /* TODO: ①親クラス名を書く */
{
public:
	// コンストラクタ: 砲台の初期位置と色を設定
	Cannon(const Vector2D& pos, unsigned int color);
	~Cannon();

	// 毎フレーム呼ばれる更新処理（キー入力で角度・速度を変更）
	void Update() override;
	
	// 毎フレーム呼ばれる描画処理（砲台本体と砲身を描画）
	void Draw() override;

	// 砲台の角度を取得（ラジアン）
	float GetAngle() const { return /* TODO: ②角度の変数名を書く */; }
	
	// 弾の初速度を取得
	float GetSpeed() const { return bulletSpeed_; }
	
	// 砲台が向いている方向の単位ベクトルを取得
	// 三角関数を使って (cos θ, sin θ) を計算する
	Vector2D GetDirection() const;
	
	// 砲身の先端位置を取得
	// 砲台の中心 + 方向ベクトル × 砲身の長さ で計算する
	Vector2D GetTipPosition() const;

private:
	// ========================================
	// メンバ変数（砲台の状態を管理）
	// ========================================
	
	float /* TODO: ②角度を格納する変数名を書く（ラジアン）*/;  // 砲台の角度（0〜π/2の範囲）
	float angleSpeed_;      // 角度変化の速さ（1フレームあたりの変化量）
	float barrelLength_;    // 砲身の長さ（ピクセル）
	float bulletSpeed_;     // 弾の初速度（現在の値）
	float bulletSpeedMin_;  // 弾の初速度の最小値
	float bulletSpeedMax_;  // 弾の初速度の最大値
	float bulletSpeedStep_; // 速度変化の刻み幅
};
