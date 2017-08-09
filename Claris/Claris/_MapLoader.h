autoTable<MapCell_t *> *LoadMap(MapCell_t *(*rgbToMapCell)(int color), autoList<uchar> *fileData);
autoTable<MapCell_t *> *LoadMap_x(MapCell_t *(*rgbToMapCell)(int color), autoList<uchar> *fileData);
autoTable<MapCell_t *> *LoadMap(MapCell_t *(*rgbToMapCell)(int color), char *file);
