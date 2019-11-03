#pragma once
#include <vector>
#include <BattleTile.h>
#include <KVector.h>
#include <Windows.h>



class KScene;
class Tile;
class KBitMap;
class TileManager
{
private:
	// 본체에서는 해야하니까
	TileManager() {} /* = delete*/;
	TileManager(const TileManager& _Other) = delete;
	TileManager(const TileManager&& _Other) = delete;
	void operator=(const TileManager& _Other) = delete;
	~TileManager() {};
	static TileManager* pKTileManager;

public:
	static TileManager* instance()
	{
		if (nullptr == pKTileManager)
		{
			pKTileManager = new TileManager();
		}

		return pKTileManager;
	}


private:
	std::vector<Tile*> VectorTile;
	std::vector<KPos2> VectorRespawn;
	std::vector<Tile*> PhoenixTile;

	std::vector<BATTLECITY_GAMETILE> VectorTileInfo;

	HDC MapHdc;
	KBitMap* MapBit;
	KScene* MomScene;
	
	int XSize;
	int YSize;

public:
	void create(KScene* _Scene);
	bool init(const wchar_t* _Name);

	void update_broken();
	void update_alltile();
	void update_tile(Tile* _Tile);
	void update_rectbrowntile(Tile* _CurTile, const KPos2& _BulletDir, const KPos2& _BulletPos);
	void render();
	void release();

	inline KRect tilemap_size()
	{
		KRect Tmp;
		Tmp.Start.x = STARTXPOS;
		Tmp.Start.y = STARTYPOS;

		Tmp.End.x = XSize * ((float)TILEXSIZE - 1.5f) + Tmp.Start.x;
		Tmp.End.y = YSize * ((float)TILEYSIZE - 1.5f) + Tmp.Start.y;

		return Tmp;
	}

	inline std::vector<KPos2>* vector_respawnpos()
	{
		return &VectorRespawn;
	}

private:
	void read_file(const wchar_t* _Name);

	void create_map();

	Tile* posto_tile(const KPos2& _Pos);
	bool check_rectbrown(
		const KPos2& _Pos,
		const BATTLECITY_GAMETILE& _Type, 
		const KPos2& _BulletPos);
	bool check_smallbrown(
		const KPos2& _Pos, 
		const BATTLECITY_GAMETILE& _Type, 
		const KPos2& _BulletDir,
		const KPos2& _BulletPos);
};

