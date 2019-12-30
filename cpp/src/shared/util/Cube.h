#pragma once

namespace cube {

	typedef float CoordType;
	typedef unsigned short IndexType;

	extern unsigned int numVertices;
	extern unsigned int numIndices;
	extern unsigned int numPointsPerVertex;

	extern CoordType vertices[];
	extern CoordType normals[];
	extern CoordType texcoords[];
	extern IndexType indices[];
}