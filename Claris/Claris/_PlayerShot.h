enum // PlayerShotKind
{
	PSK_NORMAL,
	PSK_WAVE,
	PSK_SPREAD,
	PSK_BOUNCE,

	PSK_MAX, // num of member
};

typedef struct PlayerShot_st
{
	int Kind; // PSK_*
	double X;
	double Y;
	double XAdd;
	double YAdd;
	/*
		PSK_WAVE
			wave phase, 0 or not 0

		PSK_BOUNCE
			remain bound count, 0 Å`
	*/
	int SubVal;

	// <-- ctor params

	int Frame;
	int IX;
	int IY;

	union
	{
		struct
		{
			int CrashFrame2;
			int CrashFrame4;
			int CrashFrame6;
			int CrashFrame8;
		}
		Bounce;
	}
	u;
}
PlayerShot_t;

PlayerShot_t *CreatePlayerShot(int kind, double x, double y, double xAdd, double yAdd, int subVal = -1);
void ReleasePlayerShot(PlayerShot_t *i);

// <-- cdtor

void PlayerShotPosChanged(PlayerShot_t *i);

// <-- accessor

int PlayerShotEachFrame(PlayerShot_t *i);
void AllPlayerShotEachFrame(void);

void PlayerShotProc(void);
