enum
{
	P_DUMMY,
	P_WHITEBOX,
	P_WHITECIRCLE,

	// app >

	P_COPYRIGHT,
	P_TITLE,
	P_TITLEITEM,
	P_TITLEWALL,

	P_ACTOR83_00,
	P_ACTOR83_01,
	P_ACTOR83_02,
	P_ACTOR83_03,
	P_ACTOR83_04,
	P_ACTOR83_FACE_00,
	P_ACTOR83_FACE_01,
	P_ACTOR83_RAF,

	ENUM_RANGE(P_TILE_00, TILE_MAX)

	P_ICONSET,

	P_BTLEFFECT051,
	P_BTLEFFECT052,
	P_BTLEFFECT053,
	P_BTLEFFECT054,
	P_BTLEFFECT055,
	P_BTLEFFECT056,

	P_MAHOUJIN_HAJIKE,

	// < app

	P_MAX, // num of member
};

typedef struct PicInfo_st
{
	int Handle;
	int W;
	int H;
}
PicInfo_t;

// Pic_ >

int Pic_FileData2SoftImage(autoList<uchar> *fileData);
int Pic_SoftImage2GraphicHandle(int si_h);
PicInfo_t *Pic_GraphicHandle2PicInfo(int handle);
void Pic_ReleasePicInfo(PicInfo_t *i);

void Pic_GetSoftImageSize(int si_h, int &w, int &h);
void Pic_GetGraphicHandleSize(int handle, int &w, int &h);

extern int SI_R;
extern int SI_G;
extern int SI_B;
extern int SI_A;

void Pic_GetSIPixel(int si_h, int x, int y);
void Pic_SetSIPixel(int si_h, int x, int y);

// < Pic_

resCluster<PicInfo_t *> *CreatePicRes(PicInfo_t *(*picLoader)(autoList<uchar> *), void (*picUnloader)(PicInfo_t *));
void UnloadAllPicResHandle(void);

void SetPicRes(resCluster<PicInfo_t *> *resclu);
resCluster<PicInfo_t *> *GetPicRes(void);
void ResetPicRes(void);

#define DTP 0x40000000

int Pic(int picId);
int Pic_W(int picId);
int Pic_H(int picId);
