#include "EditorCamera.h"
#include "ph/utils/Log.h"
#include "ph/debug/DebugMenu.h"

namespace ph { namespace renderer {

	using namespace math;

	EditorCamera::EditorCamera(const math::Mat4& projectionMatrix)
		: Camera(projectionMatrix) {
		m_PanSpeed = 0.0015f;
		m_RotationSpeed = 0.002f;
		m_ZoomSpeed = 0.2f;

		m_ZoomAmount = 0;
		m_LastScrollY = InputManager::GetScrollY();

		m_Position = math::Vec3(0.0f, 25.0f, -25.0f);
		m_Rotation = math::Vec3(0.0f, 0.0f, 0.0f);

		m_FocalPoint = math::Vec3(0.0f);
		m_Distance = m_Position.Distance(m_FocalPoint);

		m_Yaw = 0.0f;
		m_Pitch = F_PI / 8.0f;
	}

	void EditorCamera::Focus() {
	}

	void EditorCamera::Update() {
		const math::Vec2& mouse = InputManager::GetMousePosition();

		math::Vec2 delta = mouse - m_InitialMousePosition;
		m_InitialMousePosition = mouse;

		if (!debug::DebugMenu::HasFocus()) {
			if (InputManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
				MousePan(delta);
			}
			else if (InputManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
				MouseRotate(delta);
			}
			else if (InputManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
				MouseZoom(delta.y);
			}
		}

		/*if (m_LastScrollY != InputManager::GetScrollY()) {
			m_ZoomAmount += InputManager::GetScrollY();
			MouseZoom(m_ZoomAmount);
			m_LastScrollY = InputManager::GetScrollY();
		}
		m_ZoomAmount = 0;
		InputManager::SetScrollY(0);*/
		
		m_Position = CalculatePosition();

		Quat orientation = GetOrientation();
		m_Rotation = orientation.ToEulerAngles() * (180.0f / F_PI);

		m_ViewMatrix = math::Mat4::Translate(math::Vec3(0, 0, 1)) * math::Mat4::Rotate(orientation.Conjugate()) * math::Mat4::Translate(-m_Position);
	}

	void EditorCamera::MousePan(const math::Vec2& delta) {
		m_FocalPoint += -GetRightDirection() * delta.x * m_PanSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * delta.y * m_PanSpeed * m_Distance;
	}

	void EditorCamera::MouseRotate(const math::Vec2& delta) {
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * m_RotationSpeed;
	}

	void EditorCamera::MouseZoom(float delta) {
		m_Distance -= delta * m_ZoomSpeed;
		if (m_Distance < 1.0f) {
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	math::Vec3 EditorCamera::GetUpDirection() const {
		return Quat::Rotate(GetOrientation(), math::Vec3::YAxis());
	}

	math::Vec3 EditorCamera::GetRightDirection() const {
		return Quat::Rotate(GetOrientation(), math::Vec3::XAxis());
	}

	math::Vec3 EditorCamera::GetForwardDirection() const {
		return Quat::Rotate(GetOrientation(), -math::Vec3::ZAxis());
	}

	math::Vec3 EditorCamera::CalculatePosition() const {
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	Quat EditorCamera::GetOrientation() const {
		return Quat::RotationY(-m_Yaw) * Quat::RotationX(-m_Pitch);
	}

}}