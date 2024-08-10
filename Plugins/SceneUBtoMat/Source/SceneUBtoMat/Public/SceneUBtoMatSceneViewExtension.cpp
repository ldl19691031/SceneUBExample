#include "SceneUBtoMatSceneViewExtension.h"
#include "ExampleSceneUniformBuffer.h"
#include "SceneRendererInterface.h"
#include "Engine/DataTable.h"
#include "RenderGraphResources.h"
#include "RenderGraphBuilder.h"

FSceneUBtoMatSceneViewExtension::FSceneUBtoMatSceneViewExtension(const FAutoRegister& AutoRegister)
	: FSceneViewExtensionBase(AutoRegister)
{
}

FSceneUBtoMatSceneViewExtension::~FSceneUBtoMatSceneViewExtension()
{
}

void FSceneUBtoMatSceneViewExtension::PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
}

static FSoftObjectPath DataTablePath(TEXT("/Script/Engine.DataTable'/Game/DT_Example.DT_Example'"));

static TArray<float> LoadDataTable() {
	TSoftObjectPtr<UDataTable> DataTablePtr(DataTablePath);
	TArray<float> result;
	if (UDataTable* dt = DataTablePtr.LoadSynchronous())
	{
		for (auto& row : dt->GetRowMap())
		{
			FName rowName = row.Key;
			FExampleDataTableRow* rowData = (FExampleDataTableRow*)row.Value;
			rowData->Encode(result);
		}
	}
	return result;
}

void FSceneUBtoMatSceneViewExtension::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	if (DataTableEncoded.Num() == 0)
	{
		DataTableEncoded = LoadDataTable();
	}
}

void FSceneUBtoMatSceneViewExtension::PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily)
{
	static float tempCounter = 0.0f;
	ISceneRenderer* sceneRenderer = InViewFamily.GetSceneRenderer();
	if (sceneRenderer)
	{
		FSceneUniformBuffer& sceneUniformBuffer = sceneRenderer->GetSceneUniforms();
		FExampleSceneUniformBufferParams params;
		params.TestColor = FVector3f(FMath::Fmod(tempCounter, 1.0f), 0.0f, 0.0f);

		FRDGBufferDesc desc = FRDGBufferDesc::CreateStructuredDesc(sizeof(float), DataTableEncoded.Num());
		FRDGBufferRef buffer = GraphBuilder.CreateBuffer(desc, TEXT("ExampleData.TestBuffer"));
		GraphBuilder.QueueBufferUpload(buffer, DataTableEncoded.GetData(), DataTableEncoded.Num() * sizeof(float));
		params.TestBuffer = GraphBuilder.CreateSRV(buffer);

		sceneUniformBuffer.Set(SceneUB::ExampleData, params);
		tempCounter += 0.01f;
	}
}
