#include "factura.h"
#include "ui_factura.h"

Factura::Factura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Factura)
{
    ui->setupUi(this);
}

Factura::Factura(QList<Canasta> *canasta, Cliente *cliente)
{
    m_lista = canasta;
    m_cliente = cliente;
}

Factura::~Factura()
{
    delete ui;
}

