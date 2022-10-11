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
 * type_info/visitable_hierarchy.hxx --
 *   The library code for the `visitable_hierarchy` class.
 *   Equivalent implementation in all three variants.
 */

#ifndef STD_VISITABLE_HIERARCHY_HXX
#define STD_VISITABLE_HIERARCHY_HXX

#include "visitor_base.hxx"

/**
 * Denotes a hierarchy that may be visited by the visitors deriving from
 * visitor_base.
 **/
struct visitable_hierarchy {
    /**
     * Entry point for the visitor to start visiting.
     * Calls back into the correct descendant's do_visit with the correct type.
     **/
    virtual void accept(visitor_base& vis) = 0;
    // virtual destructor, because inheritance
    virtual ~visitable_hierarchy() = default;
};

#endif

