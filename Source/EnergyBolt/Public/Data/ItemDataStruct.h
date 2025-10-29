// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"


class AEnergyEffectActor;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 아이템 ID
	FName ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 아이템 이름
	FText ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 설명
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 아이콘
	UTexture2D* Icon = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 실제 스폰될 블루프린트 클래스
	TSoftClassPtr<AEnergyEffectActor> ItemClass = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 가격이나 희귀도 같은 추가 필드
	int32 Value = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// 드랍 확률 (0~1)
	float DropChance = 1.0f;
	
};
