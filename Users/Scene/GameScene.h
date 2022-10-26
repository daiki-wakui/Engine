#pragma once

//Engine�֘A
#include"ErrorException.h"
#include"Model.h"
#include"ModelCreate.h"
#include"Camera.h"
#include"Collision.h"
#include"Input.h"
#include"SpriteCreat.h"
#include"ParticleCreat.h"
#include"Light.h"
#include"Mesh.h"
#include"3DMesh.h"
#include"Transform.h"
#include"DefaultMaterial.h"
#include"AudioManager.h"
#include"Score.h"

//User�֘A
#include"Player.h"
#include"Enemy.h"

class GameScene
{
private:

	Mesh3D* mesh3D = nullptr;
	Input* input = nullptr;
	Score* score = nullptr;

	std::unique_ptr<Light> light;
	EngineMathF::Vector4 lightColor = { 1, 1, 1, 1 };

	std::unique_ptr<Camera> camera;

	//================//

	Player* player = nullptr;
	std::list<std::unique_ptr<Enemy>>enemys;
	int enemyGeneration = 0;

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//�Q�b�^�[
	static GameScene* GetInstance();

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};