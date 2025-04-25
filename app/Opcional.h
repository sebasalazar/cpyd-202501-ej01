#ifndef OPCIONAL_H
#define OPCIONAL_H

#include <type_traits>
#include <utility>

template<typename T>
class Opcional {
private:
    typename std::aligned_storage<sizeof (T), alignof (T)>::type almacenamiento_;
    bool isPresent_;

    T* data() {
        return reinterpret_cast<T*> (&almacenamiento_);
    }

    const T* data() const {
        return reinterpret_cast<const T*> (&almacenamiento_);
    }

public:
    // Constructor vacío

    Opcional() noexcept : isPresent_(false) {
    }

    // Constructor con copia

    Opcional(const T& value) : isPresent_(true) {
        new (data()) T(value);
    }

    // Constructor con movimiento

    Opcional(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value)
    : isPresent_(true) {
        new (data()) T(std::move(value));
    }

    // Constructor por copia de Opcional

    Opcional(const Opcional& other) : isPresent_(other.isPresent_) {
        if (isPresent_) {
            new (data()) T(*other.data());
        }
    }

    // Constructor por movimiento de Opcional

    Opcional(Opcional&& other) noexcept(std::is_nothrow_move_constructible<T>::value)
    : isPresent_(other.isPresent_) {
        if (isPresent_) {
            new (data()) T(std::move(*other.data()));
            other.reset();
        }
    }

    // Destructor

    ~Opcional() {
        reset();
    }

    // Asignación por copia

    Opcional& operator=(const Opcional& other) {
        if (this != &other) {
            reset();
            if (other.isPresent_) {
                new (data()) T(*other.data());
                isPresent_ = true;
            }
        }
        return *this;
    }

    // Asignación por movimiento

    Opcional& operator=(Opcional&& other) noexcept(std::is_nothrow_move_constructible<T>::value) {
        if (this != &other) {
            reset();
            if (other.isPresent_) {
                new (data()) T(std::move(*other.data()));
                isPresent_ = true;
                other.reset();
            }
        }
        return *this;
    }

    bool has_value() const noexcept {
        return isPresent_;
    }

    T& value() {
        if (!isPresent_) throw std::runtime_error("Opcional: no hay valor");
        return *data();
    }

    const T& value() const {
        if (!isPresent_) throw std::runtime_error("Opcional: no hay valor");
        return *data();
    }

    T value_or(const T& defaultValue) const {
        return isPresent_ ? *data() : defaultValue;
    }

    void reset() noexcept {
        if (isPresent_) {
            data()->~T();
            isPresent_ = false;
        }
    }
};

#endif /* OPCIONAL_H */

