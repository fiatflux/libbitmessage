/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// CONTRIBUTORS AND COPYRIGHT HOLDERS (c) 2013:
// Bob Mottram (bob@robotics.uk.to)
// Dag Robøle (BM-2DAS9BAs92wLKajVy9DS1LFcDiey5dxp5c)

#include <chrono>
#include "utils.h"

namespace bm {

namespace utils {

namespace internal {

struct RandomNumberGeneratorAutoSeeded
{
    static Botan::AutoSeeded_RNG& instance()
    {
        static Botan::AutoSeeded_RNG generator;
        return generator;
    }
};

} // namespace internal

Botan::AutoSeeded_RNG& random_number_generator()
{
    return internal::RandomNumberGeneratorAutoSeeded::instance();
}

SecureVector random_bytes(uint32_t count)
{
    return internal::RandomNumberGeneratorAutoSeeded::instance().random_vec(count);
}

uint32_t seconds_since_epoc()
{
    using namespace std::chrono;
    system_clock::time_point tp = system_clock::now();
    system_clock::duration dtn = tp.time_since_epoch();
    return dtn.count() * system_clock::period::num / system_clock::period::den;
}

std::string remove_prefix(const std::string& source, const std::string& prefix)
{
    std::string result;
    std::string::size_type pos = source.find_first_of(prefix);
    if(!pos)
        std::copy(source.begin() + prefix.length(), source.end(), std::back_inserter(result));
    else result = source;
    return result;
}

} // namespace utils

} // namespace bm
