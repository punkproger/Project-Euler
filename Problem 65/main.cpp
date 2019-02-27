#include <iostream>
#include <vector>

using ldouble = long double;

#define itc(n) char(n+48)
#define cti(ch) (ch-48)


std::string add(std::string s1, std::string s2)
{
    int len1=s1.length(), len2=s2.length();
    if(len1<len2)                                   //s1 should be of greater length than s2
        return add(s2, s1);
    std::string ans="";
    int carry=0, i, s;
    for(i=1;i<=len1;i++)
    {
        s = carry+cti(s1[len1-i]);

        if(i<=len2)
            s += cti(s2[len2-i]);

        ans = itc(s%10)+ans;                        //finding the character to be added to the ans
        carry = s/10;                               //finding the carry
    }
    if(carry!=0)
        ans = itc(carry)+ans;

    return ans;
}

std::string multiply(std::string s1, std::string s2)
{
    int len1=s1.length(), len2=s2.length();
    if(len1<len2)
        return multiply(s2,s1);
    int i,j,p, carry=0;
    std::string result, net="", c;
    for(i=len2-1;i>=0;i--)
    {
        carry=0;
        result="";
        c="";
        for(j=len1-1;j>=0;j--)
        {
            p=cti(s1[j])*cti(s2[i]);
            result = itc((p+carry)%10)+result;
            carry=(p+carry)/10;
        }
        if(carry!=0)
        {
            c=std::to_string(carry);
            result=c+result;

        }
        for(j=i;j<len2-1;j++)
            result+="0";

        net=add(net,result);
    }
    return net;
}

int main() {
	constexpr size_t limit{100};
	unsigned long long result{0};
	std::vector<int> A{2,1,2};
	std::vector<std::string> P{"1",std::to_string(A[0])};
	int k = 2;

	for(int i = 3; i < limit; ++i) {
		if(((i + 1) % 3) == 0) {
			A.push_back(k++ * 2);			
		} else {
			A.push_back(1);			
		}
	}

	for(int i = 2; i < limit + 1; ++i) {
		P.push_back(add(multiply(P[i-1], std::to_string(A[i-1])), P[i-2]));
	}
	
	for(int i = 0; i < P[P.size() - 1].size(); ++i) {
		result += std::stoi(P[P.size() - 1].substr(i , 1));
	}

	std::cout << result << std::endl;

	return 0;
}