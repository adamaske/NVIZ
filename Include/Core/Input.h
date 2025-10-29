#pragma once

#include <QObject>
#include <QPointF>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QHash>

#include <glm/glm.hpp> 

#include <QOpenGLWidget.h>


using KeyCode = int;
using MouseCode = Qt::MouseButton;

enum CursorMode {
	Normal = 0,
	Disabled = 1
};

class Input : public QObject
{
    Q_OBJECT
public:
    Input();
    
    // Polling Functions (now read from the cache)
    static bool IsKeyPressed(const KeyCode key);
    static bool IsMouseButtonPressed (const MouseCode button);
    static glm::vec2 GetMousePosition ();


    static Input* Instance() { return s_Instance; };
public slots:
    // Slots connected from ViewportWidget's signals to update the cache
    void onKeyPressed (KeyCode key);
    void onKeyReleased (KeyCode key);
    void onMousePressed (MouseCode button);
    void onMouseReleased (MouseCode button);
    void onMouseMoved (const QPointF& pos);

private:
    static Input* s_Instance;

    QHash<KeyCode, bool> m_keyStates;
    QHash<MouseCode, bool> m_mouseButtonStates;
    QPointF m_mousePosition;
};