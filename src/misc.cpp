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

#include <iostream>
#if !defined(_MSC_VER)

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#else

#include "dos.h"
#include <time.h>
#include <windows.h>
int gettimeofday(struct timeval *tp, struct timezone *tzp);

#endif

#include "misc.h"
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>

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
        static const char monthNames[12][4]
            = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        const char *dateString = __DATE__;
        std::stringstream s;
        int month = 0, day = 0;

        for (int i = 0; i < 12; i++)
            if (strncmp(dateString, monthNames[i], 3) == 0)
                month = i + 1;
        day = atoi(dateString + 4);

        s << "Glaurung " << (dateString + 9) << std::setfill('0') << std::setw(2) << month
          << std::setfill('0') << std::setw(2) << day;

        return s.str();
    } else
        return "Glaurung " + EngineVersion;
}

/// get_system_time() returns the current system time, measured in
/// milliseconds.

int get_system_time()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}

/// cpu_count() tries to detect the number of CPU cores.

#if !defined(_MSC_VER)

#if defined(_SC_NPROCESSORS_ONLN)
int cpu_count()
{
    return std::min(sysconf(_SC_NPROCESSORS_ONLN), 8L);
}
#else
int cpu_count()
{
    return 1;
}
#endif

#else

int cpu_count()
{
    SYSTEM_INFO s;
    GetSystemInfo(&s);
    return Min(s.dwNumberOfProcessors, 8);
}

#endif

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
