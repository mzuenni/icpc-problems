fun main() {
    val (n, qs) = readInts()
    val c = readInts()
    val used = IntArray(c.size + 1)
    val next = IntArray(c.size) { -1 }
    val idx = mutableListOf<Int>()
    for (i in c.indices.reversed()) {
        while (idx.isNotEmpty() && c[i] >= c[idx.last()]) {
            idx.removeLast()
        }
        next[i] = idx.lastOrNull() ?: n
        idx.add(i)
    }
    val answers = mutableListOf<Int>()
    var ops = 0
    for (i in 0 until qs) {
        val q = readStrings()
        if (q[0] == "+") {
            var id = q[1].toInt() - 1
            var w = q[2].toInt()
            while (w > 0 && id != n) {
                ++ops
                val done = minOf(c[id] - used[id], w)
                used[id] += done
                w -= done
                if (w != 0) {
                    while (next[id] != n && c[next[id]] == used[next[id]]) {
                        next[id] = next[next[id]]
                    }
                    id = next[id]
                }
            }
        } else {
            answers.add(used[q[1].toInt() - 1])
        }
    }
    System.err.println(ops)
    println(answers.joinToString("\n"))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
