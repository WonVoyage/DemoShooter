#pragma once

//-------------------------------------------------------------------------------------------------------------
class AnimUtils
{
public:
	template <typename T> static T *Find_Notify_By_Class(UAnimSequenceBase *animation)
	{
		const auto notify_events = animation->Notifies;

		for (auto notify_event : notify_events)
		{
			auto anim_notify = Cast<T>(notify_event.Notify);

			if (anim_notify)
			{
				return anim_notify;
			}
		}

		return nullptr;

	}
};
//-------------------------------------------------------------------------------------------------------------
