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

#if !defined(MISC_H_INCLUDED)
#define MISC_H_INCLUDED

////
//// Includes
////

#include <atomic>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

////
//// Constants
////

/// Version number.  If this is left empty, the current date (in the format
/// YYMMDD) is used as a version number.

const std::string EngineVersion = "2.2.1";

////
//// Prototypes
////

extern const std::string engine_name();
extern int get_system_time();
extern int cpu_count();

class InputReader
{
public:
    enum class INPUT_QUEUE_STATUS {
        EMPTY,
        HAS_COMMAND,
        END,
    };

    InputReader();
    ~InputReader();
    INPUT_QUEUE_STATUS ReaderStatus() const;
    std::string PopCommand();

private:
    std::queue<std::string> commands_;
    mutable std::mutex mtx_;
    std::atomic<bool> running_{true};
    std::jthread worker_;
};

extern InputReader input;

#endif // !defined(MISC_H_INCLUDED)
