// Fill out your copyright notice in the Description page of Project Settings.


#include "PpfTimeEnum.h"


ETimeMode TimeMode::GetNextState(const ETimeMode Current, const ETimeMode Applied)
{
	if (Current == Applied) {
		return ETimeMode::Present;
	}

	return Applied;
}
