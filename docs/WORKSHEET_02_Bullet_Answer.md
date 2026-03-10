# ワークシート02: Bullet クラス（弾）- 解答

## 📝 解答と解説

---

## ✅ 問題1の解答

```cpp
#pragma once
#include "Base.h"

class Bullet : public 【①Base】
{
public:
    Bullet(const Vector2D& pos, const Vector2D& vel, 
           unsigned int color, float radius);
    ~Bullet();

    void Update() override;
    void Draw() override;

    bool IsActive() const { return 【②isActive_】; }
    void SetInactive() { 【②isActive_】 = false; }
    float GetRadius() const { return radius_; }

private:
    float radius_;
    bool 【②isActive_】;  // 弾が有効かどうか
    float gravity_;
};
```

**解説：**
- ①: `Base` - すべてのゲームオブジェクトの親クラス
- ②: `isActive_` - 弾が有効（画面内）か無効（画面外）かを管理するフラグ

---

## ✅ 問題2の解答

```cpp
Bullet::Bullet(const Vector2D& pos, const Vector2D& vel, 
               unsigned int color, float radius)
    : 【③Base】(pos, vel, color)  // 親クラスを初期化
    , radius_(radius)
    , isActive_(【④true】)         // 最初は有効
    , gravity_(0.3f)
{
    objType = OBJ_TYPE::【⑤BULLET】;
}
```

**解説：**
- ③: `Base`
  - 親クラスのコンストラクタを呼び出す
  - 位置、速度、色を初期化
  
- ④: `true`
  - 弾を生成した直後は有効な状態
  - 画面外に出たら `false` に変更される
  
- ⑤: `BULLET`
  - 弾を表すオブジェクトタイプ
  - `Base.h` で定義されている列挙型

---

## ?? 問題3の解答

```cpp
void Bullet::Update()
{
    if (!isActive_) return;

    // ステップ1: 重力を速度に加える
    
    // 重力ベクトルを作る（ワールド座標では下向き = 負のy）
    Vector2D gravityVec = { 【⑥0.0f】, 【⑦-gravity_】 };
    
    // 速度 = 速度 + 重力
    vel_ = Math2D::【⑧Add】(【⑨vel_】, gravityVec);

    // ステップ2: 速度を位置に加える
    
    // 位置 = 位置 + 速度
    pos_ = Math2D::【⑩Add】(【⑪pos_】, 【⑫vel_】);

    // 画面外判定
    if (pos_.x < 0 || pos_.x > WIN_WIDTH || 
        pos_.y < 0 || pos_.y > WIN_HEIGHT)
    {
        isActive_ = false;
    }
}
```

**解説：**

### ⑥: `0.0f`
- 重力のx成分
- 横方向には重力がかからない
- x方向は等速直線運動

### ⑦: `-gravity_`
- 重力のy成分
- **マイナス記号が重要！**
- ワールド座標では y軸が上向きなので、下向きの重力は負の値
- `gravity_` = 0.3 なら、`-gravity_` = -0.3

**座標系の確認：**
```
ワールド座標:          画面座標:
     ↑ y                (0,0)
     |                    ↓ y
-----+----> x        x →
  (0,0)
```

### ⑧: `Add`
- ベクトルの加算関数
- \(\vec{v}_{new} = \vec{v}_{old} + \vec{g}\)

### ⑨: `vel_`
- 現在の速度ベクトル
- 親クラス（Base）から継承したメンバ変数

### ⑩: `Add`
- ベクトルの加算関数（同じ関数を2回使う）
- \(\vec{p}_{new} = \vec{p}_{old} + \vec{v}\)

### ⑪: `pos_`
- 現在の位置ベクトル
- 親クラスから継承したメンバ変数

### ⑫: `vel_`
- **更新された**速度ベクトル
- ステップ1で重力を加えた後の速度

---

## ?? 重要ポイント：なぜこの順序なのか？

### 正しい順序
```cpp
// ステップ1: 速度を更新
vel_ = Math2D::Add(vel_, gravityVec);

// ステップ2: 位置を更新（更新された速度を使う）
pos_ = Math2D::Add(pos_, vel_);
```

### もし順序を逆にすると？
```cpp
// 間違った順序
pos_ = Math2D::Add(pos_, vel_);      // 古い速度で位置を更新
vel_ = Math2D::Add(vel_, gravityVec); // その後で速度を更新
```

