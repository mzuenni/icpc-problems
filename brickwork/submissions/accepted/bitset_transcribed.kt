import java.util.*


const val lim = 300007
var dp = LongArray(lim / 64 + 7)
var n = 0
var w = 0
var ws: IntArray = IntArray(0) // Overridden in main

fun getDp(i: Int): Boolean {
    return dp[i / 64] ushr (i and 63) and 1L != 0L
}

fun clearDp(i: Int) {
    dp[i / 64] = dp[i / 64] and (1L shl (i and 63)).inv()
}

fun orDp(i: Int, value: Boolean) {
    if (value) dp[i / 64] = dp[i / 64] or (1L shl (i and 63))
}

fun reconstruct(first: Int): ArrayDeque<Int> {
    val res = ArrayList<Int>()
    res.add(first)
    var remains = w - first
    for (j in n - 1 downTo 0) {
        while (remains >= ws[j] && getDp(remains - ws[j])) {
            remains -= ws[j]
            res.add(ws[j])
        }
    }
    res.sort()
    return ArrayDeque(res)
}

// Copied from kunyavskiy
private fun readInts() = readln().split(" ").map { it.toInt() }

fun main() {
    val (nn, ww) = readInts()
    n = nn
    w = ww
    ws = readInts().sorted().distinct().sorted().toIntArray()
    n = ws.size
    dp[0] = 1
    for (x in ws) {
        if (getDp(w)) break
        var neq = false
        var i = x
        while (i <= w) {
            neq = neq or getDp(i)
            i += x
        }
        if (x < 64) { //multiple set operations for same long
            for (i in x until w) orDp(i, getDp(i - x))
        } else {
            val ia = x / 64
            val ib = x and 63
            var i = 0
            while (64 * i + x < w) {
                dp[i + ia] = dp[i + ia] or (dp[i] shl ib)
                if (ib != 0) dp[i + ia + 1] = dp[i + ia + 1] or (dp[i] ushr 64 - ib)
                i++
            }
            clearDp(w) //we know it wasnt set before
        }
        if (x == w || w % x != 0 || neq) orDp(w, getDp(w - x))
    }
    var divs = 0
    for (x in ws) if (w % x == 0) divs++
    if (!getDp(w) && divs < 2) {
        println("impossible")
    } else {
        println("possible")
        val rows = ArrayList<ArrayDeque<Int>>()
        for (x in ws) {
            if (getDp(w - x)) {
                var row = reconstruct(x)
                var mi = row.peekFirst()
                val ma = row.peekLast()
                rows.add(row)
                if (row.size == 1) {
                    rows.clear()
                    rows.add(row)
                    rows.add(row)
                }
                if (rows.size == 2) break
                if (mi == ma) continue
                rows.removeAt(rows.size - 1)
                if (w % ma == 0) {
                    row.addLast(mi)
                    row.removeFirst()
                    rows.add(row)
                    rows.add(ArrayDeque())
                    var i = 0
                    while (i < w) {
                        rows[rows.size - 1].addLast(ma)
                        i += ma
                    }
                    break
                } else {
                    row = reconstruct(ma)
                    mi = row.peekFirst()
                    rows.add(row.clone())
                    while (row.peekFirst() == mi) {
                        row.addLast(mi)
                        row.removeFirst()
                    }
                    rows.add(row)
                    break
                }
            }
        }
        for (v in rows) {
            println(v.size)
            for (x in v) print("$x ")
            println()
        }
    }
}
