# 砲台ゲーム実装ガイド - ステップバイステップ

## ?? はじめに

このガイドでは、`Base`クラスを継承して砲台ゲームを作る過程を、実装する順番に沿って説明します。
各ステップで「なぜそうするのか」を理解しながら進めていきましょう。

---

## ?? このゲームで学ぶこと

### 数学的な要素
- **ベクトル演算**: 位置、速度、方向を表現
- **三角関数**: 角度から方向ベクトルを作る
- **加速度運動**: 重力による放物線運動
- **当たり判定**: 円同士の衝突判定

### プログラミング的な要素
- **クラス設計**: 共通部分を親クラスにまとめる
- **継承**: Baseクラスから機能を受け継ぐ
- **ポリモーフィズム**: 同じインターフェースで異なる動作
- **入力処理**: キー入力の使い分け

---

## ?? 事前準備：クラス設計を考える

### ゲームに必要なオブジェクト

| オブジェクト | 役割 | 固有の情報 |
|------------|------|-----------|
| **砲台(Cannon)** | 弾を発射する | 角度、初速度 |
| **弾(Bullet)** | 放物線を描いて飛ぶ | 半径、重力 |
| **的(Target)** | 当たり判定の対象 | 半径、当たったか |

### 共通する情報（Base クラスに入れる）

すべてのオブジェクトは以下を持っています：

```cpp
? 位置 (pos_)
? 速度 (vel_)
? 色 (Color_)
? オブジェクトタイプ (objType)
```

**なぜ共通化するのか？**
- コードの重複を避ける
- メンテナンスしやすくなる
- 配列で一括管理できる

---

## ステップ1: Base.h にオブジェクトタイプを追加

### ?? なぜ必要？

複数のオブジェクトを`std::vector<Base*>`で管理するとき、
「これは砲台なのか、弾なのか、的なのか」を区別する必要があります。

### ?? 実装

`Base.h`の`OBJ_TYPE`列挙型を以下のように変更：

```cpp
enum OBJ_TYPE
{
    UNKNOWN,     // 不明なオブジェクト
    PLAYER,      // プレイヤー（今回は未使用）
    BULLET,      // 弾
    CANNON,      // 砲台
    TARGET,      // 的
    MAX_OBJ_TYPE // オブジェクトタイプの総数
};
```

### ?? 考えてみよう
- なぜ`enum`を使うのでしょうか？
- 数値で管理（0,1,2...）するのと何が違いますか？

**答え**: enumを使うことで、コードが読みやすく、間違いにくくなります。
例えば `objType == 2` より `objType == OBJ_TYPE::CANNON` の方が意図が明確です。

---

## ステップ2: Cannon クラスを作る（砲台）

### ?? 砲台の役割

1. 画面左下に固定
2. 左右キーで角度を変える
3. 上下キーで初速度を変える
4. スペースキーで弾を発射

### ?? 砲台だけが持つ情報

```cpp
float angle_;           // 砲台の角度（ラジアン単位）
float angleSpeed_;      // 角度変化の速さ（ラジアン/フレーム）
float barrelLength_;    // 砲身の長さ（ピクセル）
float bulletSpeed_;     // 弾の初速度（現在の設定値）
float bulletSpeedMin_;  // 弾の初速度の最小値
float bulletSpeedMax_;  // 弾の初速度の最大値
float bulletSpeedStep_; // 速度変更時の増減量
```

### ?? Cannon.h の作成

```cpp
#pragma once
#include "Base.h"

class Cannon : public Base
{
public:
    // コンストラクタ：位置と色を指定して砲台を作成
    Cannon(const Vector2D& pos, unsigned int color);
    ~Cannon();

    void Update() override;  // 入力処理（角度・速度の変更）
    void Draw() override;    // 描画（砲台本体と砲身）

    // ゲッター（値を取得する関数）
    float GetAngle() const { return angle_; }           // 現在の角度を取得
    float GetSpeed() const { return bulletSpeed_; }     // 現在の初速度を取得
    Vector2D GetDirection() const;      // 方向ベクトル（単位ベクトル）を取得
    Vector2D GetTipPosition() const;    // 砲身の先端位置を取得

private:
    float angle_;           // 砲台の角度（ラジアン）
    float angleSpeed_;      // 角度変化の速さ
    float barrelLength_;    // 砲身の長さ
    float bulletSpeed_;     // 弾の初速度
    float bulletSpeedMin_;  // 初速度の最小値
    float bulletSpeedMax_;  // 初速度の最大値
    float bulletSpeedStep_; // 速度変更の増減量
};
```

