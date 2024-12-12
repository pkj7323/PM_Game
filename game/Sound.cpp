#include "stdafx.h"
#include "Sound.h"

FMOD_SYSTEM* Sound::g_sound_system;

Sound::Sound(const char* path, bool loop) {
    if (loop) {
        FMOD_System_CreateSound(g_sound_system, path, FMOD_LOOP_NORMAL, 0, &m_sound);
    }
    else {
        FMOD_System_CreateSound(g_sound_system, path, FMOD_DEFAULT, 0, &m_sound);
    }

    m_channel = nullptr;
    m_volume = SOUND_DEFAULT;
}

Sound::~Sound() {
    FMOD_Sound_Release(m_sound);
}


int Sound::Init() {
    FMOD_System_Create(&g_sound_system,FMOD_VERSION);
    FMOD_System_Init(g_sound_system, 32, FMOD_INIT_NORMAL, NULL);

    return 0;
}

int Sound::Release() {
    FMOD_System_Close(g_sound_system);
    FMOD_System_Release(g_sound_system);

    return 0;
}


int Sound::play() {
    //if (m_channel) {
    //    FMOD_BOOL isPlaying;
    //    FMOD_Channel_IsPlaying(m_channel, &isPlaying);
    //    if (isPlaying) {
    //        return 0; // 이미 재생 중인 경우 아무 작업도 하지 않음
    //    }
    //}
    FMOD_System_PlaySound(g_sound_system, m_sound, NULL, false, &m_channel);
    return 0;
}

int Sound::pause() {
    FMOD_Channel_SetPaused(m_channel, true);

    return 0;
}

int Sound::resume() {
    FMOD_Channel_SetPaused(m_channel, false);

    return 0;
}

int Sound::stop() {
    FMOD_Channel_Stop(m_channel);

    return 0;
}

int Sound::volumeUp() {
    if (m_volume < SOUND_MAX) {
        m_volume += SOUND_WEIGHT;
    }

    FMOD_Channel_SetVolume(m_channel, m_volume);

    return 0;
}

int Sound::volumeDown() {
    if (m_volume > SOUND_MIN) {
        m_volume -= SOUND_WEIGHT;
    }

    FMOD_Channel_SetVolume(m_channel, m_volume);

    return 0;
}


int Sound::Update() {
    FMOD_Channel_IsPlaying(m_channel, &m_bool);

    if (m_bool) {
        FMOD_System_Update(g_sound_system);
    }

    return 0;
}
