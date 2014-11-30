#include <iostream>
#include <string>
#include "Grammar.h"

using namespace std;
int main(int argc, char ** argv)
{
	string nonterminate = "";
	string terminate = "";
	string start = "";
	Generate *pHead = new Generate;
	Generate *p = pHead;
	cout<<"请输入非终结符(符号之间不需要添加间隔符):"<<endl;
	cin>>nonterminate;
	cout<<"请输入终结符(符号之间不需要添加间隔符):"<<endl;
	cin>>terminate;
	cout<<"请输入开始符(符号之间不需要添加间隔符):"<<endl;
	cin>>start;
	Grammar grammar(terminate,nonterminate,*start.c_str());
	cout<<"请输入产生式(每个产生式一行,左端和右端空格隔开,结束则输入0):"<<endl;
	string left,right,r_tmp;

	while(1)
	{
		cin>>left;
		if(left[0] =='0')
		{
			break;
		}
		cin>>right;
		//处理右端的"|"
		int index = 0;
		int i;
		for(i=0;i<right.length();i++)
		{
			char t = right[i];
			if(t == '|')
			{
				r_tmp = right.substr(index,i-index);
				index = i+1;
				Generate *pNextG = new Generate;
				pNextG->left = left[0];
				pNextG->right = r_tmp;
				p->next = pNextG;
				p = pNextG;
			}
		}
		r_tmp = right.substr(index,i-index);
		index = i+1;
		Generate *pNextG = new Generate;
		pNextG->left = left[0];
		pNextG->right = r_tmp;
		p->next = pNextG;
		p = pNextG;
	}
	Grammar grammar1 = grammar;
	cout<<"消除无用产生式:"<<endl;
	grammar1.SetGenerate(pHead);
	grammar1.deleteUselessGenerate();
	grammar.Output();
	cout<<"消除无e产生式:"<<endl;
	Grammar grammar2 = grammar;
	grammar2.removeEGenerate();
	grammar2.Output();
	cout<<"消除单产生式:"<<endl;
	Grammar grammar3 = grammar;
	grammar3.removeSingleGenerate();
	grammar3.Output();
	
	return 0;
}