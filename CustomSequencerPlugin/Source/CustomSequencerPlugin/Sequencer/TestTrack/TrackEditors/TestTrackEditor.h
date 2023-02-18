#pragma once
#include "MovieSceneTrack.h"
#include "CoreMinimal.h"
#include "MovieSceneTrackEditor.h"

class UMovieScenePlotPositionTemplateTrack;
class ISequencer;

class CUSTOMSEQUENCERPLUGIN_API FMovieSceneTestEditor : public FMovieSceneTrackEditor
{
public:
	FMovieSceneTestEditor(TSharedRef<ISequencer> InSequencer);
	virtual ~FMovieSceneTestEditor();

	static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);


public:
	virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual const FSlateBrush* GetIconBrush() const override;
	virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;
	virtual bool IsResizable(UMovieSceneTrack* InTrack) const override;

	virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;
	virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;

private:
	void HandleAddTrackOnActorMenuEntryExecute(FMenuBuilder&, TArray<FGuid>);
};


class FMovieSceneTestSection : public ISequencerSection
	, public TSharedFromThis<FMovieSceneTestSection>
{
public:
	FMovieSceneTestSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);
	virtual ~FMovieSceneTestSection();

public:
	virtual UMovieSceneSection* GetSectionObject() override;

	virtual FText GetSectionTitle() const override;
	virtual FText GetSectionToolTip() const override;
	virtual float GetSectionHeight() const override;

	virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;
	virtual bool SectionIsResizable() const{ return true; }
	virtual void GenerateSectionLayout(class ISectionLayoutBuilder& LayoutBuilder);
	
	virtual void BeginResizeSection() override;
	virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;

	virtual void BeginSlipSection() override;
	virtual void SlipSection(FFrameNumber SlipTime) override;

private:
	TWeakObjectPtr<UMovieSceneSection> Section;
	TWeakPtr<ISequencer> Sequencer;
};