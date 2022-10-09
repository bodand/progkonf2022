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
 * dynamic_cast/visitor_base.hxx --
 *   The base classes of the visitor tree in the dynamic_cast implementation.
 *   Contains both the absolute root `visitor_base`, and the typed de facto 
 *   roots with the typed `visitor_impl<T>`.
 */

#ifndef DYN_VISITOR_BASE_HXX
#define DYN_VISITOR_BASE_HXX

/** 
 * Absolute root of dynamic_cast based implementation. 
 * This is the type of the pointer passed around, and when needed cast down
 * using dynamic_cast to the appropriately typed visitor_impl<T>.
 **/
struct visitor_base {
    // Virtual destructor, because inheritence
    virtual ~visitor_base() = default; 
};

/**
 * The de facto root, and the first useful element in the hiearchy.
 * Provides the virtual interface of the `do_visit` function taking a pointer to
 * the expected type to be visited.
 * This function can be overriden by the descendants to provide the actual visitation
 * logic required by the visitor.
 **/
template<class T>
struct visitor_impl : virtual visitor_base {
    /**
     * Virtual function for the visitor.
     * Implemented in the concrete visitor at the end of the hierachy for the types
     * it wishes to visit.
     **/
    virtual void do_visit(T*) = 0;

protected:
    // Protected destructor does not allow an object of this type to be explicitly destroyed,
    // only through children.
    ~visitor_impl() override = default;
};

#endif

