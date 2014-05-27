// Copyright 2013 Gneu, LLC. All Rights Reserved.

#include "AtlasPCH.h"
#include "Atlas.h"

void MAtlas::StartupModule()
{
}

void MAtlas::ShutdownModule()
{
}

void MAtlas::IsInternal(bool val)
{
	bInternal = val;
}

void MAtlas::AllowEditor(bool val)
{
	bAllowEditor = val;
}

void MAtlas::AllowGame(bool val)
{
	bAllowGame = val;
}

void MAtlas::SetServer(FString uri)
{
	ServerURI = uri;
}

bool MAtlas::CheckAccess()
{
	// Find UserID
	// Query Server
	// Test game state & fail out if tests are appropriate.
	return false;
}
