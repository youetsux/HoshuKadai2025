# ワークシート04: Stage クラス（当たり判定）- 解答

## ?? 解答と解説

---

## ?? 問題1の解答

```cpp
void Stage::ShootBullet(Cannon* cannon)
{
    if (cannon == nullptr) return;

    // 砲身の先端位置を取得
    Vector2D pos = cannon->【①GetTipPosition()】;
    
    // 方向ベクトルを取得（単位ベクトル）
    Vector2D dir = cannon->【②GetDirection()】;
    
    // 速度ベクトル = 方向ベクトル × 速さ
    Vector2D v = Math2D::【③Mul】(dir, cannon->【④GetSpeed()】);

    // 弾を生成してオブジェクトリストに追加
    Bullet* b = new Bullet(pos, v, BULLET_COLOR, BULLET_RADIUS);
    AddObject(b);
}
```

**解説：**

### ①: `GetTipPosition()`
- 砲身の先端位置を取得
- Cannonクラスで実装した関数
- 弾はここから発射される

### ②: `GetDirection()`
- 方向ベクトルを取得
- 長さ1の単位ベクトル
- 砲台の向いている方向

### ③: `Mul`
- ベクトルのスカラー倍
- `Math2D::Mul(v, s)` = \(s \times \vec{v}\)

### ④: `GetSpeed()`
- 弾の初速度（速さ）を取得
- 上下キーで調整した値

**数式の流れ：**

\[
\vec{v} = s \cdot \vec{d}
\]

- \(\vec{d}\): 方向ベクトル（長さ1）
- \(s\): 速さ（スカラー）
- \(\vec{v}\): 速度ベクトル

**例：**
- 方向: \(\vec{d} = (0.707, 0.707)\) ← 45°
- 速さ: \(s = 20\)
- 速度: \(\vec{v} = 20 \times (0.707, 0.707) = (14.14, 14.14)\)

---

## ?? 問題2の解答

```cpp
void Stage::Bullet_vs_Target()
{
    std::vector<Bullet*> activeBullets;
    std::vector<Target*> targets;

    // オブジェクト抽出（提供済み部分）
    for (auto& obj : objects)
    {
        if (obj->GetType() == OBJ_TYPE::BULLET)
        {
            Bullet* b = (Bullet*)obj;
            if (b->IsActive())
            {
                activeBullets.push_back(b);
            }
        }
        else if (obj->GetType() == OBJ_TYPE::TARGET)
        {
            Target* t = (Target*)obj;
            if (!t->IsHit())
            {
                targets.push_back(t);
            }
        }
    }

    // 当たり判定
    for (auto& bullet : activeBullets)
    {
        for (auto& target : targets)
        {
            // ステップ1: 差ベクトルを計算
            Vector2D diff = Math2D::【⑤Sub】(bullet->GetPos(), target->GetPos());
            
            // ステップ2: 距離を計算（ベクトルの長さ）
            float dist = Math2D::【⑥Length】(【⑦diff】);
            
            // ステップ3: 衝突判定距離（半径の和）
            float collisionDist = bullet->【⑧GetRadius()】 + target->【⑨GetRadius()】;
            
            // ステップ4: 衝突判定
            if (dist 【⑩<】 collisionDist)
            {
                target->SetHit();
                bullet->SetInactive();
                isHit = true;
                gameScore_ += 100;
            }
        }
    }
}
```

**解説：**

### ⑤: `Sub`
- ベクトルの減算
- `Math2D::Sub(a, b)` = \(\vec{a} - \vec{b}\)
- 2つの位置ベクトルの差 = 差ベクトル

### ⑥: `Length`
- ベクトルの長さを計算
- `Math2D::Length(v)` = \(|\vec{v}| = \sqrt{v_x^2 + v_y^2}\)
- 差ベクトルの長さ = 2点間の距離

### ⑦: `diff`
- ステップ1で計算した差ベクトル
- この長さが距離になる

### ⑧, ⑨: `GetRadius()`
- 弾と的の半径を取得
- 両方の半径を足すと「触れ合う距離」

### ⑩: `<` または `<=`
- **推奨: `<`**
- ちょうど触れている状態（`==`）も当たりに含めるなら `<=`
- 実用上は `<` で十分

---

## ?? 当たり判定の数式解説

### ステップ1: 差ベクトル

弾の位置 \(\vec{p_b} = (p_{bx}, p_{by})\)
的の位置 \(\vec{p_t} = (p_{tx}, p_{ty})\)

