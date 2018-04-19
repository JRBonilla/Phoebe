#include "FPSCamera.h"
#include "ph/app/Application.h"
#include "ph/app/InputManager.h"

namespace ph { namespace renderer {

	using namespace math;

	FPSCamera::FPSCamera(const math::Mat4& projectionMatrix)
		: Camera(projectionMatrix), m_Speed(0.4f), m_SprintSpeed(m_Speed * 4.0f), m_MouseWasGrabbed(false) {
		m_VerticalSensitivity = 0.002f;
		m_HorizontalSensitivity = 0.002f;
		m_Position = Vec3(0.0f, 25.0f, -25.0f);
		m_Rotation = Vec3(90.0f, 0.0f, 0.0f);
		m_Yaw = 2.4f;
		m_Pitch = 0.7f;
	}

	FPSCamera::~FPSCamera() {
	}

	void FPSCamera::Focus() {
	}

	void FPSCamera::Update() {
		Vec2 windowSize   = Application::GetApplication().GetWindowSize();
		Vec2 windowCenter = Vec2((float)(int32)(windowSize.x / 2.0f), (float)(int32)(windowSize.y / 2.0f));

		// Grab mouse if left mouse button clicked
		if (InputManager::IsMouseButtonClicked(GLFW_MOUSE_BUTTON_LEFT)) {
			if (!InputManager::IsMouseGrabbed()) {
				InputManager::SetMouseGrabbed(true);
			}
		}

		// If mouse is grabbed, update the camera
		if (InputManager::IsMouseGrabbed()) {
			Vec2 mouse = InputManager::GetMousePosition();
			mouse.x -= windowCenter.x;
			mouse.y -= windowCenter.y;
			if (m_MouseWasGrabbed) {
				m_Yaw   += mouse.x * m_HorizontalSensitivity;
				m_Pitch += mouse.y * m_VerticalSensitivity;
				m_Pitch  = clamp(m_Pitch, -1.0f, 1.0f);
			}
			m_MouseWasGrabbed = true;
			InputManager::SetMousePosition(windowCenter);

			Quat orientation = GetOrientation();
			m_Rotation = orientation.ToEulerAngles() * (180.0f / F_PI);

			Vec3 forward = GetForwardDirection(orientation);
			Vec3 right   = GetRightDirection(orientation);
			Vec3 up      = Vec3::YAxis();

			bool shiftKeyPressed = InputManager::IsKeyPressed(GLFW_KEY_RIGHT_SHIFT) ||
				                   InputManager::IsKeyPressed(GLFW_KEY_LEFT_SHIFT);
			bool ctrlKeyPressed  = InputManager::IsKeyPressed(GLFW_KEY_RIGHT_CONTROL) ||
				                   InputManager::IsKeyPressed(GLFW_KEY_LEFT_CONTROL);

			float speed = shiftKeyPressed ? m_SprintSpeed : m_Speed;
			if (InputManager::IsKeyPressed(GLFW_KEY_W)) {
				m_Position += forward * speed;
			}
			else if (InputManager::IsKeyPressed(GLFW_KEY_S)) {
				m_Position -= forward * speed;
			}

			if (InputManager::IsKeyPressed(GLFW_KEY_A)) {
				m_Position -= right * speed;
			}
			else if (InputManager::IsKeyPressed(GLFW_KEY_D)) {
				m_Position += right * speed;
			}

			if (InputManager::IsKeyPressed(GLFW_KEY_SPACE)) {
				m_Position += up * speed;
			}
			if (ctrlKeyPressed) {
				m_Position -= up * speed;
			}

			Mat4 rotation    = Mat4::Rotate(orientation.Conjugate());
			Mat4 translation = Mat4::Translate(-m_Position);
			m_ViewMatrix = rotation * translation;
		}

		// If the escape key is pressed, release the mouse
		if (InputManager::IsKeyPressed(GLFW_KEY_ESCAPE)) {
			InputManager::SetMouseGrabbed(false);
			m_MouseWasGrabbed = false;
		}
	}

	Quat FPSCamera::GetOrientation() const {
		return Quat::RotationY(-m_Yaw) * Quat::RotationX(-m_Pitch);
	}

	Vec3 FPSCamera::GetForwardDirection(const Quat& orientation) const {
		return Quat::Rotate(orientation, -Vec3::ZAxis());
	}

	Vec3 FPSCamera::GetForwardDirection() const {
		return GetForwardDirection(GetOrientation());
	}

	Vec3 FPSCamera::GetUpDirection(const Quat& orientation) const {
		return Quat::Rotate(orientation, Vec3::YAxis());
	}

	Vec3 FPSCamera::GetUpDirection() const {
		return GetUpDirection(GetOrientation());
	}

	Vec3 FPSCamera::GetRightDirection(const Quat& orientation) const {
		return Quat::Rotate(orientation, Vec3::XAxis());
	}

	Vec3 FPSCamera::GetRightDirection() const {
		return GetRightDirection(GetOrientation());
	}

}}