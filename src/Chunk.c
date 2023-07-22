#include "Chunk.h"
#include "util.h"
#include "graphics/Camera.h"

struct Chunk* CreateChunk(u32 x, u32 z)
{
	struct Chunk* ret = malloc(sizeof(struct Chunk));
	if (!ret) return NULL;
	ret->position.x = (float)x;
	ret->position.y = (float)0;
	ret->position.z = (float)z;

	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
	{
		
		ret->blocks[CHUNK_INDEX(x,y,z)].position = (vec3s){ret->position.x + x, ret->position.y + y, ret->position.z + z};
		ret->blocks[CHUNK_INDEX(x,y,z)] = CreateBlock(&g_TerrainShader, DIRTWGRASS, ret->blocks[y][z][x].position);
		ret->blocks[CHUNK_INDEX(x,y,z)].model = glms_translate(GLMS_MAT4_IDENTITY, ret->blocks[y][z][x].position);
	}

	SetNeighboringBlocksOfChunk(ret);
	SetChunkInnerBlocksInvisible(ret);
	return ret;
}

void DrawChunk(struct Chunk* chunk)
{
	CullBackFaces(chunk);
	for (int z = 0; z < CHUNK_DEPTH; ++z)
		for (int y = 0; y < CHUNK_HEIGHT; ++y)
			for (int x = 0; x < CHUNK_WIDTH; ++x)
				if (chunk->blocks[CHUNK_INDEX(x,y,z)].props.isVisible && !chunk->blocks[CHUNK_INDEX(x,y,z)].props.isTransparent)
					DrawGameObject(&chunk->blocks[CHUNK_INDEX(x,y,z)]);
}
