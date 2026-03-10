# 砲台ゲーム - ゲーム数学補習課題

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

GE1Aゲーム数学低点学生向けの補習課題です。
DxLibを使った砲台ゲームを作成しながら、ベクトル演算と放物線運動を学びます。

---

## 🎮 デモ

砲台から弾を発射して、的に当てるシンプルなゲームです。

### 操作方法
- **LEFT/RIGHT キー**: 砲台の角度を調整
- **UP/DOWN キー**: 弾の初速度を調整
- **SPACE キー**: 弾を発射

### デモ動画
<iframe width="560" height="315" src="https://www.youtube.com/embed/IMndUdyj8QI?si=OIAZnc5L503zQM80" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

---


## 🎯 学習目標

この課題を通して、以下の数学的概念を実践的に学習します：

### 三角関数
- 角度（ラジアン）から方向ベクトル $(\cos\theta, \sin\theta)$ への変換
- 度とラジアンの変換

### ベクトル演算
- ベクトルの加算: $\vec{a} + \vec{b}$
- ベクトルの減算: $\vec{a} - \vec{b}$
- スカラー倍: $k \cdot \vec{v}$
- ベクトルの長さ: $|\vec{v}| = \sqrt{v\_x^2 + v\_y^2}$

### 物理シミュレーション
- 等速運動: $\vec{p}_{\text{new}} = \vec{p}\_{\text{old}} + \vec{v}$
- 加速度運動: $\vec{v}\_{\text{new}} = \vec{v}\_{\text{old}} + \vec{a}$
- 重力による放物線運動

### 当たり判定
- 2点間の距離
- 円同士の衝突判定: $\text{distance} \leq r_1 + r_2$

---

## 📥 ダウンロード・セットアップ

### 1. プロジェクトをダウンロード

**方法A: ZIP ダウンロード**
1. [GitHubリポジトリ](https://github.com/youetsux/HoshuKadai2025)にアクセス
2. 「Code」→「Download ZIP」をクリック
3. ZIPを解凍

**方法B: Git クローン**
```bash
git clone https://github.com/youetsux/HoshuKadai2025.git
```

### 2. DxLib の設定

DxLibのパスをプロジェクトに設定してください。
- プロジェクトのプロパティ → VC++ディレクトリ
- インクルードディレクトリとライブラリディレクトリにDxLibのパスを追加

### 3. ビルド＆実行

`HoshuKadai.sln` を開いてビルドしてください。

**注意:** 初期状態では一部の機能が未実装なので、正しく動作しません。
ワークシートに従って実装を完成させてください。

---

## 📝 課題の進め方

### ステップ1: ワークシートを読む
各ワークシートには、数式と実装手順が詳しく書かれています。

### ステップ2: TODOを探す
ソースコード内に `// TODO:` というコメントがあります。
そこが実装すべき箇所です。

### ステップ3: 実装する
ワークシートの説明を参考に、TODOの箇所を実装します。

### ステップ4: ビルド＆テスト
実装したらビルドして、実際に動作を確認します。

---


## 📚 ワークシート一覧

### [ワークシート01: Cannon クラス（砲台）](WORKSHEET_01_Cannon_Problem.md)
**学習内容:**
- 三角関数（$\sin$, $\cos$）を使った角度から方向ベクトルへの変換
- ベクトルのスカラー倍
- ベクトルの加算

**実装する関数:**
- `GetDirection()` - 角度から方向ベクトルを作る
- `GetTipPosition()` - 砲身の先端位置を計算

**👉 [ワークシート01の詳細はこちら](WORKSHEET_01_Cannon_Problem.md)**

---

### [ワークシート02: Bullet クラス（弾）](WORKSHEET_02_Bullet_Problem.md)
**学習内容:**
- 等速運動と加速度運動
- 重力による放物線運動
- 速度と位置の更新

**実装する関数:**
- `Update()` - 重力を考慮した放物線運動

**👉 [ワークシート02の詳細はこちら](WORKSHEET_02_Bullet_Problem.md)**

---

### [ワークシート03: Target クラス（的）](WORKSHEET_03_Target_Problem.md)
**学習内容:**
- 静止オブジェクトの実装
- 状態管理（当たり判定）
- 仮想関数とオーバーライド

**実装する関数:**
- `Update()` - 空の実装でOK
- `Draw()` - 3重の円で的を表現

**👉 [ワークシート03の詳細はこちら](WORKSHEET_03_Target_Problem.md)**

---

### [ワークシート04: Stage クラス（当たり判定）](WORKSHEET_04_Stage_Problem.md)
**学習内容:**
- 2点間の距離計算
- 差ベクトルの利用
- 円同士の衝突判定

**実装する関数:**
- `ShootBullet()` - 弾を発射する
- `Bullet_vs_Target()` - 弾と的の当たり判定

**👉 [ワークシート04の詳細はこちら](WORKSHEET_04_Stage_Problem.md)**

---

## ✅ 完成チェックリスト

すべての実装が終わったら、以下を確認してください：

- [ ] コンパイルエラーがない
- [ ] 左右キーで砲台の角度が変わる
- [ ] 砲身が正しい方向を向いている
- [ ] スペースキーで弾が発射される
- [ ] 弾が放物線を描いて飛ぶ
- [ ] 弾が的に当たると色が変わる
- [ ] 弾が的に当たると「HIT!」が表示される
- [ ] 的に当たった後の弾は消える
- [ ] 画面外に出た弾は消える

---

## 🚀 発展課題

基本課題が完成したら、以下に挑戦してみましょう：

1. **複数の的**
   - 異なる位置に3つの的を配置
   - それぞれ点数を変える

2. **スコア表示**
   - 何発で当てたか表示
   - 命中率の計算

3. **軌跡予測**
   - 発射前に弾道を点線で表示

4. **的を動かす**
   - 左右に往復運動
   - $\sin$ 波で上下運動

5. **パーティクル効果**
   - 当たったときに爆発エフェクト

6. **サウンド**
   - 発射音、ヒット音、BGM

---

## 📖 参考資料

- [実装ガイド](MIGRATION_GUIDE.md) - 詳細な実装手順
- [解答例](WORKSHEET_01_Cannon_Answer.md) - 詰まったら参照

---

## 💬 質問・バグ報告

質問やバグ報告は、[GitHubのIssues](https://github.com/youetsux/HoshuKadai2025/issues)でお願いします。

---

## 📜 ライセンス

このプロジェクトはMITライセンスの下で公開されています。

---

## 👨‍🏫 作成者

ょぅぇっ＠ゲーム数学担当

**最終更新**: 2026年3月
