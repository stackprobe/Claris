#include "all.h"

int EEF_Start(Enemy_t *e)
{
	return 1;
}
int EEF_Item(Enemy_t *e)
{
	if(!e->Frame) // init
	{
		e->u.Item.ItemId = e->SubVal;
	}
	if(IsEnemyOutOfScreen(e))
		goto endFunc;

	Item_t *item = GetItems()->GetElement(e->u.Item.ItemId);
	
	int dr_x = e->IX - GDc.ICameraX;
	int dr_y = e->IY - GDc.ICameraY;

	{
		double a_rate = sin(ActFrame / 20.0) * 0.5 + 0.5;

		DPE.TL = GDc.DE;
		DPE_SetAlpha(a_rate * 0.5);
		DrawBegin(P_MAHOUJIN, dr_x, dr_y);
		DrawRotate(e->Frame / 100.0);
		DrawEnd();
		DPE_Reset();

		DPE.TL = GDc.DE;
		DrawCenter(item->PicId, dr_x, dr_y);
		DPE_SetBlendAdd(a_rate);
		DrawCenter(item->PicId, dr_x, dr_y);
		DPE_Reset();
	}

endFunc:
	return 0;
}
