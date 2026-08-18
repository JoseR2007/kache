# Kache
Un sistema de memoria `key-value` inspirado en Redis.

Mediante `sockets` en `C`, se reciven solicitudes las cuales se aceptan y se procesan en hilos separado; Cada "cliente" puede enviar diferentes tipos de solicitudes que permiten hacer operaciones de `GET`, `DEL` y `SET`.

## Solictudes y formato
- `GET` format: `GET | key`: <br>
  Le dice a kache que busque un dato con dicha `key` si el dato existe kache response con su valor correspondiente, sino, devuelve con un mensaje que indica error `404: Not found` (el dato no fue encontrado).

  **Ejemplo de solicitudes y respuestas:** <br>
    Suponga los siguientes datos almacenados:

    | key | value |
    |-----|-------|
    | user1 | "jose" |
    | user2 | "manuel" |

    Enviado: `GET | user1` <br>
    Respuesta enviada por kache: `"jose"`

- `SET` format: `SET | key:value`: <br>
  Le dice a kache que guarde en memoria un dato con dicha `key` y dicho `value`, si existe kache reescribira el dato con el nuevo `value` enviado. <br>

  Si desea que kache NO sobreescriba el valor debe especificar con la bandera `-preserve` de modo que la solicitud quedaria asi:
  `SET | key:value -preserve`, kache respondera con un mensaje indicando que existe un dato con ese `value`.

  **Ejemplo de solicitudes y respuestas:** <br>
    Suponga los siguientes datos almacenados:

    | key | value |
    |-----|-------|
    | user1 | "jose" |
    | user2 | "manuel" |

    Enviado: `SET | user1:alonso` <br>
    Respuesta enviada por kache: `user1:jose -> alonso | true`

    Enviado: `SET | user3:alonso -preserve` <br>
    Respuesta enviada por kache: `user3 | true`
    *Dado que no existe un dato con `user3` como `key` kache crea un nuevo dato y responde con su `key` y su estado*. 

    **Usando** `-preserve`
    Enviado: `SET | user1:alonso -preserve` <br>
    Respuesta enviada por kache: `"jose"`

- `DEL` format: `DEL | key`: <br>
  Le dice a kache que elimine de la memoria el dato con dicha `key`, si existe, kache respondera con el antiguo valor del dato y una bandera que indica su eliminacion.

  **Ejemplos de solictudes y respuestas:** <br>
    Suponga los siguiente datos almacenados:

    | key | value |
    |-----|-------|
    | user1 | "jose" |
    | user2 | "manuel" |

    Enviado: `DET | user1` <br>
    Respuesta enviada por kache: `"jose" | removed`