#include "Base.h"
#include "Stage.h"
#include "Math2D.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Target.h"

#include "globals.h"
#include <DxLib.h>
#include "Input.h"
#include <vector>


namespace
{
	const Vector2D CANNON_POS = { 100.0f, 100.0f };
	const unsigned int CANNON_COLOR = GetColor(0, 255, 0);
	
	const Vector2D TARGET_POS = { WIN_WIDTH - 100.0f, 400.0f };
	const float TARGET_RADIUS = 30.0f;
	const unsigned int TARGET_COLOR = GetColor(255, 0, 0);

	const float BULLET_SPEED_MIN = 10.0f;
	const float BULLET_SPEED_MAX = 25.0f;
	const float BULLET_SPEED_STEP = 0.2f;
	const float BULLET_RADIUS = 5.0f;
	const unsigned int BULLET_COLOR = GetColor(255, 255, 255);

	std::vector<Base*> objects;

	void AddObject(Base* obj)
	{
		objects.push_back(obj);
	}

	void UpdateAllObjects()
	{
		for (auto& obj : objects)
		{
			obj->Update();
		}
	}

	void DrawAllObjects()
	{
		for (auto& obj : objects)
		{
			obj->Draw();
		}
	}

	int stageState = 0;
	bool isHit = false;
}


Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	objects.clear();

	stageState = 1;
	
	isHit = false;

	Cannon* cannon = new Cannon(CANNON_POS, CANNON_COLOR);
	AddObject(cannon);

	Target* target = new Target(TARGET_POS, TARGET_RADIUS, TARGET_COLOR);
	AddObject(target);
}

void Stage::TitleUpdate()
{
}

void Stage::PlayUpdate()
{
	Bullet_vs_Target();

	DeleteInactiveBullet();

	UpdateAllObjects();

	Cannon* cannon = nullptr;
	for (auto& obj : objects)
	{
		if (obj->GetType() == OBJ_TYPE::CANNON)
		{
			cannon = (Cannon*)obj;
			break;
		}
	}

	if (cannon != nullptr && Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		ShootBullet(cannon);
	}
}

void Stage::GameOverUpdate()
{
}

void Stage::TitleDraw()
{
}

void Stage::PlayDraw()
{
	DrawAllObjects();

	Cannon* cannon = nullptr;
	for (auto& obj : objects)
	{
		if (obj->GetType() == OBJ_TYPE::CANNON)
		{
			cannon = (Cannon*)obj;
			break;
		}
	}

	if (cannon != nullptr)
	{
		float angleDeg = cannon->GetAngle() * 180.0f / Math2D::PI;
		DrawFormatString(10, 10, GetColor(255, 255, 255), _T("Angle: %.1f deg"), angleDeg);
		DrawFormatString(10, 30, GetColor(255, 255, 255), _T("Speed: %.1f"), cannon->GetSpeed());
		
		// ========================================
		// TODO: UI表示の穴埋め
		// 操作説明を表示する
		// ========================================
		// 以下の3つの操作方法を表示しよう:
		//   DrawFormatString(10, 70, GetColor(200, 200, 200), _T("LEFT/RIGHT: ..."));
		//   DrawFormatString(10, 90, GetColor(200, 200, 200), _T("UP/DOWN: ..."));
		//   DrawFormatString(10, 110, GetColor(200, 200, 200), _T("SPACE: ..."));
		//
		// ヒント: 
		//   - LEFT/RIGHT キーで角度調整
		//   - UP/DOWN キーで速度調整
		//   - SPACE キーで発射
		
		// TODO: ここに操作説明の描画を追加（3行）
		
	}

	if (isHit)
	{
		int fsize = GetFontSize();
		SetFontSize(60);
		DrawString(WIN_WIDTH / 2 - 60, WIN_HEIGHT / 2 - 30, _T("HIT!"), GetColor(255, 255, 0));
		SetFontSize(fsize);
	}
}

void Stage::GameOverDraw()
{
}

void Stage::Update()
{
	if (stageState == 0)
	{
		TitleUpdate();
	}
	else if(stageState == 1)
	{
		PlayUpdate();
	}
	else if (stageState == 2)
	{
		GameOverUpdate();
	}
}


void Stage::Release()
{
	for (auto& obj : objects)
	{
		if (obj != nullptr)
		{
			delete obj;
			obj = nullptr;
		}
	}
	objects.clear();
}

