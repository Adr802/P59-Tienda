#ifndef FACTURA_H
#define FACTURA_H

#include <QDialog>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

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


    ~Factura();

    void armarString();


    void setLista(const QList<Canasta *> &newLista);
    void setCliente(Cliente *newCliente);

private slots:
    void on_btnClose_released();

    void on_btnSave_released();

private:
    Ui::Factura *ui;
    QList<Canasta*> m_lista;
    Cliente *m_cliente;
    QString m_datos;

    float m_subtotal = 0;
    float m_IVA = 0;
    float m_total = 0;



};

#endif // FACTURA_H
