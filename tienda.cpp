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

/**
 * @brief Tienda::calcular   Calculo del subtotal, y lo muestra en pantalla
 * @param stProducto         Subtotal de cada producto
 */
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

/**
 * @brief Tienda::validarCed     Valida si una cedula es correcta
 * @param as                     Recibe un QStrig que contiene la cedula
 * @return                       Retorna true or false depending on the result
 */

bool Tienda::validarCed(QString as)
{
    //bool est = true;
    int vcedula[10];
    int vPar[4];
    int vImpar[5]={0};
    int sumaPar=0;
    int sumaImpar=0;
    int total;
    int nveri;

    double nu;


    do
    {

        //Convertir a un numero
        nu = as.toDouble();
        //istringstream(as)>>nu;

        if(nu<100000000 || nu>9999999999)
        {
            return false;
            break;
        }


        //Separar string

        QString p1 = as.mid(0,1);
        QString p2 = as.mid(1,1);
        QString p3 = as.mid(2,1);
        QString p4 = as.mid(3,1);
        QString p5 = as.mid(4,1);
        QString p6 = as.mid(5,1);
        QString p7 = as.mid(6,1);
        QString p8 = as.mid(7,1);
        QString p9 = as.mid(8,1);
        QString p10 = as.mid(9,1);

        //Transformar string
        vcedula[0] = p1.toInt();
        vcedula[1] = p2.toInt();
        vcedula[2] = p3.toInt();
        vcedula[3] = p4.toInt();
        vcedula[4] = p5.toInt();
        vcedula[5] = p6.toInt();
        vcedula[6] = p7.toInt();
        vcedula[7] = p8.toInt();
        vcedula[8] = p9.toInt();
        vcedula[9] = p10.toInt();

        if(vcedula[0]>2)
        {
            return false;
            break;
        }

        //Pares
        vPar[0]=vcedula[1];
        vPar[1]=vcedula[3];
        vPar[2]=vcedula[5];
        vPar[3]=vcedula[7];
        //Impares
        vImpar[0]=vcedula[0];
        vImpar[1]=vcedula[2];
        vImpar[2]=vcedula[4];
        vImpar[3]=vcedula[6];
        vImpar[4]=vcedula[8];


        //Punto 2. Multiplicacion impar
        for(int i=0; i<5; i++)
        {
            vImpar[i]=vImpar[i]*2;
            if(vImpar[i]>9)
            {
                vImpar[i]=vImpar[i]-9;
            }
            sumaImpar += vImpar[i];
        }
        //Punto 3. Sumar los pares
        for(int i=0; i<4; i++)
        {
            sumaPar += vPar[i];
        }

        total = sumaPar + sumaImpar;

        //Punto 4. Se obtiene el modulo;

        nveri = total%10;


        //Punto 5. Numero verificador
        if(nveri==0)
        {
            if(nveri==vcedula[9])
            {
                return true;
                break;
            }else
            {
                return true;
                break;
            }
        }else if(nveri !=0)
        {
            nveri=10-nveri;

            if(nveri==vcedula[9])
            {
                return true;
                break;
            }else
            {

                return true;
                break;
            }
        }

    }while(nu<100000000 || nu>9999999999 || vcedula[0]>2);
    return true;;

}

/**
 * @brief Tienda::validarCanasta   Valida si un producto ya esta dentro de la tabla
 * @param p                        Recibe un objetc "Producto"
 * @return                         Return true(the product is in the table) or false (the product isn´t in the table)
 */
bool Tienda::validarCanasta(Producto *p)
{
    foreach(Canasta *c, m_canasta){
        if(c->pro()->codigo() == p->codigo()){
            return true;
        }
    }
    return false;
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

    //Si no esta en la canasta(tabla)
    if(!validarCanasta(p)){
        m_canasta.append(new Canasta(p,cantidad));
        //Calcular subtotal del producto
        float subTotal = p->precio() * cantidad;
        //Agregar datos a la tabla
        int fila = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(fila);
        ui->tableWidget->setItem(fila, 0, new QTableWidgetItem(QString::number(m_canasta.at(i)->cantidad())));
        ui->tableWidget->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
        ui->tableWidget->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(),'f',2)));
        ui->tableWidget->setItem(fila, 3, new QTableWidgetItem(QString::number(subTotal,'f',2)));


        //Limpiar datos
        ui->inCantidad->setValue(0);
        ui->inProducto->setFocus();

        //Actualizar subtotales
        calcular(subTotal);

    }else{

        int i=0;
        foreach(Canasta *c, m_canasta){
            if(c->pro()->codigo() == p->codigo()){
                c->setCantidad(cantidad);
                //int canTemp = ui->tableWidget->takeItem(i,0);
               // ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(canTemp + c->cantidad())));
                float subTotal = p->precio() * cantidad;

                //Limpiar datos
                ui->inCantidad->setValue(0);
                ui->inProducto->setFocus();

                //Vuelve a calcular el subtotal
                calcular(subTotal);
                break;
            }
            i++;
        }

    }









    QString a = ui->inCedula->text();

    if(validarCed(a)){
        qDebug() << "hola";
    }else{
        ui->inCedula->setStyleSheet("background-color: rgb(217, 72, 72);");
    }

}


void Tienda::on_pushButton_released()
{

}

