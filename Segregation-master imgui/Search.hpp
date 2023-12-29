#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
//#include <imgui.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"


namespace Configuration {
    namespace Aimbot {
        extern bool aimbotEnabled;
        extern bool silentAim;
        extern bool autoFire;
        extern bool noRecoil;
        extern int aimBone;
        extern bool autoAim;
    }
    namespace Others {
        extern bool Interpolation;
        extern bool Animations,asus;
        extern bool autoFire;
        extern bool noRecoil;
        extern int aimBone;
        extern bool autoAim;
    }
    namespace Visuals {
        namespace Player {
            extern bool Box;
            extern bool Name;
            extern bool Health;
        }
        namespace View {
            extern float fieldOfView;
        }

    }
    namespace Misc {
        namespace Movement {
            extern bool autoBunnyhop;
            extern bool autoStrafe;
        }
        namespace Chams {
            extern bool Player;
            extern float Arms;
            extern bool Hands;
            extern float Outline;
        }
    }
}
class searchfunc {
private:
    void initialize() {
        {
          
            AddCheckbox("hp bar", &Configuration::Visuals::Player::Health,"esp");
            AddCheckbox("box", &Configuration::Visuals::Player::Box, "esp");
        }
    }

public:
    bool find = false;
    void Init() {
        initialize();
    }

    void AddCheckbox(const std::string& label, bool* value_ptr, const std::string& category) {
        checkbox_.push_back(std::make_tuple(label, value_ptr, category));
    }

    void AddSliderInt(const std::string& label, int* value_ptr, int min_value, int max_value, const std::string& format, const std::string& category) {
        slider_int_.push_back(std::make_tuple(label, value_ptr, min_value, max_value, format, category));
    }

    void AddSliderFloat(const std::string& label, float* value_ptr, float min_value, float max_value, const std::string& format, const std::string& category) {
        slider_float_.push_back(std::make_tuple(label, value_ptr, min_value, max_value, format, category));
    }

    void AddCombo(const std::string& label, int* current_item, const char* const items[], int items_count, const std::string& category) {
        combo_.push_back(std::make_tuple(label, current_item, items, items_count, category));
    }

    

    bool findquery(const std::string& query, const std::string& str) {
        return std::search(str.begin(), str.end(), query.begin(), query.end(),
            [](char lhs, char rhs) { return std::toupper(lhs) == std::toupper(rhs); }) != str.end();
    }

    void drawqueryresults(const std::string& query) {

        for (const auto& checkbox_args : checkbox_) {
            if (findquery(query, std::get<0>(checkbox_args))) {
              
                ImGui::Checkbox(std::get<0>(checkbox_args).c_str(), std::get<1>(checkbox_args));
            }
        }

        for (const auto& slider_int_args : slider_int_) {
            if (findquery(query, std::get<0>(slider_int_args))) {
              
                ImGui::SliderInt(std::get<0>(slider_int_args).c_str(), std::get<1>(slider_int_args), std::get<2>(slider_int_args), std::get<3>(slider_int_args), std::get<4>(slider_int_args).c_str());
            }
        }

        for (const auto& slider_float_args : slider_float_) {
            if (findquery(query, std::get<0>(slider_float_args))) {
              
                ImGui::SliderFloat(std::get<0>(slider_float_args).c_str(), std::get<1>(slider_float_args), std::get<2>(slider_float_args), std::get<3>(slider_float_args), std::get<4>(slider_float_args).c_str());

            }
        }

        for (const auto& combo_args : combo_) {
            if (findquery(query, std::get<0>(combo_args))) {
             
                ImGui::Combo(std::get<0>(combo_args).c_str(), std::get<1>(combo_args), std::get<2>(combo_args), std::get<3>(combo_args));
            
            }
        }

        

        
    }

private:
    std::vector<std::tuple<std::string, bool*, std::string>> checkbox_;
    std::vector<std::tuple<std::string, int*, int, int, std::string, std::string>> slider_int_;
    std::vector<std::tuple<std::string, float*, float, float, std::string, std::string>> slider_float_;
    std::vector<std::tuple<std::string, int*, const char* const*, int, std::string>> combo_;


};

extern searchfunc g_Search;
searchfunc g_Search;