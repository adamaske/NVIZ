#include "pch.h"
#include "Core/Input.h"
#include "Core/Base.h"

Input* Input::s_Instance = nullptr;

void Input::Init()
{
    if (!s_Instance)
    {
        s_Instance = new Input();
		NVIZ_INFO("Input system initialized.");
    }
}

bool Input::IsKeyPressed(const KeyCode key)
{
	return s_Instance->m_keyStates.value(key, false);
}

bool Input::IsMouseButtonPressed(const MouseCode button)
{
	return s_Instance->m_mouseButtonStates.value(button, false);
}

glm::vec2 Input::GetMousePosition()
{
    const auto& pos = s_Instance->m_mousePosition;
    return glm::vec2(pos.x(), pos.y());
}


void Input::onKeyPressed(KeyCode key)
{
    m_keyStates[key] = true;
}

void Input::onKeyReleased(KeyCode key)
{
    m_keyStates[key] = false;
}

void Input::onMousePressed(MouseCode button)
{
    m_mouseButtonStates[button] = true;
}

void Input::onMouseReleased(MouseCode button)
{
    m_mouseButtonStates[button] = false;
}

void Input::onMouseMoved(const QPointF& pos)
{
    m_mousePosition = pos;
}
