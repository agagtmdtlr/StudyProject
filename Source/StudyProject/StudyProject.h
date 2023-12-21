// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(StudyProject, Log, All);
//#define STLOG_CALLINFO (FString(__FILE__) + TEXT(" : ") + FString(__FUNCTION__) + TEXT("(Line:") + FString::FromInt(__LINE__) + TEXT(")"))
#define STLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(Line:") + FString::FromInt(__LINE__) + TEXT(")"))
#define STLOG_S(Verbosity) UE_LOG(StudyProject, Verbosity, TEXT("%s"), *STLOG_CALLINFO);
#define ST_LOG(Verbosity, Format, ...) UE_LOG(StudyProject, Verbosity, TEXT("%s %s"),*FString::Printf(Format, ##__VA_ARGS__), *STLOG_CALLINFO)

#define STCHECK(Expr,...) { if(!(Expr)){ ST_LOG(Error, TEXT("ASSERTION : %S") , TEXT("'"#Expr"'")); return __VA_ARGS__;}}