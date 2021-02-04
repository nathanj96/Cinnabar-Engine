#ifndef DRAWABLE
#define DRAWABLE

class RegisterDrawCommand;
class DeregisterDrawCommand;
class RegisterDraw2DCommand;
class DeregisterDraw2DCommand;
class DrawableAttorney;

#include "DrawableManager.h"

#include "RegistrationState.h"

//forward declaration
class RegistrationCommandBase;

class Drawable
{
	friend class DrawableAttorney;
private:
	//to prevent double registration
	RegistrationState drawRegState;
	//keep an iterator to this object's location in the list of the drawable manager storing it in order to enable quicker removal of it
	DrawableManager::DrawableListRef drawObjRef;
	RegisterDrawCommand* drawRegistrationCmdPtr;
	DeregisterDrawCommand* drawDeregistrationCmdPtr;
	RegisterDraw2DCommand* drawRegistration2DCmdPtr;
	DeregisterDraw2DCommand* drawDeregistration2DCmdPtr;

	void RegisterDrawable();
	void DeregisterDrawable();
	void RegisterDrawable2D();
	void DeregisterDrawable2D();

	/**********************************************************************************************//**
	 * \fn	virtual void Drawable::Draw()
	 * \ingroup GAMELOOPEVENTS
	 * \ingroup DRAWABLEMETHODS
	 * \brief	3D draw callback
	 *
	 * \note This function is called <b>every</b> tick for every Drawable that is registered to process
	 * 		 3D draw callbacks, and it should be used <b>only</b> for code relevant to rendering.
	 **************************************************************************************************/

	virtual void Draw()
	{
	};

	/**********************************************************************************************//**
	* \fn	virtual void Drawable::Draw2D()
	* \ingroup GAMELOOPEVENTS
	* \ingroup DRAWABLEMETHODS
	* \brief	2D draw callback. Draw2D calls are made after all Draw3D calls for the frame have 
	* 			finished, ensuring that 2D objects will be rendered on top of 3D ones.
	* 			
	* \note This function is called <b>every</b> tick for every Drawable that is registered to process
	* 		 2D draw callbacks, and it should be used <b>only</b> for code relevant to rendering.
	**************************************************************************************************/
	virtual void Draw2D()
	{
	};

	//for use by engine only
	void setDrawObjRef(DrawableManager::DrawableListRef ref);
protected:

	/**********************************************************************************************//**
	 * \fn	void Drawable::SubmitRegisterDrawableCommand();
	 * \ingroup DRAWABLEREGISTRATION
	 * \brief	On the frame after this function is called, the Drawable object type will be registered
	 * 			to start processing Draw() callbacks every tick.
	 * 			
	 * \note 3D objects <b>must</b> use this registration function. To register a 2D object for drawing,
	 * 		 use the SubmitRegisterDrawable2DCommand() function.
	 **************************************************************************************************/

	void SubmitRegisterDrawableCommand();

	/**********************************************************************************************//**
	 * \fn	void Drawable::SubmitDeregisterDrawableCommand();
	 * \ingroup DRAWABLEREGISTRATION
	 * \brief	On the frame after this function is called, the Drawable object type will no longer
	 * 			process Draw() callbacks every tick.
	 *
	 * \note 3D objects <b>must</b> use this deregistration function. To deregister a 2D object for drawing,
	 * 		 use the SubmitDeregisterDrawable2DCommand() function.
	 **************************************************************************************************/

	void SubmitDeregisterDrawableCommand();

	/**********************************************************************************************//**
	 * \fn	void Drawable::SubmitRegisterDrawable2DCommand();
	 * \ingroup DRAWABLEREGISTRATION
	 * \brief	On the frame after this function is called, the Drawable object type will be registered
	 * 			to start processing Draw2D() callbacks every tick.
	 *
	 * \note 2D objects <b>must</b> use this registration function. To register a 3D object for drawing,
	 * 		 use the SubmitRegisterDrawableCommand() function.
	 **************************************************************************************************/

	void SubmitRegisterDrawable2DCommand();

	/**********************************************************************************************//**
	 * \fn	void Drawable::SubmitDeregisterDrawable2DCommand();
	 * \ingroup DRAWABLEREGISTRATION
	 * \brief	On the frame after this function is called, the Drawable object type will no longer
	 * 			process Draw2D() callbacks every tick.
	 *
	 * \note 2D objects <b>must</b> use this deregistration function. To deregister a 3D object for drawing,
	 * 		 use the SubmitDeregisterDrawableCommand() function.
	 **************************************************************************************************/

	void SubmitDeregisterDrawable2DCommand();
public:
	Drawable();
	Drawable(const Drawable&) = default;
	Drawable& operator=(const Drawable&) = default;
	virtual ~Drawable();

	DrawableManager::DrawableListRef getDrawObjRef() const;
};

#endif DRAWABLE