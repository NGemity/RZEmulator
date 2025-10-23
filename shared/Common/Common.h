#pragma once
/*
 * Copyright (C) 2017-2020 NGemity <https://ngemity.org/>
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <cmath>
#include <memory>
#include <optional>
#include <set>
#include <stdint.h>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Define.h"
#include "StringFormat.h"
#include "Timer.h"

#if PLATFORM == PLATFORM_WINDOWS
#if COMPILER == COMPILER_INTEL
#if !defined(BOOST_ASIO_HAS_MOVE)
#define BOOST_ASIO_HAS_MOVE
#endif // !defined(BOOST_ASIO_HAS_MOVE)
#endif // if NGEMITY_COMPILER == NGEMITY_COMPILER_INTEL
#else

#include <cstdlib>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#endif

using namespace std::literals::string_literals;

// we always use stdlib std::max/std::min, undefine some not C++ standard
// defines (Win API and some other platforms)
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

namespace NGemity {
    using std::make_unique;
}