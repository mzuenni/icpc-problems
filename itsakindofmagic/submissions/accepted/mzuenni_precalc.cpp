#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

// lu cu ru
// lc  c rc
// ld cd rd
//
// lu teilt c*c
// ru teilt c*c
constexpr ll check(ll c, ll lu, ll ru) {
	ll ccc = c * c * c;
	ll cc = c * c;

	ll cu = ccc / lu / ru;
	// check row 1
	if (cc % cu != 0) return false;

	ll ld = cc / ru; // => diag 2 correct by definition
	ll cd = cc / cu; // => col 2 correct by definition
	ll rd = cc / lu; // => diag 1 correct by definition
	// check row 3
	if ((ccc / ld) % cd != 0) return false;
	if ((ccc / ld) / cd != rd) return false;

	if ((ccc / ru) % rd != 0) return false;
	ll rc = (ccc / ru) / rd;
	// check col 3
	if (cc % rc != 0) return false;
	ll lc = cc / rc;
	// => row 2 correct by definition

	// check col 1
	if ((ccc / lu) % lc != 0) return false;
	if ((ccc / lu) / lc != ld) return false;

	// check unique
	array<ll, 9> tmp = {lu, cu, ru, lc, c, rc, ld, cd, rd};
	sort(all(tmp));
	for (ll i = 1; i < 9; i++) {
		if (tmp[i] == tmp[i - 1]) return false;
	}
	/*cout << endl;
	cout << lu << " " << cu << " " << ru << endl;
	cout << lc << " " << c << " " << rc << endl;
	cout << ld << " " << cd << " " << rd << endl;*/

	/*cout << endl;

	cout << lu * cu * ru << endl;
	cout << lc * c * rc << endl;
	cout << ld * cd * rd << endl;

	cout << endl;

	cout << lu * lc * ld << endl;
	cout << cu * c * cd << endl;
	cout << ru * rc * rd << endl;

	cout << endl;

	cout << lu * c * rd << endl;
	cout << ld * c * ru << endl;*/
	return true;
}

ll brute(ll c) {
	vector<ll> divs;
	for (ll lu = 1; lu < c; lu++) {
		if ((c * c) % lu == 0) {
			divs.push_back(lu);
		}
	}
	sort(all(divs));

	ll res = 0;
	for (ll lu : divs) {
		for (ll ru : divs) {
			if (ru <= lu) continue;

			ll rd = (c * c) / lu;
			if (ru >= rd) break;

			if (((c * c * c) / lu) % ru != 0) continue;
			res += check(c, lu, ru);
		}
	}
	return 8*res;
}

constexpr ll lim = 1'000'007;
ll primes[7] = {2,3,5,7,11,13,17};
vector<ll> powers[7];
ll divisor[lim];
ll res[lim];

