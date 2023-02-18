#pragma once

#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "../Tracks/TestTrack.h"
#include "TestTemplate.generated.h"

class UMovieSceneTestTrack;
class UMovieSceneTestSection;


USTRUCT()
struct FMovieSceneTestSectionTemplate : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()

	FMovieSceneTestSectionTemplate();
	FMovieSceneTestSectionTemplate(const UMovieSceneTestSection& Section, const UMovieSceneTestTrack& Track);

private:
	virtual UScriptStruct& GetScriptStructImpl() const override { return *StaticStruct(); }
	virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;

};
