#include "TerrainModel.h"
#include "Model.h"
#include "GpuVertTypes.h"
#include <assert.h>
#include "GraphicsObject_TextureLight.h"
//#include "GraphicsObject_WireframeConstantColor.h"
#include "TextureTGA.h"
#include "Visualizer.h"
//debug
#include "Colors.h"
#include "ScreenLog.h"

//to render
#include "SceneManager.h"

//for abs()
#include <cmath>
#include "CMathTools.h"

//#include "ShaderManager.h"
//#include "TextureManager.h"

TerrainModel::TerrainModel(const char* heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, ShaderObject* shd, Texture* tx): mWorld(Matrix(IDENTITY))
{
	int imgWidth;
	int imgHeight;
	int icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(heightmapFile, &imgWidth, &imgHeight, &icomp, &dtype);
	//make sure the heightmap is square
	assert(imgWidth == imgHeight && imgWidth != 0);

	side = imgHeight;	// the image should be square
	length = len;
	cellDim = len / (float)(side - 1);
	size_t pixel_width = 3;			// 3 bytes RGB per pixel
	//uint8_t h_val = hgtmap->pixels[ pixel_width * (5 * side + 3) ]; // the 'R' byte of the pixel at (3,5)


	// ** much work to add below **

	//data to transfer to the model constructor
	//1 vertex for each texel (in this case, each pixel of the height map)
	int numVerts = side * side;
	VertexStride_VUN* pVerts = new VertexStride_VUN[numVerts];
	vertexNormals = new Vect[numVerts];
	//if you think about this in terms of "pairs of triangles" that make up a square (i. e.
	//a pixel), each row/column has enough room to made "side - 1" "pairs" (in an 8x8 image,
	//each row and each column has 7 of these "pairs")
	int numTris = (side - 1) * (side - 1) * 2;
	TriangleIndex* pTris = new TriangleIndex[numTris];

	//setting points
	unsigned int currRow;
	unsigned int currCol;
	int currVert = 0;
	//amount to change the UV by for each vect
	float UIncrementAmt = (float)RepeatU / (float)side;
	float VIncrementAmt = (float)RepeatV / (float)side;
	float nextUVal = 0.0f;
	float nextVVal = 0.0f;
	for (currCol= 0; currCol < side; currCol++)
	{
		nextUVal = 0.0f;
		nextVVal += VIncrementAmt;
		float currVertZLen = -(len / 2) + ((float)currCol * cellDim);
		for (currRow = 0; currRow < side; currRow++)
		{
			float currVertXLen = (len / 2) - ((float)currRow * cellDim);
			//need to do static cast to get char in (0, 255) range
			uint8_t h_val = static_cast<unsigned char>(imgData[pixel_width * (currCol * side + currRow)]);
			pVerts[currVert].set(currVertXLen, (maxheight * (h_val / 255.0f)) + ytrans, currVertZLen, nextUVal, nextVVal, 0.0f, 0.0f, 0.0f);
			currVert++;
			nextUVal += UIncrementAmt;
		}

	}

	//finally done initializing points - now for triangles...
	//will set them all in only 1 loop - 1 for = 1 row of the grid
	//going to form triangles 2 at a time in the loop - keep track of what vert will
	//be the reference point for making the pair:
	int currVertForTris = 0;
	//and which triangle index it will be filling, of course
	int currTriIndex;
	//Go through enough rows to create all the "pairs", as discussed earlier
	unsigned int currColForTriLoop;
	int rowsTraversed = 0;
	for (currColForTriLoop = 0; currColForTriLoop < side - 1; currColForTriLoop++)
	{
		//1st and last triangles in the row need to be handled differently - save what indices
		//they are for later
		int colFirstTriIndex = rowsTraversed * ((side - 1) * 2);
		//at this point, there will have been another row traversed except for 1 triangle
		int colLastTriIndex = ((rowsTraversed + 1) * ((side - 1) * 2));
		for (currTriIndex = colFirstTriIndex; currTriIndex < colLastTriIndex; currTriIndex += 2)
		{
			pTris[currTriIndex].set(currVertForTris, currVertForTris + side + 1, currVertForTris + side);
			pTris[currTriIndex + 1].set(currVertForTris, currVertForTris + 1, currVertForTris + side + 1);
			currVertForTris++;
		}
		//mark that the row has been advanced
		rowsTraversed++;
		//move the base vert ahead 1 more so that on the next loop, it starts on the 1st vert of the next row
		currVertForTris++;
	}

	//now to compute normals - go through each vertex of the plane not along its edge, do math to get the normals of the 6 faces it touches, then
	//find the average of those 6 normals to get the vertex normal
	Vect faceNormals[6];
	Vect helperVect1;
	Vect helperVect2;
	Vect helperVectCross;
	//begin at the first non-edge vertex. The outer loop is for rows, the inner loop for columns. For both loops, end at the last row/column before hitting the edge
	for (currCol = 1; currCol < side - 1; currCol++)
	{
		for (currRow = 1; currRow < side - 1; currRow++)
		{
			Vect normsAdded = Vect(0.0f, 0.0f, 0.);
			currVert = (side * currCol) + currRow;
			Vect currVertPos = Vect(pVerts[currVert].x, pVerts[currVert].y, pVerts[currVert].z);
			Vect adjVect1 = Vect(pVerts[currVert + 1].x, pVerts[currVert + 1].y, pVerts[currVert + 1].z);
			Vect adjVect2 = Vect(pVerts[currVert - 1].x, pVerts[currVert - 1].y, pVerts[currVert - 1].z);
			Vect adjVect3 = Vect(pVerts[currVert - (side + 1)].x, pVerts[currVert - (side + 1)].y, pVerts[currVert - (side + 1)].z);
			Vect adjVect4 = Vect(pVerts[currVert + (side + 1)].x, pVerts[currVert + (side + 1)].y, pVerts[currVert + (side + 1)].z);
			Vect adjVect5 = Vect(pVerts[currVert + side].x, pVerts[currVert + side].y, pVerts[currVert + side].z);
			Vect adjVect6 = Vect(pVerts[currVert - side].x, pVerts[currVert - side].y, pVerts[currVert - side].z);
			helperVect1 = currVertPos - adjVect3;
			helperVect2 = currVertPos - adjVect2;
			helperVectCross = helperVect1.cross(helperVect2);
			faceNormals[0] = helperVectCross.getNorm();
			helperVect1 = currVertPos - adjVect6;
			helperVect2 = currVertPos - adjVect3;
			helperVectCross = helperVect1.cross(helperVect2);
			faceNormals[1] = helperVectCross.getNorm();
			helperVect1 = currVertPos - adjVect1;
			helperVect2 = currVertPos - adjVect6;
			helperVectCross = helperVect1.cross(helperVect2);
			faceNormals[2] = helperVectCross.getNorm();
			helperVect1 = currVertPos - adjVect2;
			helperVect2 = currVertPos - adjVect5;
			helperVectCross = helperVect1.cross(helperVect2);
			faceNormals[3] = helperVectCross.getNorm();
			helperVect1 = currVertPos - adjVect5;
			helperVect2 = currVertPos - adjVect4;
			helperVectCross = helperVect1.cross(helperVect2);
			faceNormals[4] = helperVectCross.getNorm();
			helperVect1 = currVertPos - adjVect4;
			helperVect2 = currVertPos - adjVect1;
			helperVectCross = helperVect1.cross(helperVect2);
			faceNormals[5] = helperVectCross.getNorm();
			for (int i = 0; i < 6; i++)
			{
				normsAdded += faceNormals[i];
			}
			Vect vectNormal = Vect(normsAdded.X() / 6.0f, normsAdded.Y() / 6.0f, normsAdded.Z() / 6.0f);
			//not sure why I need to negate these...
			pVerts[currVert].setNormal(-vectNormal);
			vertexNormals[currVert] = -vectNormal;
		}
	}

	//finally this 3rd loop!!! is for finding the cell min/max pairs
	//(side - 1)^2 is how many cells are present
	numCells = (side - 1) * (side - 1);
	cellMinMaxPairs = new CellMinMaxPair[numCells];
	int curCell = 0;
	//outer loop is for rows
	for (currCol = 0; currCol < side - 1; currCol++)
	{
		//inner loop is for columns
		for (currRow = 0; currRow < side - 1; currRow++)
		{
			//"base" vertex is the "top-left" corner of the cell in XZ space
			unsigned int baseVertIndex = currRow + (currCol * side);
			VertexStride_VUN corner1 = pVerts[baseVertIndex];
			VertexStride_VUN corner2 = pVerts[baseVertIndex + 1];
			VertexStride_VUN corner3 = pVerts[baseVertIndex + side];
			VertexStride_VUN corner4 = pVerts[baseVertIndex + side + 1];
			//search for max + min Y values among the 4 vertices
			float minY = corner1.y;
			float maxY = corner1.y;
			if (corner2.y < minY)
			{
				minY = corner2.y;
			}
			else if (corner2.y > maxY)
			{
				maxY = corner2.y;
			}
			if (corner3.y < minY)
			{
				minY = corner3.y;
			}
			else if (corner3.y > maxY)
			{
				maxY = corner3.y;
			}
			if (corner4.y < minY)
			{
				minY = corner4.y;
			}
			else if (corner4.y > maxY)
			{
				maxY = corner4.y;
			}
			cellMinMaxPairs[curCell].min.set(corner4.x, minY, corner1.z);
			cellMinMaxPairs[curCell].max.set(corner1.x, maxY, corner4.z);
			curCell++;
		}
	}

	pModTerrain = new Model(pVerts, numVerts, pTris, numTris);

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	terr = new GraphicsObject_TextureLight(pModTerrain, shd, tx, LightColor, LightPos);
	Vect col = Vect(255, 255, 255);
	//terr = new GraphicsObject_WireframeConstantColor(pModTerrain, shd, col);

	delete[] pVerts;
	delete[] pTris;
}

