// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class NETTPS_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Begin Play
	virtual void NativeConstruct() override;
	
	// Game Instance
	UPROPERTY()
	class UNetGameInstance* gi;
	// WigetSwitcher
	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* widgetSwitcher;

	// 메인 화면 관련
	// 세션 생성 화면 이동 버튼
	UPROPERTY(meta=(BindWidget))
	class UButton* btnGoCreate;
	// 세션 조회 화면 이동 버튼
	UPROPERTY(meta=(BindWidget))
	class UButton* btnGoFind;
	// 세션 생성 화면 이동 함수
	UFUNCTION()
	void OnClickGoCreate();
	// 세션 조회 화면 이동 함수
	UFUNCTION()
	void OnClickGoFind();

	// 세션 생성 화면 관련
	// 세션 이름 입력
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* editSessionName;
	// 인원수 Slider
	UPROPERTY(meta=(BindWidget))
	class USlider* sliderPlayerCount;
	// 인원수 Text
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* textPlayerCount;
	// 생성 버튼
	UPROPERTY(meta=(BindWidget))
	class UButton* btnCreate;
	// 생성 버튼 눌렀을 때 호출되는 함수
	UFUNCTION()
	void OnClickCreate();
	// 세션 이름 변경 될 때 호출되는 함수
	UFUNCTION()
	void OnValueChangedSessionName(const FText& text);
	// 인원수 Slider 값이 변경 될 때 호출되는 함수
	UFUNCTION()
	void OnValueChangedPlayerCount(float value);

	// 세션 조회 관련
	// 세션 목록
	UPROPERTY(meta=(BindWidget))
	class UScrollBox* scrollSessionList;
	// 조회 버튼
	UPROPERTY(meta=(BindWidget))
	class UButton* btnFind;
	// 죄회 버튼 문구
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* textFind;
	// SessionInfoWidget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class USessionInfoWidget> sessionInfoWidget;
	// 조회 버튼 클릭시 호출되는 함수
	UFUNCTION()
	void OnClickFind();
	// 세션 정보를 받아 SessionInfoWidget 을 만드는 함수
	// (NetGameInstance 의 onFindComplete 딜리게이트에 등록할 함수)
	UFUNCTION()
	void OnFindComplete(int32 idx, FString sessionName);


	// 뒤로 가기 버튼
	UPROPERTY(meta=(BindWidget))
	class UButton* btnBackFromCreate;
	UPROPERTY(meta=(BindWidget))
	class UButton* btnBackFromFind;
	// 뒤로 가기 눌렀을 때 호출되는 함수
	UFUNCTION()
	void OnClickBack();

	UPROPERTY(meta=(BindWidget))
	class UMyButton* button_01;
	UPROPERTY(meta=(BindWidget))
	class UMyButton* button_02;
	UFUNCTION()
	void OnClick(int32 idx);
};
