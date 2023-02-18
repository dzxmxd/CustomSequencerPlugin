
#include "TestTemplate.h"

#include "../Sections/TestSection.h"


struct FTestSectionExecutionToken : IMovieSceneExecutionToken
{
	FTestSectionExecutionToken(const UMovieSceneTestSection* InTestSection, const FVector InLocation)
		: TestSection(InTestSection), NewLocation(InLocation)
	{}
	virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player)
	{
		UMovieSceneTestTrack* TestTrack = Cast<UMovieSceneTestTrack>(TestSection->GetOuter());
		TestTrack->TestCameraActor->SetActorLocation(NewLocation);
	}
	const UMovieSceneTestSection* TestSection;
	const FVector NewLocation;
	FObjectKey SectionKey;
};






FMovieSceneTestSectionTemplate::FMovieSceneTestSectionTemplate()
{
}

FMovieSceneTestSectionTemplate::FMovieSceneTestSectionTemplate(const UMovieSceneTestSection& Section, const UMovieSceneTestTrack& Track)
{
}


void FMovieSceneTestSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const
{
	if (GEngine && GEngine->UseSound() && Context.GetStatus() != EMovieScenePlayerStatus::Jumping)
	{
		const UMovieSceneTestSection* TestSection = Cast<UMovieSceneTestSection>(GetSourceSection());
		
		float TimeValue = Context.GetTime().AsDecimal() / 100;
		UMovieSceneTestTrack* TestTrack = Cast<UMovieSceneTestTrack>(TestSection->GetOuter());
		ExecutionTokens.Add(FTestSectionExecutionToken(TestSection, FVector(0,0,TimeValue)));
	}
}