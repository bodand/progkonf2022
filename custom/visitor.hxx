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
 * custom/visitor.hxx --
 *   Provides the generic visitor class, which merges together multiple sets of
 *   types that may be visited.
 *   Basically just a joint set of visitor_impl<T> for unspecified, but finite
 *   set of types.
 *   For each supported type, checks if the given runtime type is the same, and
 *   acts on this knowledge.
 */

#ifndef MY_VISITOR_HXX
#define MY_VISITOR_HXX

#include "typeid.hxx"
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
protected:
    /**
     * The function checking if a provided compile-time type T is equal to the
     * runtime provided type, whose typeid is tid.
     * If they are, then the type-erased value `typeless_visited˙ can be cast
     * safely to `T*`, since that is its actual type, meaning we can visit it.
     *
     * \tparam T The compile-time type to check equivalence to the runtime type
     *           to
     * \param typeless_visited The type-erased value to visit
     * \param tid The typeid of the type-erased value
     * \return Whether the visitation could occur, that is the compile-time and
     * runtime types were the same.
     */
    template<class T>
    [[gnu::always_inline]]
    bool visit_one_t(void* typeless_visited, my_typeid tid) {
        if (my_id_of < T > != tid) return false;
        static_cast<visitor_impl<T>*>(this)->do_visit(static_cast<T*>(typeless_visited));
        return true;
    }

    /**
     * Implements the required function to visiting a specific type based on
     * its runtime type.
     * Checks all types in Ts to be equal to the type whose typeid is tid.
     *
     * \param typeless_visited The type-erased object we are visiting
     * \param tid The type of the type-erased object
     */
    void
    visit_imp(void* typeless_visited, my_typeid tid) final {
        // fold-expression relying on the short-circuit feature of boolean ||
        (visit_one_t<Ts>(typeless_visited, tid) || ...);
    }
};

#endif
