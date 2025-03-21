import kotlin.math.pow
import kotlin.time.ExperimentalTime
import kotlin.time.measureTime

val cache = mutableMapOf<List<Int>, Long>()

val prime = IntArray(1_000_001).apply {
    for (i in 2 until size) {
        if (this[i] == 0) {
            this[i] = i
            if (i.toLong() * i <= size) {
                for (j in i * i until size step i) {
                    this[j] = i
                }
            }
        }
    }
}

fun primeDegs(x_: Int) = buildList {
    var x = x_
    while (x != 1) {
        var d = 0
        val p = prime[x]
        while (x % p == 0) {
            x /= p
            d++
        }
        if (d != 0) add(d)
    }
    sort()
}

fun solve(x: Long) = cache.getOrPut(primeDegs(x.toInt())) {
    val divs = buildList {
        for (i in 1 until  x) {
            if (x * x % i == 0L) {
                add(i)
                if (i != x * x / i) {
                    add(x * x / i)
                }
            }
        }
        sort()
    }
    val x3 = x * x * x
    val x2 = x * x
    var ans = 0L
    for (a in divs) {
        for (b in divs) {
            if (a * b >= x3) break
            if (x3 % (a * b) != 0L) continue
            val c = x3 / a / b
            if (x2 % c != 0L || (x * c % a) != 0L || (x * a % c) != 0L) continue
            val values = listOf(
                a, b, c,
                x * c / a, x, x * a / c,
                x2 / c, x2 / b, x2 / a,
            )
            if (values.distinct().size == 9) ans++
        }
    }
    //println("cache[listOf(${primeDegs(x).joinToString()})] = $ans")
    ans
}

