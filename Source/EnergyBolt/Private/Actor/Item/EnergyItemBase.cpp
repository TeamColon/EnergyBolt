// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/EnergyItemBase.h"

#include "Component/ShopItemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"


AEnergyItemBase::AEnergyItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 유연하게 만들기 위해 Scene 사용 (Sphere, mesh, box, capsule 등등은 자손에서 설정하기 )
	// Scene component는 Transform을 가지는 "기본 루트 타입"이다.
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	ShopItemComponent = CreateDefaultSubobject<UShopItemComponent>(TEXT("ShopItemComponent"));

	/*PriceText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PriceText"));
	PriceText->SetupAttachment(RootComponent);
	PriceText->SetHorizontalAlignment(EHTA_Center);
	PriceText->SetVerticalAlignment(EVRTA_TextCenter);
	PriceText->SetWorldSize(45.f);
	PriceText->SetTextRenderColor(FColor::White);
	PriceText->SetRelativeLocation(FVector(0.f, 0.f, 150.f));*/
}

void AEnergyItemBase::BeginPlay()
{
	Super::BeginPlay();

	/*if (ShopItemComponent && ShopItemComponent->bIsShopItem)
	{
		PriceText->SetText(FText::AsNumber(ShopItemComponent->Cost));
		PriceText->SetVisibility(true);
	}
	else
	{
		PriceText->SetVisibility(false);
	}*/
}

