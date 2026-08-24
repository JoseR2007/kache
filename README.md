# Kache
Un sistema de memoria `key-value` inspirado en Redis.

Mediante `sockets` en `C`, se reciven solicitudes las cuales se aceptan y se procesan en hilos separado; Cada "cliente" puede enviar diferentes tipos de solicitudes que permiten hacer operaciones de `GET`, `DEL`, `SET` y `SAV`.

## Solictudes y formato
Todas las solictudes estan compuestas por una estrctura familiar que contienen, separadores y un terminador. <br/>
- **Separadores:** `/r/n` <br/>
- **Terminacion:** `/r/c`

**Ejemplo con una solicitud** `GET` <br/>
`GET /r/n:5:"holaa"/r/c` <br/>

En este ejemplo, el numero 5 indica la longitud de la `key` que se recibio.
Tanto el metodo `GET` como el metodo `DEL` reciben unicamente la `key` de la elemento `key-value` que se quiere eliminar o obtener. <br/>

**Para los siguientes ejemplos suponga la siguiente tabla de datos:** <br>

| key | value |
|-----|-------|
|passw|1235   |
|p1   |jose   |

- ## Solicitud `GET` y formato <br />
  La solicitud `GET` le dice a kache que busque y devuelva el elemento con la `key` correspondiente. <br/>

  **Ejemplo de solicitud y salida:** <br/>
    Solicitud recibida: `GET /r/n:5:"passw"/r/c` <br/>
    Kache responderia con: `1235`

  *Kache siempre devuelve los valores como string*, y es trabajo del cliente convertirlos a numero, si de eso se tratan.

- ## Solicitud `DEL` y formato <br/>
  La solicitud `DEL` le dice a kache que busque y elimine el elemento con la `key` correspondiente. <br/>

  Cuando se recibe la solicitud pueden pasar una de dos cosas: <br/>
  1. El elemento no existe o no fue encontrado. *kache devuelve*: `404: Not found`. <br/>
  2. El elemento se elimino correctamente. *kache devuelve*: la key del elemento eliminado.

  **Ejemplo de solicitud y salida:**  <br/>
    Solicitud recibida: `DEL /r/n:5:"passw"/r/c` <br/>
    Kache responderia con: `passw` <br/>

- ## Solicitud `SET` y formato <br/>
  La solicitud `SET` le dice a kache que busque y establezca el valor del elemento asociado a la `key` recivida con el nuevo `value` recibido.

  **Ejemplo de solicitud y salida:** <br/>
    Solicitud recibida: `SET /r/n:5:"passw"/r/n:6:"123456"/r/c` <br/>
    Kache responderia con: `passw` <br/>

  Como sí existe un elemento con dicho `key` lo encuentra, lo cambia y devuelve su `key` como confirmacion. <br/>
  Si el elemento no existiera kache devolveria `404: Not found`. <br/>

- ## Solicitud `SAV` y formato <br/>
  La solicitud `SAV` le dice a kache que guarde un nuevo elemento con dicha `key` y dicha `value`. <br/>

  **Ejemplo de solicitud y salida:** <br/>
    Solicitud recibida: `SAV /r/n:6:"passw1"/r/n:6:"124223"/r/c` <br/>
    Kache responderia con: `passw1` <br/>

  Como no existe otro elemento con esa kache lo agrega a memoria y devuelve su `key` como confirmacion. <br/>