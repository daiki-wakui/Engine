#include "Score.h"
#include <stdio.h>

void Score::Update()
{
	BonusTime--;
}

void Score::ScoreAdd()
{
	if (BonusTime > 0)
	{
		scoreBonus += 0.1f;//�X�R�A�{���㏸
	}
	else
	{
		scoreBonus = 1.0f;//�X�R�A�{�[�i�X��1.0�{��
	}
	score += 100 * scoreBonus;//�X�R�A����
	BonusTime = 50;//�{�����オ�鎞��
}

void Score::Draw()
{
	printf("score:%d\n", score);
}

Score* Score::GetInstance()
{
	static Score instance;
	return &instance;
}