//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "GameMan.h"
#include "MathEngine.h"
#include "GameObject.h"
#include "ShaderObject.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "PyramidModel.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObjectWireframeConstantColor.h"
#include "Texture.h"
#include "InputMan.h"
#include "InputTest.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "AnimationGameObject.h"
#include "ModelMan.h"
#include "ShaderMan.h"
#include "BoundingSphereGameObject.h"
#include "CameraMan.h"
#include "Camera3D.h"
#include "Camera2D.h"
#include "CameraModel.h"
#include "CameraDemoInput.h"
#include "AnimTime.h"
#include "AnimTimer.h"
#include "VectApp.h"
#include "QuatApp.h"
#include "Anim.h"
#include "TimerController.h"
#include "AnimController.h"
#include "AnimControllerMan.h"
#include "Clip.h"
#include "ClipMan.h"
#include "AnimationDemoInput.h"
#include "AstroboyModel.h"
#include "BuggyModel.h"
#include "WarbearModel.h"
#include "SimpleGameObject.h"
#include "ImageMan.h"
#include "GraphicsObject_Sprite.h"
#include "SpriteModel.h"
#include "GameObject2D.h"
#include "GlyphMan.h"
#include "FontMan.h"
#include "SkinModel.h"
#include "GraphicsObject_SkinTexture.h"
#include "GameObjectRigid.h"
#include "DynamicFontDemo.h"
#include "AnimTransitionController.h"
#include "AnimTransitionControllerMan.h"


using namespace Azul;



// for dynamic font demo
char* pChar;


//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char* const pWindowName, const int Width, const int Height)
	:Engine(pWindowName, Width, Height)
{
	assert(pWindowName);
	this->globalTimer.Tic();
	this->intervalTimer.Tic();
}

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	pChar = new char[10000];
}


