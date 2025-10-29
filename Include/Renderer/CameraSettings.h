#pragma once

enum CameraMode {
	ROAM = 0,
	ORBIT = 1
};

struct RoamCameraSettings {
	float MovementSpeed = 5.0f;
	float MouseSensitivity = 0.1f;
};

struct OrbitCameraSettings {
	float Distance = 10.0f;
	float MouseSensitivity = 0.1f;
};


