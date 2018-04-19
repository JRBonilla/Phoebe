#pragma once

#include <string>
#include "ph/math/Math.h"

namespace ph { namespace debug {

	class MenuItem {
	protected:
		enum Type {
			INT_DRAG, INT_SLIDER, FLOAT_DRAG, FLOAT_SLIDER, CHECKBOX
		};
	protected:
		friend class DebugMenu;
		std::string  m_Label;
		Type         m_Type;
	public:
		MenuItem(const std::string& label, Type type)
			: m_Label(label), m_Type(type) {
		}
	};

	class IntSlider : public MenuItem {
	private:
		friend class DebugMenu;
		int* m_Var;
		int  m_Min, m_Max;
	public:
		IntSlider(const std::string& label, int* var, int min, int max)
			: m_Var(var), m_Min(min), m_Max(max), MenuItem(label, Type::INT_SLIDER) {
		}
	};

	class FloatSlider : public MenuItem {
	private:
		friend class DebugMenu;
		float* m_Var;
		float  m_Min, m_Max;
	public:
		FloatSlider(const std::string& label, float* var, float min, float max)
			: m_Var(var), m_Min(min), m_Max(max), MenuItem(label, Type::FLOAT_SLIDER) {
		}
	};

	class IntDrag : public MenuItem {
	private:
		friend class DebugMenu;
		float m_Speed;
		int*  m_Var;
		int   m_Min, m_Max;
	public:
		IntDrag(const std::string& label, float speed, int* var, int min, int max)
			: m_Speed(speed), m_Var(var), m_Min(min), m_Max(max), MenuItem(label, Type::INT_DRAG) {
		}
	};

	class FloatDrag : public MenuItem {
	private:
		friend class DebugMenu;
		float  m_Speed;
		float* m_Var;
		float  m_Min, m_Max;
	public:
		FloatDrag(const std::string& label, float speed, float* var, float min, float max)
			: m_Speed(speed), m_Var(var), m_Min(min), m_Max(max), MenuItem(label, Type::FLOAT_DRAG) {
		}
	};

	class Checkbox : public MenuItem {
	private:
		friend class DebugMenu;
		bool* m_Var;
	public:
		Checkbox(const std::string& label, bool* var)
			: m_Var(var), MenuItem(label, Type::CHECKBOX) {
		}
	};

	typedef std::vector<MenuItem*> MenuItemList;

}}