// ========================================
// TODO: ワークシート04 問題2
// 弾と的の当たり判定
// ========================================
void Stage::Bullet_vs_Target()
{
	// 有効な弾と的を集めるリスト
	std::vector<Bullet*> activeBullets;
	std::vector<Target*> targets;

	activeBullets.clear();
	targets.clear();

	// オブジェクトリストから弾と的を抽出（提供済み）
	for (auto& obj : objects)
	{
		// 弾の場合
		if (obj->GetType() == OBJ_TYPE::BULLET)
		{
			Bullet* b = (Bullet*)obj;
			// 有効な弾だけをリストに追加
			if (b->IsActive())
			{
				activeBullets.push_back(b);
			}
		}
		// 的の場合
		else if (obj->GetType() == OBJ_TYPE::TARGET)
		{
			Target* t = (Target*)obj;
			// まだ当たっていない的だけをリストに追加
			if (!t->IsHit())
			{
				targets.push_back(t);
			}
		}
	}

	// TODO: すべての弾と的の組み合わせで当たり判定
	// 
	// 二重ループで bullet と target をそれぞれ取り出す
	// 外側ループ: for (auto& bullet : activeBullets)
	// 内側ループ: for (auto& target : targets)
	//
	// 計算手順:
	// 
	// ステップ1: 差ベクトルを計算（弾の位置 - 的の位置）
	//   Vector2D diff = Math2Dのベクトル減算関数(弾の位置, 的の位置);
	//   ヒント: 減算の関数名は「Sub」（Subtraction: 引き算）
	//           弾の位置は bullet->GetPos()
	//           的の位置は target->GetPos()
	//
	// ステップ2: 距離を計算（ベクトルの長さ）
	//   float dist = Math2Dのベクトル長さ関数(差ベクトル);
	//   ヒント: 長さの関数名は「Length」
	//           √(x² + y²) を計算する関数
	//
	// ステップ3: 衝突判定距離を計算（半径の和）
	//   float collisionDist = bullet->半径取得関数() + target->半径取得関数();
	//   ヒント: Bullet.h と Target.h で定義されている関数を使う
	//           「Radius」を取得する関数
	//
	// ステップ4: 衝突判定
	//   if (距離 <= 衝突判定距離)
	//   {
	//       // 当たったときの処理
	//       target->SetHit();      // 的を「当たった」状態にする
	//       bullet->SetInactive(); // 弾を消す
	//       isHit = true;          // 「HIT!」を表示する
	//       gameScore_ += 100;     // スコアを加算
	//   }
	//   ヒント: 距離 ≤ 半径の和 のとき、2つの円は重なっている（衝突）
	
	for (auto& bullet : activeBullets)
	{
		for (auto& target : targets)
		{
			// TODO: ここに当たり判定の実装を書く
			
		}
	}
}

void Stage::Draw()
{
	if (stageState == 0)
	{
		TitleDraw();
	}
	else if (stageState == 1)
	{
		PlayDraw();
	}
	else if(stageState == 2)
	{
		GameOverDraw();
	}
}

void Stage::DeleteInactiveBullet()
{
	for (auto& itr : objects)
	{
		if(itr->GetType() == OBJ_TYPE::BULLET)
		{
			Bullet* b = (Bullet*)(itr);
			if (!b->IsActive())
			{
				delete b;
				itr = nullptr;
			}
		}
	}

	for (auto it = objects.begin(); it != objects.end(); )
	{
		if (*it == nullptr)
		{
			it = objects.erase(it);
		}
		else
		{
			it++;
		}
	}
}

// ========================================
// TODO: ワークシート04 問題1
// 弾を発射する
// ========================================
void Stage::ShootBullet(Cannon* cannon)
{
	// nullチェック: 砲台が存在しない場合は何もしない
	if (cannon == nullptr) return;

	// TODO: ここに実装を書く
	// 
	// ステップ1: 砲身の先端位置を取得
	//   Vector2D pos = cannon->先端位置取得関数();
	//   ヒント: Cannon.h で定義されている関数を使う
	//           砲身の「Tip Position」を取得する関数
	//
	// ステップ2: 方向ベクトルを取得（単位ベクトル）
	//   Vector2D dir = cannon->方向取得関数();
	//   ヒント: Cannon.h で定義されている関数を使う
	//           砲台が向いている「Direction」を取得する関数
	//
	// ステップ3: 速度ベクトルを計算（方向ベクトル × 速さ）
	//   Vector2D v = Math2Dのスカラー倍関数(方向ベクトル, cannon->速度取得関数());
	//   ヒント: スカラー倍の関数名は「Mul」
	//           速度を取得する関数は Cannon.h で定義されている「Speed」関連の関数
	//
	// ステップ4: 弾を生成してオブジェクトリストに追加
	//   Bullet* b = new Bullet(位置, 速度, BULLET_COLOR, BULLET_RADIUS);
	//   AddObject(b);
	//   ヒント: BULLET_COLOR と BULLET_RADIUS は定数として定義済み
	//           AddObject() 関数でオブジェクトリストに追加できる
}
