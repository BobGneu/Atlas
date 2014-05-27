// Copyright 2013 Gneu, LLC. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

/**
* The public interface to this module. 
*/
class IAtlas : public IModuleInterface
{

public:

	static inline IAtlas& Get()
	{
		return FModuleManager::LoadModuleChecked<IAtlas>("Atlas");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Atlas");
	}

	virtual void SetApplicationID(FString id) = 0; 
	virtual void SetServer(FString uri) = 0;

	virtual void IsInternal(bool val) = 0;

	virtual void AllowEditor(bool val) = 0;
	virtual void AllowGame(bool val) = 0;

	virtual bool CheckAccess() = 0;
};
