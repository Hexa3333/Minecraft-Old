#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "graphics/Buffer.h"
#include "graphics/Shader.h"
#include "graphics/Sprite.h"
#include <cglm/struct.h>

struct GameObject
{
	struct Buffer buffer;
	struct Shader shader;
#ifdef NO_SPRITE_SHEET
	struct Sprite sprite;
#endif
	mat4s model;
	void (*render)(struct Buffer* buffer);
};

#ifdef NO_SPRITE_SHEET
struct GameObject CreateGameObject(struct Buffer* buffer, struct Shader* shader, struct Sprite* sprite);
#else
struct GameObject CreateGameObject(struct Buffer* buffer, struct Shader* shader);
#endif
struct GameObject CreateVoxelGameObject(struct Shader* shader, enum BLOCK_TEX_NAMES texName);
void DrawGameObject(struct GameObject* go);

#endif // GAMEOBJECT_H
