#include "all.h"

Item_t *CreateItem(int picId, int attack, int defense, int hp)
{
	// picId
	errorCase(!m_isRange(attack, 0, IMAX));
	errorCase(!m_isRange(defense, 0, IMAX));
	errorCase(!m_isRange(hp, 0, IMAX));

	Item_t *i = nb(Item_t);

	i->PicId = picId;
	i->Attack = attack;
	i->Defense = defense;
	i->HP = hp;

	return i;
}
void ReleaseItem(Item_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

// <-- accessor

autoList<Item_t *> *MakeItems(void)
{
	autoList<Item_t *> *ret = new autoList<Item_t *>(ITEM_NUM);

	ret->AddElement(CreateItem(GetIconPicId(11, 3), 10, 0, 0)); // 0: ƒnƒ“ƒ}[–Ø
	ret->AddElement(CreateItem(GetIconPicId(5, 5), 5, 5, 15)); // 1: ‰t‘Ìƒrƒ“Â
	ret->AddElement(CreateItem(GetIconPicId(3, 1), 0, 5, 0)); // 2: ‚–Ø
	ret->AddElement(CreateItem(GetIconPicId(0, 9), 0, 5, 0)); // 3: Š•Šv

	errorCase(ret->GetCount() != ITEM_NUM);

	return ret;
}
oneObject(autoList<Item_t *>, MakeItems(), GetItems);
