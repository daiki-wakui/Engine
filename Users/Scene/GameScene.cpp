#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Initialize()
{
	input = Input::GetInstance();
	player = Player::GetInstance();
	score = Score::GetInstance();
	player->Initialize();

	//���C�g������
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//���f���Ƀ��C�g���Z�b�g
	Model::SetLight(light.get());

	camera = std::make_unique<Camera>();
	camera->Initialize(UpdateProjMatrixFunc_Perspective);

}

void GameScene::Update()
{
	//���C�g�̌��������ݒ�
	EngineMathF::Vector3 rightDir = { 10.0f,3.0f,5.0f };
	light->SetLightDir(rightDir);
	light->Update();

	player->Update();

	if (enemys.size() < 10)
	{
		if (enemyGeneration == 0)
		{
			EngineMathF::Vector3 position = { EngineMathF::GetRand(10,1270),EngineMathF::GetRand(10,750),0.0f };
			//Enemy�𐶐����A������
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize(position);
			//Enemy��o�^����
			enemys.push_back(std::move(newEnemy));

			enemyGeneration = 0;
		}
	}
	
	enemyGeneration++;
	if (enemyGeneration > 10)
	{
		enemyGeneration = 0;
	}

	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Update();
	}

	enemys.remove_if([](std::unique_ptr<Enemy>& enemy)
		{
			return enemy->GetIsDead();//Enemy����������
		});

	score->Update();
}

void GameScene::Draw()
{
	player->Draw();

	for (std::unique_ptr<Enemy>& enemy : enemys)
	{
		enemy->Draw();
	}

	score->Draw();
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}