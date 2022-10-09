/* Progkonf 2022
 *
 * Copyright (c) 2022 András Bodor
 * All rigths reserved.
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
 * user-code/base.hpp --
 *   User code for using the dynamic visitor implementation, contains the base 
 *   class of the user class-hierarchy.
 */

#ifndef USER_CODE_BASE_HPP
#define USER_CODE_BASE_HPP

#include <lib/visitable_hierarchy.hxx>

struct base : visitable_hierarchy {
    explicit base(int x) 
        : _x(x) { }

private:
    int _x; 
    // Dummy value, so a compiler doesn't accidentally do 
    // "empty base-class optimization" 
};

#endif
