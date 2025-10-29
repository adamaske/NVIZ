#pragma once
#include <QMainWindow.h>
#include "Core/Base.h"

class ViewportWidget;
class CameraSettingsWidget;

struct ApplicationCommandLineArgs
{
	int count = 0;
	char** args = nullptr;

	const char* operator[](int index) const
	{
		return args[index];
	}

};
struct ApplicationSpecification
{
	std::string Name = "NIRS Viz";
	std::string WorkingDirectory;
	ApplicationCommandLineArgs CommandLineArgs;
};

class Application : public QMainWindow {
	Q_OBJECT
public:

	Application(const ApplicationSpecification& spec);
	~Application();

	static Application* Instance() { return s_Instance; };
private:

	void CreateMenus();
	void CreateDocks();
	void CreateCentralWidget(); // Method for viewport

public slots:

signals:
	
private:
	static Application* s_Instance;

	ApplicationSpecification m_Specification;

	ViewportWidget* m_ViewportWidget = nullptr;
	CameraSettingsWidget* m_CameraSettingsWidget = nullptr;
	// Setup Methods
};