### ?? 重要ポイント：角度と方向ベクトル

#### 角度 → 方向ベクトルの変換

```
角度 θ (ラジアン) → 方向ベクトル (cos θ, sin θ)
```

**具体例：**
- θ = 0° (0 rad) → (1, 0) 右向き
- θ = 45° (π/4 rad) → (0.707, 0.707) 右斜め上
- θ = 90° (π/2 rad) → (0, 1) 真上

#### なぜ方向ベクトルの長さは1？

```
速度ベクトル = 方向ベクトル × 速さ
v = d × speed
```

長さ1の方向ベクトルに速さを掛けることで、簡単に速度ベクトルが作れます。

### ?? Cannon.cpp の実装

```cpp
#include "Cannon.h"
#include "Math2D.h"
#include "Input.h"
#include <DxLib.h>

Cannon::Cannon(const Vector2D& pos, unsigned int color)
    : Base(pos, { 0.0f, 0.0f }, color)
    , angle_(Math2D::PI / 4.0f)      // 初期角度 45°
    , angleSpeed_(0.02f)              // 角度変化速度
    , barrelLength_(50.0f)            // 砲身の長さ
    , bulletSpeed_(15.0f)             // 初速度
    , bulletSpeedMin_(10.0f)
    , bulletSpeedMax_(25.0f)
    , bulletSpeedStep_(0.2f)
{
    objType = OBJ_TYPE::CANNON;
}

void Cannon::Update()
{
    // 左キー: 角度を上げる（左回転）
    if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
    {
        angle_ += angleSpeed_;
        if (angle_ > Math2D::PI / 2.0f)  // 90°が上限
        {
            angle_ = Math2D::PI / 2.0f;
        }
    }
    
    // 右キー: 角度を下げる（右回転）
    if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
    {
        angle_ -= angleSpeed_;
        if (angle_ < 0.0f)  // 0°(水平)が下限
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

// 角度から方向ベクトルを作る
Vector2D Cannon::GetDirection() const
{
    return Math2D::FromAngle(angle_);
}

// 砲身の先端位置を計算
Vector2D Cannon::GetTipPosition() const
{
    Vector2D dir = GetDirection();                    // 方向ベクトル
    Vector2D offset = Math2D::Mul(dir, barrelLength_); // 長さ分のオフセット
    return Math2D::Add(pos_, offset);                 // 中心 + オフセット
}
```

### ?? 考えてみよう

**Q1: なぜ `IsKeepKeyDown()` を使うのですか？**

`IsKeepKeyDown()`は、キーを押し続けている間ずっとtrueを返します。
角度を連続的に変化させたい場合に適しています。

**Q2: 角度に上限・下限をつけるのはなぜですか？**

- 上限(90°): 真上より後ろには撃てない（物理的に不自然）
- 下限(0°): 地面より下には撃てない

---

## ステップ3: Bullet クラスを作る（弾）

### ?? 弾の役割

1. 砲台から発射される
2. 初速度を持って飛ぶ
3. 重力の影響を受けて放物線を描く
4. 画面外に出たら消える

### ?? 弾だけが持つ情報

```cpp
float radius_;   // 弾の半径（描画サイズと当たり判定に使用）
bool isActive_;  // 弾が有効かどうか（画面内ならtrue、画面外ならfalse）
float gravity_;  // 重力加速度（毎フレーム速度に加算される値）
```

### ?? 重要ポイント：放物線運動の仕組み

#### 1. 速度による位置の更新

```
新しい位置 = 古い位置 + 速度
p_new = p_old + v
```

毎フレーム、速度分だけ位置が変わります。

#### 2. 重力による速度の変化

```
新しい速度 = 古い速度 + 重力
v_new = v_old + g
```

毎フレーム、重力分だけ速度が変わります。

#### 3. なぜ放物線になるのか？

```
フレーム0: v_y = +10     → 上向き
フレーム1: v_y = +10 - 0.3 = +9.7  → 少し遅くなる
フレーム2: v_y = +9.7 - 0.3 = +9.4 → さらに遅くなる
...
フレームN: v_y = 0       → 最高点
フレームN+1: v_y = -0.3   → 下向きに
```

