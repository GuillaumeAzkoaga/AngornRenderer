/*#include "Application.h"


//TODO: why are we not outputting to error log anymore??(check git history)
//TODO: Have a default shader in case one couldn't be loaded or compiled
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR, int show)
{
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	Application::getInstance()->RunApplication(instance, show, 1280, 720, "AngornRenderer");

	return 0;
}

*/

#define _CRT_SECURE_NO_WARNINGS

#include <array>
#include <cassert>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "Discord/discord.h"

#if defined(_WIN32)
#pragma pack(push, 1)
struct BitmapImageHeader {
    uint32_t const structSize{ sizeof(BitmapImageHeader) };
    int32_t width{ 0 };
    int32_t height{ 0 };
    uint16_t const planes{ 1 };
    uint16_t const bpp{ 32 };
    uint32_t const pad0{ 0 };
    uint32_t const pad1{ 0 };
    uint32_t const hres{ 2835 };
    uint32_t const vres{ 2835 };
    uint32_t const pad4{ 0 };
    uint32_t const pad5{ 0 };

    BitmapImageHeader& operator=(BitmapImageHeader const&) = delete;
};

struct BitmapFileHeader {
    uint8_t const magic0{ 'B' };
    uint8_t const magic1{ 'M' };
    uint32_t size{ 0 };
    uint32_t const pad{ 0 };
    uint32_t const offset{ sizeof(BitmapFileHeader) + sizeof(BitmapImageHeader) };

    BitmapFileHeader& operator=(BitmapFileHeader const&) = delete;
};
#pragma pack(pop)
#endif

struct DiscordState {
    discord::User currentUser;

    std::unique_ptr<discord::Core> core;
};

namespace {
    volatile bool interrupted{ false };
}

int main(int, char**)
{
    DiscordState state{};

    discord::Core* core{};
    auto result = discord::Core::Create(708010784780976219, DiscordCreateFlags_Default, &core);
    state.core.reset(core);
    if (!state.core) {
        std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(result)
            << ")\n";
        std::exit(-1);
    }

    state.core->SetLogHook(
        discord::LogLevel::Debug, [](discord::LogLevel level, const char* message) {
            std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n";
        });

    core->UserManager().OnCurrentUserUpdate.Connect([&state]() {
        state.core->UserManager().GetCurrentUser(&state.currentUser);

        std::cout << "Current user updated: " << state.currentUser.GetUsername() << "#"
            << state.currentUser.GetDiscriminator() << "\n";

        state.core->UserManager().GetUser(130050050968518656,
            [](discord::Result result, discord::User const& user) {
                if (result == discord::Result::Ok) {
                    std::cout << "Get " << user.GetUsername() << "\n";
                }
                else {
                    std::cout << "Failed to get David!\n";
                }
            });

        discord::ImageHandle handle{};
        handle.SetId(state.currentUser.GetId());
        handle.SetType(discord::ImageType::User);
        handle.SetSize(256);

        state.core->ImageManager().Fetch(
            handle, true, [&state](discord::Result res, discord::ImageHandle handle) {
                if (res == discord::Result::Ok) {
                    discord::ImageDimensions dims{};
                    state.core->ImageManager().GetDimensions(handle, &dims);
                    std::cout << "Fetched " << dims.GetWidth() << "x" << dims.GetHeight()
                        << " avatar!\n";

                    std::vector<uint8_t> data;
                    data.reserve(dims.GetWidth() * dims.GetHeight() * 4);
                    uint8_t* d = data.data();
                    state.core->ImageManager().GetData(handle, d, data.size());

                }
                else {
                    std::cout << "Failed fetching avatar. (err " << static_cast<int>(res) << ")\n";
                }
            });
        });

    state.core->ActivityManager().RegisterCommand("run/command/foo/bar/baz/here.exe");
    state.core->ActivityManager().RegisterSteam(123123321);

    discord::Activity activity{};
    activity.SetDetails("Testing Discord SDK");
    activity.SetState("It works!");
    activity.GetAssets().SetSmallImage("the");
    activity.GetAssets().SetSmallText("i mage");
    activity.GetAssets().SetLargeImage("the");
    activity.GetAssets().SetLargeText("u mage");
    activity.SetType(discord::ActivityType::Playing);
    state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " updating activity!\n";
        });

    do {
        state.core->RunCallbacks();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    } while (!interrupted);

    return 0;
}
