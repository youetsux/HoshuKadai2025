#pragma once
#include <vector>

class Cannon;
class Bullet;
class Target;

class Stage
{
public:
	Stage();
	~Stage();
	void Initialize();
	void TitleUpdate();
	void PlayUpdate();
	void GameOverUpdate();

	void TitleDraw();
	void PlayDraw();
	void GameOverDraw();

	void Update();
	void Draw();
	void Release();
private:
	unsigned long long gameScore_;
	void Bullet_vs_Target();
	void DeleteInactiveBullet();
	void ShootBullet(Cannon* cannon);
};

