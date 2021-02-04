#include "KeyboardInputTesterObject.h"
#include "AzulCore.h"
#include "KeyTester.h"

KeyboardInputTesterObject::KeyboardInputTesterObject()
{
	keyTesterRef = new KeyTester(AZUL_KEY::KEY_T);
	SubmitRegisterUpdatableCommand();
}

void KeyboardInputTesterObject::Update()
{
	keyTesterRef->TestKey();
}

KeyboardInputTesterObject::~KeyboardInputTesterObject()
{
	SubmitDeregisterUpdatableCommand();
}