#include "TestTrackEditor.h"
#include "ISequencer.h"
#include "LevelSequence.h"
#include "SequencerSectionPainter.h"
#include "EditorStyleSet.h"

#include "../Sections/TestSection.h"
#include "../Tracks/TestTrack.h"

#define LOCTEXT_NAMESPACE "FTestTrackEditor"

TSharedRef<ISequencerTrackEditor> FMovieSceneTestEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FMovieSceneTestEditor(InSequencer));
}

FMovieSceneTestEditor::FMovieSceneTestEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{
}

FMovieSceneTestEditor::~FMovieSceneTestEditor()
{
}

const FSlateBrush* FMovieSceneTestEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("DebugConsole.Icon");
}

TSharedRef<ISequencerSection> FMovieSceneTestEditor::MakeSectionInterface(UMovieSceneSection& SectionObject,
	UMovieSceneTrack& Track,
	FGuid ObjectBinding)
{
	check(SupportsType(SectionObject.GetOuter()->GetClass()));
	return MakeShareable(new FMovieSceneTestSection(SectionObject, GetSequencer()));
}

bool FMovieSceneTestEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const
{
	return Type == UMovieSceneTestTrack::StaticClass();
}

bool FMovieSceneTestEditor::SupportsSequence(UMovieSceneSequence* InSequence) const
{
	return true;
}

bool FMovieSceneTestEditor::IsResizable(UMovieSceneTrack* InTrack) const
{
	return false;
}

bool FMovieSceneTestEditor::OnAllowDrop(const FDragDropEvent& DragDropEvent,
	FSequencerDragDropParams& DragDropParams)
{
	return false;
}

FReply FMovieSceneTestEditor::OnDrop(const FDragDropEvent& DragDropEvent,
	const FSequencerDragDropParams& DragDropParams)
{
	return FReply::Handled();
}

void FMovieSceneTestEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder,
	const TArray<FGuid>& ObjectBindings,
	const UClass* ObjectClass)
{
	if (ObjectClass != nullptr && ObjectClass->IsChildOf(AActor::StaticClass()))
	{
	}
	return;
}

void FMovieSceneTestEditor::HandleAddTrackOnActorMenuEntryExecute(FMenuBuilder& MenuBuilder,
	TArray<FGuid> ObjectBindings)
{
}


FMovieSceneTestSection::FMovieSceneTestSection(UMovieSceneSection& InSection,
	TWeakPtr<ISequencer> InSequencer)
	: Section(&InSection)
	, Sequencer(InSequencer)
{
}

FMovieSceneTestSection::~FMovieSceneTestSection()
{
}

UMovieSceneSection* FMovieSceneTestSection::GetSectionObject()
{
	return Section.Get();
}

FText FMovieSceneTestSection::GetSectionTitle() const
{
	return FText::FromString("Test  Section Name");
}

FText FMovieSceneTestSection::GetSectionToolTip() const
{
	return FText::FromString("Test  ToolTip");
}

float FMovieSceneTestSection::GetSectionHeight() const
{
	return 40;
}

int32 FMovieSceneTestSection::OnPaintSection(FSequencerSectionPainter& Painter) const
{
	return Painter.PaintSectionBackground();
}


void FMovieSceneTestSection::BeginResizeSection()
{
}

void FMovieSceneTestSection::ResizeSection(ESequencerSectionResizeMode ResizeMode,
	FFrameNumber ResizeTime)
{
	ISequencerSection::ResizeSection(ResizeMode, ResizeTime);
}

void FMovieSceneTestSection::GenerateSectionLayout(class ISectionLayoutBuilder& LayoutBuilder)
{
}

void FMovieSceneTestSection::BeginSlipSection()
{
}

void FMovieSceneTestSection::SlipSection(FFrameNumber SlipTime)
{
	ISequencerSection::SlipSection(SlipTime);
}

#undef LOCTEXT_NAMESPACE
