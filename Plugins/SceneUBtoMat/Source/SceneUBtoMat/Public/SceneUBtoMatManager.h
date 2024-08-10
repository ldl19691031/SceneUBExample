#pragma once
#include "Subsystems/EngineSubsystem.h"
#include "SceneUBtoMatManager.generated.h"

UCLASS()
class USceneUBtoMatManager : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	//Begin UEngineSubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//End UEngineSubsystem Interface
protected:
	TSharedPtr<class FSceneUBtoMatSceneViewExtension, ESPMode::ThreadSafe> ViewExtension;
};