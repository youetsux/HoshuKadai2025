#include "Target.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Target::Target(const Vector2D& pos, float radius, unsigned int color)
	: Base(pos, { 0.0f, 0.0f }, color)  // 親クラスを初期化（速度は0、的は動かない）
	, radius_(radius)                   // 的の半径
	, isHit_(false)                     // 初期状態は当たっていない（false）
{
	objType = OBJ_TYPE::TARGET;         // オブジェクトタイプを的に設定
}

Target::~Target()
{
}

// ========================================
// TODO: ワークシート03 問題3
// 的の更新処理
// ========================================
void Target::Update()
{
	// TODO: ここに処理を書く
	// 的は固定されている（動かない）ので、何も処理をしなくてOK
	// ただし、純粋仮想関数をオーバーライドするために関数定義は必要
	//
	// 注意: 関数本体は空でも構わないが、コメントを書いておくと良い
	//       例: // 的は動かないので処理なし
}

void Target::Draw()
{
	// ワールド座標を画面座標に変換
	Vector2D screenPos = Math2D::World2Screen(pos_);

	// 当たったら色を変える（グレーアウト）
	// 三項演算子: 条件 ? true時の値 : false時の値
	unsigned int drawColor = isHit_ ? GetColor(100, 100, 100) : Color_;
	
	// 3重の円で的を表現（外側から順に描画）
	// 外円: 半径100%
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)radius_, drawColor, FALSE);
	// 中円: 半径60%
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)(radius_ * 0.6f), drawColor, FALSE);
	// 内円: 半径30%
	DrawCircle((int)screenPos.x, (int)screenPos.y, (int)(radius_ * 0.3f), drawColor, FALSE);
	// 最後の引数 FALSE は「塗りつぶさない（枠だけ）」という意味
}
