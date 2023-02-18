#pragma once
#include "Tracks/MovieSceneSpawnTrack.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "Camera/CameraActor.h"
#include "MovieSceneNameableTrack.h"
#include "TestTrack.generated.h"

class UMovieSceneTestSection;

UCLASS()
class CUSTOMSEQUENCERPLUGIN_API UMovieSceneTestTrack : public UMovieSceneNameableTrack, public IMovieSceneTrackTemplateProducer
{
	GENERATED_BODY()
public:
	UMovieSceneTestTrack(const FObjectInitializer& ObjectInitializer);
	virtual ~UMovieSceneTestTrack();

public:
	virtual void AddSection(UMovieSceneSection& Section) override;
	virtual class UMovieSceneSection* CreateNewSection() override;
	virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;
	virtual bool HasSection(const UMovieSceneSection& Section) const override;
	virtual bool IsEmpty() const override;
	// virtual void RemoveAllAnimationData() override;
	virtual void RemoveSection(UMovieSceneSection & Section) override;
	virtual FName GetTrackName() const;
	virtual bool SupportsMultipleRows() const;
	virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const;

	// 用于测试的 Actor
	TWeakObjectPtr<ACameraActor> TestCameraActor;

	virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;

private:
	UPROPERTY()
	TArray<UMovieSceneSection*> Sections;
};
