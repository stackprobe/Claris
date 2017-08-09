#include "all.h"

static autoList<DerInfo_t *> *DerList;

static void AddDer(int parentPicId, int x, int y, int w, int h)
{
	DerInfo_t *i = nb(DerInfo_t);

	i->ParentPicId = parentPicId;
	i->X = x;
	i->Y = y;
	i->W = w;
	i->H = h;

	DerList->AddElement(i);
}
static void AddAnimation(int parentPicId, int x, int y, int w, int h, int xNum, int yNum, int xStep = -1, int yStep = -1)
{
	if(xStep == -1) xStep = w;
	if(yStep == -1) yStep = h;

	for(int yc = 0; yc < yNum; yc++)
	for(int xc = 0; xc < xNum; xc++)
	{
		AddDer(parentPicId, x + xc * xStep, y + yc * yStep, w, h);
	}
}
static void CreateDerList(void)
{
	DerList = new autoList<DerInfo_t *>();

	AddAnimation(P_DUMMY, 0, 0, 25, 25, 2, 2); // D_DUMMY_00

	// app >

	AddAnimation(P_TITLEITEM, 0, 0, 180, 50, 1, 4); // D_TITLEITEM_00

	for(int c = 0; c < 5; c++)
	{
		AddAnimation(P_ACTOR83_00 + c, 0, 0, 32, 32, 3, 4); // D_ACTOR83_00
	}
	for(int c = 0; c < 2; c++)
	{
		AddAnimation(P_ACTOR83_FACE_00 + c, 0, 0, 96, 96, 4, 2); // D_ACTOR83_FACE_00
	}

	for(int c = 0; c < TILE_MAX; c++)
	{
		AddAnimation(P_TILE_00 + c, 0, 0, MAPCELL_W, MAPCELL_H, TILE_W, TILE_H); // D_TILE_00
	}
	for(int c = 0; c < TILE_MAX; c++)
	{
		AddAnimation(P_TILE_00 + c, 0, 0, MINIMAPCELL_W, MINIMAPCELL_H, MINITILE_W, MINITILE_H); // D_MINITILE_00
	}

	AddAnimation(P_ICONSET, 0, 384, 24, 24, 16, 22); // D_ICONSET_00
	AddDer(P_ACTOR83_RAF, 0, 51, 260, 480);  // D_ACTOR83_RAF_01
	AddDer(P_ACTOR83_RAF, 260, 0, 260, 582); // D_ACTOR83_RAF_02

	for(int c = 0; c < 6; c++)
	{
		AddAnimation(P_BTLEFFECT051 + c, 0, 0, 120, 120, 10, 1); // D_BTLEFFECT051_00 - D_BTLEFFECT056_00
	}

	AddAnimation(P_MAHOUJIN_HAJIKE, 0, 0, 120, 120, 14, 1); // D_MAHOUJIN_HAJIKE_00

	// < app

	errorCase(DerList->GetCount() != D_MAX);
}
static autoList<DerInfo_t *> *GetDerList(void)
{
	if(!DerList)
		CreateDerList();

	return DerList;
}

static int LoadDer(PicInfo_t *parent, int x, int y, int w, int h)
{
	int der_h;

	// check rect {
	errorCase(x < 0 || IMAX < x);
	errorCase(y < 0 || IMAX < y);
	errorCase(w < 1 || IMAX - x < w);
	errorCase(h < 1 || IMAX - y < h);
	// }

	if(
		parent->W < x + w ||
		parent->H < y + h
		)
		// ? 範囲外
	{
		m_range(w, 1, 50);
		m_range(h, 1, 50);

		der_h = DerivationGraph(0, 0, w, h, GetPicRes()->GetHandle(P_DUMMY)->Handle); // ダミー画像
	}
	else
		der_h = DerivationGraph(x, y, w, h, parent->Handle);

	errorCase(der_h == -1); // ? 失敗
	return der_h;
}
static void UnloadDer(int h)
{
	if(h == -1) // ? 未オープン
		return;

	errorCase(DeleteGraph(h)); // ? 失敗
}

int Der(resCluster<PicInfo_t *> *resclu, int derId)
{
	errorCase(derId < 0 || D_MAX <= derId);

	int h = resclu->GetDerHandleList()->RefElement(derId, -1);

	if(h == -1)
	{
		DerInfo_t *i = GetDerList()->GetElement(derId);

		h = LoadDer(
			resclu->GetHandle(i->ParentPicId),
			i->X,
			i->Y,
			i->W,
			i->H
			);

		resclu->GetDerHandleList()->PutElement(derId, h, -1);
	}
	return h;
}
int Der_W(int derId)
{
	return GetDerList()->GetElement(derId)->W;
}
int Der_H(int derId)
{
	return GetDerList()->GetElement(derId)->H;
}

void UnloadAllDer(resCluster<PicInfo_t *> *resclu)
{
	for(int derId = 0; derId < resclu->GetDerHandleList()->GetCount(); derId++)
	{
		UnloadDer(resclu->GetDerHandleList()->GetElement(derId));
	}
	resclu->GetDerHandleList()->Clear();
}