**結果：**
- 1フレーム分、重力の影響が遅れる
- 初速度のまま1フレーム移動してしまう
- 物理的に正しくない

**正しい物理シミュレーション：**
1. 力（重力）を計算
2. 速度を更新
3. 位置を更新

この順序は物理エンジンの基本です。

---

## ?? 考察問題の解答

### Q1: 更新の順序

**順序を逆にした場合：**
```cpp
pos_ = Math2D::Add(pos_, vel_);      // 先に位置更新
vel_ = Math2D::Add(vel_, gravityVec); // 後で速度更新
```

**何が起こるか：**
- 位置の更新に使われる速度が、1フレーム古い速度になる
- 重力の影響が1フレーム遅れて現れる

**正しく動作するか：**
- 見た目上は「ほぼ」正しく動作する
- しかし物理的には正確ではない
- 高速な弾や強い重力では誤差が目立つ

**正しい順序：**
```
今フレームの力（重力）→ 今フレームの速度 → 今フレームの位置
```

---

### Q2: 放物線の計算

**初期条件：**
- 初速度: \(\vec{v_0} = (10, 10)\)
- 重力: \(g = 0.3\)
- 初期位置: \(\vec{p_0} = (0, 0)\)

**フレーム0（初期状態）:**
- 速度: \(\vec{v} = (10, 10)\)
- 位置: \(\vec{p} = (0, 0)\)

**フレーム1:**

1. 速度更新:
   \[
   \vec{v} = (10, 10) + (0, -0.3) = (10, 9.7)
   \]

2. 位置更新:
   \[
   \vec{p} = (0, 0) + (10, 9.7) = (10, 9.7)
   \]

**答え:**
- 速度: \(\vec{v} = (10, 9.7)\)
- 位置: \(\vec{p} = (10, 9.7)\)

**フレーム2:**

1. 速度更新:
   \[
   \vec{v} = (10, 9.7) + (0, -0.3) = (10, 9.4)
   \]

2. 位置更新:
   \[
   \vec{p} = (10, 9.7) + (10, 9.4) = (20, 19.1)
   \]

**答え:**
- 速度: \(\vec{v} = (10, 9.4)\)
- 位置: \(\vec{p} = (20, 19.1)\)

**パターンの発見：**
- v_x は常に 10（一定）
- v_y は毎フレーム 0.3 ずつ減少
- x は毎フレーム 10 ずつ増加（等間隔）
- y の増加量は徐々に小さくなる

---

### Q3: 重力の影響

#### ケース1: 重力 = 0（無重力）

**軌跡：**
```
y
|     ・・・・・・→
|    ・
|   ・
|  ・
| ・
+-----------> x
```
- 直線運動
- 初速度の方向にまっすぐ飛ぶ
- y = x の直線（45°の場合）

#### ケース2: 重力 = 0.3（通常）

**軌跡：**
```
y
|     ・
|    ・ ・
|   ・   ・
|  ・     ・
| ・       ・
+-----------> x
```
- 放物線
- 上昇→最高点→下降
- 美しい弧を描く

#### ケース3: 重力 = 0.6（2倍）

**軌跡：**
```
y
|    ・
|   ・・
|  ・  ・
| ・    ・
+-----------> x
```
- より急な放物線
- すぐに落下する
- 飛距離が短い

**まとめ：**
- 重力が大きいほど弾道が急になる
- 重力が小さいほど遠くまで飛ぶ
- 重力0なら直線運動

---

### Q4: x方向とy方向の独立性

**答え: 影響し合わない（独立している）**

**理由：**

1. **x方向の運動：**
   ```cpp
   vel_.x = vel_.x + 0.0f;  // 加速度なし
   pos_.x = pos_.x + vel_.x; // 等速
   ```
   - v_x は常に一定
   - x は等速で増加

2. **y方向の運動：**
   ```cpp
   vel_.y = vel_.y + (-gravity_); // 加速度あり
   pos_.y = pos_.y + vel_.y;      // 加速度運動
   ```
   - v_y は変化する
   - y は加速度運動

3. **独立性：**
   - x の計算に y の値は使われない
   - y の計算に x の値は使われない
   - 重力ベクトル (0, -g) の x成分が 0

**物理的な意味：**
- これは「ガリレイの相対性原理」の一例
- 横方向と縦方向の運動は独立
- だから放物線は予測可能

**実験で確認：**
```
同時に:
- 弾Aを水平に発射
- 弾Bを真下に落とす
→ 地面に着くのは同時！（y方向は同じ運動）
```

---

## ?? 完成したコード

### Bullet.h
```cpp
#pragma once
#include "Base.h"

class Bullet : public Base
{
public:
    Bullet(const Vector2D& pos, const Vector2D& vel, 
           unsigned int color, float radius);
    ~Bullet();

    void Update() override;
    void Draw() override;

    bool IsActive() const { return isActive_; }
    void SetInactive() { isActive_ = false; }
    float GetRadius() const { return radius_; }

private:
    float radius_;
    bool isActive_;
    float gravity_;
};
```

### Bullet.cpp
```cpp
#include "Bullet.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Bullet::Bullet(const Vector2D& pos, const Vector2D& vel, 
               unsigned int color, float radius)
    : Base(pos, vel, color)
    , radius_(radius)
    , isActive_(true)
    , gravity_(0.3f)
{
    objType = OBJ_TYPE::BULLET;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    if (!isActive_) return;

    // ステップ1: 重力を速度に加える
    Vector2D gravityVec = { 0.0f, -gravity_ };
    vel_ = Math2D::Add(vel_, gravityVec);

    // ステップ2: 速度を位置に加える
    pos_ = Math2D::Add(pos_, vel_);

    // 画面外判定
    if (pos_.x < 0 || pos_.x > WIN_WIDTH || 
        pos_.y < 0 || pos_.y > WIN_HEIGHT)
    {
        isActive_ = false;
    }
}

void Bullet::Draw()
{
    if (!isActive_) return;

    Vector2D screenPos = Math2D::World2Screen(pos_);
    
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)radius_, Color_, TRUE);
}
```

---

## ?? 放物線運動の完全シミュレーション

初速度 \(\vec{v_0} = (10, 10)\)、重力 \(g = 0.3\) の場合：

| フレーム | v_x | v_y | x | y | 状態 |
|---------|-----|-----|---|---|------|
| 0 | 10.0 | 10.0 | 0.0 | 0.0 | 発射 |
| 1 | 10.0 | 9.7 | 10.0 | 9.7 | 上昇 |
| 2 | 10.0 | 9.4 | 20.0 | 19.1 | 上昇 |
| 3 | 10.0 | 9.1 | 30.0 | 28.2 | 上昇 |
| ... | ... | ... | ... | ... | ... |
| 33 | 10.0 | 0.1 | 330.0 | 166.6 | 最高点付近 |
| 34 | 10.0 | -0.2 | 340.0 | 166.4 | 下降開始 |
| 35 | 10.0 | -0.5 | 350.0 | 165.9 | 下降 |
| ... | ... | ... | ... | ... | ... |

**観察：**
- 最高点は約33フレーム後
- 最高到達高さは約166ピクセル
- x方向は等速で進む（10ピクセル/フレーム）
- y方向は上昇時と下降時で対称

---

## ?? 学習のポイント

このワークシートで学んだこと：

1. **等速運動と加速度運動の違い**
   - 等速：速度が一定 → 直線
   - 加速度：速度が変化 → 曲線

2. **ベクトルの独立性**
   - x方向とy方向は独立
   - それぞれ別の運動法則に従う

3. **物理シミュレーションの基本**
   - 力 → 加速度 → 速度 → 位置
   - この順序が重要

4. **重力の本質**
   - 重力は速度を変化させる
   - 位置を直接変化させるのではない

---

## ?? 発展的な理解

### オイラー法（Euler Method）

今回実装した方法は、物理シミュレーションの基本である**オイラー法**です：

```cpp
v = v + a * dt  // dt = 1フレーム
p = p + v * dt
```

より正確な方法として：
- **ルンゲ・クッタ法**
- **ベルレ法**
などがありますが、ゲームではオイラー法で十分です。

### 空気抵抗

現実には空気抵抗があります：
```cpp
vel_ = Math2D::Mul(vel_, 0.99f); // 速度が99%になる
```

これを追加すると、より現実的な弾道になります。

---

## ?? 次のステップ

Bulletクラスが完成したら、次は **WORKSHEET_03_Target_Answer.md** の解答を確認し、
Targetクラスの実装に進みましょう！

的クラスでは、シンプルな実装ながら、当たり判定の準備を整えます。
