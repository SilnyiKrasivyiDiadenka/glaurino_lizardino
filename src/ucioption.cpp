/*
  Glaurung, a UCI chess playing engine.
  Copyright (C) 2004-2008 Tord Romstad

  Glaurung is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  Glaurung is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////
//// Includes
////

#include "ucioption.h"
#include "misc.h"
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace Glaurung {

////
//// Variables
////

bool Chess960 = false;

////
//// Local definitions
////

namespace {

///
/// Types
///

enum class OptionType : int { SPIN, COMBO, CHECK, STRING, BUTTON };

struct Option
{
    std::string name;
    std::string defaultValue;
    std::string currentValue;
    OptionType type;
    int minValue, maxValue;
    std::vector<std::string> comboValues;
};

///
/// Variables
///

std::vector<Option> Options
    = {{"Use Search Log", "false", "false", OptionType::CHECK, 0, 0, {""}},
       {"Search Log Filename", "SearchLog.txt", "SearchLog.txt", OptionType::STRING, 0, 0, {""}},
       {"Book File", "book.bin", "book.bin", OptionType::STRING, 0, 0, {""}},
       {"Mobility (Middle Game)", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Mobility (Endgame)", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Pawn Structure (Middle Game)", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Pawn Structure (Endgame)", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Passed Pawns (Middle Game)", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Passed Pawns (Endgame)", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Space", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Aggressiveness", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"Cowardice", "100", "100", OptionType::SPIN, 0, 200, {""}},
       {"King Safety Curve",
        "Quadratic",
        "Quadratic",
        OptionType::COMBO,
        0,
        0,
        {"Quadratic", "Linear" /*, "From File"*/}},
       {"King Safety Coefficient", "40", "40", OptionType::SPIN, 1, 100, {""}},
       {"King Safety X Intercept", "0", "0", OptionType::SPIN, 0, 20, {""}},
       {"King Safety Max Slope", "30", "30", OptionType::SPIN, 10, 100, {""}},
       {"King Safety Max Value", "500", "500", OptionType::SPIN, 100, 1000, {""}},
       {"Queen Contact Check Bonus", "3", "3", OptionType::SPIN, 0, 8, {""}},
       {"Queen Check Bonus", "2", "2", OptionType::SPIN, 0, 4, {""}},
       {"Rook Check Bonus", "1", "1", OptionType::SPIN, 0, 4, {""}},
       {"Bishop Check Bonus", "1", "1", OptionType::SPIN, 0, 4, {""}},
       {"Knight Check Bonus", "1", "1", OptionType::SPIN, 0, 4, {""}},
       {"Discovered Check Bonus", "3", "3", OptionType::SPIN, 0, 8, {""}},
       {"Mate Threat Bonus", "3", "3", OptionType::SPIN, 0, 8, {""}},
       {"Check Extension (PV nodes)", "2", "2", OptionType::SPIN, 0, 2, {""}},
       {"Check Extension (non-PV nodes)", "1", "1", OptionType::SPIN, 0, 2, {""}},
       {"Single Reply Extension (PV nodes)", "2", "2", OptionType::SPIN, 0, 2, {""}},
       {"Single Reply Extension (non-PV nodes)", "2", "2", OptionType::SPIN, 0, 2, {""}},
       {"Mate Threat Extension (PV nodes)", "0", "0", OptionType::SPIN, 0, 2, {""}},
       {"Mate Threat Extension (non-PV nodes)", "0", "0", OptionType::SPIN, 0, 2, {""}},
       {"Pawn Push to 7th Extension (PV nodes)", "1", "1", OptionType::SPIN, 0, 2, {""}},
       {"Pawn Push to 7th Extension (non-PV nodes)", "1", "1", OptionType::SPIN, 0, 2, {""}},
       {"Passed Pawn Extension (PV nodes)", "1", "1", OptionType::SPIN, 0, 2, {""}},
       {"Passed Pawn Extension (non-PV nodes)", "0", "0", OptionType::SPIN, 0, 2, {""}},
       {"Pawn Endgame Extension (PV nodes)", "2", "2", OptionType::SPIN, 0, 2, {""}},
       {"Pawn Endgame Extension (non-PV nodes)", "2", "2", OptionType::SPIN, 0, 2, {""}},
       {"Full Depth Moves (PV nodes)", "14", "14", OptionType::SPIN, 1, 100, {""}},
       {"Full Depth Moves (non-PV nodes)", "3", "3", OptionType::SPIN, 1, 100, {""}},
       {"Threat Depth", "5", "5", OptionType::SPIN, 0, 100, {""}},
       {"Selective Plies", "7", "7", OptionType::SPIN, 0, 10, {""}},
       {"Futility Pruning (Main Search)", "true", "true", OptionType::CHECK, 0, 0, {""}},
       {"Futility Pruning (Quiescence Search)", "true", "true", OptionType::CHECK, 0, 0, {""}},
       {"Futility Margin 0", "50", "50", OptionType::SPIN, 0, 1000, {""}},
       {"Futility Margin 1", "100", "100", OptionType::SPIN, 0, 1000, {""}},
       {"Futility Margin 2", "200", "200", OptionType::SPIN, 0, 1000, {""}},
       {"Maximum Razoring Depth", "3", "3", OptionType::SPIN, 0, 4, {""}},
       {"Razoring Margin", "300", "300", OptionType::SPIN, 150, 600, {""}},
       {"Randomness", "0", "0", OptionType::SPIN, 0, 10, {""}},
       {"Minimum Split Depth", "4", "4", OptionType::SPIN, 4, 7, {""}},
       {"Maximum Number of Threads per Split Point", "5", "5", OptionType::SPIN, 4, 8, {""}},
       {"Threads", "1", "1", OptionType::SPIN, 1, 8, {""}},
       {"Hash", "32", "32", OptionType::SPIN, 4, 4096, {""}},
       {"Clear Hash", "false", "false", OptionType::BUTTON, 0, 0, {""}},
       {"Ponder", "true", "true", OptionType::CHECK, 0, 0, {""}},
       {"OwnBook", "true", "true", OptionType::CHECK, 0, 0, {""}},
       {"MultiPV", "1", "1", OptionType::SPIN, 1, 500, {""}},
       {"UCI_ShowCurrLine", "false", "false", OptionType::CHECK, 0, 0, {""}},
       {"UCI_Chess960", "false", "false", OptionType::CHECK, 0, 0, {""}}};

