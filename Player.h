#pragma once
#include"Input.h"
#include"Mesh.h"
#include"EngineMathF.h"

class Player
{
private:

	//�N���X�ǂݍ���
	Input* input = nullptr;
	Mesh* mesh = nullptr;

	EngineMathF::Vector3 player = { 0,0,0 };
	float speed = 0.0f;

public:

	void Initialize();
	void Update();
	void Draw();

	//�Q�b�^�[
	EngineMathF::Vector3 GetPlayerPos();
	float GetSpeed();
	static Player* GetInstance();
};