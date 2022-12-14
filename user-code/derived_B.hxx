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
 * dynamic_cast/user-code/derived_B.hxx --
 *   User code for the dynamic_cast implementation, contains the code for one
 *   of the derived classes in the user class-hierarchy: dervied_b.
 */

#ifndef USER_CODE_DERB_HXX
#define USER_CODE_DERB_HXX

#include <visitable_as.hxx>

#include "base.hxx"

struct derived_b : visitable_as<base, derived_b> {
    derived_b()
        : visitable_as<base, derived_b>(2) { }
};

#endif
