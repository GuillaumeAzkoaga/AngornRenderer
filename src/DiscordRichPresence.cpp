#include "DiscordRichPresence.h"
#include "Discord/discord.h"

#include <iostream>
#include <Windows.h>
DiscordRichPresence* DiscordRichPresence::instance_ = 0;


void DiscordRichPresence::Initialize()
{	  
    discord::Core* core{};
    auto result = discord::Core::Create(applicationId_, DiscordCreateFlags_Default, &core);
    discordState_.core.reset(core);
    if (!discordState_.core) {
        std::string message = "Failed to instantiate discord core! (error: " +  std::to_string((static_cast<int>(result)));
        MessageBox(NULL, message.c_str(), "Discord plugin error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);       
    }
    else
    {
        UpdateActivity("In Visual Studio 2019", "Coding...", discord::ActivityType::Playing);
    }
    
}

void DiscordRichPresence::Update(float dt)
{
    discordState_.core->RunCallbacks();
}

void DiscordRichPresence::Shutdown()
{
}

void DiscordRichPresence::UpdateActivity(const char* details, const char* state, discord::ActivityType type)
{   
    discordState_.activity.SetDetails(details);
    discordState_.activity.SetState(state);
    discordState_.activity.SetType(type);
    discordState_.core->ActivityManager().UpdateActivity(discordState_.activity, [](discord::Result result) 
        {
            if(result != discord::Result::Ok)
                MessageBox(NULL, "Failed to update DiscordActivity", "Discord plugin error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONWARNING);
        });
}

