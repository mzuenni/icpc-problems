#include<iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	string words[n];
	int wordlength[n];
	int ind = 0;
	int maxsizeword = 0;
	int totallength = 0; //hat am Ende ein Leerzeichen -> eigentlich eins zu lang
	for(int i = 0; i< n; i++){
		cin >> words[i];
		wordlength[i] = words[i].size();
		maxsizeword = max(maxsizeword, wordlength[i]);
		totallength += wordlength[i]+1;
	}
	int lastend[totallength];
	for(int j = 0; j< wordlength[0]-1; j++){
		lastend[j] = -1;
	}
	lastend[wordlength[0]-1] = wordlength[0]-1;
	lastend[wordlength[0]] = wordlength[0]-1;
	ind = wordlength[0];
	for(int i = 1; i< n; i++){
		for(int j = 1; j< wordlength[i]; j++){
			lastend[ind+j] = lastend[ind];
		}
		ind += wordlength[i];
		lastend[ind] = ind; //Wortende
		lastend[ind+1] = ind;//Leerzeichen hinter dem Wort
		ind++;
	}

	int mini = totallength;
	for(int i = maxsizeword; i< totallength; i++){
		int pos = i-1;
		int numlines = 1;
		while(pos < totallength-2){
			pos = lastend[pos];// neue Pos ist  Ende des letzten passenden Wort
			numlines++;
			pos += i+1;
		}
		mini = min(mini, i+numlines);
	}
	cout << mini << endl;

}
