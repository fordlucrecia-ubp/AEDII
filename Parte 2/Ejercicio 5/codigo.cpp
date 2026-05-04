Se optó por implementar un algoritmo RSA para explicitar el paso a paso de cómo se cifra y descifra un mensaje concreto.
p (primo): 11
q (primo): 13
Mensaje: 7.

Cifrar:
Paso 1
Generación de claves
FUNCIÓN GenerarClaves(p, q):
  n ← p × q                // módulo público
  φ(n) ← (p−1) × (q−1)    // función de Euler
  e ← elegir tal que 1 < e < φ(n) y mcd(e, φ(n)) = 1
  d ← inverso modular de e mod φ(n)
  RETORNAR clave_publica=(e,n), clave_privada=(d,n)
p = 11, q = 13
n = p × q = 143
φ(n) = (11−1) × (13−1) = 120
e = 7  // mcd(7, 120) = 1 
d = 103  // inverso de 7 mod 120
Clave pública: (e=7, n=143)
Clave privada: (d=103, n=143)

Paso 2
Cifrado con clave pública
FUNCIÓN Cifrar(m, e, n):
  // Emisor usa clave pública (e, n)
  c ← me mod n
  RETORNAR c                 // mensaje cifrado
Mensaje original: m = 7
c = me mod n = 77 mod 143
c = 6  // mensaje cifrado (ilegible)

Paso 3
Descifrado con clave privada
FUNCIÓN Descifrar(c, d, n):
  // Receptor usa clave privada (d, n)
  m ← cd mod n
  RETORNAR m                 // mensaje original
Mensaje cifrado: c = 6
m = cd mod n = 6103 mod 143
m = 7  // mensaje recuperado

Paso 4
Verificación
Mensaje original: 7
Mensaje cifrado: 6
Mensaje descifrado: 7
Descifrado correcto. m original = m descifrado.

Código C++
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
 
// ─────────────────────────────────────────────
//  Funciones auxiliares
// ─────────────────────────────────────────────
 
// Máximo común divisor (algoritmo de Euclides)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}
 
// Exponenciación modular rápida: calcula (base^exp) mod m
// Evita desbordamiento operando en cada paso con el módulo
long long modpow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (__int128)result * base % mod;  // cast para evitar overflow
        exp = exp / 2;
        base = (__int128)base * base % mod;
    }
    return result;
}
 
// Inverso modular usando el algoritmo extendido de Euclides
// Calcula d tal que (e * d) ≡ 1 (mod phi)
long long modInverse(long long e, long long phi) {
    long long old_r = e,  r = phi;
    long long old_s = 1,  s = 0;
    while (r != 0) {
        long long q = old_r / r;
        long long temp = r;
        r = old_r - q * r;
        old_r = temp;
        temp = s;
        s = old_s - q * s;
        old_s = temp;
    }
    // Asegurar resultado positivo
    return (old_s % phi + phi) % phi;
}
 
// Verificación simple de primalidad
bool esPrimo(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}
 
// ─────────────────────────────────────────────
//  Estructura de claves RSA
// ─────────────────────────────────────────────
 
struct ClavePublica  { long long e, n; };
struct ClavePrivada  { long long d, n; };
 
struct ParDeClaves {
    ClavePublica  publica;
    ClavePrivada  privada;
    long long     phi;     // φ(n), expuesto solo para fines didácticos
};
 
// ─────────────────────────────────────────────
//  Paso 1 — Generación de claves
// ─────────────────────────────────────────────
//
//  Recibe dos números primos p y q distintos.
//  Calcula:
//    n   = p * q              (módulo público)
//    φ(n)= (p-1) * (q-1)     (función de Euler)
//    e   = exponente público  (coprimo con φ(n))
//    d   = inverso de e mod φ (exponente privado)
 
ParDeClaves generarClaves(long long p, long long q) {
    if (!esPrimo(p) || !esPrimo(q))
        throw std::invalid_argument("p y q deben ser numeros primos.");
    if (p == q)
        throw std::invalid_argument("p y q deben ser distintos.");
 
    long long n   = p * q;
    long long phi = (p - 1) * (q - 1);
 
    // Elegir e: entero en (1, φ) coprimo con φ
    // Se empieza en 3 y se avanza de 2 en 2 (solo impares)
    long long e = 3;
    while (e < phi && gcd(e, phi) != 1)
        e += 2;
 
    if (e >= phi)
        throw std::runtime_error("No se encontro un e valido para estos primos.");
 
    long long d = modInverse(e, phi);
 
    return { {e, n}, {d, n}, phi };
}
 
