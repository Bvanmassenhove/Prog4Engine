#pragma once
#include"SoundSystem.h"
#include <memory>


namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<BaseSoundSystem> m_pSoundSystemInstance;
		static std::unique_ptr<NullSoundSystem> m_pNullService;
	public:
		static BaseSoundSystem& Get_Sound_System() { return *m_pSoundSystemInstance; }
		static void Register_Sound_System(std::unique_ptr<BaseSoundSystem>&& ss)
		{
			m_pSoundSystemInstance = ss == nullptr ? std::move(m_pNullService) : std::move(ss);
		}
	};
}


