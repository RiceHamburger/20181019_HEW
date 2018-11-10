#include "Result.h"
#include "Texture.h"

#define MAXRANK 6
#define MAXTIME 999
#define NUMBER_WIDTH 32
#define NUMBER_HEIGHT 42
#define RANK_X 700
#define RANK_Y 240
#define RANK_WIDTH 1600
#define RANK_HEIGHT 900

LONGLONG g_GameTimeList[MAXRANK];

void ResultInit(void)
{
	for (int i = 0; i < MAXRANK - 1; i++)
	{
		g_GameTimeList[i] = 0;
	}

}

void ResultUnit(void)
{
}

void ResultDraw(void)
{
	Sprite_Draw(k_rank, 0, 0, 0, 0, RANK_WIDTH, RANK_HEIGHT, 0, 0, 1.0f, 1.0f, 0.0f);

	for (int i = 0; i < MAXRANK - 1; i++)
	{

		Score_Draw(RANK_X, RANK_Y + i*100, g_GameTimeList[i], MAXRANK - 2, false, true);
	}
	

	

}

void ResultUpdate(LONGLONG time)
{

	LONGLONG tempTime;

	g_GameTimeList[MAXRANK - 1] = time;

	for (int i = 0; i < MAXRANK - 1; i++) {
		for (int j = i + 1; j < MAXRANK; j++) {
			if (g_GameTimeList[i] < g_GameTimeList[j]) {
				tempTime = g_GameTimeList[i];
				g_GameTimeList[i] = g_GameTimeList[j];
				g_GameTimeList[j] = tempTime;
			}
		}
	}


}

void Number_Draw(float x, float y, int n)
{
		if (n < 0 || n > 9)
		{
			return;
		}
		int tx = n * NUMBER_WIDTH;
		Sprite_Draw(k_timerank, x, y, tx, 0, NUMBER_WIDTH, NUMBER_HEIGHT, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f);
	
}

void Score_Draw(float x, float y, int score, int fig, bool bLeft, bool bZero)
{

	int n = 0;
	int timeNumer[MAXTIME] = { 0 };
	int flag;
	if (bZero)
	{
		for (int i = 0; i < fig; i++)
		{
			int tmp = score % 10;
			score /= 10;

			timeNumer[n++] = tmp;
		}
	}
	else
	{
		while (score > 0)
		{
			int tmp = score % 10;
			score /= 10;

			timeNumer[n++] = tmp;
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		Number_Draw(x + (n - i - 1) * 32, y, timeNumer[i]);
	}
}

