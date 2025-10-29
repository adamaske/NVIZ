#include "pch.h"
#include <glad/glad.h>
#include "Widgets/ViewportWidget.h"

#include <QElapsedTimer>
#include <QKeyEvent>
#include <QOpenGLContext>

#include "Core/Input.h"

#include "Renderer/Renderer.h"
#include "Renderer/ViewportManager.h"

ViewportWidget::ViewportWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    // --- 1. Setup the Real-time Loop QTimer ---
    // Connect the QTimer's timeout signal to our frame readiness slot
    connect(&m_UpdateTimer, &QTimer::timeout, this, &ViewportWidget::onFrameReady);

    // Start the timer to run at approximately 60 FPS (16ms interval)
    m_UpdateTimer.start(16);

    // Initialize the elapsed timer for delta time calculation
    m_LastTime.start();


    // Bind to Input -> 

    connect(this, &ViewportWidget::keyPressed, Input::Instance(), &Input::onKeyPressed);
    connect(this, &ViewportWidget::keyReleased, Input::Instance(), &Input::onKeyReleased);
    connect(this, &ViewportWidget::mousePressed, Input::Instance(), &Input::onMousePressed);
    connect(this, &ViewportWidget::mouseReleased, Input::Instance(), &Input::onMouseReleased);
    connect(this, &ViewportWidget::mouseMoved, Input::Instance(), &Input::onMouseMoved);
}

ViewportWidget::~ViewportWidget()
{
}

void ViewportWidget::initializeGL()
{
    if (!gladLoadGL()) {
        NVIZ_ERROR("Failed to initialize GLAD");
        return;
	}

    Renderer::Init();

    m_RoamCamera = CreateRef<RoamCamera>();
    m_OrbitCamera = CreateRef<OrbitCamera>();

    FramebufferSpecification fbSpec; // Init a framebuffer to show the probe
    fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::Depth };
    fbSpec.Width = width(); 
    fbSpec.Height = height();
    m_Framebuffer = CreateRef<Framebuffer>(fbSpec);

    ViewportManager::RegisterViewport({ "MainViewport", m_ViewTargetID, GetActiveCamera(), m_Framebuffer });

}

void ViewportWidget::resizeGL(int w, int h)
{
	Renderer::OnWindowResize(w, h);

	m_Framebuffer->Resize(w, h);
    
    // TOOD : Update Camera

}

void ViewportWidget::paintGL()
{
    // This is the draw call. The context is current.
    // ------------------------------------------------------------------
    // Your Existing Deferred Rendering Execution (Renderer::ExecuteQueue())

    Renderer::ExecuteQueue();
}

void ViewportWidget::onFrameReady()
{
    float deltaTime = m_LastTime.restart() / 1000.0f;

    if (m_ViewportHovered) {

        // Check if right mouse button is pressed for camera control
        if (Input::IsMouseButtonPressed(Qt::RightButton)) {
            if (!m_CameraControlActive) {
                StartMouseControl();
            }
            DoMouseControl(deltaTime);
        }
        else {
            if (m_CameraControlActive) {
                EndMouseControl();
            }
		}
    }


    // 4. Request the paintGL() call
    // This tells Qt to schedule a redraw, which executes the commands built above.
    this->update();
}


void ViewportWidget::keyPressEvent(QKeyEvent* event)
{
    // Check if the key is already pressed (to ignore auto-repeat events if needed)
    if (!event->isAutoRepeat()) {
        // Emit the signal using the standard Qt key code
        emit keyPressed(event->key());
    }
    QOpenGLWidget::keyPressEvent(event); // Pass the event up the chain
}

void ViewportWidget::keyReleaseEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat()) {
        // Emit the signal using the standard Qt key code
        emit keyReleased(event->key());
    }
    QOpenGLWidget::keyReleaseEvent(event);
}

void ViewportWidget::mousePressEvent(QMouseEvent* event)
{
    // Emit the signal using the standard Qt button code
    emit mousePressed(event->button());
    QOpenGLWidget::mousePressEvent(event);
}

void ViewportWidget::mouseReleaseEvent(QMouseEvent* event)
{
    // Emit the signal using the standard Qt button code
    emit mouseReleased(event->button());
    QOpenGLWidget::mouseReleaseEvent(event);
}

void ViewportWidget::mouseMoveEvent(QMouseEvent* event)
{
    // Emit the signal with the local widget coordinates
    emit mouseMoved(event->pos());
    QOpenGLWidget::mouseMoveEvent(event);
}

void ViewportWidget::enterEvent(QEnterEvent* event)
{
    m_ViewportHovered = true;
}

void ViewportWidget::leaveEvent(QEvent* event)
{
    m_ViewportHovered = false;
}

void ViewportWidget::StartMouseControl()
{
    NVIZ_INFO("START MOUSE CONTROL");
	m_CameraControlActive = true;
}

void ViewportWidget::DoMouseControl(float dt)
{
    NVIZ_INFO("DO MOUSE CONTROL");
}

void ViewportWidget::EndMouseControl()
{
    NVIZ_INFO("END MOUSE CONTROL");
	m_CameraControlActive = false;
}
