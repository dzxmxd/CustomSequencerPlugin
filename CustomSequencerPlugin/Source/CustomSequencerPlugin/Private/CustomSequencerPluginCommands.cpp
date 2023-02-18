// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomSequencerPluginCommands.h"

#define LOCTEXT_NAMESPACE "FCustomSequencerPluginModule"

void FCustomSequencerPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CustomSequencerPlugin", "Bring up CustomSequencerPlugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
