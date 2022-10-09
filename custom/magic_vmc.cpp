#include <cassert>
#include <iostream>

struct my_typeid {
    template<class T>
    static my_typeid id_of() {
        return my_typeid(my_type<T>::create(type_cntr));
    }

    bool operator==(const my_typeid& other) const noexcept {
        return other._value == _value;
    }

    bool operator!=(const my_typeid& other) const noexcept = default;

private:
    explicit my_typeid(std::uint_fast32_t val)
          : _value(val) { }

    std::uint_fast32_t _value;
    inline static std::uint_fast32_t type_cntr = 1;

    template<class T>
    struct my_type {
        static std::uint_fast32_t create(std::uint_fast32_t& cnt) {
            if (_id == 0) _id = cnt++;
            return _id;
        }

    private:
        inline static std::uint_fast32_t _id = 0;
    };
};

template<class T>
static auto my_id_of = my_typeid::id_of<T>();

struct visitor_base {
    template<class T>
    void visit(T* visited) {
        visit_imp(static_cast<void*>(visited), my_id_of<T>);
    }

    virtual ~visitor_base() = default;
protected:
    virtual void
    visit_imp(void*, my_typeid) = 0;
};

template<class T>
struct visitor_impl : virtual visitor_base {
    virtual void do_visit(T*) = 0;

protected:
    ~visitor_impl() override = default;
};

template<class... Ts>
struct visitor : visitor_impl<Ts> ... {
    ~visitor() override = default;
protected:
    template<class T>
    [[gnu::always_inline]]
    bool visit_one_t(void* typeless_visited, my_typeid tid) {
        if (my_id_of<T> != tid) return false;
        static_cast<visitor_impl<T>*>(this)->do_visit(static_cast<T*>(typeless_visited));
        return true;
    }

    void
    visit_imp(void* typeless_visited, my_typeid tid) final {
        (visit_one_t<Ts>(typeless_visited, tid) || ...);
    }
};

struct visitable_hierarchy {
    virtual void accept(visitor_base& vis) = 0;
    virtual ~visitable_hierarchy() = default;
};

template<class Base, class T>
struct visitable_as : Base {
    using Base::Base;

    void accept(visitor_base& vtor) override {
        auto self = static_cast<T*>(this);
        assert(self);

        vtor.visit(self);
    }

    ~visitable_as() override = default;
};

int
main() {
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

    for (std::size_t i = 0; i < std::size_t(9'999'999'999ULL); ++i) {
        d1->accept(nop);
        d2->accept(nop);
        d3->accept(nop);
    }

    delete d1;
    delete d2;
    delete d3;

    std::cout << "der1: " << nop.der1_cnt << "\n";
    std::cout << "der2: " << nop.der2_cnt << "\n";
    std::cout << "der3: " << nop.der3_cnt << "\n";
}
