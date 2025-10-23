#pragma once
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
#include <algorithm>
#include <cctype>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Define.h"
#include "Errors.h"

class Tokenizer {
public:
    typedef std::vector<char const *> StorageType;

    typedef StorageType::size_type size_type;

    typedef StorageType::const_iterator const_iterator;
    typedef StorageType::reference reference;
    typedef StorageType::const_reference const_reference;

public:
    Tokenizer(const std::string &src, char const sep, uint32_t vectorReserve = 0);

    ~Tokenizer() { delete[] m_str; }

    const_iterator begin() const { return m_storage.begin(); }

    const_iterator end() const { return m_storage.end(); }

    size_type size() const { return m_storage.size(); }

    reference operator[](size_type i) { return m_storage[i]; }

    const_reference operator[](size_type i) const { return m_storage[i]; }

private:
    char *m_str;
    StorageType m_storage;
};

// See here: http://www.martinbroadhurst.com/case-insensitive-string-comparison-in-c.html
struct iequal {
    bool operator()(int c1, int c2) const { return std::toupper(c1) == std::toupper(c2); }
};

inline bool iequals(const std::string &str1, const std::string &str2)
{
    return std::equal(str1.begin(), str1.end(), str2.begin(), iequal());
}

/* Return a random number in the range min..max; (max-min) must be smaller than 32768.*/
int32_t irand(int32_t min, int32_t max);

/* Return a random number in the range min..max (inclusive). For reliable results, the difference
 * between max and min should be less than RAND32_MAX.*/
uint32_t urand(uint32_t min, uint32_t max);

/* Return a random number in the range 0 .. RAND32_MAX.*/
int32_t rand32();

/* Return a random number in the range min..max*/
float frand(float min, float max);

inline bool isNumeric(char c)
{
    return (c >= '0' && c <= '9');
}

bool isMXNumeric(std::string);

inline bool isNumeric(char const *str)
{
    for (char const *c = str; *c; ++c)
        if (!isNumeric(*c))
            return false;

    return true;
}

void string_replace(std::string &str, const std::string &from, const std::string &to);