// ─────────────────────────────────────────────
//  Paso 2 — Cifrado
// ─────────────────────────────────────────────
//
//  El EMISOR aplica la clave pública (e, n) del receptor:
//    c = m^e mod n
//  El resultado c es el mensaje cifrado (ilegible sin d).
 
long long cifrar(long long m, ClavePublica pub) {
    if (m >= pub.n)
        throw std::invalid_argument("El mensaje debe ser menor que n.");
    return modpow(m, pub.e, pub.n);
}
 
// ─────────────────────────────────────────────
//  Paso 3 — Descifrado
// ─────────────────────────────────────────────
//
//  El RECEPTOR aplica su clave privada (d, n):
//    m = c^d mod n
//  Solo quien posee d puede recuperar el mensaje original.
 
long long descifrar(long long c, ClavePrivada priv) {
    return modpow(c, priv.d, priv.n);
}
 
// ─────────────────────────────────────────────
//  Programa principal — caso concreto
// ─────────────────────────────────────────────
 
int main() {
    std::cout << "====================================\n";
    std::cout << "   Implementacion RSA en C++\n";
    std::cout << "   Caso: mensajeria tipo Telegram\n";
    std::cout << "====================================\n\n";
 
    // Parámetros del ejemplo
    long long p = 11;   // primo 1
    long long q = 13;   // primo 2
    long long m = 7;    // mensaje a cifrar (debe ser < n = p*q)
 
    try {
        // ── Paso 1: Generar claves ──────────────────
        ParDeClaves claves = generarClaves(p, q);
 
        std::cout << "[Paso 1] Generacion de claves\n";
        std::cout << "  p        = " << p << "\n";
        std::cout << "  q        = " << q << "\n";
        std::cout << "  n = p*q  = " << claves.publica.n << "\n";
        std::cout << "  phi(n)   = " << claves.phi << "\n";
        std::cout << "  e        = " << claves.publica.e
                  << "  (mcd(e, phi) = "
                  << gcd(claves.publica.e, claves.phi) << ")\n";
        std::cout << "  d        = " << claves.privada.d << "\n";
        std::cout << "  Clave publica  -> (e=" << claves.publica.e
                  << ", n=" << claves.publica.n << ")\n";
        std::cout << "  Clave privada  -> (d=" << claves.privada.d
                  << ", n=" << claves.privada.n << ")\n\n";
 
        // ── Paso 2: Cifrado (emisor) ────────────────
        long long c = cifrar(m, claves.publica);
 
        std::cout << "[Paso 2] Cifrado (emisor usa clave publica)\n";
        std::cout << "  Mensaje original : m = " << m << "\n";
        std::cout << "  c = m^e mod n    = " << m << "^"
                  << claves.publica.e << " mod " << claves.publica.n
                  << " = " << c << "\n";
        std::cout << "  Mensaje cifrado  : c = " << c
                  << "  (ilegible sin clave privada)\n\n";
 
        // ── Paso 3: Descifrado (receptor) ──────────
        long long m_recuperado = descifrar(c, claves.privada);
 
        std::cout << "[Paso 3] Descifrado (receptor usa clave privada)\n";
        std::cout << "  Mensaje cifrado  : c = " << c << "\n";
        std::cout << "  m = c^d mod n    = " << c << "^"
                  << claves.privada.d << " mod " << claves.privada.n
                  << " = " << m_recuperado << "\n";
        std::cout << "  Mensaje descifrado: m = " << m_recuperado << "\n\n";
 
        // ── Paso 4: Verificación ────────────────────
        std::cout << "[Paso 4] Verificacion\n";
        if (m == m_recuperado)
            std::cout << "  OK: mensaje original (" << m
                      << ") == mensaje descifrado (" << m_recuperado << ")\n";
        else
            std::cout << "  ERROR: los mensajes no coinciden.\n";
 
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
 
    std::cout << "\n====================================\n";
    return 0;
}

