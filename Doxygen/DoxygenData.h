/** \defgroup GETTINGSTARTED GettingStarted
\brief Functions and other information all Cinnabar Engine developers will need to be familiar with.
*/

/** \defgroup EXTERNALRESOURCEMANAGEMENT ExternalResourceManagement
\ingroup GETTINGSTARTED
\brief Information about loading and unloading external resources into Cinnabar Engine.
*/

/** \defgroup GAMEOBJECT GameObject
\ingroup GETTINGSTARTED
\brief Base class for all objects that are registerable to the game loop. Every GameObject derives from 5 classes that all offer functionality
relevant to the game loop: Updatable, Drawable, Inputable, Alarmable, and Collidable.
*/

/** \defgroup GAMELOOPEVENTS GameLoopEvents
\ingroup GAMEOBJECT
\brief Game-loop relevant events that all GameObjects <i>can</i> implement.
*/

/** \defgroup INPUTABLE Inputable
\brief Base class for all objects that need the ability to process key press and key release events. One of the 5 base classes GameObject inherits
from, but any class can inherit from it.
*/

/** \defgroup INPUTABLEMETHODS InputableMethods
\ingroup INPUTABLE
\brief Methods offered by the Inputable class.
*/

/** \defgroup INPUTABLEREGISTRATION InputableRegistration
\ingroup INPUTABLE
\brief Before an Inputable can process any input, it must first be registered to do so using the functions listed here. Deregistration functions
are also provided.
*/

/** \defgroup ALARMABLE Alarmable
\brief Base class for all objects that need the ability to process alarms. Alarms cause a function callback to occur after a specified amount of time.
All GameObjects inherit from Alarmable, though any other class can inherit from it too.
*/

/** \defgroup ALARMABLEMETHODS AlarmableMethods
\ingroup ALARMABLE
\brief Methods offered by the Alarmable class.
*/

/** \defgroup ALARMABLEREGISTRATION InputableRegistration
\ingroup ALARMABLE
\brief Before an Alarmable can process any alarms, it must first be registered to do so using the functions listed here. Deregistration functions
are also provided.
*/
* 
/** \defgroup UPDATABLE Updatable
\brief Base class for all objects that need the ability to update their state every frame. One of the 5 base classes GameObject inherits
from, but any class can inherit from it.
*/

/** \defgroup UPDATABLEMETHODS UpdatableMethods
\ingroup UPDATABLE
\brief Methods offered by the Updatable class.
*/

/** \defgroup UPDATABLEREGISTRATION UpdatableRegistration
\ingroup UPDATABLE
\brief Before an Updatable can process any update calls, it must first be registered to do so using the functions listed here. Deregistration functions
are also provided.
*/
 
/** \defgroup DRAWABLE Drawable
\brief Base class for all objects that need the ability to be drawn to the screen every frame. One of the 5 base classes GameObject inherits
from, but any class can inherit from it.
*/

/** \defgroup DRAWABLEMETHODS DrawableMethods
\ingroup DRAWABLE
\brief Methods offered by the Drawable class.
*/

/** \defgroup DRAWABLEREGISTRATION DrawableRegistration
\ingroup DRAWABLE
\brief Before a Drawable can process any update calls, it must first be registered to do so using the functions listed here. Deregistration functions
are also provided./
*/

/** \defgroup COLLISION Collision
\brief An overview of collision processing in Cinnabar Engine.
*/
 
