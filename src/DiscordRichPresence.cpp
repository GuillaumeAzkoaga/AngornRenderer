#include "DiscordRichPresence.h"
#include "Discord/discord.h"
/*
discord::Core* core{};

DiscordRichPresence* DiscordRichPresence::instance_ = 0;

void DiscordRichPresence::Initialize()
{	
	discord::Core::Create(708010784780976219, DiscordCreateFlags_Default, &core);
	discord::Activity activity{};
	activity.SetState("Testing");
	activity.SetDetails("Implementing Discord SDK");
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {

		});
}

void DiscordRichPresence::Update(float dt)
{
	//::core->RunCallbacks();
}

void DiscordRichPresence::Shutdown()
{
}
*/