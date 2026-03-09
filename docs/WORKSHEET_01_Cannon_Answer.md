# ワークシート01: Cannon クラス（砲台）- 解答

## ?? 解答と解説

---

## ?? 問題1の解答

```cpp
#pragma once
#include "Base.h"

class Cannon : public 【①Base】
{
public:
    Cannon(const Vector2D& pos, unsigned int color);
    ~Cannon();

    void Update() override;
    void Draw() override;

    float GetAngle() const { return 【②angle_】; }
    float GetSpeed() const { return bulletSpeed_; }
    Vector2D GetDirection() const;
    Vector2D GetTipPosition() const;

private:
    float 【②angle_】;      // 砲台の角度（ラジアン）
    float angleSpeed_;      // 角度変化の速さ
    float barrelLength_;    // 砲身の長さ
    float bulletSpeed_;     // 弾の初速度
    float bulletSpeedMin_;
    float bulletSpeedMax_;
    float bulletSpeedStep_;
};
```

**解説：**
- ①: `Base` - すべてのゲームオブジェクトの親クラス
- ②: `angle_` - 角度を格納するメンバ変数

---

## ?? 問題2の解答

```cpp
Cannon::Cannon(const Vector2D& pos, unsigned int color)
    : Base(pos, { 0.0f, 0.0f }, color)
    , angle_(【③Math2D::PI / 4.0f】)  // 初期角度 45°
    , angleSpeed_(0.02f)
    , barrelLength_(50.0f)
    , bulletSpeed_(15.0f)
    , bulletSpeedMin_(10.0f)
    , bulletSpeedMax_(25.0f)
    , bulletSpeedStep_(0.2f)
{
    objType = OBJ_TYPE::【④CANNON】;
}
```

**解説：**
- ③: `Math2D::PI / 4.0f`
  - 45° = π/4 ラジアン
  - `Math2D::PI` は π (? 3.14159) を表す定数
  
- ④: `CANNON`
  - 砲台を表すオブジェクトタイプ
  - `Base.h` で定義されている列挙型

---

## ?? 問題3の解答

```cpp
Vector2D Cannon::GetDirection() const
{
    return Math2D::【⑤FromAngle】(【⑥angle_】);
}
```

**解説：**
- ⑤: `FromAngle`
  - 角度（ラジアン）から方向ベクトルを作る関数
  - 内部で `(cos θ, sin θ)` を計算している
  
- ⑥: `angle_`
  - 現在の砲台の角度

**数式：**
\[
\vec{d} = (\cos\theta,\ \sin\theta)
\]

**例：**
- angle_ = π/4 のとき
- \(\vec{d} = (\cos\frac{\pi}{4},\ \sin\frac{\pi}{4}) = (0.707, 0.707)\)

---

## ?? 問題4の解答

```cpp
Vector2D Cannon::GetTipPosition() const
{
    // ステップ1: 方向ベクトルを取得
    Vector2D dir = 【⑦GetDirection()】;
    
    // ステップ2: 方向ベクトル × 砲身の長さ = オフセット
    Vector2D offset = Math2D::【⑧Mul】(dir, 【⑨barrelLength_】);
    
    // ステップ3: 中心位置 + オフセット = 先端位置
    return Math2D::【⑩Add】(【⑪pos_】, offset);
}
```

**解説：**
- ⑦: `GetDirection()`
  - 自クラスの関数を呼び出して方向ベクトルを取得
  
- ⑧: `Mul`
  - ベクトルにスカラーを掛ける（Math2D::Mul）
  - `Mul(v, s)` = \((v_x \times s, v_y \times s)\)
  
- ⑨: `barrelLength_`
  - 砲身の長さ（50.0f ピクセル）
  
- ⑩: `Add`
  - 2つのベクトルを足す（Math2D::Add）
  - `Add(a, b)` = \((a_x + b_x, a_y + b_y)\)
  
- ⑪: `pos_`
  - 砲台の中心位置（Baseクラスから継承）

**数式の流れ：**

1. 方向ベクトル: \(\vec{d} = (\cos\theta,\ \sin\theta)\)

2. オフセット: \(\vec{o} = L \cdot \vec{d} = (L\cos\theta,\ L\sin\theta)\)
   - L = barrelLength_ = 50

3. 先端位置: \(\vec{t} = \vec{p} + \vec{o}\)
   - \(\vec{p}\) = pos_ (砲台の中心)

**具体例：**
- 砲台中心: pos_ = (100, 100)
- 角度: angle_ = 45° = π/4
- 砲身の長さ: barrelLength_ = 50

計算：
1. \(\vec{d} = (0.707, 0.707)\)
2. \(\vec{o} = 50 \times (0.707, 0.707) = (35.35, 35.35)\)
3. \(\vec{t} = (100, 100) + (35.35, 35.35) = (135.35, 135.35)\)

