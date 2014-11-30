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
	cout<<"��������ս��(����֮�䲻��Ҫ��Ӽ����):"<<endl;
	cin>>nonterminate;
	cout<<"�������ս��(����֮�䲻��Ҫ��Ӽ����):"<<endl;
	cin>>terminate;
	cout<<"�����뿪ʼ��(����֮�䲻��Ҫ��Ӽ����):"<<endl;
	cin>>start;
	Grammar grammar(terminate,nonterminate,*start.c_str());
	cout<<"���������ʽ(ÿ������ʽһ��,��˺��Ҷ˿ո����,����������0):"<<endl;
	string left,right,r_tmp;

	while(1)
	{
		cin>>left;
		if(left[0] =='0')
		{
			break;
		}
		cin>>right;
		//�����Ҷ˵�"|"
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
	cout<<"�������ò���ʽ:"<<endl;
	grammar1.SetGenerate(pHead);
	grammar1.deleteUselessGenerate();
	grammar.Output();
	cout<<"������e����ʽ:"<<endl;
	Grammar grammar2 = grammar;
	grammar2.removeEGenerate();
	grammar2.Output();
	cout<<"����������ʽ:"<<endl;
	Grammar grammar3 = grammar;
	grammar3.removeSingleGenerate();
	grammar3.Output();
	
	return 0;
}