#ifndef MODEL_DATA_H
#define MODEL_DATA_H

enum class DataType : uint32_t
{
	VERT_XYZ = 0xB0000000u,
	UV,
	NORMS,
	TRI
};

struct Verts_data
{
	float x;
	float y;
	float z;
};

struct Norm_data
{
	float nx;
	float ny;
	float nz;
};

struct UV_data
{
	float u;
	float v;
};

struct Tri_data
{
	int v0;
	int v1;
	int v2;
};

#endif
