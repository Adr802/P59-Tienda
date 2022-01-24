#include "cliente.h"

Cliente::Cliente(QObject *parent) : QObject(parent)
{

}

Cliente::Cliente(const QString &cedula, const QString &nombre, const QString &telefono, const QString &email, const QString &direccion, QObject *parent) : QObject(parent),
    m_cedula(cedula),
    m_nombre(nombre),
    m_telefono(telefono),
    m_email(email),
    m_direccion(direccion)
{}

const QString &Cliente::cedula() const
{
    return m_cedula;
}

void Cliente::setCedula(const QString &newCedula)
{
    m_cedula = newCedula;
}

const QString &Cliente::nombre() const
{
    return m_nombre;
}

const QString &Cliente::telefono() const
{
    return m_telefono;
}

const QString &Cliente::email() const
{
    return m_email;
}

const QString &Cliente::direccion() const
{
    return m_direccion;
}
