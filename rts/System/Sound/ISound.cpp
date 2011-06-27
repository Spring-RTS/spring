/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#include "ISound.h"

#ifndef   NO_SOUND
#include "Sound.h"
#endif // NO_SOUND
#include "NullSound.h"

#include "SoundLog.h"
#include "System/LogOutput.h"
#include "System/ConfigHandler.h"

CONFIG(NoSound, false);

ISound* ISound::singleton = NULL;

ISound::ISound()
	: numEmptyPlayRequests(0)
	, numAbortedPlays(0)
{
}

void ISound::Initialize()
{
	if (singleton == NULL) {
#ifndef NO_SOUND
		const bool noSound = configHandler->GetBool("NoSound");
		if (!noSound) {
			singleton = new CSound();
		} else
#endif // NO_SOUND
		{
			singleton = new NullSound();
		}
	} else {
		LogObject(LOG_SOUND) <<  "warning: Sound is already initialized!";
	}
}

void ISound::Shutdown()
{
	ISound* tmpSound = singleton;
	singleton = NULL;
	delete tmpSound;
	tmpSound = NULL;
}

bool ISound::IsInitialized()
{
	return (singleton != NULL);
}

