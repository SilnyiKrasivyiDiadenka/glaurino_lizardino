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

#include "misc.h"
#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>

namespace Glaurung {

////
//// Functions
////

/// engine_name() returns the full name of the current Glaurung version.
/// This will be either "Glaurung YYMMDD" (where YYMMDD is the date when the
/// program was compiled) or "Glaurung <version number>", depending on whether
/// the constant EngineVersion (defined in misc.h) is empty.

const std::string engine_name()
{
    if (EngineVersion == "") {
        static const std::array<std::string, 12> monthNames
            = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        const std::string dateString = __DATE__;

        int monthNr{0};
        for (const auto &[i, month] : monthNames | std::views::enumerate) {
            if (dateString.substr(0, 3) == month) {
                monthNr = i + 1;
                break;
            }
        }

        int day = std::stoi(dateString.substr(4, 2));

        std::stringstream s;
        s << "Glaurung " << std::stoi(dateString.substr(9)) << std::setfill('0') << std::setw(2)
          << monthNr << std::setfill('0') << std::setw(2) << day;

        return s.str();
    } else {
        return "Glaurung " + EngineVersion;
    }
}

/// get_system_time() returns the current system time, measured in
/// milliseconds.

std::int64_t get_system_time()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

/// cpu_count() tries to detect the number of CPU cores.

int cpu_count()
{
    return std::min(std::thread::hardware_concurrency(), 8u);
}

InputReader::InputReader()
    : worker_(std::jthread([this](std::stop_token stopToken) {
        std::string line;
        while (!stopToken.stop_requested() && std::getline(std::cin, line)) {
            std::lock_guard<std::mutex> lock(mtx_);
            commands_.push(std::move(line));
        }
        running_ = false;
    })) {};

InputReader::~InputReader()
{
    worker_.request_stop();
    std::exit(0);
}

InputReader::INPUT_QUEUE_STATUS InputReader::ReaderStatus() const
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (!running_) {
        return InputReader::INPUT_QUEUE_STATUS::END;
    } else if (!commands_.empty()) {
        return InputReader::INPUT_QUEUE_STATUS::HAS_COMMAND;
    } else {
        return InputReader::INPUT_QUEUE_STATUS::EMPTY;
    }
}

std::string InputReader::PopCommand()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (commands_.empty()) {
        return "";
    }
    auto cmd = std::move(commands_.front());
    commands_.pop();
    return cmd;
}

InputReader input;

} // namespace Glaurung