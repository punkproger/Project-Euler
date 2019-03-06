#include <iostream>
#include <string>

using ldouble = long double;

#define itc(n) char(n+48)
#define cti(ch) (ch-48)

inline std::string add(const std::string & s1,const std::string & s2)
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

inline std::string multiply(const std::string & s1,const std::string & s2)
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

inline int sumOfDigits(const std::string & number) {
	int res{0};
	for(auto c : number) {
		res += c - '0';
	}

	return res;
}

int main() {
	int maxSum{0};
	for(int a = 2; a < 100; ++a) {
		std::string origin{std::to_string(a)};
		std::string current{origin};
		for(int b = 2; b < 100; ++b) {
			current = std::move(multiply(current, origin));
			int sum{sumOfDigits(current)};
			if(sum > maxSum) {
				maxSum = sum;
			}
		}
	}

	std::cout << maxSum << std::endl;

	return 0;
}