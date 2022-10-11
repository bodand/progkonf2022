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
 * user-code/main.cxx --
 *   The main function of the user code. Uses the other supplementary headers
 *   to construct a set of derived classes, then visits them using a counter
 *   visitor.
 */

#include <memory>
#include <iostream>

#include <visitor.hxx>

#include "derived_A.hxx"
#include "derived_B.hxx"
#include "derived_C.hxx"

struct cnt_visitor final : visitor<derived_a, derived_b, derived_c> {
    void do_visit(derived_a*) final { ++a_count; }
    void do_visit(derived_b*) final { ++b_count; }
    void do_visit(derived_c*) final { ++c_count; }

    std::size_t a_count = 0;
    std::size_t b_count = 0;
    std::size_t c_count = 0;
};

int
main() {
    std::unique_ptr<base> a = std::make_unique<derived_a>();
    std::unique_ptr<base> b = std::make_unique<derived_b>();
    std::unique_ptr<base> c = std::make_unique<derived_c>();

    cnt_visitor counter;

    for (std::size_t i = 0; i < 19999999LL; ++i) {
        a->accept(counter);
        b->accept(counter);
        c->accept(counter);
    }

    std::cout << "Counted A " << counter.a_count << " times.\n";
    std::cout << "Counted B " << counter.b_count << " times.\n";
    std::cout << "Counted C " << counter.c_count << " times.\n";
}