//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
	// Start the Managers
	InputMan::Create();
	ModelMan::Create();
	ShaderMan::Create();
	CameraMan::Create();
	ClipMan::Create();
	AnimControllerMan::Create();
	AnimTransitionControllerMan::Create();
	ImageMan::Create();
	GlyphMan::Create();
	FontMan::Create();
	// Load the Cameras
	Camera3D* pCam3D = new Camera3D(Camera::Type::PERSPECTIVE_3D);
	pCam3D->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
	pCam3D->setPerspective(35.0f, float(pCam3D->getScreenWidth()) / float(pCam3D->getScreenHeight()), 1.0f, 40000.0f);
	pCam3D->setOrientAndPosition(Vect(0.0f, 0.0f, 1.0f), Vect(0.0f, 0.0f, 0.0f), Vect(4000.0f, 0.0f, 0.0f));
	pCam3D->updateCamera();
	CameraMan::Add(Camera::Name::CAMERA_0, pCam3D);
	CameraMan::SetCurrent(Camera::Name::CAMERA_0, Camera::Type::PERSPECTIVE_3D);

	Camera2D* pCam2D = new Camera2D(Camera::Type::ORTHOGRAPHIC_2D);
	pCam2D->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
	pCam2D->setOrthographic((float)-pCam2D->getScreenWidth() / 2.0f, (float)pCam2D->getScreenWidth() / 2.0f,
		(float)-pCam2D->getScreenHeight() / 2.0f, (float)pCam2D->getScreenHeight() / 2.0f,
		1.0f, 1000.0f);
	pCam2D->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, -1.0f), Vect(0.0f, 0.0f, 2.0f));
	CameraMan::Add(Camera::Name::CAMERA_1, pCam2D);
	CameraMan::SetCurrent(Camera::Name::CAMERA_1, Camera::Type::ORTHOGRAPHIC_2D);


	// Astroboy with default hot pink Texture
	AstroboyModel* pAstroboyModel = new AstroboyModel("astroboy.azul");
	assert(pAstroboyModel);
	pAstroboyModel->SetModelType(Model::ModelType::ASTROBOY);
	ModelMan::Add(pAstroboyModel);

	// --- BUGGY MODEL --- //
	BuggyModel* pBuggyModel = new BuggyModel("buggy.azul", 0);
	assert(pBuggyModel);
	pBuggyModel->SetModelType(Model::ModelType::BUGGY);
	ModelMan::Add(pBuggyModel);

	// --- WARBEAR MODEL --- //
	WarbearModel* pWarbearModel = new WarbearModel("warbear.azul", 0);
	assert(pWarbearModel);
	pWarbearModel->SetModelType(Model::ModelType::BEAR);
	ModelMan::Add(pWarbearModel);

	// --- BOUNDING SPHERE MODEL --- //
	SphereModel* pSphereModel = new SphereModel("sphereModel.azul");
	assert(pSphereModel);
	pSphereModel->SetModelType(Model::ModelType::SPHERE);
	ModelMan::Add(pSphereModel);

	CameraModel* pCameraModel = new CameraModel("cameraModel.azul");
	assert(pCameraModel);
	pCameraModel->SetModelType(Model::ModelType::CAMERA);
	ModelMan::Add(pCameraModel);

	PyramidModel* pPyramidModel = new PyramidModel("pyramidModel.azul");
	pPyramidModel->SetModelType(Model::ModelType::PYRAMID);
	assert(pPyramidModel);
	ModelMan::Add(pPyramidModel);

	SpriteModel* pSpriteModel = new SpriteModel("SpriteModel.azul");
	assert(pSpriteModel);
	ModelMan::Add(pSpriteModel);

	// -- Skinned Models -- / 
	SkinModel* pSkinnedTeddyModel = new SkinModel("teddy_skinning.azul");
	pSkinnedTeddyModel->SetModelType(Model::ModelType::SKINNED_TEDDY);
	assert(pSkinnedTeddyModel);
	ModelMan::Add(pSkinnedTeddyModel);

	SkinModel* pSkinnedHumanoidModel = new SkinModel("humanoid_skinning.azul");
	pSkinnedHumanoidModel->SetModelType(Model::ModelType::SKINNED_HUMANOID);
	assert(pSkinnedHumanoidModel);
	ModelMan::Add(pSkinnedHumanoidModel);

	SkinModel* pSkinnedHumanoidModel2 = new SkinModel("humanoid_skinning.azul");
	pSkinnedHumanoidModel2->SetModelType(Model::ModelType::SKINNED_HUMANOID2);
	assert(pSkinnedHumanoidModel2);
	ModelMan::Add(pSkinnedHumanoidModel2);
	
	// Create/Load Shader 
	ShaderObject* pShaderObject_color = new ShaderObject(ShaderObject::Name::COLOR_LIGHT, "colorRender", ShaderObject::Type::GRAPHICS);
	assert(pShaderObject_color);
	ShaderMan::Add(pShaderObject_color);

	ShaderObject* pShaderObject_texture = new ShaderObject(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender", ShaderObject::Type::GRAPHICS);
	assert(pShaderObject_texture);
	ShaderMan::Add(pShaderObject_texture);

	ShaderObject* pShaderObject_textureLight = new ShaderObject(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff", ShaderObject::Type::GRAPHICS);
	assert(pShaderObject_textureLight);
	ShaderMan::Add(pShaderObject_textureLight);

	ShaderObject* pShaderObject_constColor = new ShaderObject(ShaderObject::Name::CONST_COLOR, "constcolorRender", ShaderObject::Type::GRAPHICS);
	assert(pShaderObject_constColor);
	ShaderMan::Add(pShaderObject_constColor);

	ShaderObject* pShaderObject_colorSingle = new ShaderObject(ShaderObject::Name::COLOR_SINGLE, "colorSingleRender", ShaderObject::Type::GRAPHICS);
	assert(pShaderObject_colorSingle);
	ShaderMan::Add(pShaderObject_colorSingle);

	ShaderObject* pShaderObject_sprite = new ShaderObject(ShaderObject::Name::SPRITE, "spriteRender", ShaderObject::Type::GRAPHICS);
	assert(pShaderObject_sprite);
	ShaderMan::Add(pShaderObject_sprite);

	ShaderObject* pShaderObject_skinTexture = new ShaderObject(ShaderObject::Name::SKIN_TEXTURE_COLOR, "skinTextureRender", ShaderObject::Type::GRAPHICS);
	assert(pShaderObject_skinTexture);
	ShaderMan::Add(pShaderObject_skinTexture);

	ShaderObject* pShaderObject_mixer = new ShaderObject(ShaderObject::Name::COMPUTE_MIXER, "computeMixer", ShaderObject::Type::COMPUTE);
	assert(pShaderObject_mixer);
	ShaderMan::Add(pShaderObject_mixer);

	ShaderObject* pShaderObject_world = new ShaderObject(ShaderObject::Name::COMPUTE_WORLD, "computeWorld", ShaderObject::Type::COMPUTE);
	assert(pShaderObject_world);
	ShaderMan::Add(pShaderObject_world);


	// Textures
	Texture::Add("Rocks.tga", TextureName::ROCKS);
	Texture::Add("Stone.tga", TextureName::STONES);
	Texture::Add("RedBrick.tga", TextureName::RED_BRICK);
	Texture::Add("Duckweed.tga", TextureName::DUCKWEED);
	Texture::Add("HotPink.tga", TextureName::DEFAULT);
	Texture::Add("Aliens.tga", TextureName::INVADERS);
	Texture::Add("Consolas36pt.tga", TextureName::CONSOLAS_36PT);
	Texture::Add("TeddyTexNORLE.tga", TextureName::TEDDY);

	// Add Glyphs
	GlyphMan::AddXml(Glyph::Name::Consolas36pt, "Consolas36pt.xml", TextureName::CONSOLAS_36PT);


	// --- 2D Game Objects --- //
	Image* pImageGreen = new Image(Image::Name::ALIEN_GREEN, TextureName::INVADERS, Rect(136.0f, 64.0f, 85.0f, 63.0f));
	assert(pImageGreen);
	ImageMan::Add(pImageGreen);

	Image* pImageFont = new Image(Image::Name::FONT, TextureName::CONSOLAS_36PT, Rect(250.0f, 100.0f, 100.0f, 100.0f));
	assert(pImageFont);
	ImageMan::Add(pImageFont);

	// Fonts
	GraphicsObject_Font* pGraphics_Font = new GraphicsObject_Font(pSpriteModel, pShaderObject_sprite, GlyphMan::Find(Glyph::Name::Consolas36pt, 32));
	GraphicsObject_Font* pGraphics_Font2 = new GraphicsObject_Font(pSpriteModel, pShaderObject_sprite, GlyphMan::Find(Glyph::Name::Consolas36pt, 32));

	// Add new font to the manager
	FontMan::Add(Font::Name::StaticString, pGraphics_Font, "Press 'S' to blend animations ", 200.0f, 200.0f);
	FontMan::Add(Font::Name::DynamicString, pGraphics_Font2, "  ", 800.0f, 200.0f);

	// --- CREATE CLIPS --- //
	Clip* pHumanRunClip = new Clip(80, Clip::ClipName::HUMAN_RUN, Clip::ClipType::UNCOMPRESSED);
	pHumanRunClip->SetAnimationData("humanoid.azul", "clip1", "clip1Frames");

	Clip* pHumanPunchClip = new Clip(80, Clip::ClipName::HUMAN_PUNCH, Clip::ClipType::UNCOMPRESSED);
	pHumanPunchClip->SetAnimationData("humanoid.azul", "clip2", "clip2Frames");

	Clip* pHumanShotClip = new Clip(80, Clip::ClipName::HUMAN_SHOT, Clip::ClipType::UNCOMPRESSED);
	pHumanShotClip->SetAnimationData("humanoid.azul", "clip3", "clip3Frames");

	Clip* pHumanWalkClip = new Clip(80, Clip::ClipName::HUMAN_WALK, Clip::ClipType::UNCOMPRESSED);
	pHumanWalkClip->SetAnimationData("happy_walk.anim", "clip1", "clip1Frames");

	Clip* pTeddyWalkClip = new Clip(20, Clip::ClipName::TEDDY_WALK, Clip::ClipType::UNCOMPRESSED);
	pTeddyWalkClip->SetAnimationData("teddy.azul", "clip1", "clip1Frames");

	Clip* pTeddyIdleClip = new Clip(20, Clip::ClipName::TEDDY_IDLE, Clip::ClipType::UNCOMPRESSED);
	pTeddyIdleClip->SetAnimationData("teddy.azul", "clip2", "clip2Frames");

	Clip* pHumanRunJumpClip = new Clip(80, Clip::ClipName::HERO_RUN_JUMP_ANIM, Clip::ClipType::UNCOMPRESSED);
	pHumanRunJumpClip->SetAnimationData("hero_run_jump.anim", "clip1", "clip1Frames");

	// --- ADD CLIPS TO MANAGER -- //
	ClipMan::Add(pHumanRunClip);
	ClipMan::Add(pHumanPunchClip);
	ClipMan::Add(pHumanShotClip);
	ClipMan::Add(pHumanWalkClip);
	ClipMan::Add(pTeddyWalkClip);
	ClipMan::Add(pTeddyIdleClip);
	ClipMan::Add(pHumanRunJumpClip);

	AnimTime delta1 = 0.3f * AnimTime(AnimTime::Duration::NTSC_30_FRAME);
	AnimTime delta2 = 0.1f * AnimTime(AnimTime::Duration::NTSC_30_FRAME);

	//Vect color(1.50f, 1.50f, 1.50f, 1.0f);
	Vect pos(1, 1, 1);

	// --- ADD ANIMS TO CONTROLLER -- //
	AnimControllerMan::Add(new AnimController(delta1, 20, 5.0f, "teddy.azul", AnimController::ControllerType::TEDDY, pSkinnedTeddyModel));
	AnimControllerMan::Add(new AnimController(delta1, 80, 5.0f, "humanoid.azul", AnimController::ControllerType::HUMANOID_A, pSkinnedHumanoidModel));
	AnimControllerMan::Add(new AnimController(delta1, 80, 5.0f, "humanoid.azul", AnimController::ControllerType::HUMANOID_B, pSkinnedHumanoidModel));
	AnimControllerMan::Add(new AnimController(delta1, 80, 5.0f, "humanoid.azul", AnimController::ControllerType::HUMANOID_C, pSkinnedHumanoidModel2));
	AnimControllerMan::Add(new AnimController(delta1, 80, 5.0f, "humanoid.azul", AnimController::ControllerType::HUMANOID_D, pSkinnedHumanoidModel2));

	AnimController* pAnimControllerA = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID_A);
	AnimController* pAnimControllerB = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID_B);
	AnimController* pAnimControllerC = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID_C);
	AnimController* pAnimControllerD = AnimControllerMan::Find(AnimController::ControllerType::HUMANOID_D);

	AnimTransitionController* pAnimTransition1 = new AnimTransitionController(pAnimControllerA->GetAnim()->GetClip(), pAnimControllerB->GetAnim()->GetClip(), pSkinnedHumanoidModel);
	AnimTransitionController* pAnimTransition2 = new AnimTransitionController(pAnimControllerC->GetAnim()->GetClip(), pAnimControllerD->GetAnim()->GetClip(), pSkinnedHumanoidModel2);

	AnimTransitionControllerMan::Add(pAnimTransition1);
	AnimTransitionControllerMan::Add(pAnimTransition2);

	GraphicsObject_SkinTexture* pHumanSkinGraphicsObj = new GraphicsObject_SkinTexture(pSkinnedHumanoidModel,
		pShaderObject_skinTexture, TextureName::DEFAULT);

	assert(pHumanSkinGraphicsObj);

	
	// --- 3D Game Objects --- //
	SimpleGameObject* pSimpleGameObj = nullptr;
	GraphicsObject* pGraphicsObj = nullptr;

	pGraphicsObj = new GraphicsObject_FlatTexture(pAstroboyModel, pShaderObject_texture, TextureName::DEFAULT);
	pSimpleGameObj = new SimpleGameObject(pGraphicsObj, GameObject::Type::GAME_OBJECT);
	pSimpleGameObj->SetPos(500.0f, 500.0f, 500.0f);
	pSimpleGameObj->SetScale(1.0f, 1.0f, 1.0f);
	pSimpleGameObj->deltaRotY = -0.025f;
	pSimpleGameObj->SetName("Astroboy");
	GameObjectMan::Add(pSimpleGameObj);


	pGraphicsObj = new GraphicsObject_FlatTexture(pBuggyModel, pShaderObject_texture, TextureName::BUGGY);
	pSimpleGameObj = new SimpleGameObject(pGraphicsObj, GameObject::Type::GAME_OBJECT);
	pSimpleGameObj->SetPos(-450.0f, -400.0f, 150.0f);
	pSimpleGameObj->SetScale(1.0f, 1.0f, 1.0f);
	pSimpleGameObj->deltaRotZ = -0.05f;
	pSimpleGameObj->SetName("Buggy");
	GameObjectMan::Add(pSimpleGameObj);

	pGraphicsObj = new GraphicsObject_FlatTexture(pWarbearModel, pShaderObject_texture, TextureName::WARBEAR);
	pSimpleGameObj = new SimpleGameObject(pGraphicsObj, GameObject::Type::GAME_OBJECT);
	pSimpleGameObj->SetPos(100.0f, -100.0f, 100.0f);
	pSimpleGameObj->SetScale(1.0f, 1.0f, 1.0f);
	pSimpleGameObj->deltaRotY = -0.005f;
	pSimpleGameObj->deltaRotZ = -0.125f;
	pSimpleGameObj->SetName("Bear");
	GameObjectMan::Add(pSimpleGameObj);

	// Sprites
	GraphicsObject_Sprite* pGraphics_Sprite = new GraphicsObject_Sprite(pSpriteModel, pShaderObject_sprite, pImageGreen, Rect(455, 155, 150, 150));
	GameObject2D* pAlienObj = new GameObject2D(pGraphics_Sprite);
	pAlienObj->posX = 250.0f;
	pAlienObj->posY = 450.0f;
	GameObjectMan::Add(pAlienObj, GameObjectMan::GetRoot());
	pAlienObj->SetName("ALIEN");


	GameObjectRigid* pSkinObj = new GameObjectRigid(pHumanSkinGraphicsObj, pSkinnedHumanoidModel);
	pSkinObj->SetPos(100.0f, -100.0f, 100.0f);
	pSkinObj->SetScale(1.0f, 1.0f, 1.0f);
	pSkinObj->SetName("Skinned Humanoid");
	GameObjectMan::Add(pSkinObj, GameObjectMan::GetRoot());

	PCSTree* pTree = GameObjectMan::GetPCSTree();
	pTree->Print();
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------

