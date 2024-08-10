#include "ExampleSceneUniformBuffer.h"
#include "RenderGraphResources.h"
#include "RenderGraphBuilder.h"

static void GetDefaultResourceParameters_ExampleUB(FExampleSceneUniformBufferParams& ShaderParams, FRDGBuilder& GraphBuilder)
{
	ShaderParams.TestColor = FVector3f(0.0f, 0.0f, 1.0f);
	ShaderParams.TestBuffer = GraphBuilder.CreateSRV( GraphBuilder.CreateBuffer(FRDGBufferDesc::CreateStructuredDesc(sizeof(float), 1), TEXT("DummyExampleBuffer")));
}

IMPLEMENT_SCENE_UB_STRUCT(FExampleSceneUniformBufferParams, ExampleData, GetDefaultResourceParameters_ExampleUB);

void FExampleDataTableRow::Encode(TArray<float>& inoutArray) const
{
	inoutArray.Add(TestColor1.X);
	inoutArray.Add(TestColor1.Y);
	inoutArray.Add(TestColor1.Z);
	inoutArray.Add(TestColor2.X);
	inoutArray.Add(TestColor2.Y);
	inoutArray.Add(TestColor2.Z);
	inoutArray.Add(TestColor3.X);
	inoutArray.Add(TestColor3.Y);
	inoutArray.Add(TestColor3.Z);
}