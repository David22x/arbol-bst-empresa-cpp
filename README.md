# Árbol BST Empresarial en C++


## Integrante

David Mathias Cuenca Arévalo
---

## Objetivo

Implementar en C++ un Árbol Binario de Búsqueda (BST) para organizar empleados de una empresa, usando un **código numérico como clave**. Se identifican los conceptos de: raíz, niveles, nodos internos y hojas aplicados a un organigrama empresarial.

---

## Funcionalidades

-  Insertar empleados
-  Buscar empleado por código
-  Eliminar empleado
-  Mostrar raíz del árbol
-  Recorrido **Inorden** (ordenado ascendente)
-  Recorrido **Preorden** (raíz primero)
-  Recorrido **Postorden** (raíz último)
-  Calcular altura del árbol
-  Identificar y mostrar nodos hoja
-  Estadísticas del árbol (total nodos, internos, hojas)
-  Visualizar estructura del árbol en consola

---

## Estructura del repositorio

```
arbol-bst-empresa-cpp/
├── src/
│   └── main.cpp        # Código fuente principal
├── capturas/           # Capturas de ejecución
└── README.md           # Este archivo
```

---

## Compilar y ejecutar

**Linux / Mac:**
```bash
g++ src/main.cpp -o arbol
./arbol
```

**Windows:**
```bash
g++ src/main.cpp -o arbol.exe
arbol.exe
```

---

## Datos de prueba

Al ejecutar el programa, la opción **12** carga automáticamente el organigrama de ejemplo:

| Código | Nombre | Cargo |
|--------|--------|-------|
| 50 | Empresa UTA | Raíz |
| 30 | Gerente Ventas | Nodo interno |
| 70 | Gerente Finanzas | Nodo interno |
| 20 | Emp 1 | Hoja |
| 40 | Emp 2 | Hoja |
| 60 | Emp 3 | Hoja |
| 80 | Emp 4 | Hoja |

**Árbol resultante:**
```
+-- [50] Empresa UTA (Raiz)
    +-- [30] Gerente Ventas (Nodo interno)
    |   +-- [20] Emp 1 (Hoja)
    |   +-- [40] Emp 2 (Hoja)
    +-- [70] Gerente Finanzas (Nodo interno)
        +-- [60] Emp 3 (Hoja)
        +-- [80] Emp 4 (Hoja)
```

---

## Conceptos clave

| Término | Definición |
|---------|-----------|
| **Raíz** | Nodo principal del árbol, sin padre. En el ejemplo: código 50 |
| **Nodo interno** | Nodo que tiene al menos un hijo (ej: códigos 30 y 70) |
| **Hoja** | Nodo sin hijos, en el nivel más profundo (ej: 20, 40, 60, 80) |
| **Nivel** | Distancia de un nodo a la raíz. La raíz está en nivel 0 |
| **Altura** | Número de niveles del árbol. Este árbol tiene altura 3 |
| **BST** | En un BST, los nodos menores van a la izquierda y los mayores a la derecha |

---

## Capturas de ejecución


---

## Conclusión

El Árbol Binario de Búsqueda permite organizar información jerárquica de forma eficiente. Las operaciones de **inserción y búsqueda** tienen una complejidad de O(log n) en árboles balanceados, lo que lo hace ideal para representar estructuras como organigramas empresariales donde se necesita acceso rápido a los datos por clave numérica.
