#ifndef FACTURA_H
#define FACTURA_H

#include <QDialog>

#include "canasta.h"
#include "cliente.h"

namespace Ui {
class Factura;
}

class Factura : public QDialog
{
    Q_OBJECT

public:
    explicit Factura(QWidget *parent = nullptr);
    Factura(QList<Canasta> *canasta, Cliente *cliente);
    ~Factura();

private:
    Ui::Factura *ui;
    QList<Canasta> *m_lista;
    Cliente *m_cliente;

};

#endif // FACTURA_H
