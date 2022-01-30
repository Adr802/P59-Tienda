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
    QFile archivo(nameFormat + ".txt");

    //Arbirlo para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear un stream de texto
        QTextStream salida(&archivo);
        salida << m_datos;

        QMessageBox::information(this,"Informacion","El archivo fue guardado con exito");
    }else{
        //Mensaje si no se pudo guardar
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar el archivo");
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
    m_datos += "\n\t\tAbarratore * Los panas *\n";
    for(int i=0; i < 107; i++){
        m_datos += "-";
    }

    m_datos += "\n\t\tDATOS DEL CLIENTE\n";

    m_datos += "Cedula: " + m_cliente->cedula() + "\n";
    m_datos += "Nombre: " + m_cliente->nombre() + "\n";
    m_datos += "Telefono: " + m_cliente->telefono() + "\n";
    m_datos += "Email: " + m_cliente->email() + "\n";
    m_datos += "Direccion: " + m_cliente->direccion() + "\n";

    for(int i=0; i < 107; i++){
        m_datos += "-";
    }
    m_datos += "\n\t\tDATOS DE LA COMPRA\n";
    for(int i=0; i < 107; i++){
        m_datos += "-";
    }
    m_datos += "\n   Cant.      ||                   Descripcion                ||          P.Unitario          ||        Subtotal\n";

    foreach(Canasta *c, m_lista){
        float subto = c->pro()-> precio() * c->cantidad();
        m_subtotal += subto;
        for(int i=0; i<5; i++){
            m_datos += " ";
        }
        m_datos += "" + QString::number(c->cantidad());


        for(int i=0; i<25 - QString::number(c->cantidad()).size(); i++){
            m_datos += " ";
        }
        m_datos += "" + c->pro()->nombre();


        for(int i=0; i<54 - c->pro()->nombre().size(); i++){
            m_datos += " ";
        }
        m_datos += "" + QString::number(c->pro()->precio());


        for(int i=0; i<35 - QString::number(c->pro()->precio()).size(); i++){
            m_datos += " ";
        }
        m_datos += "" + QString::number(subto, 'f', 2);
        m_datos += "\n";
    }
    m_datos += "\n\n\n\n\n\n\n\n\n";
    m_IVA = m_subtotal * 0.12;
    m_total = m_IVA + m_subtotal;

    for(int i=0; i < 107; i++){
        m_datos += " ";
    }
    m_datos += "    Subtotal:    $ " + QString::number(m_subtotal, 'f', 2) + "\n";
    for(int i=0; i < 107; i++){
        m_datos += " ";
    }
    m_datos += "    IVA:           $ " + QString::number(m_IVA, 'f', 2) + "\n";
    for(int i=0; i < 107; i++){
        m_datos += " ";
    }
    m_datos += "    Total:         $ " + QString::number(m_total, 'f', 2) + "\n";

    ui->outFactura->setPlainText(m_datos);

}




