#pragma once
#include"EngineMathF.h"
#include"ModelCreate.h"
#include"Transform.h"
#include"Mesh.h"
#include"Player.h"
#include"Score.h"

class Enemy
{
private:

	EngineMathF::Vector3 enemy = { 0,0,0 };
	Mesh* mesh = nullptr;
	Player* player = nullptr;
	Score* score = nullptr;

	EngineMathF::Vector3 enemyVec = { 0,0,0 };
	EngineMathF::Vector3 normEnemyVec = { 0,0,0 };

	bool isDead = false;
	float radius = 0.0f;

public:

	void Initialize(EngineMathF::Vector3 position);
	void Update();
	void Draw();
	bool GetIsDead();

	void Move();
	//void Score();
};