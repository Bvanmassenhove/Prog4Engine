#include "ServiceLocator.h"

using namespace dae;

std::unique_ptr<dae::NullSoundSystem> dae::ServiceLocator::m_pNullService{};
std::unique_ptr<dae::BaseSoundSystem> dae::ServiceLocator::m_pSoundSystemInstance{std::move(m_pNullService)};