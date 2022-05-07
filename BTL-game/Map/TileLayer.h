#pragma once
#include"Layer.h"
#include<string>
#include<vector>

struct tileSet {
	int sizeX, sizeY;
	int tilesize;
	std::string tag;
};

using TilesetList = std::vector<tileSet>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer :public Layer
{
public:

	TileLayer(int ts, int sx, int sy, TileMap tm) {
		

	};
	virtual void Render();
	virtual void Update();

	inline TileMap GetTileMap()
	{
		return l_Tilemap;
	}

private:
	int tilesize;
	int l_sizeX, l_sizeY;
	TileMap l_Tilemap;
};

