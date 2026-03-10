# ワークシート01: Cannon クラス（砲台）- 穴埋め問題

## 🎯 このワークシートの目標

このワークシートでは、**砲台クラス**を実装します。
特に以下の数学的概念を理解し、実装できるようになることが目標です：

- 三角関数を使った角度から方向ベクトルへの変換
- ベクトルのスカラー倍
- ベクトルの加算

---

## 🔫 砲台クラスの役割

1. 画面左下に固定
2. 左右キーで角度を変える
3. 上下キーで初速度を変える
4. 方向ベクトルを計算する
5. 砲身の先端位置を計算する

---

## 📐 数学の復習

### 1. 角度から方向ベクトルへの変換

角度 $$\\theta$$ (ラジアン) から、長さ1の方向ベクトル \($\\vec{d}$\) を作る公式：

$
$\\vec{d}$ = ($\\cos$$\\theta$,\ $\\sin$$\\theta$)
$

**例題：**
- $$\\theta$$ = 0° (0 rad) → ($$\\cos$$ 0, $$\\sin$$ 0) = (1, 0) → 右向き
- $$\\theta$$ = 45° ($$\\pi$$/4 rad) → ($$\\cos$$ $$\\pi$$/4, $$\\sin$$ $$\\pi$$/4) = (0.707, 0.707) → 右斜め上
- $$\\theta$$ = 90° ($$\\pi$$/2 rad) → ($$\\cos$$ $$\\pi$$/2, $$\\sin$$ $$\\pi$$/2) = (0, 1) → 真上

### 2. ベクトルのスカラー倍

ベクトル \($\\vec{v}$\) に数値（スカラー）s を掛ける：

$
s \cdot $\\vec{v}$ = (s \cdot $v_{x}$,\ s \cdot $v_{y}$)
$

**例題：**
- \($\\vec{v}$ = (1, 0)\)、s = 50 のとき
- \(50 \cdot (1, 0) = (50, 0)\)

### 3. ベクトルの加算

2つのベクトル \($\\vec{a}$\) と \($\\vec{b}$\) を足す：

$
$\\vec{a}$ + $\\vec{b}$ = (a_x + b_x,\ a_y + b_y)
$

**例題：**
- \($\\vec{a}$ = (100, 100)\)、\($\\vec{b}$ = (50, 0)\) のとき
- \((100, 100) + (50, 0) = (150, 100)\)

---

## ?? 問題1: Cannon.h のクラス定義

以下のクラス定義の【  】を埋めなさい。

```cpp
#pragma once
#include "Base.h"

class Cannon : public 【①】
{
public:
    Cannon(const Vector2D& pos, unsigned int color);
    ~Cannon();

    void Update() override;
    void Draw() override;

    float GetAngle() const { return 【②】; }
    float GetSpeed() const { return bulletSpeed_; }
    Vector2D GetDirection() const;
    Vector2D GetTipPosition() const;

private:
    float 【②】;           // 砲台の角度（ラジアン）
    float angleSpeed_;      // 角度変化の速さ
    float barrelLength_;    // 砲身の長さ
    float bulletSpeed_;     // 弾の初速度
    float bulletSpeedMin_;
    float bulletSpeedMax_;
    float bulletSpeedStep_;
};
```

**ヒント：**
- ①: すべてのゲームオブジェクトの親クラス名
- ②: 角度を格納する変数名（英語で "angle"）

---

## ?? 問題2: コンストラクタの実装

以下のコンストラクタの【  】を埋めなさい。

```cpp
Cannon::Cannon(const Vector2D& pos, unsigned int color)
    : Base(pos, { 0.0f, 0.0f }, color)
    , angle_(【③】)              // 初期角度 45°
    , angleSpeed_(0.02f)
    , barrelLength_(50.0f)
    , bulletSpeed_(15.0f)
    , bulletSpeedMin_(10.0f)
    , bulletSpeedMax_(25.0f)
    , bulletSpeedStep_(0.2f)
{
    objType = OBJ_TYPE::【④】;
}
```

**ヒント：**
- ③: 45°をラジアンで表すと？（`Math2D::PI` は $$\\pi$$ を表す）
- ④: 砲台を表すオブジェクトタイプ

**数学メモ：**
- 180° = $$\\pi$$ rad
- 90° = $$\\pi$$/2 rad
- 45° = $$\\pi$$/4 rad

---

## ?? 問題3: GetDirection() の実装（重要！）

角度から方向ベクトルを計算する関数を完成させなさい。

### 数式の確認
$
$\\vec{d}$ = ($\\cos$$\\theta$,\ $\\sin$$\\theta$)
$

この計算は `Math2D::FromAngle()` 関数が行ってくれます。

```cpp
Vector2D Cannon::GetDirection() const
{
    return Math2D::【⑤】(【⑥】);
}
```

**ヒント：**
- ⑤: 角度から方向ベクトルを作る関数名（`Math2D.h` に定義されている）
- ⑥: この関数に渡す角度の変数名

---

