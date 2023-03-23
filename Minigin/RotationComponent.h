#include <memory>
#include "Transform.h"
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class RotationComponent final : public BaseComponent
	{
	public:
		explicit RotationComponent(float angle, float rotDistance, bool cloackwise, GameObject* object);
		virtual ~RotationComponent() = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		void Update(float) override;
		void Render() const override;

	private:
		float m_Angle;
		float m_RotDistance;
		bool m_RotClockwise;

	};
}
