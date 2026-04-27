#include <iostream>
#include <string>
using namespace std;

// =============================================
//  ESTRUCTURA DE DATOS - Árbol BST Empresarial
//  Guía práctica: Organigrama con BST en C++
// =============================================

struct Empleado {
    int    codigo;
    string nombre;
    string cargo;
};

struct Nodo {
    Empleado dato;
    Nodo*    izquierdo;
    Nodo*    derecho;

    Nodo(Empleado emp) {
        dato       = emp;
        izquierdo  = nullptr;
        derecho    = nullptr;
    }
};

class ArbolBST {
private:
    Nodo* raiz;

    // ── Insertar ──────────────────────────────
    Nodo* insertar(Nodo* nodo, Empleado emp) {
        if (nodo == nullptr)
            return new Nodo(emp);

        if (emp.codigo < nodo->dato.codigo)
            nodo->izquierdo = insertar(nodo->izquierdo, emp);
        else if (emp.codigo > nodo->dato.codigo)
            nodo->derecho = insertar(nodo->derecho, emp);
        else
            cout << "  [!] El codigo " << emp.codigo << " ya existe en el arbol.\n";

        return nodo;
    }

    // ── Buscar ────────────────────────────────
    Nodo* buscar(Nodo* nodo, int codigo) {
        if (nodo == nullptr || nodo->dato.codigo == codigo)
            return nodo;

        if (codigo < nodo->dato.codigo)
            return buscar(nodo->izquierdo, codigo);
        else
            return buscar(nodo->derecho, codigo);
    }

    // ── Nodo con valor mínimo (usado en eliminar) ──
    Nodo* minimoNodo(Nodo* nodo) {
        while (nodo->izquierdo != nullptr)
            nodo = nodo->izquierdo;
        return nodo;
    }

    // ── Eliminar ──────────────────────────────
    Nodo* eliminar(Nodo* nodo, int codigo) {
        if (nodo == nullptr) {
            cout << "  [!] Codigo no encontrado.\n";
            return nodo;
        }

        if (codigo < nodo->dato.codigo) {
            nodo->izquierdo = eliminar(nodo->izquierdo, codigo);
        } else if (codigo > nodo->dato.codigo) {
            nodo->derecho = eliminar(nodo->derecho, codigo);
        } else {
            // Nodo encontrado
            if (nodo->izquierdo == nullptr) {
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            } else if (nodo->derecho == nullptr) {
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            // Nodo con dos hijos: reemplazar con sucesor inorden
            Nodo* sucesor = minimoNodo(nodo->derecho);
            nodo->dato    = sucesor->dato;
            nodo->derecho = eliminar(nodo->derecho, sucesor->dato.codigo);
        }
        return nodo;
    }

    // ── Recorridos ────────────────────────────
    void inorden(Nodo* nodo) {
        if (nodo != nullptr) {
            inorden(nodo->izquierdo);
            mostrarEmpleado(nodo);
            inorden(nodo->derecho);
        }
    }

    void preorden(Nodo* nodo) {
        if (nodo != nullptr) {
            mostrarEmpleado(nodo);
            preorden(nodo->izquierdo);
            preorden(nodo->derecho);
        }
    }

    void postorden(Nodo* nodo) {
        if (nodo != nullptr) {
            postorden(nodo->izquierdo);
            postorden(nodo->derecho);
            mostrarEmpleado(nodo);
        }
    }

    // ── Altura ────────────────────────────────
    int altura(Nodo* nodo) {
        if (nodo == nullptr) return 0;
        int altIzq = altura(nodo->izquierdo);
        int altDer = altura(nodo->derecho);
        return 1 + max(altIzq, altDer);
    }

    // ── Hojas ─────────────────────────────────
    void mostrarHojas(Nodo* nodo) {
        if (nodo != nullptr) {
            if (nodo->izquierdo == nullptr && nodo->derecho == nullptr)
                mostrarEmpleado(nodo);
            mostrarHojas(nodo->izquierdo);
            mostrarHojas(nodo->derecho);
        }
    }

    // ── Contar nodos ──────────────────────────
    int contarNodos(Nodo* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
    }

    // ── Contar hojas ──────────────────────────
    int contarHojas(Nodo* nodo) {
        if (nodo == nullptr) return 0;
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) return 1;
        return contarHojas(nodo->izquierdo) + contarHojas(nodo->derecho);
    }

    // ── Mostrar empleado formateado ───────────
    void mostrarEmpleado(Nodo* nodo) {
        cout << "  Codigo: " << nodo->dato.codigo
             << " | Nombre: " << nodo->dato.nombre
             << " | Cargo: "  << nodo->dato.cargo << "\n";
    }

    // ── Mostrar árbol visual (lateral) ────────
    void mostrarArbol(Nodo* nodo, string prefijo, bool esUltimo) {
        if (nodo != nullptr) {
            cout << prefijo;
            cout << (esUltimo ? "+-- " : "+-- ");
            cout << "[" << nodo->dato.codigo << "] "
                 << nodo->dato.nombre << " (" << nodo->dato.cargo << ")\n";
            string nuevoPrefijo = prefijo + (esUltimo ? "    " : "|   ");
            if (nodo->izquierdo != nullptr || nodo->derecho != nullptr) {
                if (nodo->izquierdo != nullptr)
                    mostrarArbol(nodo->izquierdo, nuevoPrefijo,
                                 nodo->derecho == nullptr);
                if (nodo->derecho != nullptr)
                    mostrarArbol(nodo->derecho, nuevoPrefijo, true);
            }
        }
    }

public:
    ArbolBST() : raiz(nullptr) {}

