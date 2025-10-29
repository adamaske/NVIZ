#pragma once

#include <QOpenGLWidget>
#include <QTimer>
#include <QElapsedTimer>

#include "Core/Base.h"
#include "Renderer/CameraSettings.h"
#include "Renderer/RoamCamera.h"
#include "Renderer/OrbitCamera.h"

class Framebuffer;
using ViewID = uint32_t;

class ViewportWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    ViewportWidget(QWidget* parent = nullptr);
    ~ViewportWidget();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;


signals:
    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(Qt::MouseButton button);
    void mouseReleased(Qt::MouseButton button);
    void mouseMoved(const QPointF& pos);

public slots:
    void SetCameraMode(CameraMode mode);
private slots:
    // Slot connected to QTimer for continuous rendering
    void onFrameReady();
private:
    // QTimer to drive the real-time loop (replaces while(m_Running))
    QTimer m_UpdateTimer;
    QElapsedTimer m_LastTime; // Used to calculate delta time



    ViewID m_ViewTargetID = 1; // Passed to renderer to specify this viewport
    Ref<Framebuffer> m_Framebuffer = nullptr;
	// THis widget checks wheter or not the user has the mouse over the viewport
    // If so, the we want to check if they have the right mouse button held down to control the camera
    // 
    CameraMode m_CameraMode = ROAM;
    Ref<RoamCamera> m_RoamCamera = nullptr;
    Ref<OrbitCamera> m_OrbitCamera = nullptr;

    Ref<Camera> GetActiveCamera() {
        return m_CameraMode == ROAM ? m_RoamCamera : (Ref<Camera>)m_OrbitCamera;
    }


    glm::vec2 m_ViewportBoundsMin = { 0.0f, 0.0f };
    glm::vec2 m_ViewportBoundsMax = { 0.0f, 0.0f };
    glm::vec2 m_InitialMousePos = { 0.0f, 0.0f };

    bool m_ViewportHovered = false;
    bool m_CameraControlActive = false;

    void StartMouseControl();
    void DoMouseControl(float dt);
    void EndMouseControl();
};
