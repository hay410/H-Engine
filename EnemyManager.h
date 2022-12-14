#pragma once
#include "Enemy.h"
#include "Player.h"

class EnemyManager :public Singleton<EnemyManager>
{
private:
	//�����o�萔
	int MAX_VALUE = 10;
	Vec3 attackVec = Vec3();
	Vec3 playerNearPos = Vec3();
	float ComparingDistance = 100000.0f;

	//�����o�ϐ�
	vector<Enemy> enemy;
public:
	//�����o�֐�
	EnemyManager();
	friend Singleton<EnemyManager>;

	void Generate(Player& player);

	void Update(Player& player);

	void CD_PushBackPlayer(Player& player);

	void Draw();

	Enemy GetEnemy(int i) { return enemy[i]; }
	Vec3 GetAttackVec() { return attackVec; }
	Vec3 GetNearPos() { return playerNearPos; }
};