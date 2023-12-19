#pragma once

#include "EngineGlobals.h"
#include "CubeImmediateMode.h"
#include "Scene.h"
#include "Loaders.h"

class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	unique_ptr<GameObject> engineCamera = make_unique<GameObject>();
	vector<shared_ptr<Scene>> scenes;
	FileLoader loader;

	void CreateScene(const string name) {
		shared_ptr<Scene> scene = make_shared<Scene>(name);
		AddScene(scene);
		scene->init();
	}

	void AddScene(shared_ptr<Scene> newScene) {
		scenes.push_back(newScene);
	}

	void RemoveScene(shared_ptr<Scene> scene) {
		scenes.erase(std::remove(scenes.begin(), scenes.end(), scene), scenes.end());
	}

	shared_ptr<Scene> GetSceneAtIndex(size_t index) const {
		if (index < scenes.size()) {
			return scenes[index];
		}
		else {
			return nullptr;
		}
	}

	void render();

public:

	void drawGrid(int grid_size, int grid_step, bool xy_plane = true, bool xz_plane = true, bool zy_plane = true) {
		glLineWidth(1.0);
		glColor3ub(128, 128, 128);

		glBegin(GL_LINES);
		for (int i = -grid_size; i <= grid_size; i += grid_step) {
			if (xz_plane) {
				//XZ plane
				glVertex3i(i, 0, -grid_size);
				glVertex3i(i, 0, grid_size);
				glVertex3i(-grid_size, 0, i);
				glVertex3i(grid_size, 0, i);
			}

			if (xy_plane) {
				//XY plane
				glVertex2i(i, -grid_size);
				glVertex2i(i, grid_size);
				glVertex2i(-grid_size, i);
				glVertex2i(grid_size, i);
			}

			if (zy_plane) {
				//ZY plane
				glVertex3i(0, i, -grid_size);
				glVertex3i(0, i, grid_size);
				glVertex3i(0, -grid_size, i);
				glVertex3i(0, grid_size, i);
			}
		}
		glEnd();
	}

	void drawAxis() {
		glLineWidth(4.0);
		glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex3d(0, 0, 0);
		glVertex3d(0.8, 0, 0);
		glColor3ub(0, 255, 0);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0.8, 0);
		glColor3ub(0, 0, 1);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, 0.8);
		glEnd();
	}
};

