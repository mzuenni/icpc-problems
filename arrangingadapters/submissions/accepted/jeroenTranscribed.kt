import java.util.*

var gap10 = 0
var gap11 = 0
var gap20 = 0
var gap22 = 0

fun main() {
    // Read input
    var ps: Array<String> = readln().split(" ").dropLastWhile { it.isEmpty() }.toTypedArray()
    var n = ps[0].toInt()
    var s = ps[1].toInt()
    val w = IntArray(n)
    ps = readln().split(" ").dropLastWhile { it.isEmpty() }.toTypedArray()
    for (i in 0 until n) w[i] = ps[i].toInt()

    // Sort and plug in both ends first
    Arrays.sort(w)
    if (n == 1 || s == 1) {
        println("1")
        return
    }
    var res = 2
    n -= 2
    s -= 2

    // Now fill from small to big, and if we make gaps
    // we keep that info so that we can swap in some
    // other adaptor later. We only need to keep that
    // info modulo 3.
    var i = 0
    while (i < n) {

        // Get the adapter, see if we can swap it into
        // an earlier gap, and count the number of sockets
        val c1 = swapAdapter(w[i])
        val s1 = (c1 + 2) / 3

        // Check if this plug still fits
        if (s1 > s) break
        res++
        s -= s1

        // Now place the next one opposite
        if (i + 1 < n) {
            val c2 = swapAdapter(w[i + 1])
            val s2 = (c1 + c2 + 2) / 3 - s1
            if (s2 > s) break
            s -= s2
            res++

            // See if we made a gap
            if (c1 % 3 + c2 % 3 == 2) {
                if (c1 % 3 == 0 || c2 % 3 == 0) gap20++ else gap11++
            } else if (c1 % 3 + c2 % 3 == 1) {
                gap10++
            } else if (c1 % 3 + c2 % 3 == 4) {
                gap22++
            }
        }
        i += 2
    }
    println(res)
}

fun swapAdapter(w: Int): Int {
    var w = w
    if (w % 3 == 2 && gap10 > 0) {
        w -= 2
        gap10--
    } else if (w % 3 == 1 && gap22 > 0) {
        w -= 2
        gap22--
    } else if (w % 3 == 2 && gap11 > 0) {
        w -= 1
        gap11--
    } else if (w % 3 == 1 && gap20 > 0) {
        w -= 1
        gap20--
    } else if (w % 3 == 1 && gap10 > 0) {
        w -= 1
        gap10--
        gap11++
    }
    return w
}