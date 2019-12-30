

namespace cube {

	typedef float CoordType;
	typedef unsigned short IndexType;


	unsigned int numVertices = 24;
	unsigned int numIndices = 12;
	unsigned int numPointsPerVertex = 3;

	CoordType vertices[] = {
		-0.25, -0.25, -0.25,
		0.25, -0.25, -0.25,
		0.25, 0.25, -0.25,
		-0.25, 0.25, -0.25,
		-0.25, -0.25, 0.25,
		-0.25, 0.25, 0.25,
		0.25, 0.25, 0.25,
		0.25, -0.25, 0.25,
		-0.25, -0.25, -0.25,
		-0.25, 0.25, -0.25,
		-0.25, 0.25, 0.25,
		-0.25, -0.25, 0.25,
		0.25, -0.25, -0.25,
		0.25, -0.25, 0.25,
		0.25, 0.25, 0.25,
		0.25, 0.25, -0.25,
		-0.25, 0.25, -0.25,
		0.25, 0.25, -0.25,
		0.25, 0.25, 0.25,
		-0.25, 0.25, 0.25,
		-0.25, -0.25, -0.25,
		-0.25, -0.25, 0.25,
		0.25, -0.25, 0.25,
		0.25, -0.25, -0.25,
	};

	CoordType normals[] = {
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	};

	CoordType texcoords[] = {
	0, 0,
	1, 0,
	1, 1,
	0, 1,
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	0, 0,
	1, 0,
	1, 1,
	0, 1,
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	0, 0,
	1, 0,
	1, 1,
	0, 1,
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	};

	IndexType indices[] = {
		0, 2, 1,
		0, 3, 2,
		4, 6, 5,
		4, 7, 6,
		8, 10, 9,
		8, 11, 10,
		12, 14, 13,
		12, 15, 14,
		16, 18, 17,
		16, 19, 18,
		20, 22, 21,
		20, 23, 22,
	};


}