#pragma once
class Score
{
private:
	int score = 0;
	int BonusTime = 0;
	float scoreBonus = 1.0f;
public:
	void Update();
	void ScoreAdd();
	void Draw();

	static Score* GetInstance();
};