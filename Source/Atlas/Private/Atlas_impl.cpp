// Copyright 2013 Gneu, LLC. All Rights Reserved.

#include "AtlasPCH.h"
#include "Atlas_impl.h"  

DEFINE_LOG_CATEGORY(AtLog);

void Atlas_impl::StartupModule()
{
}

void Atlas_impl::ShutdownModule()
{
}

void Atlas_impl::IsInternal(bool val)
{
	bInternal = val;
}

void Atlas_impl::SetServer(FString uri)
{
	ServerURI = uri;
}

void Atlas_impl::SetApplicationID(FString id)
{
	AppID = id;
}

bool Atlas_impl::CheckAccess(FString userid)
{
	FString requestURL = ServerURI + "/auth/";

	// Query Server
	// http://localhost:3000/auth/exodus/true/test

	TSharedRef<class IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &Atlas_impl::RequestComplete);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetURL(requestURL + AppID + "/" + (bInternal ? "true": "false") + "/" + userid);

	return HttpRequest->ProcessRequest();
}

void Atlas_impl::RequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpResponse.IsValid())
	{
		if (bForceQuit)
		{
			FPlatformMisc::RequestExit(true);
		}

		return;
	}

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

	if (bForceQuit)
	{
		if (GIsEditor && !allowEditor)
		{
			FPlatformMisc::RequestExit(true);
		}
		else if (!GIsEditor && !allowGame)
		{
			FPlatformMisc::RequestExit(true);
		}
	}
}

void Atlas_impl::ShouldForceQuitOnFailure(bool val)
{
	bForceQuit = val;
}