差ベクトル：
\[
\vec{r} = \vec{p_b} - \vec{p_t} = (p_{bx} - p_{tx},\ p_{by} - p_{ty})
\]

**図解：**
```
     的          弾
     ●--------->●
     pt    r    pb

r = pb - pt （的から弾への矢印）
```

### ステップ2: 距離

差ベクトルの長さ：
\[
d = |\vec{r}| = \sqrt{r_x^2 + r_y^2}
\]

これは**ピタゴラスの定理**：
```
        pb(弾)
       /|
      / |
  d  /  | ry
    /   |
   /____|
  pt    rx
  (的)
  
d? = rx? + ry?
d = √(rx? + ry?)
```

### ステップ3: 判定

衝突条件：
\[
d < r_b + r_t
\]

**図解：**
```
衝突している:
   ●●●●●
  ●  ○○○○○
 ●  ○○   ○○
●  ○○     ○○  ← 円が重なっている
 ● ○○     ○○
  ●○○   ○○
   ●○○○○○

d < rb + rt


衝突していない:
   ●●●●●      ○○○○○
  ●     ●    ○○   ○○
 ●       ●  ○○     ○○  ← 円が離れている
  ●     ●    ○○   ○○
   ●●●●●      ○○○○○

d >= rb + rt
```

---

## ?? 考察問題の解答

### Q1: 差ベクトルの意味

**答え:** 的から弾への方向と距離を表すベクトル

```cpp
Vector2D diff = Math2D::Sub(bullet->GetPos(), target->GetPos());
// diff = 弾の位置 - 的の位置
```

**図示：**
```
       弾(100, 100)
        ●
       /
      /  diff = (-8, 0)
     /
    ●
  的(108, 100)

diff = (100, 100) - (108, 100) = (-8, 0)
```

**意味：**
- x成分 = -8: 的から見て弾は左に8ピクセル
- y成分 = 0: 的と弾は同じ高さ

---

### Q2: 距離の計算

**なぜ差ベクトルの長さが距離になるのか？**

**数学的証明：**

2点 \(A(x_1, y_1)\) と \(B(x_2, y_2)\) の距離 \(d\) は：

\[
d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}
\]

差ベクトル \(\vec{r} = B - A = (x_2 - x_1, y_2 - y_1)\) の長さは：

\[
|\vec{r}| = \sqrt{r_x^2 + r_y^2} = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}
\]

∴ \(d = |\vec{r}|\)

**直感的理解：**
```
    B
    ●
   /|
  / |
 /  | y2-y1
/   |
/    |
A----+
 x2-x1

三平方の定理より:
距離? = (x2-x1)? + (y2-y1)?
距離 = √((x2-x1)? + (y2-y1)?)
```

---

### Q3: 判定条件

**`dist < collisionDist` vs `dist <= collisionDist`**

| 条件 | 意味 | 使い分け |
|------|------|----------|
| `<` | 円が重なっている | **推奨** |
| `<=` | 円が接触または重なっている | 厳密さが必要な場合 |

**理由：**

1. **浮動小数点の誤差：**
   - `dist == collisionDist` は完全一致が必要
   - 実際には誤差で一致しない可能性

2. **ゲームの実用性：**
   - ちょうど触れている状態は稀
   - `<` で十分に機能する

3. **ピクセル単位の描画：**
   - 1ピクセル以下の差は見えない

**推奨：**
```cpp
if (dist < collisionDist)  // これを使う
```

---

### Q4: 計算量

**弾が10個、的が5個の場合：**

```
判定回数 = 弾の数 × 的の数
         = 10 × 5
         = 50回
```

**弾がN個、的がM個の場合：**

\[
\text{判定回数} = N \times M
\]

これを**O(N × M)**と表記します（計算量の表記法）。

**コードの構造：**
```cpp
for (auto& bullet : activeBullets)      // N回ループ
{
    for (auto& target : targets)        // M回ループ
    {
        // 判定処理 → N × M回実行される
    }
}
```

---

### Q5: 最適化

**弾が1000個、的が1000個の場合：**

\[
\text{判定回数} = 1000 \times 1000 = 1,000,000\text{回}
\]

毎フレーム100万回の計算！これは重い。

**最適化方法：**

#### 1. 空間分割（グリッド）

画面を格子状に分割し、近くのオブジェクトだけ判定：

```
+---+---+---+---+
| □ | □ | ● | □ |  弾●と的○が
+---+---+---+---+  同じマスか隣のマスの
| □ | ○ | ● | □ |  場合だけ判定
+---+---+---+---+
| □ | □ | □ | □ |
+---+---+---+---+
```

