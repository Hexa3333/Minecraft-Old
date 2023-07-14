#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "Time.h"
#include "Chunk.h"
#include "graphics/Camera.h"
#include "Game.h"
#include "util.h"

static void KeyInput();
int main(void)
{
	InitGame("Minecraft", 720, 720);
	
	struct Shader shadethis = CreateShaderVF("res/Shaders/BasicCubeV.glsl", "res/Shaders/BasicCubeF.glsl");
	struct AmbientLight ambientLight = CreateAmbientLight((vec3s){1.0f, 1.0f, 1.0f}, 1.0f);
	struct DirectionalLight directionalLight = CreateDirectionalLight((vec3s){1.0f,1.0f,1.0f}, 1.0f, (vec3s) { -0.8f, 0.2f, 0.0f });

	struct Chunk testChunk = CreateChunk(0,0);
	printf("testBlock.left = (%.1f, %.1f)\n", testChunk.blocks[CHUNK_INDEXER(0,0)].neighbors.left->position.x, testChunk.blocks[CHUNK_INDEXER(0,0)].neighbors.left->position.z);
	printf("testBlock.right = (%.1f, %.1f)\n", testChunk.blocks[CHUNK_INDEXER(0,0)].neighbors.right->position.x, testChunk.blocks[CHUNK_INDEXER(0,0)].neighbors.right->position.z);
	
	glBindTexture(GL_TEXTURE_2D, g_SPRITE_SHEET.sheet.texObj);
	while (GetGameShouldRun())
	{
		CalculateDT();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0f, 1.0, 0.0f, 1.0f);
		//printf("\033[H\033[J"); // Clear

		UpdateView();
		KeyInput();

		float pX = g_MainCamera.position.x;
		float pY = g_MainCamera.position.y;
		float pZ = g_MainCamera.position.z;

		SendAmbientLight(&g_TerrainShader, ambientLight);
		SendDirectionalLight(&g_TerrainShader, directionalLight);
		DrawChunk(&testChunk);

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_ESCAPE)) break;

		glfwSwapBuffers(g_MainWindow.object);
		glfwPollEvents();
	}

	KillGame();
}

void KeyInput()
{
		vec3s cross = glms_vec3_cross(g_MainCamera.front, g_MainCamera.up);
		vec3s moveSpeed = {20.0f * DT, 20.0f * DT, 20.0f * DT};

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_W))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_S))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(g_MainCamera.front, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_A))
			g_MainCamera.position = glms_vec3_add(g_MainCamera.position, glms_vec3_mul(cross, moveSpeed));
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_D))
			g_MainCamera.position = glms_vec3_sub(g_MainCamera.position, glms_vec3_mul(cross, moveSpeed));

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_LEFT_CONTROL))
			g_MainCamera.position.y -= 25.0f * DT;
		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_SPACE))
			g_MainCamera.position.y += 25.0f * DT;

		if (glfwGetKey(g_MainWindow.object, GLFW_KEY_F))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
