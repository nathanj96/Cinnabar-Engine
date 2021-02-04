#include "Drawable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

#include "RegistrationCommandBase.h"
#include "RegisterDrawCommand.h"
#include "DeregisterDrawCommand.h"
#include "RegisterDraw2DCommand.h"
#include "DeregisterDraw2DCommand.h"

//object needs to be registered manually
Drawable::Drawable()
{
	drawRegState = RegistrationState::CURRENTLY_DEREGISTERED;
	drawRegistrationCmdPtr = new RegisterDrawCommand(this);
	drawDeregistrationCmdPtr = new DeregisterDrawCommand(this);
	drawRegistration2DCmdPtr = new RegisterDraw2DCommand(this);
	drawDeregistration2DCmdPtr = new DeregisterDraw2DCommand(this);
}

void Drawable::SubmitRegisterDrawableCommand()
{
	//make sure it's not already registered
	assert(drawRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::toDrawable::submitDrawCommand(drawRegistrationCmdPtr);
	drawRegState = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDeregisterDrawableCommand()
{
	//make sure it's already registered
	assert(drawRegState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::toDrawable::submitDrawCommand(drawDeregistrationCmdPtr);
	drawRegState = RegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::SubmitRegisterDrawable2DCommand()
{
	//make sure it's not already registered
	assert(drawRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::toDrawable::submitDrawCommand(drawRegistration2DCmdPtr);
	drawRegState = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDeregisterDrawable2DCommand()
{
	//make sure it's already registered
	assert(drawRegState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::toDrawable::submitDrawCommand(drawDeregistration2DCmdPtr);
	drawRegState = RegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::RegisterDrawable()
{
	//make sure it's waiting to be registered (this is called from a registration command Execute())
	assert(drawRegState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::toDrawable::registerDraw(this);
	drawRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::RegisterDrawable2D()
{
	//make sure it's waiting to be registered (this is called from a registration command Execute())
	assert(drawRegState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::toDrawable::registerDraw2D(this);
	drawRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::DeregisterDrawable()
{
	//make sure it's waiting to be registered (this is called from a registration command Execute())
	assert(drawRegState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::toDrawable::deregisterDraw(this);
	drawRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::DeregisterDrawable2D()
{
	//make sure it's waiting to be registered (this is called from a registration command Execute())
	assert(drawRegState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::toDrawable::deregisterDraw2D(this);
	drawRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::setDrawObjRef(DrawableManager::DrawableListRef ref)
{
	drawObjRef = ref;
}

DrawableManager::DrawableListRef Drawable::getDrawObjRef() const
{
	return drawObjRef;
}

Drawable::~Drawable()
{
	delete drawRegistrationCmdPtr;
	drawRegistrationCmdPtr = nullptr;
	delete drawDeregistrationCmdPtr;
	drawDeregistrationCmdPtr = nullptr;
	delete drawRegistration2DCmdPtr;
	drawRegistration2DCmdPtr = nullptr;
	delete drawDeregistration2DCmdPtr;
	drawDeregistration2DCmdPtr = nullptr;
}