/** \defgroup COLLISIONHOWTO HowTo
\ingroup COLLISION
\brief Explains how to set up collision in Cinnabar Engine. Collidables require some maintenance on the user side in order
for them to work properly. Given 2 Collidables:
\code
{
    CollidableType1* c1;
    CollidableType2* c2;
}
\endcode

each one needs to be assigned a collider model, collidable group, and a world matrix the collision engine can use to
determine the bounds of its collision volume. It must also be registered for collision, like the other <x>ables. This 
is often done when the object is created, as such:
\code
CollidableType1::CollidableType1()
{
    ...
    SetColliderModel(someModel, someVolumeType);
    SetCollisionGroup<CollidableType1*>();
    Matrix m = //some matrix, usually the object's world matrix
    ...
    UpdateCollisionData(m);
    SubmitRegisterCollidableCommand();
}

//same code in CollidableType2::CollidableType2()
\endcode
Note that SetCollisionGroup<>() is a template function to which the Collidable class is the argument. From here, every time
the Collidable moves in world space, another call to UpdateCollisionData() is required using the object's new world matrix.

The collision callback is the Collision() function present in each Collidable, which can be overridden for collisions
with different derived Collidables:
\code
\\in CollisionType1.h
void Collision(CollisionType2*)
{
    //do stuff
}

\\in CollisionType2.h
void Collision(CollisionType1*)
{
    //do stuff
}
\endcode

Finally, the Scene containing these Collidables needs to be told to check for collisions between these two Collidable types.
This is done within the Scene's code, again usually when the scene begins:
\code
SampleScene::SampleScene()
{
    ...
    SetCollisionPair<CollidableType1*, CollidableType2*>();
}
\endcode

Now the two Collidables should have their collision automatically processed. Whenever a CollidableType1 and a CollidableType2
collide, CollidableType1::Collision(CollidableType2*) and CollidableType2::Collision(CollidableType1*) will both be called once.
There is also a SetCollisionSelf<>() function available for when a Collidable needs to be able to collide with other instances
of itself. For example, SetCollisionSelf<CollidableType1*>() would result in two calls to CollidableType1::Collision(CollidableType1*)
occurring whenever two CollidableType1 objects collide. Collision with a terrain is handled via a separate manager, and
requires a call to SetCollisionTerrain<>() to begin being processed.
*/

/** \defgroup COLLIDABLE Collidable
\ingroup COLLISION
\brief Base class for all objects that need the ability to process collision. One of the 5 base classes GameObject inherits
from, but any class can inherit from it.
*/

/** \defgroup COLLIDABLEMETHODS CollidableMethods
\ingroup COLLIDABLE
\brief Methods offered by the Collidable class.
*/

/** \defgroup COLLIDABLEREGISTRATION CollidbaleRegistration
\ingroup COLLIDABLE
\brief Before a Collidable can process any collision, it must first be registered to do so using the functions listed here. Deregistration functions
are also provided.
*/

/** \defgroup VISUALIZER Visualizer
\brief The Visualizer is a tool provided by Cinnabar Engine to display an object's bounding volumes on screen for debugging purposes.
*/

/** \defgroup VISUALIZERMETHODS VisualizerMethods
\ingroup VISUALIZER
\brief Methods relevant to the Visualizer.
*/

/** \defgroup CSPRITE CSprite
\brief The Cinnabar Engine base class for 2D sprites.
*/
 
/** \defgroup CSPRITEMETHODS CSpriteMethods
\ingroup CSPRITE
\brief Methods offered by the CSprite class.
*/

/** \defgroup CMATHTOOLS CMathTools
\brief A library provided by the Cinnabar Engine containing commonly used math operations.
*/

/** \defgroup COLLISIONHELPERS CollisionHelpers
\ingroup CMATHTOOLS
\brief Functions used specifically for calculating collision. The user should not access these, but it is helpful
for other engine developers to know of their use.
*/

/** \defgroup SCENE Scene
\ingroup GETTINGSTARTED
\brief Cinnabar Engine's Scene base class. Scenes are essentially containers for game objects, and in turn have the mechanics necessary to 
perform all <x>able operations necessary on them each frame.
*/
 
/** \defgroup SCENEMETHODS SceneMethods
\ingroup SCENE
\brief Methods relevant to any scene.
*/

/** \defgroup SCENEUPDATE SceneUpdate
\ingroup SCENELOOP
\brief Methods called by the engine when updating at the scene level. These control the registration of GameObjects to and from the scene, as well
as the processing of <x>able events. Note that RegistrationCommandBroker::processCommands() <b>MUST</b> be called first in this loop, as modifying
any object registration during the frame will cause major problems.
*/

/** \defgroup SCENELOOP SceneLoop
\ingroup SCENE
\brief Methods used by Cinnabar Engine to control scenes on a per-frame basis. Most of this is at an engine level and should not be modified by the user,
but an understanding of it may prove helpful nonetheless.
*/