void initRes() {
	res[2] = 0;
	res[4] = 0;
	res[6] = 8;
	res[8] = 0;
	res[12] = 32;
	res[16] = 8;
	res[24] = 72;
	res[30] = 72;
	res[32] = 24;
	res[36] = 104;
	res[48] = 136;
	res[60] = 232;
	res[64] = 32;
	res[72] = 232;
	res[96] = 224;
	res[120] = 488;
	res[128] = 56;
	res[144] = 408;
	res[180] = 680;
	res[192] = 320;
	res[210] = 464;
	res[216] = 480;
	res[240] = 848;
	res[256] = 80;
	res[288] = 648;
	res[360] = 1392;
	res[384] = 448;
	res[420] = 1352;
	res[432] = 840;
	res[480] = 1312;
	res[512] = 104;
	res[576] = 920;
	res[720] = 2360;
	res[768] = 592;
	res[840] = 2736;
	res[864] = 1312;
	res[900] = 1896;
	res[960] = 1864;
	res[1024] = 136;
	res[1080] = 2784;
	res[1152] = 1264;
	res[1260] = 3760;
	res[1296] = 1440;
	res[1440] = 3600;
	res[1536] = 752;
	res[1680] = 4624;
	res[1728] = 1848;
	res[1800] = 3816;
	res[1920] = 2528;
	res[2048] = 176;
	res[2160] = 4688;
	res[2304] = 1648;
	res[2310] = 2640;
	res[2520] = 7472;
	res[2592] = 2224;
	res[2880] = 5080;
	res[3072] = 936;
	res[3360] = 7016;
	res[3456] = 2520;
	res[3600] = 6384;
	res[3840] = 3288;
	res[4096] = 208;
	res[4320] = 7104;
	res[4608] = 2088;
	res[4620] = 7312;
	res[5040] = 12480;
	res[5184] = 3128;
	res[5400] = 7552;
	res[5760] = 6840;
	res[6144] = 1144;
	res[6300] = 10184;
	res[6480] = 7840;
	res[6720] = 9896;
	res[6912] = 3280;
	res[7200] = 9664;
	res[7560] = 14696;
	res[7680] = 4144;
	res[7776] = 3400;
	res[8192] = 256;
	res[8640] = 9984;
	res[9216] = 2576;
	res[9240] = 14480;
	res[10080] = 18800;
	res[10368] = 4240;
	res[10800] = 12576;
	res[11520] = 8848;
	res[12288] = 1360;
	res[12600] = 20016;
	res[12960] = 11832;
	res[13440] = 13288;
	res[13824] = 4128;
	res[13860] = 19760;
	res[14400] = 13576;
	res[15120] = 24432;
	res[15360] = 5104;
	res[15552] = 4776;
	res[16384] = 304;
	res[17280] = 13400;
	res[18432] = 3128;
	res[18480] = 24152;
	res[20160] = 26400;
	res[20736] = 5496;
	res[21600] = 18936;
	res[23040] = 11120;
	res[24576] = 1608;
	res[25200] = 33200;
	res[25920] = 16600;
	res[26880] = 17176;
	res[27000] = 14784;
	res[27648] = 5088;
	res[27720] = 38712;
	res[28800] = 18208;
	res[30030] = 14168;
	res[30240] = 36680;
	res[30720] = 6168;
	res[31104] = 6440;
	res[32400] = 20864;
	res[32768] = 352;
	res[34560] = 17304;
	res[36864] = 3712;
	res[36960] = 36328;
	res[37800] = 39072;
	res[38880] = 17800;
	res[40320] = 35320;
	res[41472] = 6912;
	res[43200] = 26536;
	res[44100] = 27152;
	res[45360] = 40488;
	res[46080] = 13648;
	res[46656] = 6696;
	res[49152] = 1872;
	res[50400] = 49800;
	res[51840] = 22232;
	res[53760] = 21560;
	res[54000] = 24552;
	res[55296] = 6160;
	res[55440] = 64160;
	res[57600] = 23480;
	res[60060] = 38192;
	res[60480] = 51392;
	res[61440] = 7320;
	res[62208] = 8328;
	res[64800] = 31344;
	res[65536] = 408;
	res[69120] = 21696;
	res[69300] = 52624;
	res[73728] = 4368;
	res[73920] = 50992;
	res[75600] = 64616;
	res[77760] = 24944;
	res[80640] = 45528;
	res[82944] = 8496;
	res[83160] = 75432;
	res[86400] = 35496;
	res[88200] = 53008;
	res[90720] = 60664;
	res[92160] = 16448;
	res[93312] = 9024;
	res[98304] = 2152;
	res[100800] = 69736;
	res[103680] = 28664;
	res[107520] = 26448;
	res[108000] = 36856;
	res[110592] = 7296;
	res[110880] = 96120;
	res[115200] = 29456;
	res[120120] = 74712;
	res[120960] = 68640;
	res[122880] = 8584;
	res[124416] = 10456;
	res[129600] = 43872;
	res[131072] = 472;
	res[138240] = 26600;
	res[138600] = 102416;
	res[147456] = 5064;
	res[147840] = 68168;
	res[151200] = 96696;
	res[155520] = 33352;
	res[161280] = 57040;
	res[162000] = 40640;
	res[165888] = 10264;
	res[166320] = 124664;
	res[172800] = 45720;
	res[176400] = 87552;
	res[180180] = 101560;
	res[181440] = 84896;
	res[184320] = 19488;
	res[186624] = 11664;
	res[189000] = 75912;
	res[194400] = 46984;
	res[196608] = 2456;
	res[201600] = 93096;
	res[207360] = 35912;
	res[215040] = 31840;
	res[216000] = 51552;
	res[221184] = 8568;
	res[221760] = 134560;
	res[226800] = 106656;
	res[230400] = 36080;
	res[233280] = 34920;
	res[240240] = 123736;
	res[241920] = 88376;
	res[245760] = 9944;
	res[248832] = 12832;
	res[259200] = 58616;
	res[262144] = 528;
	res[264600] = 102984;
	res[272160] = 90768;
	res[276480] = 32016;
	res[277200] = 169080;
	res[279936] = 12128;
	res[294912] = 5816;
	res[295680] = 87840;
	res[302400] = 135216;
	res[311040] = 42960;
	res[322560] = 69848;
	res[324000] = 60888;
	res[331776] = 12152;
	res[332640] = 186408;
	res[345600] = 57256;
	res[352800] = 130992;
	res[360360] = 197432;
	res[362880] = 113272;
	res[368640] = 22808;
	res[373248] = 14632;
	res[378000] = 125288;
	res[388800] = 65712;
	res[393216] = 2784;
	res[403200] = 119800;
	res[414720] = 43984;
	res[415800] = 198632;
	res[430080] = 37720;
	res[432000] = 68856;
	res[442368] = 9928;
	res[443520] = 179520;
	res[453600] = 159416;
	res[460800] = 43416;
	res[466560] = 46664;
	res[480480] = 185264;
	res[483840] = 110600;
	res[485100] = 138896;
	res[491520] = 11400;
	res[497664] = 15472;
	res[498960] = 205672;
	res[510510] = 73752;
	res[518400] = 75432;
	res[524288] = 600;
	res[529200] = 169776;
	res[544320] = 126928;
	res[552960] = 37896;
	res[554400] = 252680;
	res[559872] = 15656;
	res[589824] = 6616;
	res[591360] = 110008;
	res[604800] = 180296;
	res[622080] = 53784;
	res[645120] = 83968;
	res[648000] = 85104;
	res[663552] = 14248;
	res[665280] = 260616;
	res[691200] = 70080;
	res[705600] = 183104;
	res[720720] = 325800;
	res[725760] = 145728;
	res[737280] = 26376;
	res[746496] = 17952;
	res[756000] = 187200;
	res[777600] = 87696;
	res[786432] = 3120;
	res[806400] = 149912;
	res[810000] = 67112;
	res[829440] = 52896;
	res[831600] = 327336;
	res[860160] = 44112;
	res[864000] = 88624;
	res[884736] = 11376;
	res[887040] = 230968;
	res[900900] = 267824;
	res[907200] = 222752;
	res[921600] = 51384;
	res[933120] = 60080;
	res[960960] = 259280;
	res[967680] = 135336;
	res[970200] = 269208;
	res[972000] = 91080;
	res[983040] = 12960;
	res[995328] = 18312;
	res[997920] = 307200;
}

