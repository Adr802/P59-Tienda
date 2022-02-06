#include "factura.h"
#include "ui_factura.h"

Factura::Factura(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Factura)
{
    ui->setupUi(this);
    m_datos = "";
}



Factura::~Factura()
{
    delete ui;
}


void Factura::on_btnClose_released()
{
    Factura::close();
}

void Factura::on_btnSave_released()
{
    QDateTime c = QDateTime::currentDateTime();
    QString nameFormat = c.toString("ddMMyyyy_hhmmss");

    //Crear un archivo
    QFile archivo("../" + nameFormat + ".txt");

    //Arbirlo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear un stream de texto
        QTextStream salida(&archivo);
        salida << m_datos;

        QMessageBox::information(this,tr("Informacion"),tr("El archivo fue guardado con exito"));
    }else{
        //Mensaje si no se pudo guardar
        QMessageBox::warning(this,
                             tr("Guardar datos"),
                             tr("No se pudo guardar el archivo"));
    }

    //Cerrar el archivo
    archivo.close();


}

void Factura::setLista(const QList<Canasta *> &newLista)
{
    m_lista = newLista;
}

void Factura::setCliente(Cliente *newCliente)
{
    m_cliente = newCliente;
}



void Factura::armarString()
{
    m_datos += "\n\n";
    for(int i=0; i < 107; i++){
        m_datos += "-";
    }
    m_datos += tr("\n\t\tAbarratore * Los panas *\n");
    for(int i=0; i < 107; i++){
        m_datos += "-";
    }

    m_datos += tr("\n\t\tDATOS DEL CLIENTE\n");

    m_datos += tr("Cedula: ") + m_cliente->cedula() + "\n";
    m_datos += tr("Nombre: ") + m_cliente->nombre() + "\n";
    m_datos += tr("Telefono: ") + m_cliente->telefono() + "\n";
    m_datos += tr("Email: ") + m_cliente->email() + "\n";
    m_datos += tr("Direccion: ") + m_cliente->direccion() + "\n";

    for(int i=0; i < 107; i++){
        m_datos += "-";
    }
    m_datos += tr("\n\t\tDATOS DE LA COMPRA\n");
    for(int i=0; i < 107; i++){
        m_datos += "-";
    }
    m_datos += tr("\n   Cant.\t  Descripcion\t                       P.Unitario\t                   Subtotal\n");

    foreach(Canasta *c, m_lista){
        float subto = c->pro()-> precio() * c->cantidad();
        m_subtotal += subto;

        m_datos += "    " + QString::number(c->cantidad());



        m_datos += "\t  " + c->pro()->nombre();



        m_datos += "\t                       " + QString::number(c->pro()->precio());


        m_datos += "\t                   " + QString::number(subto, 'f', 2);
        m_datos += "\n";
    }
    m_datos += "\n\n\n\n\n\n\n\n\n";
    m_IVA = m_subtotal * 0.12;
    m_total = m_IVA + m_subtotal;


    m_datos += tr("\t\t\t          Subtotal:\t$ ") + QString::number(m_subtotal, 'f', 2) + "\n";

    m_datos += tr("\t\t\t          IVA:\t$ ") + QString::number(m_IVA, 'f', 2) + "\n";

    m_datos += tr("\t\t\t          Total:\t$ ") + QString::number(m_total, 'f', 2) + "\n";

    ui->outFactura->setPlainText(m_datos);

}




