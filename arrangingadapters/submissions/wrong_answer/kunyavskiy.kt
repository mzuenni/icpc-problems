fun main() {
    var (n, s) = readInts()
    var bal = 0
    val a = readInts().toIntArray().apply { sort() }
    println((a.takeLast(2).map { 3 } + a.dropLast(2)).takeWhile {
        s -= (it + 2) / 3
        val change = when (it % 3) {
            0 -> 0
            1 -> 1
            2 -> -1
            else -> TODO()
        }
        if (change * bal < 0) s++
        while (bal > 2 && s < 0) {
            s++
            bal -= 2
        }
        bal += change
        s >= 0
    }.size)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
