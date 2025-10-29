#include "pch.h"
#include "Core/Application.h"

#include <QApplication> // <-- Required for qApp and QApplication::quit
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QDebug>

#include "Widgets/ViewportWidget.h"
#include "Widgets/CameraSettingsWidget.h"

Application* Application::s_Instance = nullptr;
Application::Application(const ApplicationSpecification& spec) : m_Specification(spec)
{
	s_Instance = this;
	// Set working directory here// Check if the WorkingDirectory string is NOT empty.
	if (!m_Specification.WorkingDirectory.empty())
	{
		// If it's not empty, set the current path to the specified directory.
		// Note: You might want to add error handling here in case the path is invalid.
		std::filesystem::current_path(m_Specification.WorkingDirectory);
	}

	NVIZ_INFO("Application Created : {}", m_Specification.Name);
	NVIZ_INFO("\tWorking Directory : {}", m_Specification.WorkingDirectory);

	setStyleSheet(R"(
    /* Target common widgets that usually have rounded corners */
    QComboBox, QLineEdit, QPushButton, QWidget {
        border-radius: 1px;
    }

    /* Set the QWidget base style to sharp edges */
    QWidget {
        border-radius: 1px; 
    }
	)");

	setWindowTitle(m_Specification.Name.c_str());
	setMinimumSize(1200, 800);

	CreateMenus();
	CreateDocks();
	CreateCentralWidget();
}

Application::~Application()
{

}

void Application::CreateMenus()
{

	// --- File ---
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	QAction* exitAction = fileMenu->addAction(tr("E&xit"));

	// Connect the exit action to the QApplication::quit slot
	connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

	// --- View ---
	QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
	QAction* toggleCameraSettingsDockAction = viewMenu->addAction(tr("Camera Settings"));
	connect(toggleCameraSettingsDockAction, &QAction::triggered, [this]() {
		if (m_CameraSettingsWidget) {
			m_CameraSettingsWidget->parentWidget()->setVisible(!m_CameraSettingsWidget->parentWidget()->isVisible());
		}
		});

	// --- Help ---
	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(tr("&About"));
}

void Application::CreateDocks()
{
	// What goes here? 

}

void Application::CreateCentralWidget()
{
	// OpenGL viewport -> 
	m_ViewportWidget = new ViewportWidget(this);
	setCentralWidget(m_ViewportWidget);

	QDockWidget* dockWidget = new QDockWidget(tr("Camera Settings"), this);
	m_CameraSettingsWidget = new CameraSettingsWidget(this);
	dockWidget->setWidget(m_CameraSettingsWidget);
	dockWidget->setMinimumWidth(200);

	addDockWidget(Qt::RightDockWidgetArea, dockWidget);

	connect(m_CameraSettingsWidget,
		&CameraSettingsWidget::OnCameraModeChanged,
		m_ViewportWidget,
		&ViewportWidget::SetCameraMode);
}
