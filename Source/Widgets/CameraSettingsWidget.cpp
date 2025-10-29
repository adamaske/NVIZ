#include "pch.h"
#include "Widgets/CameraSettingsWidget.h"
#include <QVBoxLayout>
#include <QComboBox>
#include "ui_cameracontrolwidget.h" // This fails and doesnt allow compilation....

CameraSettingsWidget::CameraSettingsWidget(QWidget* parent) : QWidget(parent), ui(new Ui::CameraControlWidget)
{
    ui->setupUi(this); // 2. Initialize the UI and populate 'this' widget

    // Now, access the widgets using the objectName you set in Designer:
    QComboBox* modeComboBox = ui->comboBox;

    // Populate the QComboBox (do this in C++ if the items are dynamic/enum based)
    modeComboBox->addItem("Roam Camera", CameraMode::ROAM);
    modeComboBox->addItem("Orbit Camera", CameraMode::ORBIT);

    // Connect the signal from the UI widget to your private slot
    connect(modeComboBox,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &CameraSettingsWidget::OnComboBoxIndexChanged);

	QSlider* moveSpeedSlider = ui->MovementSpeedSlider;
    QSlider* rotSpeedSlider = ui->RotationSpeedSlider;

    // 
}

CameraSettingsWidget::~CameraSettingsWidget()
{
}

void CameraSettingsWidget::OnComboBoxIndexChanged(int index)
{
    // Retrieve the associated data (our CameraMode enum value) from the selected item
    std::map<int, CameraMode> indexToMode = {
        {0, CameraMode::ROAM},
        {1, CameraMode::ORBIT}
	};
    CameraMode newMode = indexToMode[ui->comboBox->itemData(index).toInt()];

    // Only emit if the mode has actually changed
    if (newMode != m_CurrentCameraMode)
    {
        m_CurrentCameraMode = newMode;
        emit OnCameraModeChanged(newMode);
    }
}


