#include "SoundSystem.h"
#include "ResourceManager.h"
#include <iostream>

using namespace dae;


SoundLogger::SoundLogger()
{
	m_pSoundSystem = std::make_unique<SoundSystem>();
}

void SoundLogger::AddSound(const std::string& soundPath)
{
	m_pSoundSystem.get()->AddSound(soundPath);
	std::cout << "Sound added: " << soundPath << "\n";
}

void SoundLogger::PlaySound(int ID, Uint8 Volume)
{
	m_pSoundSystem.get()->PlaySound(ID, Volume);
	std::cout << "Sound ID: " << ID << " now playing with volume of : " << int(Volume) << "\n";
}

void SoundLogger::SoundPause()
{
	m_pSoundSystem.get()->SoundPause();
	std::cout << "Paused" << "\n";
}

void SoundLogger::Update()
{
	m_pSoundSystem->Update();
}

SoundSystem::SoundSystem()
	:m_SoundThread(AudioThreadFunctor{ this })
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}
SoundSystem::~SoundSystem()
{
	m_StopThread = true;
	m_ConditionVariable.notify_one();
	m_SoundThread.join();
}

void SoundSystem::AddSound(const std::string& soundPath)
{
	std::unique_lock<std::mutex> lock{ m_Mutex };


	Mix_Chunk* sound = Mix_LoadWAV(soundPath.c_str());

	if (sound != nullptr) 
	{
		m_PendingSounds.push_back(sound);
	}
}
void SoundSystem::PlaySound(int ID, Uint8 Volume)
{
	std::unique_lock<std::mutex> lock{ m_Mutex };
	
	std::pair<int, Uint8> sound{ ID, Volume };
	m_SoundIdVolumeQueue.push(sound);

	m_ConditionVariable.notify_one();
}
void SoundSystem::SoundPause()
{
	Mix_Pause(-1);
}
void SoundSystem::Update()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock{ m_Mutex };

		m_ConditionVariable.wait(lock, [this] { return !m_SoundIdVolumeQueue.empty() || m_StopThread; });

		if (m_StopThread) {
			break;
		}

		if (m_SoundIdVolumeQueue.size() > 0)
		{
			auto sound = m_SoundIdVolumeQueue.front();
			m_SoundIdVolumeQueue.pop();

			lock.unlock();

			Mix_Chunk* chunk = m_PendingSounds[sound.first];
			Mix_PlayChannel(-1, chunk, 0);
		}
	}
}