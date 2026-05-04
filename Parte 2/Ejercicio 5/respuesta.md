![descripcion](imagenes/ej5.png)


a) Para pensar la aplicación real de un algoritmo que cumpla pautas de cifrado y seguridad, se propone tomar la aplicación de comunicación instantánea Telegram. En este tipo de sistemas, la prioridad es garantizar que los mensajes enviados entre dos usuarios no puedan ser leídos por terceros no autorizados. Aquí entra en juego el algoritmo RSA, que es un algoritmo de cifrado asimétrico: utiliza una clave pública para cifrar y una clave privada para descifrar, basándose en propiedades matemáticas de los números primos.
Telegram implementa RSA de 2048 bits como parte de su protocolo de seguridad MTProto. En este esquema, RSA no cifra el contenido del mensaje directamente, sino que cumple una función igualmente crítica: proteger el intercambio inicial de claves entre el cliente y el servidor. Es decir, RSA garantiza que las claves de sesión que luego cifrarán los mensajes lleguen al destinatario correcto sin haber sido comprometidas en tránsito. De esta manera, incluso si alguien intercepta la comunicación, no podrá obtener las claves necesarias para descifrar los mensajes.
La elección de RSA se fundamenta en tres aspectos clave. En primer lugar, resguarda la confidencialidad, asegurando que sólo el destinatario pueda acceder a la información cifrada. En segundo lugar, garantiza autenticidad mediante firmas digitales, siendo así posible verificar que el mensaje realmente proviene del remitente declarado y no de un impostor. En tercer lugar, provee escalabilidad, ya que el esquema de claves públicas y privadas resulta viable en sistemas de mensajería con millones de usuarios simultáneos.
En comparación, algoritmos más simples como el cifrado César no serían adecuados porque son triviales de romper con técnicas básicas de análisis de frecuencia. RSA, en cambio, se basa en la dificultad matemática de factorizar números grandes, lo que lo hace resistente frente a ataques computacionales convencionales.
En síntesis, Telegram ilustra cómo RSA puede aplicarse en un sistema de mensajería masiva para cubrir las necesidades críticas de seguridad en la comunicación digital: confidencialidad en el intercambio de claves, autenticidad del origen y capacidad de escalar a grandes volúmenes de usuarios.

b) Se optó por implementar un algoritmo RSA para explicitar el paso a paso de cómo se cifra y descifra un mensaje concreto.
p (primo): 11
q (primo): 13
Mensaje: 7.

(VER CÓDIGO)

 c) Mejoras sugeridas por la ChatGPT frente a la consigna:
“Con mi producción adjunta responde si se considera posible una mejora del código presentado con fines de que sea funcional e implementable para resolver un problema concreto.

Respuesta:
Revisión y posible mejora del código presentado

El código desarrollado en C++ implementa correctamente el algoritmo de cifrado RSA, permitiendo demostrar de forma práctica y didáctica el proceso completo de generación de claves, cifrado, descifrado y verificación de un mensaje concreto. La estructura es clara, modular y funcional, ya que separa cada responsabilidad en funciones específicas como gcd, modpow, modInverse, cifrar y descifrar, lo que mejora la legibilidad y facilita el mantenimiento.

Como aspecto positivo, se destaca el uso de la exponenciación modular rápida, ya que optimiza el cálculo de potencias grandes y reduce el riesgo de desbordamiento al aplicar el módulo en cada iteración. Además, la validación de que p y q sean números primos y distintos fortalece la robustez del programa y evita errores conceptuales en la generación de claves.

Sin embargo, se identifican algunas oportunidades de mejora para convertirlo en una solución más implementable en un entorno real. Por ejemplo, actualmente los valores de p, q y el mensaje m están definidos manualmente dentro del código; una mejora sería permitir el ingreso dinámico de datos por teclado para hacerlo más interactivo y reutilizable. También podría mejorarse la función esPrimo(), ya que utiliza una verificación básica que resulta ineficiente con números grandes; en aplicaciones reales se emplean algoritmos más avanzados como Miller-Rabin.

Otra mejora importante sería permitir el cifrado de cadenas de texto completas en lugar de un único número, transformando cada carácter a su valor ASCII antes del cifrado. Esto acercaría la implementación a un caso real de mensajería, como el ejemplo planteado tipo Telegram. Asimismo, para aumentar la seguridad, podrían utilizarse tipos de datos más grandes o bibliotecas especializadas en criptografía, ya que long long limita el tamaño de las claves.

En conclusión, el código presentado cumple correctamente con el objetivo didáctico de mostrar cómo RSA resuelve el problema concreto de cifrar y descifrar un mensaje. Con pequeñas mejoras en la entrada de datos, eficiencia, escalabilidad y seguridad, podría evolucionar hacia una implementación más realista y profesional.

Opinión personal crítica
Considerando las sugerencias de mejora propuestas son válidas porque apuntan a transformar una implementación académica en una solución más cercana a un entorno profesional. Por ejemplo, permitir el ingreso dinámico de datos, cifrar cadenas completas o utilizar algoritmos de primalidad más eficientes aumentaría la escalabilidad, flexibilidad y realismo del programa. Además, incorporar bibliotecas criptográficas especializadas fortalecería la seguridad y alinearía la implementación con estándares actuales.
Sin embargo, también es importante cuestionar si todas estas mejoras son realmente oportunas para el objetivo concreto del caso presentado. En este contexto, el propósito principal no es desarrollar un sistema de mensajería real ni una aplicación criptográfica de nivel industrial, sino demostrar de manera clara y comprensible el funcionamiento interno del algoritmo RSA. Agregar demasiada complejidad podría dificultar la comprensión, desviar la atención del aprendizaje conceptual y volver menos transparente el paso a paso del proceso de cifrado y descifrado.
Por lo tanto, la decisión más adecuada sería adoptar una postura intermedia, manteniendo la implementación actual como base didáctica, ya que cumple correctamente con su finalidad educativa; y a su vez incorporar mejoras puntuales que no comprometan la claridad del código, como permitir entrada por teclado o aceptar mensajes algo más amplios. En cambio, optimizaciones avanzadas o mecanismos de seguridad robustos deberían reservarse para una segunda etapa, orientada a una implementación real. De esta manera, se equilibra la simplicidad pedagógica con la posibilidad de evolución futura.
