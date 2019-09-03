#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mp(a,b) make_pair(a,b)

class stacks
{
	vector<pair<ll,ll> > elements;
	ll top;

public:
	stacks()
	{
		top=-1;
	}
	bool empty()
	{
		return top==-1;
	}
	void push(ll e)
	{
		if(empty())
		{
			elements.push_back(mp(e,e));
			top=0;
		}
		else
		{
			ll mx=max(e,elements[top].second);
			elements.push_back(mp(e,mx));
			top++;
		}
	}
	void pop()
	{
		elements.pop_back();
		top--;
	}
	ll maxe()
	{
		return elements[top].second;
	}
};

int main()
{	//cin.tie(true);
	ll n;
	cin>>n;
	stacks s;
	string inp;
	ll e,i;
	for(i=0;i<n;++i)
	{
		cin>>inp;
		if(inp=="push")
		{
			cin>>e;
			s.push(e);
		}
		else if(inp=="pop")
			s.pop();
		else
			cout<<s.maxe()<<"\n";
	}
	return 0;
}
