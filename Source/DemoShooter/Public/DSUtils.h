#pragma once

class DSUtils
{
public:
	template <typename T> static T *Get_Component_PlayerPawn(AActor *pawn)
	{
		const auto component = pawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(component);
	}
};