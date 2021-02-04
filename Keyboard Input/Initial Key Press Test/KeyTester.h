#ifndef KEY_TESTER
#define KEY_TESTER

#include "AzulCore.h"

class KeyTester
{
private:
	AZUL_KEY keyToTest;
	//need to save to compare to current key state
	bool prevKeyState;
public:
	KeyTester(AZUL_KEY key);

	KeyTester() = delete;
	KeyTester(const KeyTester&) = delete;
	KeyTester& operator=(const KeyTester&) = delete;
	~KeyTester() = default;

	void TestKey();
};

#endif KEY_TESTER