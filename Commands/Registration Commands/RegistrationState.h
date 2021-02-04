//Used to label whether a registerable object is currently registered or not in order to prevent double registration

#ifndef REGISTRATION_STATE
#define REGISTRATION_STATE

enum class RegistrationState
{
	CURRENTLY_REGISTERED,
	CURRENTLY_DEREGISTERED,
	PENDING_REGISTRATION,
	PENDING_DEREGISTRATION
};

#endif REGISTRATION_STATE