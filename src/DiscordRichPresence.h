#ifndef DISCORD_H_
#define DISCORD_H_
#include <Discord/discord.h>
#include "ISystem.h"

#include <string>
#include <thread>

#ifndef DISCORD_ENABLED
#define DISCORD_ENABLED false
#endif

struct DiscordState {
	discord::User currentUser;
	std::unique_ptr<discord::Core> core;

	discord::Activity activity;
};


class DiscordRichPresence : public ISystem
{
public:
	static DiscordRichPresence* getInstance()
	{
		if (!instance_)
			instance_ = new DiscordRichPresence();
		return instance_;
	}

	void Initialize();
	void Update(float dt = 0);
	void Shutdown();

private:
	DiscordRichPresence() {}
	static DiscordRichPresence* instance_;

	void UpdateActivity(const char* details, const char* state, discord::ActivityType type);

	DiscordState discordState_{};
	const DiscordClientId applicationId_ = 708010784780976219;
};

#endif