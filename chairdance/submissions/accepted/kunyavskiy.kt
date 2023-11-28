tailrec fun gcd(a: Int, b: Int): Int = if (b == 0) a else gcd(b, a % b)

fun gcdex(a: Int, b: Int) : Pair<Int, Int> {
    if (b == 0) {
        return 1 to 0
    }
    // b * x + (a - [a/b] * b) * y = 1
    val (x, y) = gcdex(b, a % b)
    return y to (x - (a / b) * y)
}

fun inverse(a: Int, n: Int) = gcdex(a, n).first.let { ((it + n) % n + n) % n }

fun main() {
    System.setIn(System.`in`.buffered())
    val (n, q) = readInts()
    var cur = IntArray(n) { it }
    cur[0] = n
    var g = 1
    var a = 1
    var ai = 1
    var b = 0
    for(qid in 0 until q) {
        val (ty, x) = readStrings()
        fun get(x: Int, b:Int, ai: Int, g: Int) : Int {
            val rb = (x - b + n) % n
            return if (rb % g != 0) {
                -1
            } else {
                cur[((rb.toLong() / g * ai) % (n / g)).toInt()]
            }
        }
        when (ty) {
            "*" -> {
                val v = x.toInt()
                val ng = gcd(mul(a, v, n), n)
                if (g != ng) {
                    val merged = cur.indices
                        .map { (mul(it, a, n) + b) % n to cur[it] }
                        .groupingBy { mul(it.first, v, n) }
                        .reduce { key, accumulator, element ->
                            if ((key - element.first + n) % n < (key - accumulator.first + n) % n) {
                                element
                            } else {
                                accumulator
                            }
                        }.mapValues { it.value.second }
                    g = ng
                    b = mul(b, v, n)
                    a = g
                    ai = 1
                    cur = IntArray(n / g) { merged[(it * a + b + n) % n]!! }
                } else {
                    a = mul(a, v, n)
                    b = mul(b, v, n)
                    ai = inverse(a / g, n / g)
                }
            }
            "+" -> b = (b + x.toInt()) % n
            "?" -> println(get(x.toInt(), b, ai, g))
            else -> TODO()
        }
    }
}

private fun mul(a: Int, v: Int, n: Int) = ((a.toLong() * v) % n).toInt()

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }