// Copyright 2013 Gneu, LLC. All Rights Reserved.

#include "HttpModule.h"
#include "Http.h"
#include "IAtlas.h"

#pragma once

class MAtlas : public IAtlas
{

public:
	
	/** IModuleInterface implementation */
	virtual void StartupModule() OVERRIDE;
	virtual void ShutdownModule() OVERRIDE;

	void SetApplicationID(FString id);

	void IsInternal(bool val);

	void SetServer(FString uri);
	bool CheckAccess(FString userid);
	void RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void ShouldForceQuitOnFailure(bool val);

protected:
	FString ServerURI;
	FString AppID;

	bool bInternal;

	bool bAllowEditor;
	bool bAllowGame;
	bool bForceQuit;
};

IMPLEMENT_MODULE(MAtlas, Atlas)

