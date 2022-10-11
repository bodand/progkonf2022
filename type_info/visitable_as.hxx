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
 * type_info/visitable_as.hxx --
 *   Helper class for the std::type_info based implementation of the dynamic
 *   visitor.
 *   This is basically the same as if with a classical visitor.
 */

#ifndef STD_VISITABLE_AS_HXX
#define STD_VISITABLE_AS_HXX

#include <cassert>

#include "visitor_base.hxx"

/**
 * The implementation helper for the dynamic_cast based implementation.
 * Takes a variable of visitor_base type, marking that some kind of visitor is
 * here, then tries to downcast it into the correct type.
 * This causes most performance problems.
 *
 * The type itself basically just wires itself between a class and its baseclass
 * to provide some functionality automatically.
 * For the interested, the pattern of passing the current type into its template
 * base is called CRTP: Curiously recurring template pattern.
 * For use-cases see the user-code directory.
 *
 * \tparam Base The base type of T
 * \tparam T The type we are plugging into
 */
template<class Base, class T>
struct visitable_as : Base {
    using Base::Base; // take the exact same constructors as Base

    /**
     * Takes a visitor of some kind and accepts it.
     * Then the visitor will then try to visit us if we are of the
     * expected type.
     *
     * \param dyn_vtor The dynamic visitor
     */
    void accept(visitor_base& dyn_vtor) override {
        auto self = static_cast<T*>(this);
        assert(self);

        dyn_vtor.visit(self);
    }


    ~visitable_as() override = default; // inheritance things
};

#endif
