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
		scoreBonus += 0.1f;//スコア倍率上昇
	}
	else
	{
		scoreBonus = 1.0f;//スコアボーナスを1.0倍に
	}
	score += 100 * scoreBonus;//スコア増加
	BonusTime = 50;//倍率が上がる時間
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