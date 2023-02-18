
#include "TestTrack.h"
#include "../Sections/TestSection.h"
#include "../Evaluation/TestTemplate.h"

#define LOCTEXT_NAMESPACE "UMovieSceneTestTrack"

UMovieSceneTestTrack::UMovieSceneTestTrack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedBlendTypes.Add(EMovieSceneBlendType::Absolute);
#if WITH_EDITORONLY_DATA
	TrackTint = FColor(249, 98, 31, 150);
#endif
}

UMovieSceneTestTrack::~UMovieSceneTestTrack()
{
}

FName UMovieSceneTestTrack::GetTrackName() const 
{
    static FName TestTrackName = TEXT("TestTrack");
	return TestTrackName;
}

bool UMovieSceneTestTrack::IsEmpty() const 
{
	return (Sections.Num() == 0);
}

bool UMovieSceneTestTrack::SupportsMultipleRows() const 
{
	return true;
}

bool UMovieSceneTestTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneTestSection::StaticClass();
}

FMovieSceneEvalTemplatePtr UMovieSceneTestTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const
{
	return FMovieSceneTestSectionTemplate(*CastChecked<UMovieSceneTestSection>(&InSection), *this);
}

void UMovieSceneTestTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}

UMovieSceneSection* UMovieSceneTestTrack::CreateNewSection() {
	UMovieSceneTestSection* Section = NewObject<UMovieSceneTestSection>(this, NAME_None, RF_Transactional);
	return Section;
}

const TArray<UMovieSceneSection*>& UMovieSceneTestTrack::GetAllSections() const {
	return Sections;
}

bool UMovieSceneTestTrack::HasSection(const UMovieSceneSection& Section) const {
	return Sections.Contains(&Section);
}

void UMovieSceneTestTrack::RemoveSection(UMovieSceneSection& Section) {
	Sections.Remove(&Section);
}

#undef LOCTEXT_NAMESPACE