///
/// Functions
///

Option *option_with_name(const std::string &optionName);

} // namespace

////
//// Functions
////

/// init_uci_options() initializes the UCI options.  Currently, the only
/// thing this function does is to initialize the default value of the
/// "Threads" parameter to the number of available CPU cores.

void init_uci_options()
{
    auto o = option_with_name("Threads");
    assert(o != nullptr);

    // Limit the default value of "Threads" to 7 even if we have 8 CPU cores.
    // According to Ken Dail's tests, Glaurung plays much better with 7 than
    // with 8 threads.  This is weird, but it is probably difficult to find out
    // why before I have a 8-core computer to experiment with myself.
    o->defaultValue = std::to_string(std::min(cpu_count(), 7));
    set_option_value("Threads", std::to_string(std::min(cpu_count(), 7)));

    // Increase the minimum split depth when the number of CPUs is big.
    // It would probably be better to let this depend on the number of threads
    // instead.
    o = option_with_name("Minimum Split Depth");
    assert(o != nullptr);
    if (cpu_count() > 4) {
        const int newVal = 6;
        o->defaultValue = std::to_string(newVal);
        set_option_value("Minimum Split Depth", std::to_string(newVal));
    }
}

/// print_uci_options() prints all the UCI options to the standard output,
/// in the format defined by the UCI protocol.

void print_uci_options()
{
    const std::map<OptionType, std::string> optionTypeName = {{OptionType::SPIN, "spin"},
                                                              {OptionType::COMBO, "combo"},
                                                              {OptionType::CHECK, "check"},
                                                              {OptionType::STRING, "string"},
                                                              {OptionType::BUTTON, "button"}};

    for (const auto &o : Options) {
        std::cout << "option name " << o.name << " type " << optionTypeName.at(o.type);
        if (o.type != OptionType::BUTTON) {
            std::cout << " default " << o.defaultValue;
            if (o.type == OptionType::SPIN) {
                std::cout << " min " << o.minValue << " max " << o.maxValue;
            } else if (o.type == OptionType::COMBO) {
                for (const auto &comboVal : o.comboValues) {
                    if (!comboVal.empty()) {
                        std::cout << " var " << comboVal;
                    }
                }
            }
        }
        std::cout << std::endl;
    }
}

/// get_option_value_bool() returns the current value of a UCI parameter of
/// type "check".

bool get_option_value_bool(const std::string &optionName)
{
    Option *o = option_with_name(optionName);
    return (o != nullptr) && (o->currentValue == "true");
}

/// get_option_value_int() returns the value of a UCI parameter as an integer.
/// Normally, this function will be used for a parameter of type "spin", but
/// it could also be used with a "combo" parameter, where all the available
/// values are integers.

int get_option_value_int(const std::string &optionName)
{
    Option *o = option_with_name(optionName);
    if (o != nullptr) {
        std::istringstream iss(o->currentValue);
        int val{0};
        if (iss >> val) {
            return val;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/// get_option_value_string() returns the current value of a UCI parameter as
/// a string.  It is used with parameters of type "combo" and "string".

const std::string get_option_value_string(const std::string &optionName)
{
    Option *o = option_with_name(optionName);
    if (o != nullptr) {
        return o->currentValue;
    } else {
        return "";
    }
}

/// button_was_pressed() tests whether a UCI parameter of type "button" has
/// been selected since the last time the function was called.

bool button_was_pressed(const std::string &buttonName)
{
    if (get_option_value_bool(buttonName)) {
        set_option_value(buttonName, "false");
        return true;
    } else {
        return false;
    }
}

/// set_option_value() inserts a new value for a UCI parameter.  Note that
/// the function does not check that the new value is legal for the given
/// parameter:  This is assumed to be the responsibility of the GUI.

void set_option_value(const std::string &optionName, const std::string &newValue)
{
    Option *o = option_with_name(optionName.c_str());
    if (o != nullptr) {
        o->currentValue = newValue;
    } else {
        std::cout << "No such option: " << optionName << std::endl;
    }
}

/// push_button() is used to tell the engine that a UCI parameter of type
/// "button" has been selected:

void push_button(const std::string &buttonName)
{
    set_option_value(buttonName, "true");
}

namespace {

// option_with_name() tries to find a UCI option with a given
// name.  It returns a pointer to the UCI option or the null pointer,
// depending on whether an option with the given name exists.

Option *option_with_name(const std::string &optionName)
{
    for (auto &o : Options) {
        if (o.name == optionName) {
            return &o;
        }
    }
    return nullptr;
}

} // namespace

} // namespace Glaurung
