#ifndef CANASTA_H
#define CANASTA_H

#include <QObject>

#include "producto.h"

class Canasta : public QObject
{
    Q_OBJECT
public:
    explicit Canasta(QObject *parent = nullptr);
    Canasta(Producto *pro, int cantidad);


    Producto *pro() const;

    void setPro(Producto *newPro);

    int cantidad() const;
    void setCantidad(int newCantidad);

signals:

private:
    Producto *m_pro;
    int m_cantidad;

};

#endif // CANASTA_H
