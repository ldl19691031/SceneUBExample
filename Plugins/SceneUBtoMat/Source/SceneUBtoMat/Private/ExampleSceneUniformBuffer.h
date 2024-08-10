#pragma once
#include "CoreMinimal.h"
#include "ShaderParameterMacros.h"
#include "SceneUniformBuffer.h"
#include "Engine/DataTable.h"
#include "ExampleSceneUniformBuffer.generated.h"

BEGIN_SHADER_PARAMETER_STRUCT(FExampleSceneUniformBufferParams,)
	SHADER_PARAMETER(FVector3f, TestColor)
	SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float>, TestBuffer)
END_SHADER_PARAMETER_STRUCT()

DECLARE_SCENE_UB_STRUCT(FExampleSceneUniformBufferParams, ExampleData, )

USTRUCT(BlueprintType)
struct FExampleDataTableRow : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector3f TestColor1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector3f TestColor2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector3f TestColor3;

public:
	void Encode(TArray<float>& inoutArray) const;
};