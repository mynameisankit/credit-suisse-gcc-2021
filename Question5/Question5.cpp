using namespace std;
#include <string>
#include <iostream>
#include<cmath>

string solution(string n){
    int longest_substring = 0, longest_count = 0;
    int longest_than_half_substring = 0, longest_than_half = 0;

    string ans = "";

    bool counting = false;
    int curr_count = 0;
    
    for(int i = 0; i <= n.length(); i++) {
        if(i == n.length() || n[i] == '1') {
            if(counting) {
                //A longer than longest substring has been found
                if(curr_count >= longest_substring) {
                    if(curr_count == longest_substring)
                        longest_count++;
                    else {
                        //If the old string was longer than half of the current one
                        if(longest_substring >= ceil((double)curr_count/2)) {
                            if(longest_substring == longest_than_half_substring)
                                longest_than_half++;
                            else
                                longest_than_half = 1;

                            longest_than_half_substring = longest_substring;
                        }
                        else {
                            longest_than_half = 0;
                            longest_than_half_substring = 0;
                        }
                        
                        longest_count = 1;
                    }

                    longest_substring = curr_count;
                }
                else if(curr_count >= ceil((double)longest_substring/2)) {
                    if(curr_count == longest_than_half_substring)
                        longest_than_half++;
                    else
                        longest_than_half = 1;

                    longest_than_half_substring = max<int>(longest_than_half_substring, curr_count);
                }


                curr_count = 0;
                counting = false;
            }
        }
        else {
            if(!counting) {
                curr_count = 1;
                counting = true;
            }
            else 
                curr_count++;
        }
    }

    if(longest_substring == 1) {
        if(longest_count == 1)
            ans = "A";
        else
            ans = "B";
    }
    if(longest_substring % 2 == 0 || longest_count > 1 || longest_than_half_substring >= 1)
        ans = "B";
    else
        ans = "A";

    return ans;
}

/*  Do not edit below code */
int main() {
	string n;
    cin >> n;
    string answer = solution(n);
	cout << answer << endl;	
}
