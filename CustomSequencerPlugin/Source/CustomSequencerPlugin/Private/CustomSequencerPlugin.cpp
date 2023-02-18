// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomSequencerPlugin.h"
#include "CustomSequencerPluginStyle.h"
#include "CustomSequencerPluginCommands.h"
#include "ISequencerModule.h"
#include "LevelEditor.h"
#include "LevelSequence.h"
#include "MovieSceneToolsProjectSettings.h"
#include "Widgets/Docking/SDockTab.h"
#include "ToolMenus.h"
#include "Sequencer/TestTrack/TrackEditors/TestTrackEditor.h"
#include "Sequencer/TestTrack/Tracks/TestTrack.h"
#include "LevelViewportTabContent.h"
#include "SLevelViewport.h"
#include "LevelSequenceEditorBlueprintLibrary.h"

#include "Modules/ModuleManager.h"



static const FName CustomSequencerPluginTabName("CustomSequencerPlugin");

#define LOCTEXT_NAMESPACE "FCustomSequencerPluginModule"

void FCustomSequencerPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomSequencerPluginStyle::Initialize();
	FCustomSequencerPluginStyle::ReloadTextures();

	FCustomSequencerPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomSequencerPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCustomSequencerPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCustomSequencerPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CustomSequencerPluginTabName, FOnSpawnTab::CreateRaw(this, &FCustomSequencerPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCustomSequencerPluginTabTitle", "CustomSequencerPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	ISequencerModule& SequencerModule = FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer");
	MovieSceneTestEditorHandler = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FMovieSceneTestEditor::CreateTrackEditor));
}

void FCustomSequencerPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCustomSequencerPluginStyle::Shutdown();

	FCustomSequencerPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CustomSequencerPluginTabName);
	
	ISequencerModule& SequencerModule = FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(MovieSceneTestEditorHandler);
}

TSharedRef<SDockTab> FCustomSequencerPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef< SDockTab> DockTab = SNew(SDockTab);
	// DockTab->SetTabIcon(FEditorStyle::GetBrush("LevelEditor.Tabs.Viewports"));
	TSharedPtr<FLevelViewportTabContent> ViewportTabContent = MakeShareable(new FLevelViewportTabContent());
	auto MakeLevelViewportFunc = [this](const FAssetEditorViewportConstructionArgs& InConstructionArgs)
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		TSharedPtr<ILevelEditor> LevelEditor = LevelEditorModule.GetFirstLevelEditor();
		return SNew(SLevelViewport, InConstructionArgs).ParentLevelEditor(LevelEditor);
	};
	ViewportTabContent->Initialize(MakeLevelViewportFunc, DockTab, TEXT(" Test Viewport"));
	return  DockTab;
}

void FCustomSequencerPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CustomSequencerPluginTabName);
	ULevelSequence* LevelSequencer = NewObject<ULevelSequence>();
	LevelSequencer->Initialize();
	const UMovieSceneToolsProjectSettings* ProjectSettings = GetDefault<UMovieSceneToolsProjectSettings>();
	FFrameRate TickResolution = LevelSequencer->GetMovieScene()->GetTickResolution();
	LevelSequencer->GetMovieScene()->SetPlaybackRange((ProjectSettings->DefaultStartTime * TickResolution).FloorToFrame(),
		(ProjectSettings->DefaultDuration * TickResolution).FloorToFrame().Value);
	UMovieSceneTestTrack* TestTrack = Cast<UMovieSceneTestTrack>(LevelSequencer->MovieScene->AddMasterTrack(UMovieSceneTestTrack::StaticClass()));
	check(TestTrack != nullptr);
	if (TestTrack != nullptr)
	{
		TestTrack->SetDisplayName(FText::FromString(" Test Track "));
		UWorld* World = GEditor->GetEditorWorldContext().World();
		check(World != nullptr);
		ACameraActor* CameraActor = World->SpawnActor<ACameraActor>();
		TestTrack->TestCameraActor = CameraActor;
	}
	ULevelSequenceEditorBlueprintLibrary::OpenLevelSequence(LevelSequencer);
}

void FCustomSequencerPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCustomSequencerPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCustomSequencerPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomSequencerPluginModule, CustomSequencerPlugin)