/** \defgroup SCENECREATION SceneCreation
\ingroup SCENELOOP
\brief Methods called in the creation of new scenes. In Cinnabar Engine, scenes are created and deleted dynamically every time a scene change occurs,
so in our context, these functions also essentially capture the scene switching process.
*/

/** \defgroup IMAGEMANAGER ImageManager
\ingroup EXTERNALRESOURCEMANAGEMENT
\brief In the context of Cinnabar Engine, images are textures, or subsections thereof, that are mainly used as 2D sprites. This manager centralizes
the loading, retrieval, and unloading of images.
\note 
*/

/** \defgroup MODELMANAGER ModelManager
\ingroup EXTERNALRESOURCEMANAGEMENT
\brief Centralizes the loading, retrieval, and unloading of 3D models. Cinnabar Engine supports importing models in the propietary .azul file format,
and also includes a few premade models.
\note Models can <b>only</b> be imported in the .azul file format. Cinnabar Engine comes with a program for converting .fbx files to .azul files, see
the Getting Started section for more information.
\note All imported models must be placed inside the engine's Assets/Models folder or else they will not import properly and the engine will not run.
*/

/** \defgroup SHADERMANAGER ShaderManager
\ingroup EXTERNALRESOURCEMANAGEMENT
\brief Centralizes the loading, retrieval, and unloading of shaders.
\note All imported shaders must be placed inside the engine's Assets/Shaders folder or else they will not import properly and the engine will not run.
*/

/** \defgroup SPRITEFONTMANAGER SpriteFontManager
\ingroup EXTERNALRESOURCEMANAGEMENT
\brief Centralizes the loading, retrieval, and unloading of sprite fonts. As the name implies, sprite fonts are representations of fonts using 2D sprites.
They consist of 2 parts: a texture containing the actual characters, and a .xml file used by the engine to split the texture into separate characters.
The texture and .xml are both created using SpriteFont2, however, the texture will need to be converted to the .tga format before use.
\note For SpriteFonts to work, the .tga and .xml must both be placed in the Assets/Fonts folder, and share the same file name
*/

/** \defgroup TEXTUREMANAGER TextureManager
\ingroup EXTERNALRESOURCEMANAGEMENT
\brief Centralizes The loading, retrieval, and unloading of textures.
\note All textures used in Cinnabar Engine must be in the .tga format.
\note All imported shaders must be placed in the engine's Assets/Textures folder or else they will not import properly and the engine will not run.
*/

/** \defgroup TERRAINMODELMANAGER TerrainModelManager
\ingroup EXTERNALRESOURCEMANAGEMENT
\brief Cinnabar Engine treats terrain objects as an asset managed at the engine level due to the complexity in their
creation. The TerrainModelManager thereby centralizes the loading, retrieval, and unloading of them.
A given terrain model is automatically generated based on a heightmap, a 2D grayscale image provided as a Texture object,
and another Texture object which is the one used to actually texture the model.
*/

/** \defgroup TERRAINMODEL TerrainModel
\brief A class containing a loaded terrain. Every scene has at most one active Terrain associated with it; this can be
set and retrieved with SceneManager::SetCurrentTerrain() and SceneManager::GetCurrentTerrain(), respectively.
*/

/** \defgroup TERRAINMODELMETHODS TerrainModelMethods
\ingroup TERRAINMODEL
\brief Methods relevant to TerrainModels.
*/

/** \defgroup CAUDIO CAudio
\brief CAudio is the system used by Cinnabar Engine to implement audio playback.
*/

/** \defgroup CSOUND CSound
\ingroup CAUDIO
\brief A class containing the samples of a loaded sound. Playback is done through CSoundChannels.
\note Most systems in Cinnabar Engine measure time in seconds, while CAudio measures it in milliseconds.
Due to IEEE-754 limitations making a perfect conversion from seconds to milliseconds impossible (converting a float
time in seconds to an int time in milliseconds), any CAudio functions that use time <b>must have the time provided
in milliseconds!!!</b>
*/

/** \defgroup CSOUNDMETHODS CSoundMethods
\ingroup CSOUND
\brief Methods relevant to CSounds.
*/

/** \defgroup CSOUNDCHANNEL CSoundChannel
\ingroup CAUDIO
\brief CSoundChannels are essentially playing "instances" of CSounds. Each CSoundChannel can have its volume, pitch,
and other playback parameters modified independently of other CSoundChannels playing the same CSound, as well as have
3D effects applied to them. They can also be assigned to CSoundChannelGroups and controlled in aggregate, saving time
and performance.
*/

