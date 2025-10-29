#pragma once

#include "Core/Base.h"


// EventBus is a singleton class that manages event subscriptions and publishing.
// Here we define the structs which represent different commands/events in the application.

struct CoordinateSystemGenerated {

	// No additional data needed for this command
};

struct SNIRFFileLoadedEvent {
};

struct HeadAnatomyLoadedEvent {

};

struct CortexAnatomyLoadedEvent {

};

struct ToggleProjectHemodynamicsToCortexCommand {
	bool Enabled = true;

};

struct ExitApplicationCommand {
	// No additional data needed for this event
};

struct UpdateProjectionDataChannelValuesCommand {

};