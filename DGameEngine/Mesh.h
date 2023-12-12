#pragma once

#include "EngineGlobals.h"
#include "Graphic.h"
#include "Texture2D.h"
#include "Scene.h"
#include "Components.h"



class Mesh : public Graphic
{
public:
	enum Formats { F_V3, F_V3C4, F_V3T2 };
	struct V3 { vec3f v; };
	struct V3C4 { vec3f v; vec4f c; };
	struct V3T2 { vec3f v; vec2f t; };

private:
	enum Formats _format;

	unsigned int _vertex_buffer_id;
	unsigned int _numVerts;

	unsigned int _indexs_buffer_id;
	unsigned int _numIndexs;

public:
	using Ptr = shared_ptr<Mesh>;

	string name;
	shared_ptr<Texture2D> texture;

	unsigned int mMaterialIndex;

	Mesh(Formats format, const void* vertex_data, unsigned int numVerts, const unsigned int* indexs_data = nullptr, unsigned int numIndexs = 0);
	Mesh(Mesh&& b) noexcept;
	~Mesh();
	void draw() override;

private:
	Mesh(const Mesh& cpy);
	Mesh& operator=(const Mesh&);
};

