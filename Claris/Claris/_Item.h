typedef struct Item_st
{
	int PicId;
	int Attack;
	int Defense;
	int HP;

	// <-- ctor params
}
Item_t;

Item_t *CreateItem(int picId, int attack, int defense, int hp);
void ReleaseItem(Item_t *i);

// <-- cdtor

// <-- accessor

#define ITEM_NUM 4

oneObjectProto(autoList<Item_t *>, GetItems);
