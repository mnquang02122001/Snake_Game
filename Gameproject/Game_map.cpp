#include"Game_map.h"

void GameMap::LoadMap(char* name) {
	/*std::ifstream file;
	file.open(name, std::ios::in);
	if (!file.is_open()) {
		return;
	}*/
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		return;
	}
	game_map_.max_x = 0;
	game_map_.max_y = 0;
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			//file >> game_map_.tile[i][j];
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
		    int val = game_map_.tile[i][j];
		if (val > 0) {
			if (j > game_map_.max_x)
			{
				game_map_.max_x = j;
			}
			if (i > game_map_.max_y)
			{
				game_map_.max_y = i;
			}
		}
		}
	}
	game_map_.max_x = (game_map_.max_x + 1) * TILE_SIZE;
	game_map_.max_y = (game_map_.max_y + 1) * TILE_SIZE;
	game_map_.start_x = 0;
	game_map_.start_y = 0;
	game_map_.file_name_ = name;
	fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen) {
	char file_img[30];
	//std::ofstream file(file_img, std::ios::out);
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILES; i++)
	{
		/*file.open(file_img, std::ios::out);
		file << "map/" << i << ".png";
		if (!file.is_open()) {
			continue;
		}
		file.close();*/
		sprintf_s(file_img, "map/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == NULL) {
			continue;
		}
		fclose(fp);
		tile_mat[i].LoadImg(file_img, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int map_x = 0;
	int map_y = 0;

	map_x = game_map_.start_x / TILE_SIZE;
	map_y = game_map_.start_y / TILE_SIZE;

	x1 = (game_map_.start_x % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	y1 = (game_map_.start_y % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map_.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map_.tile[map_y][map_x];
			if (val > 0)
			{
				tile_mat[val].SetRect(j, i);
				tile_mat[val].Render(screen,NULL);
			}
			map_x++;
		}
		map_y++;
	}
	
}