**効果:** O(N × M) → O(N + M)

#### 2. 四分木（QuadTree）

空間を再帰的に分割：

```
+-------+-------+
|       |   ●   |
|   ○   +---+---+
|       | ● | □ |
+-------+---+---+
|       |       |
|   □   |   □   |
+-------+-------+
```

**効果:** O(N × M) → O(N log M)

#### 3. 距離の早期判定（最も簡単）

```cpp
// 最適化前
float dist = Math2D::Length(diff);  // √の計算（重い）
if (dist < collisionDist)

// 最適化後
float distSq = Math2D::LengthSquared(diff);  // √なし（軽い）
float collisionDistSq = collisionDist * collisionDist;
if (distSq < collisionDistSq)
```

**理由:**
- \(\sqrt{x}\) の計算は重い
- \(x^2\) の計算は軽い
- \(d < r\) ⇔ \(d^2 < r^2\) （同じ判定結果）

---

## ?? 完成したコード

### Stage.cpp（抜粋）

```cpp
void Stage::ShootBullet(Cannon* cannon)
{
    if (cannon == nullptr) return;

    Vector2D pos = cannon->GetTipPosition();
    Vector2D dir = cannon->GetDirection();
    Vector2D v = Math2D::Mul(dir, cannon->GetSpeed());

    Bullet* b = new Bullet(pos, v, BULLET_COLOR, BULLET_RADIUS);
    AddObject(b);
}

void Stage::Bullet_vs_Target()
{
    std::vector<Bullet*> activeBullets;
    std::vector<Target*> targets;

    for (auto& obj : objects)
    {
        if (obj->GetType() == OBJ_TYPE::BULLET)
        {
            Bullet* b = (Bullet*)obj;
            if (b->IsActive())
            {
                activeBullets.push_back(b);
            }
        }
        else if (obj->GetType() == OBJ_TYPE::TARGET)
        {
            Target* t = (Target*)obj;
            if (!t->IsHit())
            {
                targets.push_back(t);
            }
        }
    }

    for (auto& bullet : activeBullets)
    {
        for (auto& target : targets)
        {
            Vector2D diff = Math2D::Sub(bullet->GetPos(), target->GetPos());
            float dist = Math2D::Length(diff);
            float collisionDist = bullet->GetRadius() + target->GetRadius();
            
            if (dist < collisionDist)
            {
                target->SetHit();
                bullet->SetInactive();
                isHit = true;
                gameScore_ += 100;
            }
        }
    }
}
```

---

## ?? 学習のポイント

このワークシートで学んだこと：

1. **ベクトルの減算**
   - 2点間の相対位置を表す
   - 差ベクトル = 終点 - 始点

2. **ベクトルの長さ**
   - ピタゴラスの定理の応用
   - 2点間の距離を計算

3. **円の衝突判定**
   - 中心間距離 < 半径の和
   - ゲームでよく使う基本技術

4. **計算量の考え方**
   - 二重ループは O(N × M)
   - 最適化の必要性

---

## ?? 発展的な話題

### 他の当たり判定

#### 1. 矩形（四角形）同士
```cpp
bool IsCollision(Rect a, Rect b)
{
    return (a.left < b.right && a.right > b.left &&
            a.top < b.bottom && a.bottom > b.top);
}
```

#### 2. 円と矩形
```cpp
// 矩形の最も近い点を求めて、円との距離を計算
```

#### 3. 多角形同士（高度）
- 分離軸定理（SAT）
- GJKアルゴリズム

---

## ?? おめでとうございます！

すべてのワークシートが完成しました！

### 習得したスキル：

| 分野 | 内容 |
|------|------|
| **数学** | 三角関数、ベクトル演算、距離計算 |
| **物理** | 等速運動、加速度運動、放物線 |
| **プログラミング** | クラス設計、継承、ポリモーフィズム |
| **ゲーム開発** | 当たり判定、オブジェクト管理 |

### これからの学習：

1. **3D への拡張**
   - ベクトルがz成分を持つ
   - 基本的な考え方は同じ

2. **物理エンジン**
   - 衝突応答（跳ね返り）
   - 摩擦、反発係数

3. **AI**
   - 敵の移動パターン
   - 追跡アルゴリズム

4. **エフェクト**
   - パーティクルシステム
   - シェーダー

**次のステップに進む準備ができました！**
今回の経験を活かして、さらに複雑なゲームを作っていきましょう！??
