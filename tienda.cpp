#include "tienda.h"
#include "ui_tienda.h"

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    //Lista de productos
    cargarProductos();
    //Mostrar los productos en el combo
    foreach(Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }

    //Configurar cabecera de la tabla
    QStringList cabecera = {"Cantidad","Producto","P. Unitario","Subtotal"};
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(cabecera);

    //Establecer el subtotal en cero
    m_subtotal = 0;
}

Tienda::~Tienda()
{
    delete ui;
}
/**
 * @brief Tienda::cargarProductos  Carga la lista de productos de la tienda
 *
 */
void Tienda::cargarProductos()
{
    //Crear productos "quemados" en el codigo
    m_productos.append(new Producto(1, "Leche", 0.80));
    m_productos.append(new Producto(2, "Pan", 0.15));
    m_productos.append(new Producto(3, "Queso", 2.50));
    //Podria leerse de una base de datos, de un archivo o incluso de internet
    // ordernarProductos();
}

void Tienda::calcular(float stProducto)
{
    m_subtotal += stProducto;
    float iva = (m_subtotal * IVA) / 100;
    float total = m_subtotal + iva;

    //Mostrar valores en la GUI
    ui->outSubTotal->setText("$ " + QString::number(m_subtotal,'f',2));
    ui->outIVA->setText("$ " + QString::number(iva,'f',2));
    ui->outTotal->setText("$ " + QString::number(total,'f',2));

}

void Tienda::ordernarProductos()
{
    for(int i=0; i > m_productos.length(); i++){
        for(int j=0; j > m_productos.length(); j++){
            if(m_productos[i]->nombre() > m_productos[j]->nombre()){
                Producto *temp = m_productos[i];
                m_productos[i] = m_productos[j];
                m_productos[j] = temp;
            }
        }
    }

 /*   QListIterator<Producto*> iter(m_productos);
    iter.toFront();
    foreach(Producto *p, m_productos){
        if(iter.next() > iter.peekNext()){
            qDebug()<<p->nombre();
        }

    }*/
}



void Tienda::on_inProducto_currentIndexChanged(int index)
{
    //Obtener el precio del producto actual seleccionado
    float precio = m_productos.at(index)->precio();
    //Mostrar el precio del product en la etiqueta
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
    //Resetear el spinbox de cantidad a 0
    ui->inCantidad->setValue(0);


}


void Tienda::on_btnAgregar_released()
{
    //Validar que no se agreguen productos con 0 cantidades
    int cantidad = ui->inCantidad->value();
    if( cantidad == 0){
        return;
    }
    //Obetener los datos de la GUI
    int i = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(i);

    //Calcular subtotal del producto
    float subTotal = p->precio() * cantidad;

    //Agregar datos a la tabla
    int fila = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(fila);
    ui->tableWidget->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
    ui->tableWidget->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
    ui->tableWidget->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(),'f',2)));
    ui->tableWidget->setItem(fila, 3, new QTableWidgetItem(QString::number(subTotal,'f',2)));


    //Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    //Actualizar subtotales
    calcular(subTotal);
}

