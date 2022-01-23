#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QMessageBox>

#include "producto.h"
#include "canasta.h"


#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();

private slots:
    void on_inProducto_currentIndexChanged(int index);

    void on_btnAgregar_released();

    void on_pushButton_released();

private:
    Ui::Tienda *ui;
    QList<Producto*> m_productos;
    QList<Canasta*> m_canasta;

    float m_subtotal;

    void cargarProductos();

    void calcular(float stProducto);

    bool validarCed(QString as);

    bool validarCanasta(Producto *p);


    void ordernarProductos();
};
#endif // TIENDA_H
