#ifndef OPCIONAL_H
#define OPCIONAL_H

template<typename T>
class Opcional {
private:
    bool tieneValor;
    T valor;

public:

    Opcional() : tieneValor(false), valor() {
    }

    explicit Opcional(const T& val) : tieneValor(true), valor(val) {
    }

    bool estaPresente() const {
        return tieneValor;
    }

    const T& obtener() const {
        return valor;
    }
};

#endif // OPCIONAL_H
