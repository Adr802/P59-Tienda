#include "canasta.h"

Canasta::Canasta(QObject *parent) : QObject(parent)
{
    m_cantidad = 0;
}

Canasta::Canasta(Producto *pro, int cantidad)
{
    m_pro = pro;
    m_cantidad = cantidad;
}

Producto *Canasta::pro() const
{
    return m_pro;
}

void Canasta::setPro(Producto *newPro)
{
    m_pro = newPro;
}

int Canasta::cantidad() const
{
    return m_cantidad;
}

void Canasta::setCantidad(int newCantidad)
{
    m_cantidad = newCantidad;
}