y方向の速度が徐々に減少し、やがて負（下向き）になることで、
放物線を描きます。

### ?? Bullet.h の作成

```cpp
#pragma once
#include "Base.h"

class Bullet : public Base
{
public:
    // コンストラクタ：位置、速度、色、半径を指定して弾を作成
    Bullet(const Vector2D& pos, const Vector2D& vel, 
           unsigned int color, float radius);
    ~Bullet();

    void Update() override;  // 位置の更新（重力と速度による移動）
    void Draw() override;    // 描画（円として表示）

    // ゲッター・セッター
    bool IsActive() const { return isActive_; }      // 弾が有効かどうか
    void SetInactive() { isActive_ = false; }        // 弾を無効にする
    float GetRadius() const { return radius_; }      // 弾の半径を取得

private:
    float radius_;   // 弾の半径
    bool isActive_;  // 有効フラグ
    float gravity_;  // 重力加速度
};
```

### ?? Bullet.cpp の実装

```cpp
#include "Bullet.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Bullet::Bullet(const Vector2D& pos, const Vector2D& vel, 
               unsigned int color, float radius)
    : Base(pos, vel, color)      // 親クラスのコンストラクタを呼び出し
    , radius_(radius)             // 弾の半径を初期化
    , isActive_(true)             // 最初は有効
    , gravity_(0.3f)              // 重力加速度を設定
{
    objType = OBJ_TYPE::BULLET;  // オブジェクトタイプを設定
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    if (!isActive_) return;  // 無効な弾は更新しない

    // ステップ1: 重力を速度に加える
    Vector2D gravityVec = { 0.0f, -gravity_ };  // 下向き（ワールド座標）
    vel_ = Math2D::Add(vel_, gravityVec);       // 速度 = 速度 + 重力

    // ステップ2: 速度を位置に加える
    pos_ = Math2D::Add(pos_, vel_);             // 位置 = 位置 + 速度

    // 画面外判定：画面外に出たら無効にする
    if (pos_.x < 0 || pos_.x > WIN_WIDTH || 
        pos_.y < 0 || pos_.y > WIN_HEIGHT)
    {
        isActive_ = false;
    }
}

void Bullet::Draw()
{
    if (!isActive_) return;  // 無効な弾は描画しない

    // ワールド座標を画面座標に変換
    Vector2D screenPos = Math2D::World2Screen(pos_);
    
    // 円を描画（塗りつぶし）
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)radius_, Color_, TRUE);
}
```

### ?? 考えてみよう

**Q1: なぜ重力は負の値なのですか？**

ワールド座標では、y軸が上向きです。
重力は下向きなので、y方向の速度を**減らす**（負の値を加える）必要があります。

**Q2: 重力を0にするとどうなりますか？**

速度が変化しないので、まっすぐ飛びます（直線運動）。

**Q3: 重力を大きくするとどうなりますか？**

より急激に下に落ちるようになります（弾道が急になる）。

---

## ステップ4: Target クラスを作る（的）

### ?? 的の役割

1. 画面右側に固定
2. 弾との当たり判定
3. 当たったら状態を変える

### ?? 的だけが持つ情報

```cpp
float radius_;  // 的の半径（描画サイズと当たり判定に使用）
bool isHit_;    // 当たったかどうか（当たったらtrue）
```

### ?? Target.h の作成

```cpp
#pragma once
#include "Base.h"

class Target : public Base
{
public:
    // コンストラクタ：位置、半径、色を指定して的を作成
    Target(const Vector2D& pos, float radius, unsigned int color);
    ~Target();

    void Update() override;  // 更新（今回は固定なので何もしない）
    void Draw() override;    // 描画（3重の円として表示）

    // ゲッター・セッター
    bool IsHit() const { return isHit_; }   // 当たったかどうか
    void SetHit() { isHit_ = true; }        // 当たり状態にする
    float GetRadius() const { return radius_; }  // 半径を取得

private:
    float radius_;  // 的の半径
    bool isHit_;    // 当たりフラグ
};
```

### ?? Target.cpp の実装

