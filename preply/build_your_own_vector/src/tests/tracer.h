#pragma once
struct Tracer {
    static inline int alive = 0;
    static inline int default_constructed = 0;
    static inline int copies = 0;
    static inline int moves = 0;
    int value = 0;
    Tracer() { ++alive; ++default_constructed; }
    explicit Tracer(int v) : value(v) { ++alive; }
    Tracer(const Tracer& o) : value(o.value) {
        ++alive; ++copies;
    }
    Tracer(Tracer&& o) noexcept : value(o.value) {
        ++alive; ++moves;
    }
    Tracer& operator=(const Tracer& o) {
        value = o.value; ++copies; return *this;
    }
    Tracer& operator=(Tracer&& o) noexcept {
        value = o.value; ++moves; return *this;
    }
    ~Tracer() { --alive; }
    static void reset() {
        alive = default_constructed = copies = moves = 0;
    }
};
