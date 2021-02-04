#include "CSoundGeometry.h"
#include "CAudioManager.h"
#include "Visualizer.h"
#include "Colors.h"

CSoundGeometry::CSoundGeometry(int maxPolys, int maxVerts)
{
	FMOD_RESULT result;
	result = CAudioManager::CreateFMODGeometry(maxPolys, maxVerts, &geoObj);
	assert(result == FMOD_OK);
}

CSoundGeometry::~CSoundGeometry()
{
	FMOD_RESULT result;
	result = geoObj->release();
	assert(result == FMOD_OK);
}

void CSoundGeometry::SetPosition(const Vect& newPos)
{
	//convert vect to FMOD format
	FMOD_VECTOR FMODnewPos;
	FMODnewPos.x = newPos.X();
	FMODnewPos.y = newPos.Y();
	FMODnewPos.z = newPos.Z();
	
	FMOD_RESULT result;
	result = geoObj->setPosition(&FMODnewPos);
	assert(result == FMOD_OK);
}

Vect CSoundGeometry::GetPosition() const
{
	FMOD_VECTOR FMODpos;
	FMOD_RESULT result;
	result = geoObj->getPosition(&FMODpos);
	assert(result == FMOD_OK);

	//convert FMOD vect to Cinnabar vect
	return Vect(FMODpos.x, FMODpos.y, FMODpos.z);
}

void CSoundGeometry::SetRotation(const Vect& newFwd, const Vect& newUp)
{
	//convert vects to FMOD format
	FMOD_VECTOR FMODnewFwd;
	FMODnewFwd.x = newFwd.X();
	FMODnewFwd.y = newFwd.Y();
	FMODnewFwd.z = newFwd.Z();
	FMOD_VECTOR FMODnewUp;
	FMODnewUp.x = newUp.X();
	FMODnewUp.y = newUp.Y();
	FMODnewUp.z = newUp.Z();

	FMOD_RESULT result;
	result = geoObj->setRotation(&FMODnewFwd, &FMODnewUp);
	assert(result == FMOD_OK);
}

void CSoundGeometry::GetRotation(Vect* fwd, Vect* up) const
{
	FMOD_VECTOR FMODfwd;
	FMOD_VECTOR FMODup;
	FMOD_RESULT result;
	result = geoObj->getRotation(&FMODfwd, &FMODup);
	assert(result == FMOD_OK);

	//convert FMOD vects to Cinnabar vects
	fwd->set(FMODfwd.x, FMODfwd.y, FMODfwd.z);
	up->set(FMODup.x, FMODup.y, FMODup.z);
}

void CSoundGeometry::SetScale(const Vect& newScale)
{
	//convert vect to FMOD format
	FMOD_VECTOR FMODnewScale;
	FMODnewScale.x = newScale.X();
	FMODnewScale.y = newScale.Y();
	FMODnewScale.z = newScale.Z();

	FMOD_RESULT result;
	result = geoObj->setScale(&FMODnewScale);
	assert(result == FMOD_OK);
}

Vect CSoundGeometry::getScale() const
{
	FMOD_VECTOR FMODscl;
	FMOD_RESULT result;
	result = geoObj->getScale(&FMODscl);
	assert(result == FMOD_OK);

	//convert FMOD vect to Cinnabar vect
	return Vect(FMODscl.x, FMODscl.y, FMODscl.z);
}

void CSoundGeometry::SetActive(bool newActive)
{
	FMOD_RESULT result;
	result = geoObj->setActive(newActive);
	assert(result == FMOD_OK);
}

bool CSoundGeometry::GetActive() const
{
	FMOD_RESULT result;
	bool active;
	result = geoObj->getActive(&active);
	assert(result == FMOD_OK);
	return active;
}

void CSoundGeometry::AddPolygon(float directOcclusion, float reverbOcclusion, bool doubleSided, int numVerts, Vect* verts, int* polyInd)
{
	//convert entire Vect array to FMOD_VECTORs...gotta love FMOD
	FMOD_VECTOR* FMODverts = new FMOD_VECTOR[numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		FMODverts[i].x = verts[i].X();
		FMODverts[i].y = verts[i].Y();
		FMODverts[i].z = verts[i].Z();
	}

	FMOD_RESULT result;
	result = geoObj->addPolygon(directOcclusion, reverbOcclusion, doubleSided, numVerts, FMODverts, polyInd);
	assert(result == FMOD_OK);

	delete[] FMODverts;
	FMODverts = nullptr;
}

void CSoundGeometry::SetPolygonAttributes(int index, float directOcclusion, float reverbOcclusion, bool doubleSided)
{
	FMOD_RESULT result;
	result = geoObj->setPolygonAttributes(index, directOcclusion, reverbOcclusion, doubleSided);
	assert(result == FMOD_OK);
}

void CSoundGeometry::GetPolygonAttributes(int index, float* directOcclusion, float* reverbOcclusion, bool* doubleSided) const
{
	FMOD_RESULT result;
	result = geoObj->getPolygonAttributes(index, directOcclusion, reverbOcclusion, doubleSided);
	assert(result == FMOD_OK);
}

//debug function used in visualizing geometry dims
void CSoundGeometry::ComputePolysMinMax(Vect* outMin, Vect* outMax, const Matrix& world)
{
	//initial reference for min/max
	FMOD_VECTOR FMODmin;
	FMOD_VECTOR FMODmax;
	FMOD_RESULT result;
	result = geoObj->getPolygonVertex(0, 0, &FMODmin);
	assert(result == FMOD_OK);
	FMODmax = FMODmin;

	//unfortunately need to convert every single vector checked to Cinnabar vects first. This is because FMOD_VECTORs
	//don't have a w, and no FMOD_MATRIX class exists. So to move the FMOD_VECTORs to world space I have to convert them
	//first then do Vect * world Matrix
	Vect min(FMODmin.x, FMODmin.y, FMODmin.z);
	min *= world;
	Vect max(FMODmax.x, FMODmax.y, FMODmax.z);
	max *= world;

	float minX = min.X();
	float maxX = max.X();
	float minY = min.Y();
	float maxY = max.Y();
	float minZ = min.Z();
	float maxZ = max.Z();

	int numPolys;
	result = geoObj->getNumPolygons(&numPolys);
	assert(result == FMOD_OK);

	int numVerts;

	for (int i = 0; i < numPolys; i++)
	{
		result = geoObj->getPolygonNumVertices(i, &numVerts);
		assert(result == FMOD_OK);
		for (int j = 0; j < numVerts; j++)
		{
			FMOD_VECTOR FMODcurrVert;
			result = geoObj->getPolygonVertex(i, j, &FMODcurrVert);
			assert(result == FMOD_OK);

			//convert vect + move to world
			Vect currVert(FMODcurrVert.x, FMODcurrVert.y, FMODcurrVert.z);
			currVert *= world;

			if (currVert.X() < minX)
			{
				minX = currVert.X();
			}
			else if (currVert.X() > maxX)
			{
				maxX = currVert.X();
			}
			if (currVert.Y() < minY)
			{
				minY = currVert.Y();
			}
			else if (currVert.Y() > maxY)
			{
				maxY = currVert.Y();
			}
			if (currVert.Z() < minZ)
			{
				minZ = currVert.Z();
			}
			else if (currVert.Z() > maxZ)
			{
				maxZ = currVert.Z();
			}
		}
	}
	outMin->set(minX, minY, minZ);
	outMax->set(maxX, maxY, maxZ);
}