# �C��Q�[�������K�C�h - �X�e�b�v�o�C�X�e�b�v

## ?? �͂��߂�

���̃K�C�h�ł́A`Base`�N���X���p�����ĖC��Q�[�������ߒ����A�������鏇�Ԃɉ����Đ������܂��B
�e�X�e�b�v�Łu�Ȃ���������̂��v�𗝉����Ȃ���i�߂Ă����܂��傤�B

---

## ?? ���̃Q�[���Ŋw�Ԃ���

### ���w�I�ȗv�f
- **�x�N�g�����Z**: �ʒu�A���x�A������\��
- **�O�p�֐�**: �p�x��������x�N�g�������
- **�����x�^��**: �d�͂ɂ��������^��
- **�����蔻��**: �~���m�̏Փ˔���

### �v���O���~���O�I�ȗv�f
- **�N���X�݌v**: ���ʕ�����e�N���X�ɂ܂Ƃ߂�
- **�p��**: Base�N���X����@�\���󂯌p��
- **�|�����[�t�B�Y��**: �����C���^�[�t�F�[�X�ňقȂ铮��
- **���͏���**: �L�[���͂̎g������

---

## ?? ���O�����F�N���X�݌v���l����

### �Q�[���ɕK�v�ȃI�u�W�F�N�g

| �I�u�W�F�N�g | ���� | �ŗL�̏�� |
|------------|------|-----------|
| **�C��(Cannon)** | �e�𔭎˂��� | �p�x�A�����x |
| **�e(Bullet)** | ��������`���Ĕ�� | ���a�A�d�� |
| **�I(Target)** | �����蔻��̑Ώ� | ���a�A���������� |

### ���ʂ�����iBase �N���X�ɓ����j

���ׂẴI�u�W�F�N�g�͈ȉ��������Ă��܂��F

```cpp
? �ʒu (pos_)
? ���x (vel_)
? �F (Color_)
? �I�u�W�F�N�g�^�C�v (objType)
```

**�Ȃ����ʉ�����̂��H**
- �R�[�h�̏d���������
- �����e�i���X���₷���Ȃ�
- �z��ňꊇ�Ǘ��ł���

---

## �X�e�b�v1: Base.h �ɃI�u�W�F�N�g�^�C�v��ǉ�

### ?? �Ȃ��K�v�H

�����̃I�u�W�F�N�g��`std::vector<Base*>`�ŊǗ�����Ƃ��A
�u����͖C��Ȃ̂��A�e�Ȃ̂��A�I�Ȃ̂��v����ʂ���K�v������܂��B

### ?? ����

`Base.h`��`OBJ_TYPE`�񋓌^���ȉ��̂悤�ɕύX�F

```cpp
enum OBJ_TYPE
{
    UNKNOWN,     // �s���ȃI�u�W�F�N�g
    PLAYER,      // �v���C���[�i����͖��g�p�j
    BULLET,      // �e
    CANNON,      // �C��
    TARGET,      // �I
    MAX_OBJ_TYPE // �I�u�W�F�N�g�^�C�v�̑���
};
```

### ?? �l���Ă݂悤
- �Ȃ�`enum`���g���̂ł��傤���H
- ���l�ŊǗ��i0,1,2...�j����̂Ɖ����Ⴂ�܂����H

**����**: enum���g�����ƂŁA�R�[�h���ǂ݂₷���A�ԈႢ�ɂ����Ȃ�܂��B
�Ⴆ�� `objType == 2` ��� `objType == OBJ_TYPE::CANNON` �̕����Ӑ}�����m�ł��B

---

## �X�e�b�v2: Cannon �N���X�����i�C��j

### ?? �C��̖���

1. ��ʍ����ɌŒ�
2. ���E�L�[�Ŋp�x��ς���
3. �㉺�L�[�ŏ����x��ς���
4. �X�y�[�X�L�[�Œe�𔭎�

### ?? �C�䂾���������

```cpp
float angle_;           // �C��̊p�x�i���W�A���P�ʁj
float angleSpeed_;      // �p�x�ω��̑����i���W�A��/�t���[���j
float barrelLength_;    // �C�g�̒����i�s�N�Z���j
float bulletSpeed_;     // �e�̏����x�i���݂̐ݒ�l�j
float bulletSpeedMin_;  // �e�̏����x�̍ŏ��l
float bulletSpeedMax_;  // �e�̏����x�̍ő�l
float bulletSpeedStep_; // ���x�ύX���̑�����
```

### ?? Cannon.h �̍쐬

```cpp
#pragma once
#include "Base.h"

class Cannon : public Base
{
public:
    // �R���X�g���N�^�F�ʒu�ƐF���w�肵�ĖC����쐬
    Cannon(const Vector2D& pos, unsigned int color);
    ~Cannon();

    void Update() override;  // ���͏����i�p�x�E���x�̕ύX�j
    void Draw() override;    // �`��i�C��{�̂ƖC�g�j

    // �Q�b�^�[�i�l���擾����֐��j
    float GetAngle() const { return angle_; }           // ���݂̊p�x���擾
    float GetSpeed() const { return bulletSpeed_; }     // ���݂̏����x���擾
    Vector2D GetDirection() const;      // �����x�N�g���i�P�ʃx�N�g���j���擾
    Vector2D GetTipPosition() const;    // �C�g�̐�[�ʒu���擾

private:
    float angle_;           // �C��̊p�x�i���W�A���j
    float angleSpeed_;      // �p�x�ω��̑���
    float barrelLength_;    // �C�g�̒���
    float bulletSpeed_;     // �e�̏����x
    float bulletSpeedMin_;  // �����x�̍ŏ��l
    float bulletSpeedMax_;  // �����x�̍ő�l
    float bulletSpeedStep_; // ���x�ύX�̑�����
};
```

### ?? �d�v�|�C���g�F�p�x�ƕ����x�N�g��

#### �p�x �� �����x�N�g���̕ϊ�

```
�p�x �� (���W�A��) �� �����x�N�g�� (cos ��, sin ��)
```

**��̗�F**
- �� = 0�� (0 rad) �� (1, 0) �E����
- �� = 45�� (��/4 rad) �� (0.707, 0.707) �E�΂ߏ�
- �� = 90�� (��/2 rad) �� (0, 1) �^��

#### �Ȃ������x�N�g���̒�����1�H

```
���x�x�N�g�� = �����x�N�g�� �~ ����
v = d �~ speed
```

����1�̕����x�N�g���ɑ������|���邱�ƂŁA�ȒP�ɑ��x�x�N�g�������܂��B

### ?? Cannon.cpp �̎���

```cpp
#include "Cannon.h"
#include "Math2D.h"
#include "Input.h"
#include <DxLib.h>

Cannon::Cannon(const Vector2D& pos, unsigned int color)
    : Base(pos, { 0.0f, 0.0f }, color)
    , angle_(Math2D::PI / 4.0f)      // �����p�x 45��
    , angleSpeed_(0.02f)              // �p�x�ω����x
    , barrelLength_(50.0f)            // �C�g�̒���
    , bulletSpeed_(15.0f)             // �����x
    , bulletSpeedMin_(10.0f)
    , bulletSpeedMax_(25.0f)
    , bulletSpeedStep_(0.2f)
{
    objType = OBJ_TYPE::CANNON;
}

void Cannon::Update()
{
    // ���L�[: �p�x���グ��i����]�j
    if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
    {
        angle_ += angleSpeed_;
        if (angle_ > Math2D::PI / 2.0f)  // 90�������
        {
            angle_ = Math2D::PI / 2.0f;
        }
    }
    
    // �E�L�[: �p�x��������i�E��]�j
    if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
    {
        angle_ -= angleSpeed_;
        if (angle_ < 0.0f)  // 0��(����)������
        {
            angle_ = 0.0f;
        }
    }

    // ��L�[: �����x���グ��
    if (Input::IsKeepKeyDown(KEY_INPUT_UP))
    {
        bulletSpeed_ += bulletSpeedStep_;
        if (bulletSpeed_ > bulletSpeedMax_)
        {
            bulletSpeed_ = bulletSpeedMax_;
        }
    }

    // ���L�[: �����x��������
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
    
    // �C��{�́i�~�j
    DrawCircle((int)screenPos.x, (int)screenPos.y, 20, Color_, TRUE);
    
    // �C�g�i���j
    Vector2D tip = GetTipPosition();
    Vector2D screenTip = Math2D::World2Screen(tip);
    
    DrawLine((int)screenPos.x, (int)screenPos.y, 
             (int)screenTip.x, (int)screenTip.y, 
             GetColor(255, 255, 0), 5);
}

// �p�x��������x�N�g�������
Vector2D Cannon::GetDirection() const
{
    return Math2D::FromAngle(angle_);
}

// �C�g�̐�[�ʒu���v�Z
Vector2D Cannon::GetTipPosition() const
{
    Vector2D dir = GetDirection();                    // �����x�N�g��
    Vector2D offset = Math2D::Mul(dir, barrelLength_); // �������̃I�t�Z�b�g
    return Math2D::Add(pos_, offset);                 // ���S + �I�t�Z�b�g
}
```

### ?? �l���Ă݂悤

**Q1: �Ȃ� `IsKeepKeyDown()` ���g���̂ł����H**

`IsKeepKeyDown()`�́A�L�[�����������Ă���Ԃ�����true��Ԃ��܂��B
�p�x��A���I�ɕω����������ꍇ�ɓK���Ă��܂��B

**Q2: �p�x�ɏ���E����������̂͂Ȃ��ł����H**

- ���(90��): �^������ɂ͌��ĂȂ��i�����I�ɕs���R�j
- ����(0��): �n�ʂ�艺�ɂ͌��ĂȂ�

---

## �X�e�b�v3: Bullet �N���X�����i�e�j

### ?? �e�̖���

1. �C�䂩�甭�˂����
2. �����x�������Ĕ��
3. �d�͂̉e�����󂯂ĕ�������`��
4. ��ʊO�ɏo���������

### ?? �e�����������

```cpp
float radius_;   // �e�̔��a�i�`��T�C�Y�Ɠ����蔻��Ɏg�p�j
bool isActive_;  // �e���L�����ǂ����i��ʓ��Ȃ�true�A��ʊO�Ȃ�false�j
float gravity_;  // �d�͉����x�i���t���[�����x�ɉ��Z�����l�j
```

### ?? �d�v�|�C���g�F�������^���̎d�g��

#### 1. ���x�ɂ��ʒu�̍X�V

```
�V�����ʒu = �Â��ʒu + ���x
p_new = p_old + v
```

���t���[���A���x�������ʒu���ς��܂��B

#### 2. �d�͂ɂ�鑬�x�̕ω�

```
�V�������x = �Â����x + �d��
v_new = v_old + g
```

���t���[���A�d�͕��������x���ς��܂��B

#### 3. �Ȃ��������ɂȂ�̂��H

```
�t���[��0: v_y = +10     �� �����
�t���[��1: v_y = +10 - 0.3 = +9.7  �� �����x���Ȃ�
�t���[��2: v_y = +9.7 - 0.3 = +9.4 �� ����ɒx���Ȃ�
...
�t���[��N: v_y = 0       �� �ō��_
�t���[��N+1: v_y = -0.3   �� ��������
```

y�����̑��x�����X�Ɍ������A�₪�ĕ��i�������j�ɂȂ邱�ƂŁA
��������`���܂��B

### ?? Bullet.h �̍쐬

```cpp
#pragma once
#include "Base.h"

class Bullet : public Base
{
public:
    // �R���X�g���N�^�F�ʒu�A���x�A�F�A���a���w�肵�Ēe���쐬
    Bullet(const Vector2D& pos, const Vector2D& vel, 
           unsigned int color, float radius);
    ~Bullet();

    void Update() override;  // �ʒu�̍X�V�i�d�͂Ƒ��x�ɂ��ړ��j
    void Draw() override;    // �`��i�~�Ƃ��ĕ\���j

    // �Q�b�^�[�E�Z�b�^�[
    bool IsActive() const { return isActive_; }      // �e���L�����ǂ���
    void SetInactive() { isActive_ = false; }        // �e�𖳌��ɂ���
    float GetRadius() const { return radius_; }      // �e�̔��a���擾

private:
    float radius_;   // �e�̔��a
    bool isActive_;  // �L���t���O
    float gravity_;  // �d�͉����x
};
```

### ?? Bullet.cpp �̎���

```cpp
#include "Bullet.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Bullet::Bullet(const Vector2D& pos, const Vector2D& vel, 
               unsigned int color, float radius)
    : Base(pos, vel, color)      // �e�N���X�̃R���X�g���N�^���Ăяo��
    , radius_(radius)             // �e�̔��a��������
    , isActive_(true)             // �ŏ��͗L��
    , gravity_(0.3f)              // �d�͉����x��ݒ�
{
    objType = OBJ_TYPE::BULLET;  // �I�u�W�F�N�g�^�C�v��ݒ�
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    if (!isActive_) return;  // �����Ȓe�͍X�V���Ȃ�

    // �X�e�b�v1: �d�͂𑬓x�ɉ�����
    Vector2D gravityVec = { 0.0f, -gravity_ };  // �������i���[���h���W�j
    vel_ = Math2D::Add(vel_, gravityVec);       // ���x = ���x + �d��

    // �X�e�b�v2: ���x���ʒu�ɉ�����
    pos_ = Math2D::Add(pos_, vel_);             // �ʒu = �ʒu + ���x

    // ��ʊO����F��ʊO�ɏo���疳���ɂ���
    if (pos_.x < 0 || pos_.x > WIN_WIDTH || 
        pos_.y < 0 || pos_.y > WIN_HEIGHT)
    {
        isActive_ = false;
    }
}

void Bullet::Draw()
{
    if (!isActive_) return;  // �����Ȓe�͕`�悵�Ȃ�

    // ���[���h���W����ʍ��W�ɕϊ�
    Vector2D screenPos = Math2D::World2Screen(pos_);
    
    // �~��`��i�h��Ԃ��j
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)radius_, Color_, TRUE);
}
```

### ?? �l���Ă݂悤

**Q1: �Ȃ��d�͕͂��̒l�Ȃ̂ł����H**

���[���h���W�ł́Ay����������ł��B
�d�͉͂������Ȃ̂ŁAy�����̑��x��**���炷**�i���̒l��������j�K�v������܂��B

**Q2: �d�͂�0�ɂ���Ƃǂ��Ȃ�܂����H**

���x���ω����Ȃ��̂ŁA�܂�������т܂��i�����^���j�B

**Q3: �d�͂�傫������Ƃǂ��Ȃ�܂����H**

���}���ɉ��ɗ�����悤�ɂȂ�܂��i�e�����}�ɂȂ�j�B

---

## �X�e�b�v4: Target �N���X�����i�I�j

### ?? �I�̖���

1. ��ʉE���ɌŒ�
2. �e�Ƃ̓����蔻��
3. �����������Ԃ�ς���

### ?? �I�����������

```cpp
float radius_;  // �I�̔��a�i�`��T�C�Y�Ɠ����蔻��Ɏg�p�j
bool isHit_;    // �����������ǂ����i����������true�j
```

### ?? Target.h �̍쐬

```cpp
#pragma once
#include "Base.h"

class Target : public Base
{
public:
    // �R���X�g���N�^�F�ʒu�A���a�A�F���w�肵�ēI���쐬
    Target(const Vector2D& pos, float radius, unsigned int color);
    ~Target();

    void Update() override;  // �X�V�i����͌Œ�Ȃ̂ŉ������Ȃ��j
    void Draw() override;    // �`��i3�d�̉~�Ƃ��ĕ\���j

    // �Q�b�^�[�E�Z�b�^�[
    bool IsHit() const { return isHit_; }   // �����������ǂ���
    void SetHit() { isHit_ = true; }        // �������Ԃɂ���
    float GetRadius() const { return radius_; }  // ���a���擾

private:
    float radius_;  // �I�̔��a
    bool isHit_;    // ������t���O
};
```

### ?? Target.cpp �̎���

```cpp
#include "Target.h"
#include "Math2D.h"
#include "globals.h"
#include <DxLib.h>

Target::Target(const Vector2D& pos, float radius, unsigned int color)
    : Base(pos, { 0.0f, 0.0f }, color)  // �e�N���X�������i���x��0�j
    , radius_(radius)                    // ���a��������
    , isHit_(false)                      // �ŏ��͓������Ă��Ȃ�
{
    objType = OBJ_TYPE::TARGET;         // �I�u�W�F�N�g�^�C�v��ݒ�
}

Target::~Target()
{
}

void Target::Update()
{
    // ����͌Œ�Ȃ̂ŉ������Ȃ�
    // ���W�ۑ�F�����ō��E�ɓ������Ɩʔ���
}

void Target::Draw()
{
    // ���[���h���W����ʍ��W�ɕϊ�
    Vector2D screenPos = Math2D::World2Screen(pos_);

    // ����������F��ς���i�O���[�A�E�g�j
    unsigned int drawColor = isHit_ ? GetColor(100, 100, 100) : Color_;
    
    // 3�d�̉~�œI��\���i�O�����珇�ɕ`��j
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)radius_, drawColor, FALSE);  // �O�~�i�g�̂݁j
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)(radius_ * 0.6f), drawColor, FALSE);  // ���~
    DrawCircle((int)screenPos.x, (int)screenPos.y, 
               (int)(radius_ * 0.3f), drawColor, FALSE);  // ���~
}
```

---

## �X�e�b�v5: Stage �N���X�ŊǗ�����

### ?? Stage�̖���

1. ���ׂẴI�u�W�F�N�g���Ǘ�
2. �X�V�ƕ`����s��
3. �����蔻����s��
4. UI�\��

### ?? �d�v�|�C���g�F�����蔻��̐��w

#### �~���m�̏Փ˔���

```
���S�Ԃ̋��� �� ���a�̘a  �� �Փ�
```

**�v�Z�菇�F**

1. ���x�N�g�������߂�
   ```
   r = p_target - p_bullet
   ```

2. ���x�N�g���̒����i�����j�����߂�
   ```
   distance = ��(r.x? + r.y?)
   ```

3. ���a�̘a�Ɣ�r
   ```
   if (distance < r_bullet + r_target) �� HIT!
   ```

### ?? Stage.h �̍X�V

```cpp
#pragma once
#include <vector>

// �O���錾�F�w�b�_�t�@�C���̃C���N���[�h�����炷����
class Cannon;
class Bullet;
class Target;

class Stage
{
public:
    Stage();
    ~Stage();
    void Initialize();  // �������i�I�u�W�F�N�g�̐����j
    
    void Update();      // ���t���[���̍X�V����
    void Draw();        // ���t���[���̕`�揈��
    void Release();     // �I�������i����������j

private:
    unsigned long long gameScore_;  // �Q�[���X�R�A
    
    void PlayUpdate();  // �v���C���̍X�V����
    void PlayDraw();    // �v���C���̕`�揈��
    
    void Bullet_vs_Target();         // �e�ƓI�̓����蔻��
    void DeleteInactiveBullet();     // �����Ȓe���폜
    void ShootBullet(Cannon* cannon); // �e�𔭎�
};
```

### ?? Stage.cpp �̎�v����

```cpp
void Stage::Initialize()
{
    objects.clear();     // �I�u�W�F�N�g���X�g���N���A
    stageState = 1;      // �v���C���̏�Ԃɐݒ�
    gameScore_ = 0;      // �X�R�A��������
    isHit = false;       // �q�b�g�t���O��������

    // �C����쐬���ēo�^
    Cannon* cannon = new Cannon(CANNON_POS, CANNON_COLOR);
    AddObject(cannon);

    // �I���쐬���ēo�^
    Target* target = new Target(TARGET_POS, TARGET_RADIUS, TARGET_COLOR);
    AddObject(target);
}

void Stage::PlayUpdate()
{
    // �����蔻��̏���
    Bullet_vs_Target();

    // �����Ȓe���폜
    DeleteInactiveBullet();

    // ���ׂẴI�u�W�F�N�g���X�V
    UpdateAllObjects();

    // �C���T��
    Cannon* cannon = nullptr;
    for (auto& obj : objects)
    {
        if (obj->GetType() == OBJ_TYPE::CANNON)
        {
            cannon = (Cannon*)obj;  // Base*��Cannon*�ɃL���X�g
            break;
        }
    }

    // �X�y�[�X�L�[�������ꂽ��e�𔭎�
    if (cannon != nullptr && Input::IsKeyDown(KEY_INPUT_SPACE))
    {
        ShootBullet(cannon);
    }
}

void Stage::Bullet_vs_Target()
{
    // �L���Ȓe�ƓI���W�߂郊�X�g
    std::vector<Bullet*> activeBullets;
    std::vector<Target*> targets;

    // �I�u�W�F�N�g���X�g����e�ƓI�𒊏o
    for (auto& obj : objects)
    {
        if (obj->GetType() == OBJ_TYPE::BULLET)
        {
            Bullet* b = (Bullet*)obj;  // �L���X�g
            if (b->IsActive())  // �L���Ȓe�̂�
            {
                activeBullets.push_back(b);
            }
        }
        else if (obj->GetType() == OBJ_TYPE::TARGET)
        {
            Target* t = (Target*)obj;  // �L���X�g
            if (!t->IsHit())  // �܂��������Ă��Ȃ��I�̂�
            {
                targets.push_back(t);
            }
        }
    }

    // ���ׂĂ̒e�ƓI�̑g�ݍ��킹�œ����蔻��
    for (auto& bullet : activeBullets)
    {
        for (auto& target : targets)
        {
            // ���x�N�g�����v�Z
            Vector2D diff = Math2D::Sub(bullet->GetPos(), target->GetPos());
            
            // �������v�Z�i�x�N�g���̒����j
            float dist = Math2D::Length(diff);
            
            // �Փ˔��苗���i���a�̘a�j
            float collisionDist = bullet->GetRadius() + target->GetRadius();
            
            // �Փ˔���F���������a�̘a��菬������Γ�����
            if (dist < collisionDist)
            {
                target->SetHit();        // �I�𓖂����Ԃ�
                bullet->SetInactive();   // �e�𖳌���
                isHit = true;            // HIT�t���O�𗧂Ă�
                gameScore_ += 100;       // �X�R�A�����Z
            }
        }
    }
}

void Stage::ShootBullet(Cannon* cannon)
{
    if (cannon == nullptr) return;  // �C�䂪�Ȃ���Ή������Ȃ�

    // �C�g�̐�[�ʒu���擾
    Vector2D pos = cannon->GetTipPosition();
    
    // �����x�N�g�����擾�i�P�ʃx�N�g���j
    Vector2D dir = cannon->GetDirection();
    
    // ���x�x�N�g�� = �����x�N�g�� �~ ����
    Vector2D v = Math2D::Mul(dir, cannon->GetSpeed());

    // �e�𐶐����ăI�u�W�F�N�g���X�g�ɒǉ�
    Bullet* b = new Bullet(pos, v, BULLET_COLOR, BULLET_RADIUS);
    AddObject(b);
}
```

---

## ?? �܂Ƃ߁F�w�񂾂���

### ���w�I�ȗ���

1. **�x�N�g���̉��Z**: �ʒu + ���x�A���x + �d��
2. **�X�J���[�{**: �����x�N�g�� �~ ����
3. **�x�N�g���̒���**: �����̌v�Z
4. **�O�p�֐�**: �p�x �� �����x�N�g��
5. **�����x�^��**: �d�͂ŕ�����

### �v���O���~���O�̗���

1. **�p��**: ���ʕ�����Base�ɂ܂Ƃ߂�
2. **�|�����[�t�B�Y��**: `std::vector<Base*>`�ňꊇ�Ǘ�
3. **�J�v�Z����**: �N���X���Ƃɖ����𕪂���
4. **���͂̎g������**: `IsKeyDown` vs `IsKeepKeyDown`

---

## ?? �l�@���̓���

### Q1: Base�N���X�ɂ͉����������܂������H

�ʒu�A���x�A�F�A�I�u�W�F�N�g�^�C�v

### Q2: �e�N���X�̌ŗL���́H

- Cannon: �p�x�A�����x�A�C�g�̒���
- Bullet: ���a�A�L���t���O�A�d��
- Target: ���a�A�q�b�g�t���O

### Q3: �Ȃ��C��̉�]�ɂ�`IsKeepKeyDown()`�H

�A���I�Ɋp�x��ω�������������B
���������Ă���Ԃ����Ɖ�]����K�v������B

### Q4: �Ȃ��e�̔��˂ɂ�`IsKeyDown()`�H

1��̃L�[������1���������˂���������B
���������Ă��A�˂���Ȃ��悤�ɂ���B

### Q5: �����x�N�g���Ƒ��x�x�N�g���̈Ⴂ�́H

- �����x�N�g��: ����1�A����������\��
- ���x�x�N�g��: �����Ƒ����̗�����\��

### Q6: �d�͂ŕ������ɂȂ闝�R�́H

�d�͂����x�ɉe�����A���x���ς�邱�Ƃ�
�ʒu�̕ω��̎d�����ς�邩��B
����y�����̑��x�����X�Ɍ��������ɂȂ邱�ƂŁA
�㏸���ō��_�����~ �Ƃ����O���ɂȂ�B

### Q7: `Math2D::Sub()`��`Math2D::Length()`�̎g�����́H

```cpp
Vector2D diff = Math2D::Sub(pos1, pos2);  // ���x�N�g��
float distance = Math2D::Length(diff);    // ����
```

### Q8: �N���X�𕪂��闘�_�́H

- �R�[�h���ǂ݂₷��
- �ύX���Ǐ��������
- �ė��p���₷��
- �e�X�g���₷��

---

## ?? ���̃X�e�b�v�F���W�ۑ�

�]�T������Έȉ��ɒ��킵�Ă݂܂��傤�F

1. **�^�[�Q�b�g�𓮂���**: `Target::Update()`�ō��E�Ɉړ�
2. **�����̃^�[�Q�b�g**: �z��ŕ����̓I���Ǘ�
3. **�e������**: �c�e����\�����A�����[�h�@�\
4. **�O�՗\��**: ���ˑO�ɒe����_���ŕ\��
5. **�s��ϊ�**: �C�g�̐�[�ʒu���s��Ōv�Z

����ŖC��Q�[���̎����K�C�h�͊����ł��I
���ۂɓ������āA�����Ɠ����̊֌W���m���߂܂��傤�B