---

## ?? 考察問題の解答

### Q1: 方向ベクトルの長さ

**答え:** 長さは **1** です。

**理由:**
\[
|\vec{d}| = \sqrt{\cos^2\theta + \sin^2\theta} = \sqrt{1} = 1
\]

三角関数の基本公式 \(\cos^2\theta + \sin^2\theta = 1\) より、
方向ベクトルの長さは常に1になります。

これを**単位ベクトル**（unit vector）と呼びます。

**利点:**
- 長さ1なので、スカラー倍するだけで任意の長さのベクトルが作れる
- \(\vec{v} = s \cdot \vec{d}\) で速度ベクトルを簡単に作れる

---

### Q2: 砲身の先端位置の計算

**与えられた条件:**
- 砲台の中心: (100, 100)
- 角度: 45°
- 砲身の長さ: 50 ピクセル
- cos 45° = sin 45° = 0.707

**計算:**

1. 方向ベクトル:
   \[
   \vec{d} = (\cos 45°, \sin 45°) = (0.707, 0.707)
   \]

2. オフセット:
   \[
   \vec{o} = 50 \times (0.707, 0.707) = (35.35, 35.35)
   \]

3. 先端位置:
   \[
   \vec{t} = (100, 100) + (35.35, 35.35) = (135.35, 135.35)
   \]

**答え:** **(135.35, 135.35)**

---

### Q3: ベクトル演算の利点

**Math2D を使わない場合:**

```cpp
Vector2D Cannon::GetTipPosition() const
{
    float dirX = cos(angle_);
    float dirY = sin(angle_);
    
    float offsetX = dirX * barrelLength_;
    float offsetY = dirY * barrelLength_;
    
    Vector2D tip;
    tip.x = pos_.x + offsetX;
    tip.y = pos_.y + offsetY;
    
    return tip;
}
```

**ベクトル演算を使った場合（問題4の解答）:**

```cpp
Vector2D Cannon::GetTipPosition() const
{
    Vector2D dir = GetDirection();
    Vector2D offset = Math2D::Mul(dir, barrelLength_);
    return Math2D::Add(pos_, offset);
}
```

**ベクトル演算の利点:**

1. **コードが短く読みやすい**
   - x, y を別々に扱わなくてよい
   - 意図が明確

2. **ミスが減る**
   - x だけ計算し忘れる、などのミスがない
   - xとyの計算を対称的に書ける

3. **保守しやすい**
   - 3Dに拡張する場合も同じ構造
   - 数式とコードが対応している

4. **数学的に正しい**
   - ベクトルとして扱うべきものをベクトルとして扱える

---

## ?? 完成したコード

### Cannon.h
```cpp
#pragma once
#include "Base.h"

class Cannon : public Base
{
public:
    Cannon(const Vector2D& pos, unsigned int color);
    ~Cannon();

    void Update() override;
    void Draw() override;

    float GetAngle() const { return angle_; }
    float GetSpeed() const { return bulletSpeed_; }
    Vector2D GetDirection() const;
    Vector2D GetTipPosition() const;

private:
    float angle_;
    float angleSpeed_;
    float barrelLength_;
    float bulletSpeed_;
    float bulletSpeedMin_;
    float bulletSpeedMax_;
    float bulletSpeedStep_;
};
```

### Cannon.cpp
```cpp
#include "Cannon.h"
#include "Math2D.h"
#include "Input.h"
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
    // 左キー: 角度を上げる
    if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
    {
        angle_ += angleSpeed_;
        if (angle_ > Math2D::PI / 2.0f)
        {
            angle_ = Math2D::PI / 2.0f;
        }
    }
    
    // 右キー: 角度を下げる
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

Vector2D Cannon::GetDirection() const
{
    return Math2D::FromAngle(angle_);
}

Vector2D Cannon::GetTipPosition() const
{
    Vector2D dir = GetDirection();
    Vector2D offset = Math2D::Mul(dir, barrelLength_);
    return Math2D::Add(pos_, offset);
}
```

---

## ?? 学習のポイント

このワークシートで学んだこと：

1. **三角関数とベクトル**
   - 角度から方向ベクトルを作る
   - cos と sin の関係

2. **ベクトルのスカラー倍**
   - 方向ベクトルに長さを掛けて位置のオフセットを作る

3. **ベクトルの加算**
   - 基準点にオフセットを加えて最終位置を求める

4. **コードの可読性**
   - Math2D関数を使うことでコードが簡潔になる
   - 数式とコードの対応が明確になる

---

## ?? 次のステップ

Cannonクラスが完成したら、次は **WORKSHEET_02_Bullet_Answer.md** の解答を確認し、
Bulletクラスの実装に進みましょう！

弾クラスでは、重力による放物線運動を実装します。
