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

## Compilacion y ejecucion

Hay un Makefile naive que deberia bastar por ahora.

```
make && ./main
```


## Y ahora que?

```
- Necesitamos pensar bien el calculo de profundidaes

- Necesitamos plantear las super ecuaciones y resolverlas

- Tenemos el tip de que son bandas, asi que hay que ver eso sino seguro son super grandes e ineficientes

- Informe: mas sobre el desarrollo

- Experimentacion: (nos faltan ideas)

    : Ver graficos de normales con diferentes luces

    : Ver resultados finales con diferentes luces
    
    : Comparaciones con mismas luces pero nuestras vs catedra
    
    : Tiempos, gauss vs lu sin usar mascara
    
    : Tiempos, gauss vs lu usando mascara
    
    : Algo con cholesky
    
    : Comparaciones haciendo con vs sin pivoteo por los errores numericos
    
    
- Informe: conclusiones
```
