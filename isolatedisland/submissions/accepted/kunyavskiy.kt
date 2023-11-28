fun main() {
    println(if (List(readln().toInt()) { readln().split(" ").chunked(2) }.flatten().groupBy { it }.any { it.value.size % 2 == 1 }) "yes" else "no")
}