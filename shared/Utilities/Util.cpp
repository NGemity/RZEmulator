/*
 * Copyright (C) 2011-2017 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2017 MaNGOS <https://www.getmangos.eu/>
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

#include "Util.h"

#include <cstdarg>
#include <cstring>
#include <float.h>
#include <random>
#include <sstream>

#include "Common.h"
#include "Errors.h" // for ASSERT
#include "utf8.h"

#if PLATFORM == PLATFORM_WINDOWS
#include <Windows.h>
#endif

std::random_device r;
std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
std::mt19937 randGenerator{seed};

int32_t irand(const int32_t min, const int32_t max)
{
    ASSERT(max >= min);
    std::uniform_int_distribution<int32_t> distr(min, max);
    return distr(randGenerator);
}

uint32_t urand(const uint32_t min, const uint32_t max)
{
    ASSERT(max >= min);
    std::uniform_int_distribution<uint32_t> distr(min, max);
    return distr(randGenerator);
}

float frand(const float min, const float max)
{
    ASSERT(max >= min);
    std::uniform_real_distribution<float> distr(min, max);
    return distr(randGenerator);
}


int32_t rand32()
{
    return irand(INT_MIN, RAND_MAX);
}

bool isMXNumeric(std::string input)
{
    std::istringstream iss(input);
    double f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

Tokenizer::Tokenizer(const std::string &src, const char sep, uint32_t vectorReserve)
{
    m_str = new char[src.length() + 1];
    memcpy(m_str, src.c_str(), src.length() + 1);

    if (vectorReserve)
        m_storage.reserve(vectorReserve);

    char *posold = m_str;
    char *posnew = m_str;

    for (;;) {
        if (*posnew == sep) {
            m_storage.push_back(posold);
            posold = posnew + 1;

            *posnew = '\0';
        }
        else if (*posnew == '\0') {
            // Hack like, but the old code accepted these kind of broken strings,
            // so changing it would break other things
            if (posold != posnew)
                m_storage.push_back(posold);

            break;
        }

        ++posnew;
    }
}


void string_replace(std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

bool StringToBool(std::string const &str)
{
    std::string lowerStr = str;
    std::transform(str.begin(), str.end(), lowerStr.begin(), [](char c) { return char(::tolower(c)); });
    return lowerStr == "1" || lowerStr == "true" || lowerStr == "yes";
}