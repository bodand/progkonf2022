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
 * dynamic_cast/visitor.hxx --
 *   Provides the generic visitor class, which merges together multiple sets of
 *   types that may be visited.
 *   Basically just a joint set of visitor_impl<T> for unspecified, but finite
 *   set of types.
 */

#ifndef DYN_VISITOR_HXX
#define DYN_VISITOR_HXX

#include "visitor_base.hxx"

/**
 * Visitor class capable of visiting multiple types in a class hierarchy.
 * The types it may visit are provided in the template parameters, such the
 * code only needs to know the correct set of types when the type is to be
 * used.
 *
 * \tparam Ts A parameter pack of types to visit.
 */
template<class... Ts>
struct visitor : visitor_impl<Ts> ... {
    ~visitor() override = default;
};

#endif