## ?? 問題4: GetTipPosition() の実装（重要！）

砲身の先端位置を計算する関数を完成させなさい。

### 数式の確認

砲台の中心位置を \($\\vec{p}$\)、方向ベクトルを \($\\vec{d}$\)、砲身の長さを L とすると、
砲身の先端位置 \($\\vec{t}$\) は：

$
$\\vec{t}$ = $\\vec{p}$ + L \cdot $\\vec{d}$
$

**手順：**
1. 方向ベクトルを取得する
2. 方向ベクトルに砲身の長さを掛ける（スカラー倍）
3. 砲台の中心位置に加える（ベクトル加算）

```cpp
Vector2D Cannon::GetTipPosition() const
{
    // ステップ1: 方向ベクトルを取得
    Vector2D dir = 【⑦】;
    
    // ステップ2: 方向ベクトル × 砲身の長さ = オフセット
    Vector2D offset = Math2D::【⑧】(dir, 【⑨】);
    
    // ステップ3: 中心位置 + オフセット = 先端位置
    return Math2D::【⑩】(【⑪】, offset);
}
```

**ヒント：**
- ⑦: 方向ベクトルを取得する関数を呼び出す
- ⑧: ベクトルにスカラーを掛ける関数（Math2D の関数）
- ⑨: 砲身の長さを表すメンバ変数
- ⑩: 2つのベクトルを足す関数（Math2D の関数）
- ⑪: 砲台の中心位置を表すメンバ変数（親クラスから継承）

**利用可能な Math2D の関数：**
- `Math2D::Add(a, b)` - ベクトルの加算
- `Math2D::Mul(v, s)` - ベクトルのスカラー倍
- `Math2D::FromAngle(rad)` - 角度から方向ベクトル

---

## ?? 問題5: Update() の実装（提供済み）

以下の `Update()` 関数は**すでに完成しています**。
角度と速度の調整処理が実装されているので、そのまま使用してください。

```cpp
void Cannon::Update()
{
    // 左キー: 角度を上げる
    if (Input::IsKeepKeyDown(KE$Y_{INPUT}$_LEFT))
    {
        angle_ += angleSpeed_;
        if (angle_ > Math2D::PI / 2.0f)
        {
            angle_ = Math2D::PI / 2.0f;
        }
    }
    
    // 右キー: 角度を下げる
    if (Input::IsKeepKeyDown(KE$Y_{INPUT}$_RIGHT))
    {
        angle_ -= angleSpeed_;
        if (angle_ < 0.0f)
        {
            angle_ = 0.0f;
        }
    }

    // 上キー: 初速度を上げる
    if (Input::IsKeepKeyDown(KE$Y_{INPUT}$_UP))
    {
        bulletSpeed_ += bulletSpeedStep_;
        if (bulletSpeed_ > bulletSpeedMax_)
        {
            bulletSpeed_ = bulletSpeedMax_;
        }
    }

    // 下キー: 初速度を下げる
    if (Input::IsKeepKeyDown(KE$Y_{INPUT}$_DOWN))
    {
        bulletSpeed_ -= bulletSpeedStep_;
        if (bulletSpeed_ < bulletSpeedMin_)
        {
            bulletSpeed_ = bulletSpeedMin_;
        }
    }
}
```

---

## ?? 問題6: Draw() の実装（提供済み）

以下の `Draw()` 関数は**すでに完成しています**。
砲台本体と砲身を描画する処理が実装されているので、そのまま使用してください。

```cpp
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
```

---

## ?? 考察問題

実装が完了したら、以下の問いに答えなさい。

### Q1: 方向ベクトルの長さ
`GetDirection()` が返す方向ベクトルの長さは何ですか？
なぜその長さになるのですか？

### Q2: 砲身の先端位置の計算
砲身の長さが 50 ピクセルで、角度が 45° のとき、
砲台の中心が (100, 100) だとすると、砲身の先端位置はどこになりますか？
（$$\\cos$$ 45° = $$\\sin$$ 45° = 0.707 として計算してください）

### Q3: ベクトル演算の利点
もし Math2D の関数を使わずに、x と y を別々に計算する場合、
コードはどうなりますか？ベクトル演算を使う利点は何ですか？

---

## ?? 解答欄

以下に、完成したコードを記入してください。

### Cannon.h
```cpp
// ここに完成した Cannon.h のコードを書く








```

### Cannon.cpp
```cpp
// ここに完成した Cannon.cpp のコードを書く
// （Update() と Draw() は提供済みなので、それ以外を記入）








```

---

## ✅ 完成チェックリスト

実装が終わったら、以下を確認してください：

- [ ] コンパイルエラーがない
- [ ] 左右キーで砲台の角度が変わる
- [ ] 砲身が正しい方向を向いている
- [ ] 砲身の先端位置が正しく計算されている
- [ ] 上下キーで初速度が変わる

---

## ?? 次のステップ

このワークシートが完成したら、次は **WORKSHEET_02_Bullet_Problem.md** に進みましょう！
弾クラスで放物線運動を実装します。
