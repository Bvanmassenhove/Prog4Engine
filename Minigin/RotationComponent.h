#include <memory>
#include "Transform.h"
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class RotationComponent final : public BaseComponent
	{
	public:
		explicit RotationComponent(glm::vec3 rotCenter,float rotSpeed,bool cloackwise,float rotDistance, GameObject* object);
		virtual ~RotationComponent() = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		void Update(float) override;
		void Render() const override;
		void SetRotCenter(glm::vec3 rotCenter) { m_RotCenter = rotCenter; }

	private:
		glm::vec3 m_RotCenter;
		float m_RotSpeed;
		bool m_RotClockwise;
		float m_RotDistance;

	};
}
