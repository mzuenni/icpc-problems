import java.io.BufferedReader
import java.io.InputStreamReader
import java.math.BigInteger


@Throws(Exception::class)
fun main() {
    // Read input
    val ps = readln().split(" ").dropLastWhile { it.isEmpty() }.toTypedArray()
    val sa = ps[0]
    val sb = ps[1]
    val a = sa.toLong()
    val b = sb.toLong()
    val c = BigInteger(ps[2])
    val d = BigInteger(ps[3])

    // Brute force taking a subset of digits from 'a'
    val len = sa.length
    for (i in 1 until (1L shl len)) {
        // Construct the number with digits removed
        val removed = IntArray(10)
        var a2: Long = 0
        for (j in 0 until len) {
            if (i and (1L shl j) > 0) {
                // Prevent leading zeroes
                if (a2 == 0L && sa[j] == '0') {
                    a2 = -1
                    break
                }
                a2 *= 10
                a2 += (sa[j].code - '0'.code).toLong()
            } else {
                removed[sa[j].code - '0'.code]++
            }
        }

        // What should 'b' be in this case, check if we
        // could make it.
        // a * d / c
        val ba2 = BigInteger(a2.toString())
        val b2 = ba2.multiply(d).divide(c)
        if (ba2.multiply(d) != c.multiply(b2)) continue
        val sb2 = b2.toString()
        var k = 0
        var ok = true
        val removedb = IntArray(10)
        for (j in 0 until sb2.length) {
            while (k < sb.length && sb[k] != sb2[j]) {
                removedb[sb[k].code - '0'.code]++
                k++
            }
            if (k == sb.length) {
                ok = false
                break
            }
            k++
        }
        while (k < sb.length) {
            removedb[sb[k].code - '0'.code]++
            k++
        }
        for (j in 0..9) ok = ok and (removed[j] == removedb[j])
        if (ok) {
            println("possible")
            println("$a2 $b2")
            return
        }
    }
    println("impossible")
}