```cpp
#include "Target.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Target::Target(const Vector2D& pos, float radius, unsigned int color)
    : Base(pos, { 0.0f, 0.0f }, color)  // 親クラス初期化（速度は0）
    , radius_(radius)                    // 半径を初期化
    , isHit_(false)                      // 最初は当たっていない
{
    objType = OBJ_TYPE::TARGET;         // オブジェクトタイプを設定
}

Target::~Target()
{
}

void Target::Update()
{
    // 今回は固定なので何もしない
    // 発展課題：ここで左右に動かすと面白い
}

void Target::Draw()
{
    // ワールド座標を画面座標に変換
    Vector2D screenPos = Math2D::World2Screen(pos_);

    // 当たったら色を変える（グレーアウト）
    unsigned int drawColor = isHit_ ? GetColor(100, 100, 100) : Color_;
    
    // 3重の円で的を表現（外側から順に描画）
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)radius_, drawColor, FALSE);  // 外円（枠のみ）
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)(radius_ * 0.6f), drawColor, FALSE);  // 中円
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)(radius_ * 0.3f), drawColor, FALSE);  // 内円
}
```

---

## ステップ5: Stage クラスで管理する

### ?? Stageの役割

1. すべてのオブジェクトを管理
2. 更新と描画を行う
3. 当たり判定を行う
4. UI表示

### ?? 重要ポイント：当たり判定の数学

#### 円同士の衝突判定

```
中心間の距離 ≦ 半径の和  → 衝突
```

**計算手順：**

1. 差ベクトルを求める
   ```
   r = p_target - p_bullet
   ```

2. 差ベクトルの長さ（距離）を求める
   ```
   distance = √(r.x? + r.y?)
   ```

3. 半径の和と比較
   ```
   if (distance < r_bullet + r_target) → HIT!
   ```

### ?? Stage.h の更新

```cpp
#pragma once
#include <vector>

// 前方宣言：ヘッダファイルのインクルードを減らすため
class Cannon;
class Bullet;
class Target;

class Stage
{
public:
    Stage();
    ~Stage();
    void Initialize();  // 初期化（オブジェクトの生成）
    
    void Update();      // 毎フレームの更新処理
    void Draw();        // 毎フレームの描画処理
    void Release();     // 終了処理（メモリ解放）

private:
    unsigned long long gameScore_;  // ゲームスコア
    
    void PlayUpdate();  // プレイ中の更新処理
    void PlayDraw();    // プレイ中の描画処理
    
    void Bullet_vs_Target();         // 弾と的の当たり判定
    void DeleteInactiveBullet();     // 無効な弾を削除
    void ShootBullet(Cannon* cannon); // 弾を発射
};
```

### ?? Stage.cpp の主要部分

```cpp
void Stage::Initialize()
{
    objects.clear();     // オブジェクトリストをクリア
    stageState = 1;      // プレイ中の状態に設定
    gameScore_ = 0;      // スコアを初期化
    isHit = false;       // ヒットフラグを初期化

    // 砲台を作成して登録
    Cannon* cannon = new Cannon(CANNON_POS, CANNON_COLOR);
    AddObject(cannon);

    // 的を作成して登録
    Target* target = new Target(TARGET_POS, TARGET_RADIUS, TARGET_COLOR);
    AddObject(target);
}

void Stage::PlayUpdate()
{
    // 当たり判定の処理
    Bullet_vs_Target();

    // 無効な弾を削除
    DeleteInactiveBullet();

    // すべてのオブジェクトを更新
    UpdateAllObjects();

    // 砲台を探す
    Cannon* cannon = nullptr;
    for (auto& obj : objects)
    {
        if (obj->GetType() == OBJ_TYPE::CANNON)
        {
            cannon = (Cannon*)obj;  // Base*をCannon*にキャスト
            break;
        }
    }

    // スペースキーが押されたら弾を発射
    if (cannon != nullptr && Input::IsKeyDown(KEY_INPUT_SPACE))
    {
        ShootBullet(cannon);
    }
}

void Stage::Bullet_vs_Target()
{
    // 有効な弾と的を集めるリスト
    std::vector<Bullet*> activeBullets;
    std::vector<Target*> targets;

    // オブジェクトリストから弾と的を抽出
    for (auto& obj : objects)
    {
        if (obj->GetType() == OBJ_TYPE::BULLET)
        {
            Bullet* b = (Bullet*)obj;  // キャスト
            if (b->IsActive())  // 有効な弾のみ
            {
                activeBullets.push_back(b);
            }
        }
        else if (obj->GetType() == OBJ_TYPE::TARGET)
        {
            Target* t = (Target*)obj;  // キャスト
            if (!t->IsHit())  // まだ当たっていない的のみ
            {
                targets.push_back(t);
            }
        }
    }

    // すべての弾と的の組み合わせで当たり判定
    for (auto& bullet : activeBullets)
    {
        for (auto& target : targets)
        {
            // 差ベクトルを計算
            Vector2D diff = Math2D::Sub(bullet->GetPos(), target->GetPos());
            
            // 距離を計算（ベクトルの長さ）
            float dist = Math2D::Length(diff);
            
            // 衝突判定距離（半径の和）
            float collisionDist = bullet->GetRadius() + target->GetRadius();
            
            // 衝突判定：距離が半径の和より小さければ当たり
            if (dist < collisionDist)
            {
                target->SetHit();        // 的を当たり状態に
                bullet->SetInactive();   // 弾を無効に
                isHit = true;            // HITフラグを立てる
                gameScore_ += 100;       // スコアを加算
            }
        }
    }
}

void Stage::ShootBullet(Cannon* cannon)
{
    if (cannon == nullptr) return;  // 砲台がなければ何もしない

    // 砲身の先端位置を取得
    Vector2D pos = cannon->GetTipPosition();
    
    // 方向ベクトルを取得（単位ベクトル）
    Vector2D dir = cannon->GetDirection();
    
    // 速度ベクトル = 方向ベクトル × 速さ
    Vector2D v = Math2D::Mul(dir, cannon->GetSpeed());

    // 弾を生成してオブジェクトリストに追加
    Bullet* b = new Bullet(pos, v, BULLET_COLOR, BULLET_RADIUS);
    AddObject(b);
}
```

