#include "pch.h"
#include "Core/Application.h"

#include <QApplication> // <-- Required for qApp and QApplication::quit
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QDebug>

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

	NVIZ_INFO("Application : {}", m_Specification.Name);
	NVIZ_INFO("\tWorking Directory : {}", m_Specification.WorkingDirectory.c_str());

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

	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	QAction* exitAction = fileMenu->addAction(tr("E&xit"));

	// Connect the exit action to the QApplication::quit slot
	connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(tr("&About"));
}

void Application::CreateDocks()
{


}

void Application::CreateCentralWidget()
{

	m_ViewportWidget = new ViewportWidget(this);

	setCentralWidget(m_ViewportWidget);
}