void TerrainModel::TerrainRender()
{
	terr->Render(SceneManager::getCurrentCamera());
	//Visualizer::ShowTerrainCollision(this, numCells, Colors::Yellow);
	//Visualizer::ShowTerrainCell(this, 46.0f, 16.0f, Colors::Yellow);
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
	pModTerrain = nullptr;
	delete terr;
	terr = nullptr;
	delete[] cellMinMaxPairs;
	cellMinMaxPairs = nullptr;
	delete[] vertexNormals;
	vertexNormals = nullptr;
}

//int TerrainModel::getVertexIndex(int x, int y)
//{
//	return x + (y * side);
//}

TerrainModel::CellMinMaxPair* TerrainModel::getCellMinMaxCoords() const
{
	return cellMinMaxPairs;
}

int TerrainModel::getCellIndexAt2DCoords(float xCoord, float zCoord) const
{
	if (xCoord >= (length / 2) || xCoord <= -(length / 2))
	{
		throw std::runtime_error("X-coordinate is off of the terrain!");
	}

	if (zCoord >= (length / 2) || zCoord <= -(length / 2))
	{
		throw std::runtime_error("Z-coordinate is off of the terrain!");
	}
	//calculating row cell. Cells start in the bottom-left corner, so the "origin" of the plane in world-space is (length, -length). Adding
	//xCoord from -length gives us the offset from the origin in the x direction. We don't care about the sign, only the number returned
	float xOffset = -(length / 2) + xCoord;
	//the same process applies for the z-coordinates, except this time subtract zCoord from +length
	float zOffset = -(length / 2) - zCoord;
	//take the absolute value of each offset to get the raw distance units traveled in each direction
	xOffset = abs(xOffset);
	zOffset = abs(zOffset);
	//dividing the resulting offsets by the dimensions of a cell returns which number row/column you are currently in, since the rows/columns start
	//at 0. For example, an x offset of 40 divided by a cell dimension of 16 will return being in row 2. The same applies for the column.
	float rowF = xOffset / cellDim;
	float colF = zOffset / cellDim;
	unsigned int rowIn = (int)(floorf(rowF));
	unsigned int columnIn = (int)(floorf(colF));
	//use these new values to access the correct cell in the array. columnIn is multiplied by side to account for the length of all the rows
	//that must have been traversed to reach the column currently being occupied.
	return (int)(rowIn)+(int)(columnIn * (side - 1));
}

