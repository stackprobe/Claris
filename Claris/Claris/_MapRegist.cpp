#include "all.h"

#define MRTKN_DLMTR ":"

void LoadMapRegist(autoTable<MapCell_t *> *map, int mapId)
{
	errorCase(!map);
	errorCase(!m_isRange(mapId, 0, IMAX));

	if(Gnd.MapRegistLines->GetCount() <= mapId)
		return;

	char *mrLine = Gnd.MapRegistLines->GetElement(mapId);
	autoList<char *> *mrTokens = tokenize(mrLine, MRTKN_DLMTR);
	int rIndex = 0;

	while(rIndex < mrTokens->GetCount())
	{
		int x = s2i(mrTokens->GetElement(rIndex++), 0, map->GetWidth() - 1, 0);
		int y = s2i(mrTokens->GetElement(rIndex++), 0, map->GetHeight() - 1, 0);

		MapCell_t *mc = map->GetCell(x, y);

		// Regist {

		mc->Regist.Retired = s2i(mrTokens->GetElement(rIndex++), -1, 1, 0) ? 1 : 0;

		// <- ‚±‚±‚É’Ç‰Á

		// }
	}
	releaseList(mrTokens, (void (*)(char *))memFree);
}
void SaveMapRegist(autoTable<MapCell_t *> *map, int mapId)
{
	errorCase(!map);
	errorCase(!m_isRange(mapId, 0, IMAX));

	autoList<char *> *mrTokens = new autoList<char *>();

	for(int x = 0; x < map->GetWidth(); x++)
	for(int y = 0; y < map->GetHeight(); y++)
	{
		MapCell_t *mc = map->GetCell(x, y);

		if(isallzero(&mc->Regist))
			continue;

		mrTokens->AddElement(xcout("%d", x));
		mrTokens->AddElement(xcout("%d", y));

		// Regist {

		mrTokens->AddElement(xcout("%d", mc->Regist.Retired));

		// <- ‚±‚±‚É’Ç‰Á

		// }
	}

	while(mapId < Gnd.MapRegistLines->GetCount())
		Gnd.MapRegistLines->AddElement(strx(""));

	strz_x(*Gnd.MapRegistLines->ElementAt(mapId), untokenize(mrTokens, MRTKN_DLMTR));
}