int var = 0;

void Game::Update(float)
{
	CameraDemoInput();
	CameraModel* pCameraModel = (CameraModel*)ModelMan::Find(Model::ModelType::CAMERA);
	pCameraModel->update();

	Camera3D* p3DCam = (Camera3D*)CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
	p3DCam->updateCamera();

	Camera2D* p2DCam = (Camera2D*)CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
	p2DCam->updateCamera();

	Font* pDynamicFont = FontMan::Find(Font::Name::DynamicString);
	assert(pDynamicFont);

	FontDemo(pChar, var);

	pDynamicFont->UpdateMessage(pChar);

	var++;

	if (var >= 200)
		var = 0;

	Keyboard* key = InputMan::GetKeyboard();

	if (key->GetKeyState(Keyboard::Key::KEY_S))
	{
		AnimTransitionControllerMan::StartTransition();
	}

	AnimControllerMan::Update();

	AnimTransitionControllerMan::Update();

	GameObjectMan::Update(this->globalTimer.Toc());

	
}


//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	GameObjectMan::Draw();
}


//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	FontMan::Destroy();
	Texture::Destroy();
	InputMan::Destroy();
	GameObjectMan::Destroy();
	ModelMan::Destroy();
	ShaderMan::Destroy();
	CameraMan::Destroy();
	ClipMan::Destroy();
	AnimControllerMan::Destroy();
	AnimTransitionControllerMan::Destroy();
	ImageMan::Destroy();
	GlyphMan::Destroy();


	delete pChar;

}


//-----------------------------------------------------------------------------
// Game::ScreenResize()
//-----------------------------------------------------------------------------

//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBufferFunc()
{
	const GLfloat grey[] = { 0.7f, 0.7f, 0.8f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, grey);
	glClearBufferfv(GL_DEPTH, 0, &one);
}


// --- End of File ---
