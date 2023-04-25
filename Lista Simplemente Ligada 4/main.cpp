#include <iostream>
#include <string>
using namespace std;

class SocioClub {
public:
    int NumeroSocio;
    std::string Nombre;
    std::string Domicilio;
    int AnoIngreso;
    SocioClub() = default;
    SocioClub(int numeroSocio, std::string nombre, std::string domicilio, int anoIngreso) {
        NumeroSocio = numeroSocio;
        Nombre = nombre;
        Domicilio = domicilio;
        AnoIngreso = anoIngreso;
    }

    bool operator==(const SocioClub& otro) const {
        return NumeroSocio == otro.NumeroSocio;
    }

    bool operator!=(const SocioClub& otro) const {
        return !(*this == otro);
    }

    bool operator<(const SocioClub& otro) const {
        return NumeroSocio < otro.NumeroSocio;
    }

    bool operator>(const SocioClub& otro) const {
        return otro < *this;
    }
};

template<class T>
class LSLSE;
template<class T>
class node{
private:
    T data;

public:
    node<T>* sig;
    node():sig(nullptr){};
    T getData() const { return data; }
    friend class LSLSE<T>;
};
template<class T>
class LSLSE{
private:
    node<T>* lista;
public:
    LSLSE():lista(nullptr){};
    bool vacia()const;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
    void imprimir()const;
};
template<class T>
void LSLSE<T>::imprimir()const{
    node<T>* aux=lista;
    while(aux!=nullptr){
        cout << "NumeroSocio: " << aux->getData().NumeroSocio << endl;
        cout << "Nombre: " << aux->getData().Nombre << endl;
        cout << "Domicilio: " << aux->getData().Domicilio << endl;
        cout << "AnoIngreso: " << aux->getData().AnoIngreso << endl << endl;
        aux=aux->sig;
    }
}
template<class T>
bool LSLSE<T>::eliminar(node<T>* pos){
    if(vacia() || pos==nullptr){
        return false;
        }
    if(pos==lista){
        lista=lista->sig;
    }
    else{
        anterior(pos)->sig=pos->sig;
    }
    delete pos;
    return true;
}
template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem){
    node<T>* aux= new node<T>;
    aux->data=elem;
    if(pos==nullptr){
        aux->sig=lista;
        lista=aux;
    }
    else{
        aux->sig=pos->sig;
        pos->sig=aux;
    }
}
template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos)const{
    if(vacia() || pos==nullptr){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux!=nullptr && aux->sig!=pos){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return lista;
}
template<class T>
node<T>* LSLSE<T>::ultimo()const{
    if(vacia()){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux->sig!=nullptr){
        aux=aux->sig;
    }
    return aux;
}
template<class T>
bool LSLSE<T>::vacia()const{
    if(lista==nullptr)
        return true;
    return false;
}

int main() {
    LSLSE<SocioClub> listaSocios;

    int opcion;
    do {
        cout << "Menu" << endl;
        cout << "1. Registrar un nuevo socio" << endl;
        cout << "2. Dar de baja un socio del club" << endl;
        cout << "3. Generar un reporte con los datos de todos los socios" << endl;
        cout << "4. Buscar por nombre y domicilio a un socio del club" << endl;
        cout << "5. Calcular e imprimir el total de socios registrados" << endl;
        cout << "6. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int numeroSocio;
                std::string nombre;
                std::string domicilio;
                int anoIngreso;

                cout << "Ingrese el numero de socio: ";
                cin >> numeroSocio;
                cout << "Ingrese el nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese el domicilio: ";
                getline(cin, domicilio);
                cout << "Ingrese el ano de ingreso: ";
                cin >> anoIngreso;

                listaSocios.insertar(nullptr, SocioClub(numeroSocio, nombre, domicilio, anoIngreso));
                break;
            }
            case 2: {
                int numeroSocio;
                cout << "Ingrese el número de socio a dar de baja: ";
                cin >> numeroSocio;
                node<SocioClub> *actual = listaSocios.primero();
                while (actual != nullptr) {
                    if (actual->getData().NumeroSocio == numeroSocio) {
                        listaSocios.eliminar(actual);
                        break; // Encontrado
                    }
                    actual = actual->sig; // Siguiente nodo
                }
                break;
            }
            case 3: {
                listaSocios.imprimir();
                break;
            }
            case 4: {
                std::string nombre;
                std::string domicilio;

                cout << "Ingrese el nombre del socio a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese el domicilio del socio a buscar: ";
                getline(cin, domicilio);

                node<SocioClub> *actual = listaSocios.primero();
                while (actual != nullptr) {
                    if (actual->getData().Nombre == nombre && actual->getData().Domicilio == domicilio) {
                        cout << "NumeroSocio: " << actual->getData().NumeroSocio << endl;
                        cout << "Nombre: " << actual->getData().Nombre << endl;
                        cout << "Domicilio: " << actual->getData().Domicilio << endl;
                        cout << "AnoIngreso: " << actual->getData().AnoIngreso << endl<<endl;

                        break; // Encontrado
                    }
                    actual = actual->sig; // Siguiente nodo
                }
                break;
            }
            case 5: {
                int total = 0;
                node<SocioClub> *actual = listaSocios.primero();
                while (actual != nullptr) {
                    total++;
                    actual = actual->sig;
                }
                cout << "Total de socios registrados: " << total << endl;
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}
