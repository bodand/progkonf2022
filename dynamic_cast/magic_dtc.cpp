#include <cassert>
#include <iostream>
#include <typeinfo>

struct visitor_base {
    virtual ~visitor_base() = default;
};

template<class... Ts>
struct visitor : visitor_impl<Ts> ... {
    ~visitor() override = default;
};



template<class Base, class T>
struct visitable_as : Base {
    using Base::Base;

    void accept(visitor_base& dyn_vtor) override {
        if (auto vtor = dynamic_cast<visitor_impl<T>*>(&dyn_vtor)) {
            auto self = static_cast<T*>(this);
            assert(self);

            vtor->do_visit(self);
        }
    }

    ~visitable_as() override = default;
};

int main() {
    struct nop_visitor final : visitor<der1, der2, der3> {
        void do_visit(der1*) final { ++der1_cnt; }

        void do_visit(der2*) final { ++der2_cnt; }

        void do_visit(der3*) final { ++der3_cnt; }

        std::size_t der1_cnt = 0;
        std::size_t der2_cnt = 0;
        std::size_t der3_cnt = 0;
    } nop;

    base* d1 = new der1;
    base* d2 = new der2;
    base* d3 = new der3;

    for (std::size_t j = 0; j < std::size_t(9ULL); ++j) {
        for (std::size_t i = 0; i < std::size_t(999'999'999ULL); ++i) {
            d1->accept(nop);
            d2->accept(nop);
            d3->accept(nop);
        }
    }

    delete d1;
    delete d2;
    delete d3;

    std::cout << "der1: " << nop.der1_cnt << "\n";
    std::cout << "der2: " << nop.der2_cnt << "\n";
    std::cout << "der3: " << nop.der3_cnt << "\n";
}