void calcRes() {
	for (ll i = 0; i < 7; i++) {
		powers[i] = {1};
		while (powers[i].back() < lim) powers[i].push_back(powers[i].back() * primes[i]);
	}
	vector<ll> count;
	count.reserve(8);
	for (ll i = 2; i < lim; i++) {
		if (divisor[i] == 0) {
			divisor[i] = i;
			for (ll j = i*i; j < lim; j += i) {
				divisor[j] = i;
			}
		}
		count.clear();
		ll j = i;
		while (j > 1) {
			ll d = divisor[j];
			ll c = 0;
			do {
				c++;
				j /= d;
			} while (j % d == 0);
			count.push_back(c);
		}
		sort(all(count), greater<ll>{});
		ll k = 1;
		for (ll j = 0; j < sz(count); j++) k *= powers[j][count[j]];
		res[i] = res[k];
		//if (k == i) cout << "res[" << k << "] = " << brute(k) << ";" << endl;
	}
	for (ll i = 1; i < lim; i++) res[i] += res[i - 1];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	initRes();
	calcRes();

	ll n;
	cin >> n;
	for (ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		ll r = std::cbrtl(x);
		while ((r+1) * (r+1) * (r+1) <= x) r++;
		while (r * r * r > x) r--;
		cout << res[r] << endl;
	}
}
