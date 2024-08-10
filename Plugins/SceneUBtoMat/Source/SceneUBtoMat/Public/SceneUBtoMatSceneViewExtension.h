#pragma once
#include "SceneViewExtension.h"

class FSceneUBtoMatSceneViewExtension : public FSceneViewExtensionBase
{
public:
	FSceneUBtoMatSceneViewExtension(const FAutoRegister& AutoRegister);
	virtual ~FSceneUBtoMatSceneViewExtension();
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {}
	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& RHICmdList, FSceneViewFamily& InViewFamily) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {}
	virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override { return true;  }
private:
	TArray<float> DataTableEncoded;
};