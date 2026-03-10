# ワークシート03: Target クラス（的）- 解答

## 📝 解答と解説

---

## ✅ 問題1の解答

```cpp
#pragma once
#include "Base.h"

class Target : public 【①Base】
{
public:
    Target(const Vector2D& pos, float radius, unsigned int color);
    ~Target();

    void Update() override;
    void Draw() override;

    bool IsHit() const { return 【②isHit_】; }
    void SetHit() { 【②isHit_】 = true; }
    float GetRadius() const { return 【③radius_】; }

private:
    float 【③radius_】;  // 的の半径
    bool 【②isHit_】;    // 当たったかどうか
};
```

**解説：**
- ①: `Base` - すべてのゲームオブジェクトの親クラス
- ②: `isHit_` - 弾が当たったかどうかを管理するフラグ
- ③: `radius_` - 的の半径（描画と当たり判定に使用）

---

## ✅ 問題2の解答

```cpp
Target::Target(const Vector2D& pos, float radius, unsigned int color)
    : 【④Base】(pos, { 0.0f, 0.0f }, color)  // 親クラス初期化
    , radius_(【⑤radius】)
    , isHit_(【⑥false】)                     // 最初は当たっていない
{
    objType = OBJ_TYPE::【⑦TARGET】;
}
```

**解説：**

### ④: `Base`
- 親クラスのコンストラクタを呼び出す
- 位置、速度、色を初期化

### ⑤: `radius`
- 引数で受け取った半径を使う
- コンストラクタの引数名と同じ

### ⑥: `false`
- 的を生成した直後は当たっていない状態
- 弾が当たったら `SetHit()` で `true` に変更される

### ⑦: `TARGET`
- 的を表すオブジェクトタイプ
- `Base.h` で定義されている列挙型

**速度を { 0.0f, 0.0f } にする理由：**
- 的は**静止している**（動かない）
- 速度が0なので、位置は変化しない
- もし動かしたい場合は、速度を変更するか、`Update()` で位置を変更する

---

## ?? 問題3の解答

```cpp
void Target::Update()
{
    // 【⑧今回は固定なので何もしない】
    // 発展課題：ここで左右に動かすと面白い
}
```

**解説：**

### なぜ何も書かなくてよいのか？

1. **静止オブジェクト：**
   - 的は動かない
   - 速度が0なので、位置の更新も不要

2. **仮想関数のオーバーライド：**
   - `Base` クラスで `virtual void Update() = 0;` と定義されている
   - 純粋仮想関数なので、派生クラスで必ず実装が必要
   - 処理が空でも関数自体は定義する必要がある

**正しい書き方の例：**

```cpp
// 方法1: 何も書かない
void Target::Update()
{
}

// 方法2: コメントを入れる（推奨）
void Target::Update()
{
    // 今回は固定なので何もしない
}

// 方法3: 将来の拡張を考慮
void Target::Update()
{
    // TODO: 発展課題で動かす処理を追加
}
```

---

## ?? 考察問題の解答

### Q1: 静止オブジェクトの Update()

**答え：** C++の仮想関数の仕組みのため

**詳しい説明：**

1. **Baseクラスの定義：**
   ```cpp
   class Base
   {
   public:
       virtual void Update() = 0;  // 純粋仮想関数
   };
   ```

2. **純粋仮想関数：**
   - `= 0` が付いている仮想関数
   - 派生クラスで**必ず**実装が必要
   - 実装しないとコンパイルエラー

3. **なぜこの仕組みがあるのか？**
   ```cpp
   // Stageクラスでオブジェクトを一括管理
   std::vector<Base*> objects;
   
   // すべてのオブジェクトを統一的に扱える
   for (auto& obj : objects)
   {
       obj->Update();  // 各クラスのUpdate()が呼ばれる
   }
   ```
   - `Target` の `Update()` は何もしない
   - `Bullet` の `Update()` は位置を更新する
   - しかし、**同じインターフェース**で呼び出せる

**ポリモーフィズムの利点：**
- オブジェクトの種類を気にせず一括処理できる
- 新しいクラスを追加しても既存のコードを変更しなくてよい

---

### Q2: 三項演算子

**元のコード：**
```cpp
unsigned int drawColor = isHit_ ? GetColor(100, 100, 100) : Color_;
```

**if-else 文で書き直すと：**
```cpp
unsigned int drawColor;
if (isHit_)
{
    drawColor = GetColor(100, 100, 100);  // 灰色
}
else
{
    drawColor = Color_;  // 元の色
}
```

**比較：**

| 項目 | 三項演算子 | if-else |
|------|----------|---------|
| 行数 | 1行 | 7行 |
| 読みやすさ | 慣れれば簡潔 | 明確 |
| 変数宣言 | 初期化と同時 | 先に宣言が必要 |
| 使い所 | 単純な条件分岐 | 複雑な処理 |

**三項演算子の構文：**
```cpp
条件式 ? 真の場合の値 : 偽の場合の値
```

---

