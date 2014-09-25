// Copyright 2013 Gneu, LLC. All Rights Reserved.

#include "Atlas.h"

#pragma once

class ATLAS_API Atlas_impl : public Atlas
{
public:
	virtual void StartupModule() ;
	virtual void ShutdownModule() ;

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

IMPLEMENT_MODULE(Atlas_impl, Atlas)

