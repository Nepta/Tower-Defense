#include "map.h"

Map** initMap(){
	Map *map_ = malloc(800 * 600 * sizeof (Map));
	Map **map = malloc(800 * sizeof (Map*));
	
	for(int i=0; i<800; i++){
		map[i] = &map_[i*600];
		for(int j=0; j< 600; j++){
			map[i][j].x = i;
			map[i][j].y = j;
			map[i][j].parent.x = i;
			map[i][j].parent.y = j;
			if(i == 0 || j == 0 || i == 799 || j == 599){
				map[i][j].hasTower = 1;
			}else{
				map[i][j].hasTower = 0;
			}
		}
	}
 return map;
}