const TerrainModel::CellMinMaxPair& TerrainModel::getCellAtIndex(int index) const
{
	return cellMinMaxPairs[index];
}

const TerrainModel::CellMinMaxPair& TerrainModel::getCellAt2DCoords(float xCoord, float zCoord) const
{
	int ind = getCellIndexAt2DCoords(xCoord, zCoord);
	ScreenLog::Add("Inside cell %d", ind);
	return getCellAtIndex(ind);
}

int TerrainModel::GetNumCells() const
{
	return numCells;
}

const TriangleIndex& TerrainModel::getTriAt2DCoords(float xCoord, float zCoord) const
{
	if (xCoord >= (length / 2) || xCoord <= -(length / 2))
	{
		throw std::runtime_error("X-coordinate is off of the terrain!");
	}

	if (zCoord >= (length / 2) || zCoord <= -(length / 2))
	{
		throw std::runtime_error("Z-coordinate is off of the terrain!");
	}
	int triInd;

	//calculating row cell. Cells start in the bottom-left corner, so the "origin" of the plane in world-space is (length, -length). Adding
	//xCoord from -length gives us the offset from the origin in the x direction. We don't care about the sign, only the number returned
	float xOffset = -(length / 2) + xCoord;
	//the same process applies for the z-coordinates, except this time subtract zCoord from +length
	float zOffset = -(length / 2) - zCoord;
	//take the absolute value of each offset to get the raw distance units traveled in each direction
	xOffset = abs(xOffset);
	zOffset = abs(zOffset);
	//dividing the resulting offsets by the dimensions of a cell returns which number row/column you are currently in, since the rows/columns start
	//at 0. For example, an x offset of 40 divided by a cell dimension of 16 will return being in row 2. The same applies for the column.
	float rowF = xOffset / cellDim;
	float colF = zOffset / cellDim;
	unsigned int rowIn = (int)(floorf(rowF));
	unsigned int columnIn = (int)(floorf(colF));
	//use these new values to access the correct cell in the array. columnIn is multiplied by side to account for the length of all the rows
	//that must have been traversed to reach the column currently being occupied.
	int cellInd = (int)(rowIn)+(int)(columnIn * (side - 1));

	//get the base vertex of the cell to be able to perform the upper or lower triangle test
	Vect baseVert = pModTerrain->getVectList()[cellInd + columnIn];
	//y values are unimportant here
	Vect testVect = Vect(xCoord, 0.0f, zCoord) - Vect(baseVert.X(), 0.0f, baseVert.Z());
	if (-testVect.X() > testVect.Z())
	{
		triInd = (cellInd * 2) + 1;
	}
	else
	{
		triInd = cellInd * 2;
	}
	//ScreenLog::Add("Got triangle %d", triInd);
	return pModTerrain->getTriangleList()[triInd];
}

