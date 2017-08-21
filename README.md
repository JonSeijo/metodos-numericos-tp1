# metodos-numericos-tp1
TP1 de metodos numericos

## INFORME

En el directorio principal, para compilar y ver el pdf resultante:
```
python makepdf.py
```
Puede pasarsele un parametro opcional P, numero de pagina en el cual queres que se abra el pdf (Util posta!).
Por ejemplo:

```
python makepdf.py --p=3
```

## Y ahora que?

```
Para un objeto fijo, por ejemplo "gato":

- Tomemos luces.txt como las direcciones de las luces. Mas adelante tenemos que ver como calcularlas nosotros mismos.

- Elegimos 3 figuras, digamos la 1, 2 y 3.


Para cada pixel:

    S = la matriz de luces, de 3x3

    I_i = El brillo de la imagen i en el pixel actual
    I = (I_1, I_2, I_3) vector brillo del pixel actual de las 3 imagens

    m = nuestra incognita, un vector de 3 coordenadas
        (m_i representa I0*p*n_i)

    Resolvemos el sistema  Sm = I

    n: vector normal, lo que queriamos calcular
    n = (m_1 / (I_0*p) , m_2 / (I_0*p), m_3 / (I_0*p))

    normalizar n

    Tarán!
    Ya tenemos las normales estimadas para el pixel actual
```