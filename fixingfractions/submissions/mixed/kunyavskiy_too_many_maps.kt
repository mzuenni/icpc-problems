// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
import java.math.BigInteger

private fun build(a: Long) = buildList {
    val s = a.toString()
    for (mask in 1 until (1 shl s.length)) {
        val r = s.filterIndexed { index, _ -> mask and (1 shl index) != 0 }
        if (r[0] == '0') continue
        val rem = s.filterIndexed { index, _ -> mask and (1 shl index) == 0 }.toCharArray().sorted().joinToString("")
        add(rem to r.toLong())
    }
}.groupBy({ it.first}, { it.second }).mapValues { it.value.toSet() }

fun main() {
    val (a, b, c_, d_) = readLongs()
    val c = c_.toBigInteger()
    val d = d_.toBigInteger()
    val am = build(a)
    val bm = build(b)
    val max = Long.MAX_VALUE.toBigInteger()
    for ((k , s) in am) {
        if (k !in bm) continue
        for (v in s) {
            val eac = v.toBigInteger() * d
            if (eac % c != BigInteger.ZERO) {
                continue
            }
            val eb = eac / c
            if (eb < max) {
                val ebl = eb.toLong()
                if (bm[k]!!.contains(ebl)) {
                    println("possible")
                    println("$v $ebl")
                    return
                }
            }
        }
    }
    println("impossible")
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
