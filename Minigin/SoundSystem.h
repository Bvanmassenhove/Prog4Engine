#pragma once
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#include <queue>
#include <SDL_mixer.h>

namespace dae
{
	class BaseSoundSystem
	{
	public:
		BaseSoundSystem() = default;
		virtual ~BaseSoundSystem() = default;
		BaseSoundSystem(const BaseSoundSystem& other) = delete;
		BaseSoundSystem(BaseSoundSystem&& other) noexcept = delete;
		BaseSoundSystem& operator=(const BaseSoundSystem& other) = delete;
		BaseSoundSystem& operator=(BaseSoundSystem&& other) noexcept = delete;

		virtual void AddSound(const std::string& soundPath) = 0;
		virtual void PlaySound(int ID , Uint8 Volume) = 0;
		virtual void SoundPause() = 0;
		virtual void Update() = 0;
	};

	class NullSoundSystem final : public BaseSoundSystem
	{
	public:
		NullSoundSystem() = default;
		virtual ~NullSoundSystem() override = default;
		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) noexcept = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) noexcept = delete;

		virtual void AddSound(const std::string& /*soundPath*/) override {}
		virtual void PlaySound(int /*ID*/, Uint8 /*Volume*/) override {}
		virtual void SoundPause() override {}
		virtual void Update() override {}
	};

	class SoundLogger : public BaseSoundSystem
	{
	public:
		SoundLogger();
		virtual ~SoundLogger() override = default;
		SoundLogger(const SoundLogger& other) = delete;
		SoundLogger(SoundLogger&& other) noexcept = delete;
		SoundLogger& operator=(const SoundLogger& other) = delete;
		SoundLogger& operator=(SoundLogger&& other) noexcept = delete;

		virtual void AddSound(const std::string& soundPath) override;
		virtual void PlaySound(int ID, Uint8 Volume) override;
		virtual void SoundPause() override;
		virtual void Update() override;
	private:
		std::unique_ptr<BaseSoundSystem> m_pSoundSystem;
	};

	class SoundSystem final : public BaseSoundSystem
	{
	public:
		SoundSystem();
		virtual ~SoundSystem() override;
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) noexcept = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) noexcept = delete;

		virtual void AddSound(const std::string& soundPath) override;
		virtual void PlaySound(int ID, Uint8 Volume) override;
		virtual void SoundPause() override;
		virtual void Update() override;

	private:
		class AudioThreadFunctor
		{
		public:
			explicit AudioThreadFunctor(SoundSystem* soundSystem) : m_SoundSystem{ soundSystem } {}
			void operator()() { m_SoundSystem->Update(); }

		private:
			SoundSystem* m_SoundSystem;
		};

		bool m_StopThread{ false };
		std::jthread m_SoundThread;
		std::condition_variable m_ConditionVariable;
		std::mutex m_Mutex;

		std::queue<std::pair<int, Uint8>> m_SoundIdVolumeQueue;
		std::vector<Mix_Chunk*> m_PendingSounds;
		
	};
}