    // ── API pública ───────────────────────────
    void insertarEmpleado(Empleado emp) {
        raiz = insertar(raiz, emp);
    }

    void eliminarEmpleado(int codigo) {
        raiz = eliminar(raiz, codigo);
    }

    void buscarEmpleado(int codigo) {
        Nodo* res = buscar(raiz, codigo);
        if (res != nullptr) {
            cout << "\n  Empleado encontrado:\n";
            mostrarEmpleado(res);
        } else {
            cout << "\n  Empleado con codigo " << codigo << " no encontrado.\n";
        }
    }

    void mostrarRaiz() {
        if (raiz != nullptr) {
            cout << "\n  Raiz del arbol:\n";
            mostrarEmpleado(raiz);
        } else {
            cout << "  El arbol esta vacio.\n";
        }
    }

    void mostrarInorden()   { cout << "\n  Recorrido Inorden (ordenado):\n";   inorden(raiz);   }
    void mostrarPreorden()  { cout << "\n  Recorrido Preorden (raiz primero):\n"; preorden(raiz); }
    void mostrarPostorden() { cout << "\n  Recorrido Postorden (raiz ultimo):\n"; postorden(raiz); }

    void mostrarAltura() {
        cout << "\n  Altura del arbol: " << altura(raiz) << " nivel(es)\n";
    }

    void mostrarNodosHoja() {
        cout << "\n  Nodos hoja (sin hijos):\n";
        mostrarHojas(raiz);
    }

    void mostrarEstadisticas() {
        int total = contarNodos(raiz);
        int hojas = contarHojas(raiz);
        cout << "\n  === Estadisticas del Arbol ===\n";
        cout << "  Total de nodos  : " << total << "\n";
        cout << "  Nodos hoja      : " << hojas << "\n";
        cout << "  Nodos internos  : " << total - hojas << "\n";
        cout << "  Altura          : " << altura(raiz) << "\n";
    }

    void mostrarEstructura() {
        cout << "\n  === Estructura del Arbol ===\n";
        if (raiz == nullptr)
            cout << "  (arbol vacio)\n";
        else
            mostrarArbol(raiz, "  ", true);
    }

    bool estaVacio() { return raiz == nullptr; }
};

// ── Utilidad: limpiar buffer de entrada ───────
void limpiarBuffer() {
    cin.ignore(1000, '\n');
}

// ── Cargar datos de prueba de la guía ─────────
void cargarDatosPrueba(ArbolBST& arbol) {
    Empleado prueba[] = {
        {50, "Empresa UTA",      "Raiz"},
        {30, "Gerente Ventas",   "Nodo interno"},
        {70, "Gerente Finanzas", "Nodo interno"},
        {20, "Emp 1",            "Hoja"},
        {40, "Emp 2",            "Hoja"},
        {60, "Emp 3",            "Hoja"},
        {80, "Emp 4",            "Hoja"}
    };
    for (auto& e : prueba)
        arbol.insertarEmpleado(e);
    cout << "  [OK] 7 empleados de prueba cargados.\n";
}

// ═══════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════
int main() {
    ArbolBST arbol;
    int opcion;

    cout << "========================================\n";
    cout << "   ARBOL BST EMPRESARIAL - C++\n";
    cout << "   Estructura de Datos\n";
    cout << "========================================\n";

    do {
        cout << "\n===== MENU ARBOL BST EMPRESARIAL =====\n";
        cout << " 1.  Insertar empleado\n";
        cout << " 2.  Buscar empleado\n";
        cout << " 3.  Eliminar empleado\n";
        cout << " 4.  Mostrar raiz\n";
        cout << " 5.  Recorrido inorden\n";
        cout << " 6.  Recorrido preorden\n";
        cout << " 7.  Recorrido postorden\n";
        cout << " 8.  Mostrar altura\n";
        cout << " 9.  Mostrar nodos hoja\n";
        cout << " 10. Estadisticas del arbol\n";
        cout << " 11. Visualizar estructura del arbol\n";
        cout << " 12. Cargar datos de prueba (guia)\n";
        cout << " 0.  Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Empleado emp;
                cout << "  Codigo : "; cin >> emp.codigo;
                limpiarBuffer();
                cout << "  Nombre : "; getline(cin, emp.nombre);
                cout << "  Cargo  : "; getline(cin, emp.cargo);
                arbol.insertarEmpleado(emp);
                cout << "  [OK] Empleado insertado.\n";
                break;
            }
            case 2: {
                int cod;
                cout << "  Codigo a buscar: "; cin >> cod;
                arbol.buscarEmpleado(cod);
                break;
            }
            case 3: {
                if (arbol.estaVacio()) {
                    cout << "  El arbol esta vacio.\n"; break;
                }
                int cod;
                cout << "  Codigo a eliminar: "; cin >> cod;
                arbol.eliminarEmpleado(cod);
                cout << "  [OK] Operacion de eliminacion completada.\n";
                break;
            }
            case 4:  arbol.mostrarRaiz();        break;
            case 5:  arbol.mostrarInorden();     break;
            case 6:  arbol.mostrarPreorden();    break;
            case 7:  arbol.mostrarPostorden();   break;
            case 8:  arbol.mostrarAltura();      break;
            case 9:  arbol.mostrarNodosHoja();   break;
            case 10: arbol.mostrarEstadisticas(); break;
            case 11: arbol.mostrarEstructura();  break;
            case 12: cargarDatosPrueba(arbol);   break;
            case 0:  cout << "\n  Hasta luego!\n"; break;
            default: cout << "  Opcion invalida. Intente de nuevo.\n";
        }

    } while (opcion != 0);

    return 0;
}
