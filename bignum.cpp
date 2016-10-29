#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class bignum {

	string value;
	bool isPositive;

public:

	bignum(int n) 
	{
		if(n<0)
			isPositive = false;
		else
			isPositive = true;					//sign of the number
		value = "";
		n = abs(n);
		if(n==0)
			value = "0";

		while(n!=0)
		{
			value = (char)((n%10)+'0') + value;
			n/=10;
		}
	}

	bignum(string s)
	{
		if(s[0]=='-')			//negative number
		{
			isPositive = false;
			for(int i=1;i<s.length();i++)
			{
				if(s[i]<'0' or s[i]>'9')
				{
					value = "";
					break;
				}
				value += s[i];
			}
		}
		else
		{
			isPositive = true;
			for(int i=0;i<s.length();i++)
			{
				if(s[i]<'0' or s[i]>'9')
				{
					value = "";
					break;
				}
				value += s[i];
			}
		}														//positive

		for(int i=0;i<value.length();i++);
			//delete the beginning zeroes;
	}


	bignum() 
	{
		value = "";
		isPositive = true;
	}

	~bignum() {
		value = "";				//for nothing 
	}

	bool operator==(const bignum b)				//comaparing 2 bignums
	{
		if(isPositive == b.isPositive and value == b.value)
			return true;
		else
			return false;
	}

	bool operator==(int b)			//comparing bignum and int
	{
		if(b>0 and isPositive==false)
			return false;
		else if(b<0 and isPositive==true)
			return false;

		b = abs(b);			//comapring negative numbers

		for(int i=value.length()-1;i>=0 and b!=0 ;i--,b/=10)
		{
			if(b%10 != int(value[i] - '0'))
				return false;
		}
		if(b==0)
			return true;
		return false;
	}

	bool operator>(bignum b)
	{
		if(*this == b)
			return false;
		
		if(isPositive==true and b.isPositive == false)		//first number is positive and second is negative
			return true;
		else if(isPositive==false and b.isPositive==true)		//first number is negative and second is positive
			return false;
		else 
		{
			if(isPositive and b.isPositive)		//both are positive
			{
				if(value.length() > b.value.length())
					return true;
				else if(value.length() < b.value.length())
					return false;
				else 
				{
					for(int i=0;i<value.length();i++)
					{
						if(value[i] > b.value[i])
							return true;
						else if(value[i] < b.value[i])
							return false;
					}
				}
			}
		}
	}

	bool modcomp(bignum b)			//Boolean function returns if(|a|>|b|)
	{
		if(value.length()>b.value.length())
			return true;
		else if(value.length()<b.value.length())
			return false;
		else
		{
			for(int i=0;i<value.length();i++)
			{
				if(value[i] > b.value[i])
					return true;
				else if(value[i] < b.value[i])
					return false;
			}
		}
	}

	bignum operator+(bignum b)
	{
		bignum sum;
		int carry=0;int i,j,x,k=0;
		if(isPositive == b.isPositive)		//Both have same signs, so value is added.
		{
			for(i=value.length()-1,j=b.value.length()-1;(i>=0&&j>=0);i--,j--)
			{
				sum.value[k++]=carry+(value[i]-'0')+(b.value[j]-'0')%10+'0';
				carry = carry+(value[i]-'0')+(b.value[j]-'0')/10;
			}
			while(i--)
			{
				sum.value[k++]=carry+(value[i]-'0')%10+'0';
				carry = carry+(value[i]-'0')/10;
			}
			while(j--)
			{
				sum.value[k++]=carry+(b.value[j]-'0')%10+'0';
				carry = carry+(b.value[j]-'0')/10;
			}
			sum.isPositive = isPositive;
		}
		else		//Both have opposite signs, so values are substracted.
		{
			string copy;
			if(modcomp(b))			//if(|a|>|b|), value is |a|-|b|,sign is a's sign.
			{
				copy = value;
				for(i=copy.length()-1,j=b.value.length()-1;(i>=0&&j>=0);i--,j--)
				{
					if(copy[i]>b.value[j])
						sum.value[k++]=copy[i]-b.value[j]+'0';
					else
					{
						sum.value[k++]=copy[i]-b.value[j]+10+'0';
						for(x=i-1;copy[x]!='0';x--)
							copy[x]='9';
						copy[x]--;
					}
				}
				while(i--)
					sum.value[k++]=copy[i]+'0';
				sum.isPositive = isPositive;
			}
			else				//if(|b|>|a|), value is |b|-|a|, sign is b's sign
			{
				copy = b.value;
				for(i=copy.length()-1,j=value.length()-1;(i>=0&&j==0);i--,j--)
				{
					if(copy[i]>value[j])
						sum.value[k++]=copy[i]-value[j]+'0';
					else
					{
						sum.value[k++]=copy[i]-value[j]+10+'0';
						for(x=i-1;copy[x]!='0';x--)
							copy[x]='9';
						copy[x]--;
					}
				}
				while(i--)
					sum.value[k++]=copy[i]+'0';
				sum.isPositive = b.isPositive;
			}
		}char temp;		//Reversing the sum's value string.
		for(i=0;i<sum.value.length()/2;i++)
		{
			temp = sum.value[i];
			sum.value[i]=sum.value[sum.value.length()-i-1];
			sum.value[sum.value.length()-i-1]=temp;
		}
		return sum;
	}

	void print()
	{
		if(value=="")
			return;
		if(!isPositive)
			cout<<"-";
		cout<<value<<endl;
	}
};

int main()
{
	//testcases
	bignum a("125"),b(0),c("-234");
	a.print();
	b.print();
	c.print();
	bool checks[] = {a==b,b==c,c==-234};
	//comapring bignums and numbers
	cout<<checks[0]<<checks[1]<<checks[2]<<endl;
	//TODO- Addition, Substraction, Multiplication, Division
}