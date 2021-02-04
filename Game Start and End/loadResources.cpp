#include "../CinnabarEngine.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "TerrainModelManager.h"
#include "CAudioManager.h"
#include "CSoundAssetManager.h"
#include "DemoScene.h"
#include "CameraManager.h"
#include "VisualizerAttorney.h"
#include "SpriteFontManager.h"
#include "ScreenLogAttorney.h"
#include "BulletFactory.h"
#include "TankIntroScene.h"
#include "TankScene1.h"
#include "TankScene2.h"
#include "CAudioManagerAttorney.h"

//for creating skybox model
#include "GpuVertTypes.h"

/**********************************************************************************************//**
 * \fn	void CinnabarEngine::loadResources()
 *
 * \brief	User-defined. Specify which resources need to be loaded for a specific game. Kept in a separate file from
 * 			the engine initialization code so the user can't access/modify it.
 **************************************************************************************************/

void CinnabarEngine::loadResources()
{
	//---------------------------------------------------------------------------------------------------------
// Load the Models
//---------------------------------------------------------------------------------------------------------

// Model from file ( .azul format)
	ModelManager::loadModel("ModelAxis", "Axis.azul");
	ModelManager::loadModel("ModelPlane", "Plane.azul");

	ModelManager::loadModel("ModelSpaceFrigate", "space_frigate.azul");
	ModelManager::loadModel("ModelCottage", "Cottage.azul");
	ModelManager::loadModel("ModelSphere", Model::PreMadeModels::UnitSphere);
	ModelManager::loadModel("ModelBox_WF", Model::PreMadeModels::UnitBox_WF);
	//standard model for sprites to use
	ModelManager::loadModel("SpriteModel", Model::PreMadeModels::UnitSquareXY);
	ModelManager::loadModel("TankBody", "t99body.azul");
	ModelManager::loadModel("TankTurret", "t99turret.azul");
	ModelManager::loadModel("Tree", "tree.azul");
	ModelManager::loadModel("Tree2", "tree2.azul");
	ModelManager::loadModel("Rock", "rock.azul");

	//creating skybox model? Not really sure the best way to port this...
	float dim = 1100.0f;
	int nverts = 24;
	VertexStride_VUN* pVerts = new VertexStride_VUN[nverts];
	int ntri = 12;
	TriangleIndex* pTriList = new TriangleIndex[ntri];

	// Setting up faces
	// Forward
	//top rt top left
	//top lt bot lt
	//bot lt bot rt
	//bot rt top rt
	//bot lt 0 0.375
	//bot rt 0 0.625
	//top lt 0.25 0.375
	//top rt 0.25 0.625
	int vind = 0;
	int tind = 0;
	//top right
	pVerts[vind].set(dim, dim * 2, dim, 0.25, 0.375, 1.0f, 1.0f, 1.0f);
	//top left
	pVerts[vind + 1].set(-dim, dim * 2, dim, 0.5, 0.375, 1.0f, 1.0f, 1.0f);
	//bottom left
	pVerts[vind + 2].set(-dim, -1, dim, 0.5, 0.625, 1.0f, 1.0f, 1.0f);
	//bottom right
	pVerts[vind + 3].set(dim, -1, dim, 0.25, 0.625, 1.0f, 1.0f, 1.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Back
	vind += 4;
	tind += 2;

	//top rt bot rt
	//top lt top rt
	//bot lt top lt
	//bot rt bot lt
	//bot lt 0.75 0.625
	//bot rt 1 0.625
	//top lt 0.75 0.375
	//top rt 1 0.375

	//top left?
	pVerts[vind].set(dim, dim * 2, -dim, 1, 0.375, 1.0f, 1.0f, 1.0f);
	//bottom left?
	pVerts[vind + 1].set(-dim, dim * 2, -dim, 0.75, 0.375, 1.0f, 1.0f, 1.0f);
	//bottom right
	pVerts[vind + 2].set(-dim, -1, -dim, 0.75, 0.625, 1.0f, 1.0f, 1.0f);
	//top right
	pVerts[vind + 3].set(dim, -1, -dim, 1, 0.625, 1.0f, 1.0f, 1.0f);
	/*
	// used to demo texture address modes
	pVerts[vind].set(0.5f, 0.5f, -0.5f, -3, -3);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 3, -3);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 3, 3);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, -3, 3);
	//*/
	pTriList[tind].set(vind + 1, vind + 2, vind);
	pTriList[tind + 1].set(vind + 2, vind + 3, vind);

	// Left
	vind += 4;
	tind += 2;
	//top right
	pVerts[vind].set(dim, dim * 2, -dim, 0, 0.375, 1.0f, 1.0f, 1.0f);
	//top left
	pVerts[vind + 1].set(dim, dim * 2, dim, 0.25, 0.375, 1.0f, 1.0f, 1.0f);
	//bot left
	pVerts[vind + 2].set(dim, -1, dim, 0.25, 0.625, 1.0f, 1.0f, 1.0f);
	//bot right
	pVerts[vind + 3].set(dim, -1, -dim, 0, 0.625, 1.0f, 1.0f, 1.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Right
	vind += 4;
	tind += 2;
	//top right
	pVerts[vind].set(-dim, dim * 2, dim, 0.5, 0.375, 1.0f, 1.0f, 1.0f);
	//top left
	pVerts[vind + 1].set(-dim, dim * 2, -dim, 0.75, 0.375, 1.0f, 1.0f, 1.0f);
	//bot left
	pVerts[vind + 2].set(-dim, -1, -dim, 0.75, 0.625, 1.0f, 1.0f, 1.0f);
	//bot right
	pVerts[vind + 3].set(-dim, -1, dim, 0.5, 0.625, 1.0f, 1.0f, 1.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Top
	vind += 4;
	tind += 2;

	//top rt bot rt
	//top lt top rt
	//bot lt top lt
	//bot rt bot lt
	//bot lt 0.25 0.375
	//bot rt 0.5 0.375
	//top lt 0.25 0.125
	//top rt 0.5 0.125

	//bottom left?
	pVerts[vind].set(dim, dim * 2, -dim, 0.25, 0.125, 1.0f, 1.0f, 1.0f);
	//top left?
	pVerts[vind + 1].set(-dim, dim * 2, -dim, 0.5, 0.125, 1.0f, 1.0f, 1.0f);
	//top right?
	pVerts[vind + 2].set(-dim, dim * 2, dim, 0.5, 0.375, 1.0f, 1.0f, 1.0f);
	//bottom right?
	pVerts[vind + 3].set(dim, dim * 2, dim, 0.25, 0.375, 1.0f, 1.0f, 1.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Bottom
	vind += 4;
	tind += 2;

	//bot left top right
	//bot right top left
	//top right bot left
	//top left bot right

	//bot left = (1, 0.625)
	//bot right = (1, 0.375)
	//top left = (0.75, 0.625)
	//top right = (0.75, 0.375)

	//top right
	pVerts[vind].set(dim, -1, dim, 0.25, 0.625, 1.0f, 1.0f, 1.0f);
	//top left
	pVerts[vind + 1].set(-dim, -1, dim, 0.5, 0.625, 1.0f, 1.0f, 1.0f);
	//bottom left
	pVerts[vind + 2].set(-dim, -1, -dim, 0.5, 0.875, 1.0f, 1.0f, 1.0f);
	//bottom right
	pVerts[vind + 3].set(dim, -1, -dim, 0.25, 0.875, 1.0f, 1.0f, 1.0f);
	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	ModelManager::loadModel("Skybox", new Model(pVerts, nverts, pTriList, ntri));

	delete[] pVerts;
	delete[] pTriList;

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	// Direct loads
	TextureManager::loadTexture("SpaceFrigateTex", "space_frigate.tga");
	TextureManager::loadTexture("TextPlane", "grid.tga");
	TextureManager::loadTexture("CottageTex", "Rooftexture.tga");
	TextureManager::loadTexture("Enemy1Tex", 255, 0, 255);
	TextureManager::loadTexture("StitchTexture", "stitch.tga");
	TextureManager::loadTexture("TankBodyTex", "body.tga");
	TextureManager::loadTexture("TankTrackTex", "track.tga");
	TextureManager::loadTexture("Level1Ground", "grass.tga");
	TextureManager::loadTexture("PlayerTank", 0, 255, 0);
	TextureManager::loadTexture("EnemyTank", 255, 0, 0);
	TextureManager::loadTexture("RedBrick", "RedBrick.tga");
	TextureManager::loadTexture("TreeTex", "tree_tex.tga");
	TextureManager::loadTexture("SkyboxTex", "SBSeaView.tga");
	TextureManager::loadTexture("TreeBark", "TreeBark.tga");
	TextureManager::loadTexture("TreeLeaves", "TreeLeaves.tga");
	TextureManager::loadTexture("Rock", "RockTex.tga");
	TextureManager::loadTexture("MoonTex", "MoonTex.tga");
	TextureManager::loadTexture("MoonSkybox", "NightSkybox.tga");

	TextureManager::loadFontTexture("TestFont", "Fonts/TestFont.tga");


	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------

	ShaderManager::loadShader("ShaderObject_texture", "textureFlatRender");
	ShaderManager::loadShader("ShaderObject_textureLight", "textureLightRender");
	ShaderManager::loadShader("ShaderObject_constantColor", "colorConstantRender");
	ShaderManager::loadShader("ShaderObject_colorNoTexture", "colorNoTextureRender");
	//standard shader for sprites to use
	ShaderManager::loadShader("SpriteShader", "spriteRender");

	//---------------------------------00------------------------------------------------------------------------
	// Load the Images
	//---------------------------------------------------------------------------------------------------------

	ImageManager::loadImage("StitchImg", TextureManager::getTexture("StitchTexture"));

	//Initialize visualizer (need to do this after models and shaders are loaded)
	VisualizerAttorney::GameLoop::Initialize();

	//---------------------------------------------------------------------------------------------------------
	// Load the Sprite Fonts
	// DO NOT INCLUDE THE .tga IN THE FILE NAMES - so the XML parser can work as provided
	// also the sprite font key must match the key of the texture it uses
	//---------------------------------------------------------------------------------------------------------
	SpriteFontManager::loadSpriteFont("TestFont", "TestFont");
	ScreenLogAttorney::GameLoop::Initialize();

	//Load Terrains
	TerrainModelManager::loadTerrain("TestTerrain", "HMtest.tga", 900.0f, 100.0f, 0.0f, 10, 10, ShaderManager::getShader("ShaderObject_textureLight"), TextureManager::getTexture("Level1Ground"));
	TerrainModelManager::loadTerrain("TestTerrain2", "HMtest2.tga", 900.0f, 100.0f, 0.0f, 10, 10, ShaderManager::getShader("ShaderObject_textureLight"), TextureManager::getTexture("MoonTex"));

	//Initialize Factories
	BulletFactory::Initialize();

	//Load Sounds
	CAudioManagerAttorney::gameLoop::Initialize();
	CSoundAssetManager::loadSound("TestSound", "TestSound.wav");
	CSoundAssetManager::loadSound("ForestTestSound", "ForestTestSound.wav");
	CSoundAssetManager::loadSound("SoapTestSound", "SoapTestSound.wav");
	CSoundAssetManager::loadSound("LaunchTestSound", "LaunchTestSound.wav");

	//SceneManager::setStartScene(new DemoScene());
	SceneManager::setStartScene(new TankIntroScene());
	//SceneManager::setStartScene(new TankScene2());
}