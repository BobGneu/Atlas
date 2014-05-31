// Copyright 2013 Gneu, LLC. All Rights Reserved.

#include "AtlasPCH.h"
#include "Atlas.h"  
#include "Json.h"

DEFINE_LOG_CATEGORY(Atlas);

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

void MAtlas::SetServer(FString uri)
{
	ServerURI = uri;
}

void MAtlas::SetApplicationID(FString id)
{
	AppID = id;
}

bool MAtlas::CheckAccess(FString userid)
{
	FString requestURL = ServerURI + "/tracking/auth/";

	// Query Server
	// http://localhost:3000/tracking/auth/exodus/true/test

	TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &MAtlas::RequestComplete);
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetURL(requestURL + AppID + "/" + (bInternal ? "true": "false") + "/" + userid);

	UE_LOG(Atlas, Log, TEXT("%s"), *HttpRequest->GetURL());

	return HttpRequest->ProcessRequest();
}

void MAtlas::RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	UE_LOG(Atlas, Log, TEXT("%s"), bSucceeded ? TEXT("SUCCEEDED") : TEXT("FAILED"));

	UE_LOG(Atlas, Log, TEXT("%s"), *HttpRequest->GetURL());

	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());

	TSharedPtr<FJsonObject> Object;
	check(FJsonSerializer::Deserialize(Reader, Object));
	check(Object.IsValid());

	const TSharedPtr<FJsonValue>* Value = Object->Values.Find(TEXT("allowGame"));
	check(Value && (*Value)->Type == EJson::Boolean);
	const bool allowGame = (*Value)->AsBool();

	Value = Object->Values.Find(TEXT("allowEditor"));
	check(Value && (*Value)->Type == EJson::Boolean);
	const bool allowEditor = (*Value)->AsBool();

	if (bForceQuit && (!(GIsEditor && allowEditor) || !(!GIsEditor && allowGame)))
	{
		FPlatformMisc::RequestExit(true);
	}
}

void MAtlas::ShouldForceQuitOnFailure(bool val)
{
	bForceQuit = val;
}