float TerrainModel::interpHeightAt2DCoords(float xCoord, float zCoord) const
{
	//First get the triangle at the 2D coords so the points to interpolate with can
	//be determined
	Vect* vectList = pModTerrain->getVectList();
	TriangleIndex tri = getTriAt2DCoords(xCoord, zCoord);
	float height = CMathTools::interpFloat2D(vectList[tri.v0], vectList[tri.v1], vectList[tri.v2], vectList[tri.v0].Y(), vectList[tri.v1].Y(), vectList[tri.v2].Y(), Vect(xCoord, 0.0f, zCoord));
	//ScreenLog::Add("Height is %f", height);
	return height;
}

Vect TerrainModel::interpNormalAt2DCoords(float xCoord, float zCoord) const
{
	//First get the triangle at the 2D coords so the points to interpolate with can
	//be determined
	Vect* vectList = pModTerrain->getVectList();
	TriangleIndex tri = getTriAt2DCoords(xCoord, zCoord);
	Vect norm = CMathTools::interpVect2D(vectList[tri.v0], vectList[tri.v1], vectList[tri.v2], vertexNormals[tri.v0], vertexNormals[tri.v1], vertexNormals[tri.v2], Vect(xCoord, 0.0f, zCoord));
	//ScreenLog::Add("Normal is: (%f, %f, %f)", norm.X(), norm.Y(), norm.Z());
	return norm;
}

float TerrainModel::getCellDim() const
{
	return cellDim;
}

size_t TerrainModel::getSideLen() const
{
	return side;
}