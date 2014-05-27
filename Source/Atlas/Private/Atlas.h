// Copyright 2013 Gneu, LLC. All Rights Reserved.

#include "IAtlas.h"

#pragma once

class MAtlas : public IAtlas
{

public:
	
	/** IModuleInterface implementation */
	virtual void StartupModule() OVERRIDE;
	virtual void ShutdownModule() OVERRIDE;

	void SetApplicationID(FString id)
	{
		AppID = id;
	}

	void IsInternal(bool val);

	void AllowEditor(bool val);
	void AllowGame(bool val);

	void SetServer(FString uri);
	bool CheckAccess();

protected:
	FString ServerURI;
	FString AppID;

	bool bInternal;

	bool bAllowEditor;
	bool bAllowGame;
};

IMPLEMENT_MODULE(MAtlas, Atlas)

