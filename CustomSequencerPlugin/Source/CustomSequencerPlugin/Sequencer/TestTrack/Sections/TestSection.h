#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"

#include "TestSection.generated.h"

class FPlotSequenceManager;

UCLASS()
class CUSTOMSEQUENCERPLUGIN_API UMovieSceneTestSection :public UMovieSceneSection
{
	GENERATED_BODY()
public:
	UMovieSceneTestSection(const FObjectInitializer& ObjectInitializer);
	virtual ~UMovieSceneTestSection();

	int32 GetTestValue() { return TestValue; };
	int32 TestValue = 114514;
public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
private:
};