### Q3: 3重の円の計算

**半径が 30 の場合：**

| 円 | 計算式 | 半径（ピクセル） |
|----|--------|-----------------|
| 外円 | `radius_` | 30.0 |
| 中円 | `radius_ * 0.6f` | 18.0 |
| 内円 | `radius_ * 0.3f` | 9.0 |

**計算過程：**

1. **外円：**
   - `radius_` = 30.0

2. **中円：**
   - 30.0 × 0.6 = 18.0

3. **内円：**
   - 30.0 × 0.3 = 9.0

**比率：**
- 外円 : 中円 : 内円 = 10 : 6 : 3
- 等間隔ではなく、内側ほど間隔が狭い（的らしい見た目）

**図解：**
```
        ●●●●●●●●●     ← 外円（半径30）
      ●●        ●●
    ●●   ●●●●   ●●   ← 中円（半径18）
    ●●   ●●●●   ●●
      ●●        ●●
        ●●●●●●●●●

中心の小円（半径9）   ← 内円
```

---

### Q4: 発展課題 - 的を動かす

**考え方1: 左右に往復運動**

```cpp
class Target : public Base
{
private:
    float speed_;        // 移動速度
    float leftLimit_;    // 左端の限界
    float rightLimit_;   // 右端の限界
};

void Target::Update()
{
    // x座標を更新
    pos_.x += speed_;
    
    // 範囲外に出たら反転
    if (pos_.x > rightLimit_)
    {
        pos_.x = rightLimit_;
        speed_ *= -1.0f;  // 左向きに
    }
    else if (pos_.x < leftLimit_)
    {
        pos_.x = leftLimit_;
        speed_ *= -1.0f;  // 右向きに
    }
}
```

**考え方2: sin波で上下運動**

```cpp
class Target : public Base
{
private:
    float time_;           // 経過時間
    float amplitude_;      // 振幅
    float frequency_;      // 周波数
    Vector2D initialPos_;  // 初期位置
};

void Target::Update()
{
    time_ += 0.016f;  // 約60FPS
    
    // y座標をsin波で変化
    pos_.y = initialPos_.y + amplitude_ * sin(frequency_ * time_);
}
```

**考え方3: 円運動**

```cpp
void Target::Update()
{
    time_ += 0.05f;
    
    // 円の中心からの相対位置
    float offsetX = radius_ * cos(time_);
    float offsetY = radius_ * sin(time_);
    
    pos_.x = centerX + offsetX;
    pos_.y = centerY + offsetY;
}
```

---

## ?? 完成したコード

### Target.h
```cpp
#pragma once
#include "Base.h"

class Target : public Base
{
public:
    Target(const Vector2D& pos, float radius, unsigned int color);
    ~Target();

    void Update() override;
    void Draw() override;

    bool IsHit() const { return isHit_; }
    void SetHit() { isHit_ = true; }
    float GetRadius() const { return radius_; }

private:
    float radius_;
    bool isHit_;
};
```

### Target.cpp
```cpp
#include "Target.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Target::Target(const Vector2D& pos, float radius, unsigned int color)
    : Base(pos, { 0.0f, 0.0f }, color)
    , radius_(radius)
    , isHit_(false)
{
    objType = OBJ_TYPE::TARGET;
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

## ?? 学習のポイント

このワークシートで学んだこと：

1. **静止オブジェクトの実装**
   - 速度を0に設定
   - `Update()` は空でもよい

2. **仮想関数とオーバーライド**
   - 純粋仮想関数は必ず実装が必要
   - 処理が空でも定義は必要

3. **状態管理**
   - `isHit_` フラグで状態を管理
   - ゲッター/セッターで安全にアクセス

4. **描画の工夫**
   - 複数の円で「的らしい」見た目
   - 三項演算子で状態による色変更

---

## ?? 設計のポイント

### カプセル化の例

**良い設計：**
```cpp
class Target
{
public:
    bool IsHit() const { return isHit_; }
    void SetHit() { isHit_ = true; }
    
private:
    bool isHit_;  // 外部から直接変更できない
};

// 使用例
if (!target->IsHit())
{
    target->SetHit();
}
```

**悪い設計：**
```cpp
class Target
{
public:
    bool isHit_;  // 外部から直接アクセス可能
};

// 使用例（危険）
target->isHit_ = true;  // タイポの可能性、履歴が追えない
```

**カプセル化の利点：**
- データの整合性を保てる
- 変更時の影響範囲が限定される
- デバッグしやすい

---

## ?? 次のステップ

Targetクラスが完成したら、次は **WORKSHEET_04_Stage_Answer.md** の解答を確認し、
最後のワークシート（当たり判定）に進みましょう！

当たり判定では、今まで学んだすべての要素が組み合わさります：
- Cannon: 弾を発射
- Bullet: 放物線で飛ぶ
- Target: 的として待つ
- **Stage: 弾と的の衝突を判定** ← 次はここ！

砲台ゲームの完成まであと一歩です！??
