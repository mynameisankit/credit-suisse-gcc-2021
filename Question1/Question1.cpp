
using namespace std;
#include <string>
#include <iostream>

typedef long long int lli;

lli ceil(double a) {
    double mantissa = a - (lli)a;
    return (mantissa == 0) ? a : (lli)a + 1;
}

int solution(int n){
    lli twos1, ones1;
    twos1 = n/3;
    ones1 = n - 2*twos1;

    lli twos2, ones2;
    twos2 = ceil((double)n/3);
    ones2 = n - 2*twos2;
    
    int ans;
    if(abs(twos2 - ones2) > abs(twos1 - ones1))
        ans = twos1 + ones1;
    else
        ans = twos2 + ones2;

    return ans;
}

/*  Do not edit below code */
int main() {
	int n;
	cin >> n;	
    int answer = solution(n);
	cout << answer << endl;	
}
