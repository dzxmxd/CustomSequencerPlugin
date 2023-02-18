#include "TestSection.h"


UMovieSceneTestSection::UMovieSceneTestSection(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

UMovieSceneTestSection::~UMovieSceneTestSection()
{
}

#if WITH_EDITOR
void UMovieSceneTestSection::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif