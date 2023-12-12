#pragma once

#include "EngineGlobals.h"

class Texture2D
{

private:
	unsigned int _id;
public:
	string path;

public:
	using Ptr = shared_ptr<Texture2D>;
	explicit Texture2D(const string& path);
	Texture2D() = default;
	Texture2D(Texture2D&& tex) noexcept;
	void bind() const;
	~Texture2D();
	string name;

private:
	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;

};


