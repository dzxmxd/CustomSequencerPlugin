// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomSequencerPluginStyle.h"

class FCustomSequencerPluginCommands : public TCommands<FCustomSequencerPluginCommands>
{
public:

	FCustomSequencerPluginCommands()
		: TCommands<FCustomSequencerPluginCommands>(TEXT("CustomSequencerPlugin"), NSLOCTEXT("Contexts", "CustomSequencerPlugin", "CustomSequencerPlugin Plugin"), NAME_None, FCustomSequencerPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};