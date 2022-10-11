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
 * custom/visitor_base.hxx --
 *   Visitor base for the using the custom implementation for typeid.
 *   Otherwise equivalent to the other implementation.
 */

#ifndef MY_VISITOR_BASE_HXX
#define MY_VISITOR_BASE_HXX

#include <typeinfo>
#include "typeid.hxx"

/**
 * The smarter visitor base.
 * Encapsulates type erasure into itself and passes runtime information using
 * my_typeid.
 */
struct visitor_base {
    /**
     * Visits a given object of type T.
     * This type may or may not be visitable by the current visitor, but that
     * will be decided later.
     *
     * \tparam T The type of the visited object
     * \param visited The object we are trying to visit
     */
    template<class T>
    void visit(T* visited) {
        visit_imp(static_cast<void*>(visited), my_id_of<T>);
    }

    virtual ~visitor_base() = default; // nop virtual destructor for inheritance
protected:
    /**
     * Virtual function to push down the requirement to each subclass.
     * They will decide how to deal with it.
     * NOTE: The typeinfo has been converted into runtime data, now represented
     * only as an integer.
     */
    virtual void
    visit_imp(void*, my_typeid) = 0;
};

/**
 * A visitor type providing the function that allows visiting one particular
 * type.
 *
 * \tparam T The type this implementation can visit
 */
template<class T>
struct visitor_impl : virtual visitor_base {
    /**
     * The pure-virtual function that allows descendants to implement the
     * visitation logic for a given T type.
     */
    virtual void do_visit(T*) = 0;

protected:
    ~visitor_impl() override = default;
};

#endif

