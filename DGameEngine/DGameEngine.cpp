#include "EngineGlobals.h"
#include "DGameEngine.h"

static double angle = 0.0;

void GameEngine::step(std::chrono::duration<double> dt) {
    const double angle_vel = 180.0; // 360 degrees per second
	angle += angle_vel * dt.count();
}

static void drawAxis() {
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

static void drawGrid(int grid_size, int grid_step, bool xy_plane = true, bool xz_plane = true) {
    glLineWidth(1.0);
    glColor3ub(128, 128, 128);

    glBegin(GL_LINES);
    for (int i = -grid_size; i <= grid_size; i += grid_step) {
        if (xy_plane) {
            //XY plane
            glVertex2i(i, -grid_size);
            glVertex2i(i, grid_size);
            glVertex2i(-grid_size, i);
            glVertex2i(grid_size, i);
        }

        if (xz_plane) {
            //XZ plane
            glVertex3i(i, 0, -grid_size);
            glVertex3i(i, 0, grid_size);
            glVertex3i(-grid_size, 0, i);
            glVertex3i(grid_size, 0, i);
        }
    }
    glEnd();
}

void GameEngine::render(RenderModes renderMode) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.fov, camera.aspect, camera.zNear, camera.zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( camera.eye.x, camera.eye.y, camera.eye.z,
        camera.center.x, camera.center.y, camera.center.z,
        camera.up.x, camera.up.y, camera.up.z);

    if (renderMode == RenderModes::DEBUG) {
        drawGrid(100, 1, grid_xy, grid_xz);
        drawAxis();
    }
    
#pragma region direct draw test
    glPushMatrix();
    glRotated(angle, 0.5, 0.5, 0.5);

    glBegin(GL_TRIANGLES);
    //Quad 1
    glColor4ub(255, 0, 0, 255);
    glVertex3d(1, 0, 0);
    glVertex3d(1, 1, 0);
    glVertex3d(0, 0, 0);

    glVertex3d(0, 1, 0);
    glVertex3d(1, 1, 0);
    glVertex3d(0, 0, 0);

    //Quad 2
    glColor4ub(200, 0, 0, 255);
    glVertex3d(1, 0, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(1, 0, 0);

    glVertex3d(1, 1, 0);
    glVertex3d(1, 1, 1);
    glVertex3d(1, 0, 0);

    //Quad 3
    glColor4ub(155, 0, 0, 255);
    glVertex3d(1, 0, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(0, 0, 1);

    glVertex3d(0, 1, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(0, 0, 1);

    //Quad 4
    glColor4ub(100, 0, 0, 255);
    glVertex3d(0, 0, 1);
    glVertex3d(0, 1, 1);
    glVertex3d(0, 0, 0);

    glVertex3d(0, 1, 0);
    glVertex3d(0, 1, 1);
    glVertex3d(0, 0, 0);

    //Quad 5
    glColor4ub(55, 100, 0, 255);
    glVertex3d(1, 0, 0);
    glVertex3d(1, 0, 1);
    glVertex3d(0, 0, 0);

    glVertex3d(0, 0, 1);
    glVertex3d(1, 0, 1);
    glVertex3d(0, 0, 0);

    //Quad 6
    glColor4ub(55, 55, 0, 255);
    glVertex3d(1, 1, 0);
    glVertex3d(1, 1, 1);
    glVertex3d(0, 1, 0);

    glVertex3d(0, 1, 1);
    glVertex3d(1, 1, 1);
    glVertex3d(0, 1, 0);

    glEnd();

    glPopMatrix();
#pragma endregion

}