/** \defgroup CSOUNDCHANNELMETHODS CSoundChannelMethods
\ingroup CSOUNDCHANNEL
\brief Methods relevant to CSoundChannels.
*/

/** \defgroup CSOUNDCHANNELGROUPS CSoundChannelGroup
\ingroup CAUDIO
\brief CSoundChannels can be placed into CSoundChannelGroups and have effects applied to them in aggregate in order to save
time and resources. 
\note All effects applied to CSoundChannelGroups do not directly manipulate the associated parameters within
each CSoundChannel. For example, if a CSoundChanneGroup has 3 CSoundChannels in it and its volume is raised to 5, all 3
of the sounds will become louder, but each individual CSoundChannel's volume will still be 1. From this point, each
CSoundChannel can have its individual volume altered to be even louder or quieter than their containing
CSoundChannelGroup.
*/

/** defgroup CSOUNDCHANNELGROUPMETHODS CSoundChannelGroupMethods
\ingroup CSOUNDCHANNEL
\brief Methods relevant to CSoundChannelGroups.
*/

/** \defgroup COMMONCHANNELMETHODS CommonChannelMethods
\ingroup CAUDIO
\ingroup CSOUNDCHANNELMETHODS
\ingroup CSOUNDCHANNELGROUPMETHODS
\brief The methods listed here can be used on both CSoundChannels and CSoundChannelGroups, and are called the
same way for both.
*/

/** \defgroup CSOUNDDSP CSoundDSP
\ingroup CAUDIO
\brief CSoundDSPs are essentially premade special effects that you can apply to a CSoundChannel or CSoundChannelGroup.
To use them, simply create a CSoundDSP object and connect it as such:
\code
{
    CSoundDSP* dsp = new CSoundDSP(CSoundDSP::DSPTypes::Echo);
    CSoundChannel* chn = newCSoundChannel();
    chn->AddDSP(0, dsp);
}
and the DSP effect will automatically be applied to the CSoundChannel or CSoundChannelGroup.
*/

/** \defgroup CSOUNDDSPMETHODS CSoundDSPMethods
\ingroup CSOUNDDSP
\brief Methods relevant to CSoundDSPs.
*/

/** \defgroup CSOUNDGEOMETRY CSoundGeometry
\ingroup CAUDIO
\brief CSoundGeometry objects are 3D models that are used by CAudio to apply occlusion.
*/

/** \defgroup CSOUNDGEOMETRYMETHODS CSoundGeometryMethods
\ingroup CSOUNDGEOMETRY
\brief Methods relevant to CSoundGeometry objects.
*/

/** \defgroup CSOUNDREVERB CSoundReverb
\ingroup CAUDIO
\brief CSoundReverbs are spheres in 3D space inside of which a given reverb effect is automatically applied. To use, simply
create a reverb and place it in the world as such:
\code
{
    rvb = new CSound3DReverb(ReverbTypes::PaddedCell);
    rvb->Set3DAttributes(Vect(0.0f, 0.0f, 20.0f), 2.0f, 30.0f));
}
\endcode
and CAudio will automatically process it.
*/

/** \defgroup CSOUNDREVERBMETHODS CSoundReverbMethods
\ingroup CSOUNDREVERB
\brief Methods relevant to CSoundReverb objects.
*/

/** \defgroup CSOUNDASSETMANAGER CSoundAssetManager
\ingroup EXTERNALRESOURCEMANAGEMENT
\brief Centralizes the loading, unloading, and retrieval of CSound objects.
*/

/** \defgroup COLORS Colors
\brief A collection of predefined colors as RGBA Vects.
*/

/** \defgroup SCREENLOG ScreenLog
\brief A debugging tool that prints strings directly to the screen. Highly helpful for visualizing things such as object
positions, registration states, time left in an alarm, et al. Each additional call to the ScreenLog in the same frame
puts the next line of text above the previous one.
*/

/** \defgroup SCREENLOGMETHODS ScreenLogMethods
\ingroup SCREENLOG
\brief Methods relevant to the ScreenLog.
*/