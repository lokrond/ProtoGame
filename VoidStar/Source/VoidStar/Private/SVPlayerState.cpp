// Fill out your copyright notice in the Description page of Project Settings.


#include "SVPlayerState.h"

void ASVPlayerState::AddCreditScore(int32 Delta)
{
	if(!ensure(Delta > 0.f))
	{
		return;
	}

	CreditScore += Delta;

	OnCreditsChanged.Broadcast(this, CreditScore, Delta);
}

bool ASVPlayerState::SubtractCreditScore(int32 Delta)
{

	if (!ensure(Delta > 0))
	{
		return false;
	}

	if (CreditScore < Delta)
	{
		return false;
	}

	CreditScore -= Delta;

	OnCreditsChanged.Broadcast(this, CreditScore, -Delta);

	return true;
}
