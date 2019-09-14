#include <iostream>
#include <string>

using namespace std;

void calculateFreqs(double[], double[], double[], const string[], const size_t&);

void orderAbbrevsByFreq(string[], double[], const size_t&);
size_t findMax(const double[], const size_t&, const size_t&);

string concatenateResult(const string[], const size_t&);

int main() {
	const size_t N = 57;
	
	string result;
	
	string abbrevs[N] = {"AK", "AL", "AR", "AS", "AZ", "CA", "CO", "CT", "DC", "DE", "FL", "FT", "GA", "GU", "HI", "IA", "ID", "IL", "IN", "KS", "KY", "LA", "MA", "MD", "ME", "MI", "MN", "MO", "MP", "MS", "MT", "NC", "ND", "NE", "NH", "NJ", "NM", "NV", "NY", "OH", "OK", "OR", "PA", "PR", "RI", "SC", "SD", "TN", "TX", "UT", "VA", "VI", "VT", "WA", "WI", "WV", "WY"};
	
	double firstLetterFreqs[N];
	double secondLetterFreqs[N];
	double averageFreqs[N];
	
	calculateFreqs(firstLetterFreqs, secondLetterFreqs, averageFreqs, abbrevs, N);
	
	
	orderAbbrevsByFreq(abbrevs, averageFreqs, N);
	result = concatenateResult(abbrevs, N);
	
	cout<< result << endl;

}

void calculateFreqs(double firstLetterFreqs[], double secondLetterFreqs[], double averageFreqs[], const string abbrevs[], const size_t &N) {
	int firstLetterMatches;
	int secondLetterMatches;
	
	for(size_t i = 0; i < N; i++) {
		firstLetterMatches = 0;
		secondLetterMatches = 0;
		
		for(size_t j = 0; j < N; j++) {
			if(i != j && abbrevs[i].at(0) == abbrevs[j].at(1))
				firstLetterMatches++;
			
			if(i != j && abbrevs[i].at(1) == abbrevs[j].at(0))
				secondLetterMatches++;
		}
		
		firstLetterFreqs[i] = double(firstLetterMatches) / double(N - 1);
		secondLetterFreqs[i] = double(secondLetterMatches) / double(N - 1);
		
		averageFreqs[i] = (firstLetterFreqs[i] + secondLetterFreqs[i]) / 2.0;
	}
}

void orderAbbrevsByFreq(string abbrevs[], double freqs[], const size_t &N) {
	size_t max;
	
	double tempFreq;
	string tempAbbrev;

	for(size_t i = 0; i < N; i++) {
		max = findMax(freqs, i, N);
		
		tempFreq = freqs[max];
		freqs[max] = freqs[i];
		freqs[i] = tempFreq;
		
		tempAbbrev = abbrevs[max];
		abbrevs[max] = abbrevs[i];
		abbrevs[i] = tempAbbrev;
	}
}

size_t findMax(const double freqs[], const size_t &a, const size_t &b) {
	if(b <= a)
		return 0;
	
	size_t max = a;
	
	for(size_t i = a; i < b; i++) {
		if(freqs[max] < freqs[i])
			max = i;
	}
	
	return max;
}

string concatenateResult(const string abbrevs[], const size_t &N) {
	bool canAdd = true;
	
	string *availableAbbrevs = new string[N];
	
	for(int i = 0; i < N; i++)
		availableAbbrevs[i] = abbrevs[i];
	
	string result = availableAbbrevs[0];
	availableAbbrevs[0] = "00";
	
	while(canAdd) {
		canAdd = false;
		
		for(int i = 1; i < N; i++) {
			if(availableAbbrevs[i].at(0) == result.back()) {
				result += availableAbbrevs[i].at(1);
				availableAbbrevs[i] = "00";
				
				canAdd = true;
			}
		}
	}
	
	delete [] availableAbbrevs;
	
	return result;
}