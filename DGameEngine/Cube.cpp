#include "Cube.h"


Cube::Cube() : 
	a(-1, -1, 1),
	b(1, -1, 1),
	c(1, 1, 1),
	d(-1, 1, 1),
	e(-1, -1, -1),
	f(1, -1, -1),
	g(1, 1, -1),
	h(-1, 1, -1),

	red(1, 0, 0),
	green(0, 1, 0),
	blue(0, 0, 1),
	yellow(1, 1, 0),
	white(0, 1, 1),
	black(1, 0, 1)

{
}

static void drawQuadFaceTriangles(vec3 a, vec3 b, vec3 c, vec3 d) {
	glTexCoord2d(0, 1);
	glVertex3dv(&a.x);
	glTexCoord2d(1, 1);
	glVertex3dv(&b.x);
	glTexCoord2d(1, 0);
	glVertex3dv(&c.x);

	glTexCoord2d(1, 0);
	glVertex3dv(&c.x);
	glTexCoord2d(0, 0);
	glVertex3dv(&d.x);
	glTexCoord2d(0, 1);
	glVertex3dv(&a.x);
}

void Cube::draw()
{
	GLubyte indices[] = { 0, 1, 2,   2, 3, 0,      // front
						  4, 5, 6,   6, 7, 4,      // right
						  8, 9, 10,  10,11,8,      // top
						  12,13,14,  14,15,12,     // left
						  16,17,18,  18,19,16,     // bottom
						  20,21,22,  22,23,20 };   // back

	GLfloat vertices2[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
						1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
						1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
					   -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
					   -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
						1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

	GLfloat colors2[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
						1, 1, 1,   1, 0, 1,   0, 0, 1,   0, 1, 1,   // v0,v3,v4,v5 (right)
						1, 1, 1,   0, 1, 1,   0, 1, 0,   1, 1, 0,   // v0,v5,v6,v1 (top)
						1, 1, 0,   0, 1, 0,   0, 0, 0,   1, 0, 0,   // v1,v6,v7,v2 (left)
						0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,   // v7,v4,v3,v2 (bottom)
						0, 0, 1,   0, 0, 0,   0, 1, 0,   0, 1, 1 }; // v4,v7,v6,v5 (back)

	

	GLfloat vertices[] = {  a.x, a.y , a.z ,
							b.x, b.y , b.z ,
							c.x, c.y , c.z ,
							d.x, d.y , d.z ,
							e.x, e.y , e.z ,
							f.x, f.y , f.z ,
							g.x, g.y , g.z ,
							h.x, h.y , h.z };

	GLfloat colors[] = { red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,
						 red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,
						 red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,
						 red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,
						 red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,
						 red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b,	red.r, red.g, red.b, };


	//glGenBuffers(1, (GLuint*)&(my_id));
	//glBindBuffer(GL_ARRAY_BUFFER, my_id);
	//glBufferData(GL_ARRAY_BUFFER, (float)(36 * 3), vertices2, GL_DYNAMIC_DRAW);

	//glEnable(GL_TEXTURE_2D);
	//texture.bind();

	//glBegin(GL_TRIANGLES);
	////front
	////glColor3dv(&red.x);
	//drawQuadFaceTriangles(a, b, c, d);
	////back
	////glColor3dv(&green.x);
	//drawQuadFaceTriangles(h, g, f, e);
	////left
	////glColor3dv(&blue.x);
	//drawQuadFaceTriangles(e, a, d, h);
	////right
	////glColor3dv(&yellow.x);
	//drawQuadFaceTriangles(b, f, g, c);
	////top
	////glColor3dv(&white.x);
	//drawQuadFaceTriangles(d, c, g, h);
	////bottom
	////glColor3dv(&black.x);
	//drawQuadFaceTriangles(b, a, e, f);
	//glEnd();

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	

 	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices2);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glDisable(GL_TEXTURE_2D);


	/*glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_DOUBLE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glColorPointer(3, GL_DOUBLE, 0, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);*/

}