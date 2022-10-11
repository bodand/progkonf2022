/* Progkonf 2022
 *
 * Copyright (c) 2022 András Bodor
 * All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * custom/typeid.hxx --
 *   Implements the custom typeid operator.
 */


#ifndef MY_TYPEID_HXX
#define MY_TYPEID_HXX

#include <cstdint>

struct my_typeid {
    template<class T>
    static my_typeid id_of() {
        return my_typeid(my_type<T>::create(type_cntr));
    }

    bool operator==(const my_typeid& other) const noexcept {
        return other._value == _value;
    }

    bool operator!=(const my_typeid& other) const noexcept = default;

private:
    explicit my_typeid(std::uint_fast32_t val)
          : _value(val) { }

    std::uint_fast32_t _value;
    inline static std::uint_fast32_t type_cntr = 1;

    template<class T>
    struct my_type {
        static std::uint_fast32_t create(std::uint_fast32_t& cnt) {
            if (_id == 0) _id = cnt++;
            return _id;
        }

    private:
        inline static std::uint_fast32_t _id = 0;
    };
};

template<class T>
static auto my_id_of = my_typeid::id_of<T>();

#endif
