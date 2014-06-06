// Copyright 2013 Gneu, LLC. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

/**
* The public interface to this module. 
*/
class Atlas : public IModuleInterface
{

public:

	static inline Atlas& Get()
	{
		return FModuleManager::LoadModuleChecked<Atlas>("Atlas");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Atlas");
	}

	virtual void SetApplicationID(FString id) = 0; 
	virtual void SetServer(FString uri) = 0;
	virtual void IsInternal(bool val) = 0;
	virtual void ShouldForceQuitOnFailure(bool val) = 0;

	virtual bool CheckAccess(FString userid) = 0;
};
