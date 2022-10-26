#pragma once

//Engine関連
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

//User関連
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
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//ゲッター
	static GameScene* GetInstance();

private:

	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};