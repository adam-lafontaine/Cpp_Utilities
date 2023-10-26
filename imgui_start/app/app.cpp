#include "app.hpp"
#include "../imgui/imgui.h"

#include <chrono>

namespace
{
    class App_State
    {
    public:

        bool app_running = false;

        bool message_visible = false;
    };


    class UI_Input
    {
    public:

        char user_name[50] = { 0 };
    };


    class UI_Command
    {
    public:

        bool stop_app_running = false;
        bool button_clicked = false;

        bool has_command()
        {
            return false ||
                stop_app_running ||
                button_clicked;
        }
    };
}


namespace ui
{
    constexpr auto WHITE = ImVec4(1, 1, 1, 1);
	constexpr auto GREEN = ImVec4(0, 1, 0, 1);
	constexpr auto RED = ImVec4(1, 0, 0, 1);

	using ImColor = ImVec4;


    static int letters_only(ImGuiInputTextCallbackData* data)
    {
        constexpr int OK = 0;
        constexpr int NOT_OK = 1;

        auto c = data->EventChar;

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '\0')
        {
            return OK;
        }

        return NOT_OK;
    }


    static void show_window(App_State const& state, UI_Command& cmd, UI_Input& input)
    {
        ImGui::Begin("Window");

        ImGui::SetNextItemWidth(150);
		ImGui::InputText("Enter your name", input.user_name, sizeof(input.user_name), ImGuiInputTextFlags_CallbackCharFilter, letters_only);

        if (ImGui::Button("Toggle message", ImVec2(120, 30)))
        {
            cmd.button_clicked = true;
        }

        if (state.message_visible)
        {
            ImGui::TextColored(GREEN, "Hello %s", input.user_name);
        }

        ImGui::SetCursorPosY(150);
        if (ImGui::Button("End program", ImVec2(120, 30)))
        {
            cmd.stop_app_running = true;
        }

        ImGui::End();
    }
}


static void process_command(UI_Command const& cmd, App_State& state)
{
    if (cmd.stop_app_running)
    {
        state.app_running = false;
    }
    else if (cmd.button_clicked)
    {
        state.message_visible = !state.message_visible;
    }
}


static App_State g_app_state;
static UI_Input g_user_input;


static void start_app()
{
    // startup background work

    while (g_app_state.app_running)
    {
        // run while app is running
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}


namespace app
{
    void init()
    {
        
    }


	void shutdown()
    {
        g_app_state.app_running = false;
    }


	std::thread start_worker()
    {
        g_app_state.app_running = true;

        auto worker = std::thread(start_app);

		return worker;
    }


	bool render_ui()
    {
        constexpr bool END_PROGRAM = false;
        constexpr bool CONTINUE_PROGRAM = true;

        auto& state = g_app_state;
		auto& input = g_user_input;

        UI_Command cmd{};

        ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_None);

        ui::show_window(state, cmd, input);

        if (cmd.has_command())
		{
			if (cmd.stop_app_running)
			{
				return END_PROGRAM;
			}

			process_command(cmd, state);
		}
        
        return CONTINUE_PROGRAM;
    }
}