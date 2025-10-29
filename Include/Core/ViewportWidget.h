#pragma once

#include <QOpenGLWidget>
#include <QTimer>

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

signals:

    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(Qt::MouseButton button);
    void mouseReleased(Qt::MouseButton button);
    void mouseMoved(const QPointF& pos);


private slots:
    // Slot connected to QTimer for continuous rendering
    void onFrameReady();

private:
    // QTimer to drive the real-time loop (replaces while(m_Running))
    QTimer m_UpdateTimer;
    QElapsedTimer m_LastTime; // Used to calculate delta time

    // Placeholders for your existing C++ rendering engine/state
    // Renderer m_renderer;
    // LayerStack m_layerStack;
};