fun prefill() {
    cache[listOf()] = 0
    cache[listOf(1)] = 0
    cache[listOf(2)] = 0
    cache[listOf(1, 1)] = 8
    cache[listOf(3)] = 0
    cache[listOf(1, 2)] = 32
    cache[listOf(4)] = 8
    cache[listOf(1, 3)] = 72
    cache[listOf(1, 1, 1)] = 72
    cache[listOf(5)] = 24
    cache[listOf(2, 2)] = 104
    cache[listOf(1, 4)] = 136
    cache[listOf(1, 1, 2)] = 232
    cache[listOf(6)] = 32
    cache[listOf(2, 3)] = 232
    cache[listOf(1, 5)] = 224
    cache[listOf(1, 1, 3)] = 488
    cache[listOf(7)] = 56
    cache[listOf(2, 4)] = 408
    cache[listOf(1, 2, 2)] = 680
    cache[listOf(1, 6)] = 320
    cache[listOf(1, 1, 1, 1)] = 464
    cache[listOf(3, 3)] = 480
    cache[listOf(1, 1, 4)] = 848
    cache[listOf(8)] = 80
    cache[listOf(2, 5)] = 648
    cache[listOf(1, 2, 3)] = 1392
    cache[listOf(1, 7)] = 448
    cache[listOf(1, 1, 1, 2)] = 1352
    cache[listOf(3, 4)] = 840
    cache[listOf(1, 1, 5)] = 1312
    cache[listOf(9)] = 104
    cache[listOf(2, 6)] = 920
    cache[listOf(1, 2, 4)] = 2360
    cache[listOf(1, 8)] = 592
    cache[listOf(1, 1, 1, 3)] = 2736
    cache[listOf(3, 5)] = 1312
    cache[listOf(2, 2, 2)] = 1896
    cache[listOf(1, 1, 6)] = 1864
    cache[listOf(10)] = 136
    cache[listOf(1, 3, 3)] = 2784
    cache[listOf(2, 7)] = 1264
    cache[listOf(1, 1, 2, 2)] = 3760
    cache[listOf(4, 4)] = 1440
    cache[listOf(1, 2, 5)] = 3600
    cache[listOf(1, 9)] = 752
    cache[listOf(1, 1, 1, 4)] = 4624
    cache[listOf(3, 6)] = 1848
    cache[listOf(2, 2, 3)] = 3816
    cache[listOf(1, 1, 7)] = 2528
    cache[listOf(11)] = 176
    cache[listOf(1, 3, 4)] = 4688
    cache[listOf(2, 8)] = 1648
    cache[listOf(1, 1, 1, 1, 1)] = 2640
    cache[listOf(1, 1, 2, 3)] = 7472
    cache[listOf(4, 5)] = 2224
    cache[listOf(1, 2, 6)] = 5080
    cache[listOf(1, 10)] = 936
    cache[listOf(1, 1, 1, 5)] = 7016
    cache[listOf(3, 7)] = 2520
    cache[listOf(2, 2, 4)] = 6384
    cache[listOf(1, 1, 8)] = 3288
    cache[listOf(12)] = 208
    cache[listOf(1, 3, 5)] = 7104
    cache[listOf(2, 9)] = 2088
    cache[listOf(1, 1, 1, 1, 2)] = 7312
    cache[listOf(1, 1, 2, 4)] = 12480
    cache[listOf(4, 6)] = 3128
    cache[listOf(2, 3, 3)] = 7552
    cache[listOf(1, 2, 7)] = 6840
    cache[listOf(1, 11)] = 1144
    cache[listOf(1, 2, 2, 2)] = 10184
    cache[listOf(1, 4, 4)] = 7840
    cache[listOf(1, 1, 1, 6)] = 9896
    cache[listOf(3, 8)] = 3280
    cache[listOf(2, 2, 5)] = 9664
    cache[listOf(1, 1, 3, 3)] = 14696
    cache[listOf(1, 1, 9)] = 4144
    cache[listOf(5, 5)] = 3400
    cache[listOf(13)] = 256
    cache[listOf(1, 3, 6)] = 9984
    cache[listOf(2, 10)] = 2576
    cache[listOf(1, 1, 1, 1, 3)] = 14480
    cache[listOf(1, 1, 2, 5)] = 18800
    cache[listOf(4, 7)] = 4240
    cache[listOf(2, 3, 4)] = 12576
    cache[listOf(1, 2, 8)] = 8848
    cache[listOf(1, 12)] = 1360
    cache[listOf(1, 2, 2, 3)] = 20016
    cache[listOf(1, 4, 5)] = 11832
    cache[listOf(1, 1, 1, 7)] = 13288
    cache[listOf(3, 9)] = 4128
    cache[listOf(1, 1, 1, 2, 2)] = 19760
    cache[listOf(2, 2, 6)] = 13576
    cache[listOf(1, 1, 3, 4)] = 24432
    cache[listOf(1, 1, 10)] = 5104
    cache[listOf(5, 6)] = 4776
    cache[listOf(14)] = 304
    cache[listOf(1, 3, 7)] = 13400
    cache[listOf(2, 11)] = 3128
    cache[listOf(1, 1, 1, 1, 4)] = 24152
    cache[listOf(1, 1, 2, 6)] = 26400
    cache[listOf(4, 8)] = 5496
    cache[listOf(2, 3, 5)] = 18936
    cache[listOf(1, 2, 9)] = 11120
    cache[listOf(1, 13)] = 1608
    cache[listOf(1, 2, 2, 4)] = 33200
    cache[listOf(1, 4, 6)] = 16600
    cache[listOf(1, 1, 1, 8)] = 17176
    cache[listOf(3, 3, 3)] = 14784
    cache[listOf(3, 10)] = 5088
    cache[listOf(1, 1, 1, 2, 3)] = 38712
    cache[listOf(2, 2, 7)] = 18208
    cache[listOf(1, 1, 1, 1, 1, 1)] = 14168
    cache[listOf(1, 1, 3, 5)] = 36680
    cache[listOf(1, 1, 11)] = 6168
    cache[listOf(5, 7)] = 6440
    cache[listOf(2, 4, 4)] = 20864
    cache[listOf(15)] = 352
    cache[listOf(1, 3, 8)] = 17304
    cache[listOf(2, 12)] = 3712
    cache[listOf(1, 1, 1, 1, 5)] = 36328
    cache[listOf(1, 2, 3, 3)] = 39072
    cache[listOf(1, 5, 5)] = 17800
    cache[listOf(1, 1, 2, 7)] = 35320
    cache[listOf(4, 9)] = 6912
    cache[listOf(2, 3, 6)] = 26536
    cache[listOf(2, 2, 2, 2)] = 27152
    cache[listOf(1, 1, 4, 4)] = 40488
    cache[listOf(1, 2, 10)] = 13648
    cache[listOf(6, 6)] = 6696
    cache[listOf(1, 14)] = 1872
    cache[listOf(1, 2, 2, 5)] = 49800
    cache[listOf(1, 4, 7)] = 22232
    cache[listOf(1, 1, 1, 9)] = 21560
    cache[listOf(3, 3, 4)] = 24552
    cache[listOf(3, 11)] = 6160
    cache[listOf(1, 1, 1, 2, 4)] = 64160
    cache[listOf(2, 2, 8)] = 23480
    cache[listOf(1, 1, 1, 1, 1, 2)] = 38192
    cache[listOf(1, 1, 3, 6)] = 51392
    cache[listOf(1, 1, 12)] = 7320
    cache[listOf(5, 8)] = 8328
    cache[listOf(2, 4, 5)] = 31344
    cache[listOf(16)] = 408
    cache[listOf(1, 3, 9)] = 21696
    cache[listOf(1, 1, 2, 2, 2)] = 52624
    cache[listOf(2, 13)] = 4368
    cache[listOf(1, 1, 1, 1, 6)] = 50992
    cache[listOf(1, 2, 3, 4)] = 64616
    cache[listOf(1, 5, 6)] = 24944
    cache[listOf(1, 1, 2, 8)] = 45528
    cache[listOf(4, 10)] = 8496
    cache[listOf(1, 1, 1, 3, 3)] = 75432
    cache[listOf(2, 3, 7)] = 35496
    cache[listOf(2, 2, 2, 3)] = 53008
    cache[listOf(1, 1, 4, 5)] = 60664
    cache[listOf(1, 2, 11)] = 16448
    cache[listOf(6, 7)] = 9024
    cache[listOf(1, 15)] = 2152
    cache[listOf(1, 2, 2, 6)] = 69736
    cache[listOf(1, 4, 8)] = 28664
    cache[listOf(1, 1, 1, 10)] = 26448
    cache[listOf(3, 3, 5)] = 36856
    cache[listOf(3, 12)] = 7296
    cache[listOf(1, 1, 1, 2, 5)] = 96120
    cache[listOf(2, 2, 9)] = 29456
    cache[listOf(1, 1, 1, 1, 1, 3)] = 74712
    cache[listOf(1, 1, 3, 7)] = 68640
    cache[listOf(1, 1, 13)] = 8584
    cache[listOf(5, 9)] = 10456
    cache[listOf(2, 4, 6)] = 43872
    cache[listOf(17)] = 472
    cache[listOf(1, 3, 10)] = 26600
    cache[listOf(1, 1, 2, 2, 3)] = 102416
    cache[listOf(2, 14)] = 5064
    cache[listOf(1, 1, 1, 1, 7)] = 68168
    cache[listOf(1, 2, 3, 5)] = 96696
    cache[listOf(1, 5, 7)] = 33352
    cache[listOf(1, 1, 2, 9)] = 57040
    cache[listOf(3, 4, 4)] = 40640
    cache[listOf(4, 11)] = 10264
    cache[listOf(1, 1, 1, 3, 4)] = 124664
    cache[listOf(2, 3, 8)] = 45720
    cache[listOf(2, 2, 2, 4)] = 87552
    cache[listOf(1, 1, 1, 1, 2, 2)] = 101560
    cache[listOf(1, 1, 4, 6)] = 84896
    cache[listOf(1, 2, 12)] = 19488
    cache[listOf(6, 8)] = 11664
    cache[listOf(1, 3, 3, 3)] = 75912
    cache[listOf(2, 5, 5)] = 46984
    cache[listOf(1, 16)] = 2456
    cache[listOf(1, 2, 2, 7)] = 93096
    cache[listOf(1, 4, 9)] = 35912
    cache[listOf(1, 1, 1, 11)] = 31840
    cache[listOf(3, 3, 6)] = 51552
    cache[listOf(3, 13)] = 8568
    cache[listOf(1, 1, 1, 2, 6)] = 134560
    cache[listOf(1, 2, 4, 4)] = 106656
    cache[listOf(2, 2, 10)] = 36080
    cache[listOf(1, 6, 6)] = 34920
    cache[listOf(1, 1, 1, 1, 1, 4)] = 123736
    cache[listOf(1, 1, 3, 8)] = 88376
    cache[listOf(1, 1, 14)] = 9944
    cache[listOf(5, 10)] = 12832
    cache[listOf(2, 4, 7)] = 58616
    cache[listOf(18)] = 528
    cache[listOf(2, 2, 3, 3)] = 102984
    cache[listOf(1, 1, 5, 5)] = 90768
    cache[listOf(1, 3, 11)] = 32016
    cache[listOf(1, 1, 2, 2, 4)] = 169080
    cache[listOf(7, 7)] = 12128
    cache[listOf(2, 15)] = 5816
    cache[listOf(1, 1, 1, 1, 8)] = 87840
    cache[listOf(1, 2, 3, 6)] = 135216
    cache[listOf(1, 5, 8)] = 42960
    cache[listOf(1, 1, 2, 10)] = 69848
    cache[listOf(3, 4, 5)] = 60888
    cache[listOf(4, 12)] = 12152
    cache[listOf(1, 1, 1, 3, 5)] = 186408
    cache[listOf(2, 3, 9)] = 57256
    cache[listOf(2, 2, 2, 5)] = 130992
    cache[listOf(1, 1, 1, 1, 2, 3)] = 197432
    cache[listOf(1, 1, 4, 7)] = 113272
    cache[listOf(1, 2, 13)] = 22808
    cache[listOf(6, 9)] = 14632
    cache[listOf(1, 3, 3, 4)] = 125288
    cache[listOf(2, 5, 6)] = 65712
    cache[listOf(1, 17)] = 2784
    cache[listOf(1, 2, 2, 8)] = 119800
    cache[listOf(1, 4, 10)] = 43984
    cache[listOf(1, 1, 2, 3, 3)] = 198632
    cache[listOf(1, 1, 1, 12)] = 37720
    cache[listOf(3, 3, 7)] = 68856
    cache[listOf(3, 14)] = 9928
    cache[listOf(1, 1, 1, 2, 7)] = 179520
    cache[listOf(1, 2, 4, 5)] = 159416
    cache[listOf(2, 2, 11)] = 43416
    cache[listOf(1, 6, 7)] = 46664
    cache[listOf(1, 1, 1, 1, 1, 5)] = 185264
    cache[listOf(1, 1, 3, 9)] = 110600
    cache[listOf(1, 2, 2, 2, 2)] = 138896
    cache[listOf(1, 1, 15)] = 11400
    cache[listOf(5, 11)] = 15472
    cache[listOf(1, 1, 1, 4, 4)] = 205672
    cache[listOf(1, 1, 1, 1, 1, 1, 1)] = 73752
    cache[listOf(2, 4, 8)] = 75432
    cache[listOf(19)] = 600
    cache[listOf(2, 2, 3, 4)] = 169776
    cache[listOf(1, 1, 5, 6)] = 126928
    cache[listOf(1, 3, 12)] = 37896
    cache[listOf(1, 1, 2, 2, 5)] = 252680
    cache[listOf(7, 8)] = 15656
    cache[listOf(2, 16)] = 6616
    cache[listOf(1, 1, 1, 1, 9)] = 110008
    cache[listOf(1, 2, 3, 7)] = 180296
    cache[listOf(1, 5, 9)] = 53784
    cache[listOf(1, 1, 2, 11)] = 83968
    cache[listOf(3, 4, 6)] = 85104
    cache[listOf(4, 13)] = 14248
    cache[listOf(1, 1, 1, 3, 6)] = 260616
    cache[listOf(2, 3, 10)] = 70080
    cache[listOf(2, 2, 2, 6)] = 183104
    cache[listOf(1, 1, 1, 1, 2, 4)] = 325800
    cache[listOf(1, 1, 4, 8)] = 145728
    cache[listOf(1, 2, 14)] = 26376
    cache[listOf(6, 10)] = 17952
    cache[listOf(1, 3, 3, 5)] = 187200
    cache[listOf(2, 5, 7)] = 87696
    cache[listOf(1, 18)] = 3120
    cache[listOf(1, 2, 2, 9)] = 149912
    cache[listOf(4, 4, 4)] = 67112
    cache[listOf(1, 4, 11)] = 52896
    cache[listOf(1, 1, 2, 3, 4)] = 327336
    cache[listOf(1, 1, 1, 13)] = 44112
    cache[listOf(3, 3, 8)] = 88624
    cache[listOf(3, 15)] = 11376
    cache[listOf(1, 1, 1, 2, 8)] = 230968
    cache[listOf(1, 1, 1, 2, 2, 2)] = 267824
    cache[listOf(1, 2, 4, 6)] = 222752
    cache[listOf(2, 2, 12)] = 51384
    cache[listOf(1, 6, 8)] = 60080
    cache[listOf(1, 1, 1, 1, 1, 6)] = 259280
    cache[listOf(1, 1, 3, 10)] = 135336
    cache[listOf(1, 2, 2, 2, 3)] = 269208
    cache[listOf(3, 5, 5)] = 91080
    cache[listOf(1, 1, 16)] = 12960
    cache[listOf(5, 12)] = 18312
    cache[listOf(1, 1, 1, 4, 5)] = 307200
}

fun main() {
    prefill()
    val ans = LongArray(1_000_001) { if (it == 0) 0 else solve(it.toLong()) }
    for (i in 1 until ans.size) {
        ans[i] += ans[i-1]
    }
    println(buildList {
        repeat(readInt()) {
            val x = readLong()
            var rt = x.toDouble().pow(1.0 / 3).toLong()
            while (rt * rt * rt > x) rt--
            while ((rt + 1) * (rt + 1) * (rt + 1) <= x) rt++
            add(ans[rt.toInt()])
        }
    }.joinToString("\n"))
}

private fun readInt() = readln().toInt()
private fun readLong() = readln().toLong()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
