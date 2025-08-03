////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2016 RWS Inc, All Rights Reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of version 2 of the GNU General Public License as published by
// the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
///////////////////////////////////////////////////////////////////////////////
//
//	bsound.cpp
// 
// History:
//		10/29/95 JMI	Started.  Based on original WinMM bsound.cpp.
//							This is now the interface by which Blue decides into
//							which namespace to call.
//
//		08/05/97	JMI	Added rspIsSoundOutPaused().
//
//////////////////////////////////////////////////////////////////////////////
//
// This calls into the correct namespace for sound functionality based on
// the current value of gsi.sAudioType via the AUDIO_CALL macro defined
// in wSound.h.
//
//////////////////////////////////////////////////////////////////////////////

#include <SDL3/SDL.h>
#include "Blue.h"

// Only set value if not NULL.
#define SET(ptr, val)		( ((ptr) != NULL) ? *(ptr) = (val) : 0)

static uint32_t callback_data = 0;

static void sdl_audio_callback(void *userdata, Uint8 *stream, int len)
{
    RSP_SND_CALLBACK callback = (RSP_SND_CALLBACK) userdata;
    SDL_memset(stream, '\0', len);
    callback(stream, len, 0, &callback_data);
}

static bool audio_opened = false;
static SDL_AudioSpec desired;
static int32_t cur_buf_time = 0;
static int32_t max_buf_time = 0;
static SDL_AudioDeviceID device = 0;

extern int16_t rspSetSoundOutMode(				// Returns 0 if successfull, non-zero otherwise
	int32_t lSampleRate,								// In:  Sample rate
	int32_t lBitsPerSample,							// In:  Bits per sample
	int32_t lChannels,								// In:  Channels (mono = 1, stereo = 2)
	int32_t lCurBufferTime,							// In:  Current buffer time (in ms.)
	int32_t lMaxBufferTime,							// In:  Maximum buffer time (in ms.)
	RSP_SND_CALLBACK callback,					// In:  Callback function
	uint32_t ulUser)									// In:  User-defined value to pass to callback
{
    if (audio_opened)
        rspKillSoundOutMode();

    memset(&desired, '\0', sizeof (desired));

    if ((lChannels < 1) || (lChannels > 2))
    {
		TRACE("rspSetSoundOutMode(): Must be 1 or 2 channels.\n");
        return -1;
    }

    if (lBitsPerSample == 8)
        desired.format = SDL_AUDIO_U8;
    else if (lBitsPerSample == 16)
        desired.format = SDL_AUDIO_S16;
    else
    {
		TRACE("rspSetSoundOutMode(): Format must be 8 or 16 bit.\n");
        return -1;
    }

#if 0
    // Fragment sizes I used for Serious Sam...seem to work well...
    if (desired.freq <= 11025)
        desired.samples = 512;
    else if (desired.freq <= 22050)
        desired.samples = 1024;
    else if (desired.freq <= 44100)
        desired.samples = 2048;
    else
        desired.samples = 4096;  // (*shrug*)

#ifdef __ANDROID__
    desired.samples = 2048;
#endif
#endif

    desired.freq = lSampleRate;
    desired.channels = lChannels;

    cur_buf_time = lCurBufferTime;
    max_buf_time = lMaxBufferTime;

    callback_data = ulUser;

    if (rspCommandLine("nosound"))
        return BLU_ERR_NO_DEVICE;

    if (!SDL_WasInit(SDL_INIT_AUDIO))
    {
        if (!SDL_Init(SDL_INIT_AUDIO))
            return BLU_ERR_NO_DEVICE;
    }

    if (!(device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &desired)))
    {
		TRACE("rspSetSoundOutMode(): SDL_OpenAudioDevice failed: %s.\n", SDL_GetError());
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return BLU_ERR_NO_DEVICE;
    }

    SDL_ResumeAudioDevice(device);

    audio_opened = true;
    return 0;
}

extern int16_t rspGetSoundOutMode(				// Returns 0 if successfull, non-zero otherwise
	int32_t* plSampleRate,							// Out: Sample rate or -1 (unless NULL)
	int32_t* plBitsPerSample,				// Out: Bits per sample or -1 (unless NULL)
	int32_t* plChannels,					// Out: Channels (mono=1, stereo=2) or -1 (unless NULL)
	int32_t* plCurBufferTime,				// Out: Current buffer time or -1 (unless NULL)
	int32_t* plMaxBufferTime)			// Out: Maximum buffer time or -1 (unless NULL)
{
    SET(plSampleRate, desired.freq);
    SET(plBitsPerSample, desired.format & 0x00FF);
    SET(plBitsPerSample, desired.channels);
    SET(plCurBufferTime, cur_buf_time);
    SET(plMaxBufferTime, max_buf_time);
    return 0;
}

extern void rspSetSoundOutBufferTime(
	int32_t lCurBufferTime)						// In:  New buffer time
{
    cur_buf_time = lCurBufferTime;
}

extern void rspKillSoundOutMode(void)		// Returns 0 if successfull, non-zero otherwise
{
    if (audio_opened)
    {
        SDL_PauseAudioDevice(device);
        SDL_CloseAudioDevice(device);
        audio_opened = false;
    }
}

extern int16_t rspClearSoundOut(void)		// Returns 0 on success, non-zero otherwise
{
    // no-op?
    return 0;
}

extern int16_t rspPauseSoundOut(void)		// Returns 0 on success, non-zero otherwise
{
    if (!audio_opened)
        return 0;

    SDL_PauseAudioDevice(device);
    return 0;
}

extern int16_t rspResumeSoundOut(void)		// Returns 0 on success, non-zero otherwise
{
    if (!audio_opened)
        return 0;

    SDL_ResumeAudioDevice(device);
    return 0;
}

extern int16_t rspIsSoundOutPaused(void)	// Returns TRUE if paused, FALSE otherwise
{
    if (!audio_opened)
        return TRUE;

    return(SDL_AudioDevicePaused(device) ? TRUE : FALSE);
}

extern int32_t rspGetSoundOutPos(void)		// Returns sound output position in bytes
{
    return 0;
}

extern int32_t rspGetSoundOutTime(void)		// Returns sound output position in time
{
    return 0;
}

extern int32_t rspDoSound(void)
{
    // no-op; in Soviet Russia, audio callback pumps YOU.
    //  seriously, the SDL audio callback runs in a seperate thread.
    return 0;
}

extern void rspLockSound(void)
{
#if 0
    if (audio_opened)
        SDL_LockAudio();
#endif
}

extern void rspUnlockSound(void)
{
#if 0
    if (audio_opened)
        SDL_UnlockAudio();
#endif
}


//////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////
