#include "pch.h"
#include "Core/ViewportWidget.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QKeyEvent>

#include "Core/Input.h"

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

    // Renderer::Init();
    
    // The OpenGL context is now current and active.
    // ------------------------------------------------------------------
    // 1. Load GL Functions (using Qt's QOpenGLFunctions or your own GLAD/GLEW)
    // If using QOpenGLFunctions: initializeOpenGLFunctions();

    // 2. Your Existing GL Setup (Shaders, VBOs, FBOs)

    // glClearColor(0.1f, 0.1f, 0.2f, 1.0f); 
    // glEnable(GL_DEPTH_TEST);
    // m_renderer.compileShaders();
    // m_renderer.setupGeometry();
    // ------------------------------------------------------------------

}

void ViewportWidget::resizeGL(int w, int h)
{
    // ------------------------------------------------------------------
    // Your Existing GL Resize Logic
    // 1. Update the viewport
    // glViewport(0, 0, w, h);

    // 2. Recalculate Projection Matrix
    // m_camera.setPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
    // ------------------------------------------------------------------

}

void ViewportWidget::paintGL()
{
    // This is the draw call. The context is current.
    // ------------------------------------------------------------------
    // Your Existing Deferred Rendering Execution (Renderer::ExecuteQueue())

    // 1. Clear Screen
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 2. Execute Deferred Pipeline
    // m_renderer.ExecuteQueue(); 

    // 3. Render ImGui/Overlays (must be done here)
    // m_ImGuiLayer->Render();
    // ------------------------------------------------------------------
}

void ViewportWidget::onFrameReady()
{
    // This is your new "Game Loop" tick function.

    // 1. Calculate Delta Time (in seconds)
    float deltaTime = m_LastTime.restart() / 1000.0f;

    // 2. Clear the Renderer Queue (BeginScene)
    // m_renderer.BeginScene();

    // 3. Update Scene Logic (LayerStack) - Commands submitted to renderer queue
    // for (Layer* layer : m_layerStack) {
    //     layer->OnUpdate(deltaTime);
    // }

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
