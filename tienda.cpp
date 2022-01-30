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
    ui->inCedula->setFocus();
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
    bool est = true;
    int vcedula[10];
    int vPar[4];
    int vImpar[5]={0};
    int sumaPar=0;
    int sumaImpar=0;
    int total;
    int nveri;

    double nu;

    if(as=="9999999999"){
        return true;
    }

    do
    {

        nu=as.toInt();
        if(nu<100000000 || nu>9999999999)
        {

            est=false;
            break;
        }


        //Separar string
        QString p1=as.mid(0,1);
        QString p2=as.mid(1,1);
        QString p3=as.mid(2,1);
        QString p4=as.mid(3,1);
        QString p5=as.mid(4,1);
        QString p6=as.mid(5,1);
        QString p7=as.mid(6,1);
        QString p8=as.mid(7,1);
        QString p9=as.mid(8,1);
        QString p10=as.mid(9,1);

        //Transformar string
        vcedula[0]=p1.toInt();
        vcedula[1]=p2.toInt();
        vcedula[2]=p3.toInt();
        vcedula[3]=p4.toInt();
        vcedula[4]=p5.toInt();
        vcedula[5]=p6.toInt();
        vcedula[6]=p7.toInt();
        vcedula[7]=p8.toInt();
        vcedula[8]=p9.toInt();
        vcedula[9]=p10.toInt();

        if(vcedula[0]>2)
        {

            est = false;
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
                est=true;
                break;
            }else
            {
                est=false;
                break;
            }
        }else if(nveri !=0)
        {
            nveri=10-nveri;

            if(nveri==vcedula[9])
            {
                est=true;
                break;
            }else
            {

                est=false;
                break;
            }
        }

    }while(nu<100000000 || nu>9999999999 || vcedula[0]>2);
    return est;

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

bool Tienda::validarUsuario()
{
    bool flag = false;
    QString ced = ui->inCedula->text();


    //Validar si la cedula es consumidor final
    if(ced == "9999999999"){
        m_cliente = new Cliente(ced,".",".",".",".");
        return true;
    }


    //Validar campos vacios
    if(ui->inCedula->text() == ""){
        flag = true;
        ui->inCedula->setStyleSheet("background-color: rgb(217, 72, 72);");

    }
    if(ui->inNombre->text() == ""){
        flag = true;
        ui->inNombre->setStyleSheet("background-color: rgb(217, 72, 72);");
    }
    if(ui->inEmail->text() == ""){
        flag = true;
        ui->inEmail->setStyleSheet("background-color: rgb(217, 72, 72);");
    }
    if(ui->inTelefono->text() == ""){
        flag = true;
        ui->inTelefono->setStyleSheet("background-color: rgb(217, 72, 72);");
    }

    if(flag){ //Si se encontro un error con campos vacios
        ui->statusbar->showMessage("Campos vacios",4000);
        return false;
    }


    //Validar cedula
    if(validarCed(ced)){
        QString nombre = ui->inNombre->text();
        QString email = ui->inEmail->text();
        QString telefono = ui->inTelefono->text();
        m_cliente = new Cliente(ced,nombre,telefono,email,"Ave");
        return true;

    }else{
        ui->inCedula->setStyleSheet("background-color: rgb(217, 72, 72);");
        ui->statusbar->showMessage("Cedula incorrecta",4000);
        return false;
    }

    return true;
}

void Tienda::limpiar()
{
    ui->inCedula->clear();
    ui->inNombre->clear();
    ui->inEmail->clear();
    ui->inTelefono->clear();
    ui->inDireccion->clear();
    //Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    int fila = ui->tableWidget->rowCount();
    for(int i=0; i <= fila;){
        ui->tableWidget->removeRow(fila);
        fila--;
    }


    ui->inCedula->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->inNombre->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->inEmail->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->inTelefono->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->inDireccion->setStyleSheet("background-color: rgb(255, 255, 255);");

    m_subtotal = 0;
    m_totalCompras = 0;
    ui->outSubTotal->setText("$ 0.0");
    ui->outIVA->setText("$ 0.0");
    ui->outTotal->setText("$ 0.0");


    m_canasta.clear();
    delete m_cliente;
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
    m_totalCompras++;
    Producto *p = m_productos.at(i);

    //Si no esta en la canasta(tabla)
    if(!validarCanasta(p)){
        m_canasta.append(new Canasta(p,cantidad));

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
        return;
    }else{

        int i=0;
        foreach(Canasta *c, m_canasta){
            if(c->pro()->codigo() == p->codigo()){

                float precioAntiguo = m_canasta.at(i)->cantidad() * p->precio(); //Obtener el subtotal antiguo


                int canAnti = m_canasta.at(i)->cantidad(); //Obtener la cantidad que ya estaba en la canasta
                c->setCantidad(cantidad + canAnti);    //Setear laa nueva cantidad con la que ya habia mas la nueva

                ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(c->cantidad())));   //Setear la nueva cantidad en pantalla


                float subTotal = p->precio() * cantidad;  //Calcula el subtotal de la nueva cantidad

                float subTotalUnitario = precioAntiguo + subTotal;   //Calcular el nuevo subtotal unitario
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(subTotalUnitario)));  //Mostrar el nuevo subtotal unitario



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

}


void Tienda::on_pushButton_released()
{


    if(validarUsuario() && m_totalCompras != 0){
        ui->inCedula->setStyleSheet("background-color: rgb(159, 255, 162);");
        ui->inNombre->setStyleSheet("background-color: rgb(159, 255, 162);");
        ui->inEmail->setStyleSheet("background-color: rgb(159, 255, 162);");
        ui->inTelefono->setStyleSheet("background-color: rgb(159, 255, 162);");
        ui->inDireccion->setStyleSheet("background-color: rgb(159, 255, 162);");

        Factura p;
        p.setCliente(m_cliente);
        p.setLista(m_canasta);
        p.armarString();
        p.exec();

        limpiar();

    }else{
        if(m_totalCompras == 0)
            ui->statusbar->showMessage("No hay compras",5000);
        return;
    }

}


