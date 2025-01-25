// Fill out your copyright notice in the Description page of Project Settings.


#include "PpfTimeEnum.h"

EPpfTime::EType EPpfTime::GetNextState(const EType Current, const EType Applied)
{
	if (Current == Applied) {
		return EType::Present;
	}

	return Applied;
}