---

## ?? まとめ：学んだこと

### 数学的な理解

1. **ベクトルの加算**: 位置 + 速度、速度 + 重力
2. **スカラー倍**: 方向ベクトル × 速さ
3. **ベクトルの長さ**: 距離の計算
4. **三角関数**: 角度 → 方向ベクトル
5. **加速度運動**: 重力で放物線

### プログラミングの理解

1. **継承**: 共通部分をBaseにまとめる
2. **ポリモーフィズム**: `std::vector<Base*>`で一括管理
3. **カプセル化**: クラスごとに役割を分ける
4. **入力の使い分け**: `IsKeyDown` vs `IsKeepKeyDown`

---

## ?? 考察問題の答え

### Q1: Baseクラスには何を持たせましたか？

位置、速度、色、オブジェクトタイプ

### Q2: 各クラスの固有情報は？

- Cannon: 角度、初速度、砲身の長さ
- Bullet: 半径、有効フラグ、重力
- Target: 半径、ヒットフラグ

### Q3: なぜ砲台の回転には`IsKeepKeyDown()`？

連続的に角度を変化させたいから。
押し続けている間ずっと回転する必要がある。

### Q4: なぜ弾の発射には`IsKeyDown()`？

1回のキー押下で1発だけ発射したいから。
押し続けても連射されないようにする。

### Q5: 方向ベクトルと速度ベクトルの違いは？

- 方向ベクトル: 長さ1、向きだけを表す
- 速度ベクトル: 向きと速さの両方を表す

### Q6: 重力で放物線になる理由は？

重力が速度に影響し、速度が変わることで
位置の変化の仕方が変わるから。
特にy方向の速度が徐々に減少→負になることで、
上昇→最高点→下降 という軌道になる。

### Q7: `Math2D::Sub()`と`Math2D::Length()`の使い方は？

```cpp
Vector2D diff = Math2D::Sub(pos1, pos2);  // 差ベクトル
float distance = Math2D::Length(diff);    // 距離
```

### Q8: クラスを分ける利点は？

- コードが読みやすい
- 変更が局所化される
- 再利用しやすい
- テストしやすい

---

## ?? 次のステップ：発展課題

余裕があれば以下に挑戦してみましょう：

1. **ターゲットを動かす**: `Target::Update()`で左右に移動
2. **複数のターゲット**: 配列で複数の的を管理
3. **弾数制限**: 残弾数を表示し、リロード機能
4. **軌跡予測**: 発射前に弾道を点線で表示
5. **行列変換**: 砲身の先端位置を行列で計算

これで砲台ゲームの実装ガイドは完成です！
実際に動かして、数式と動きの関係を確かめましょう。
