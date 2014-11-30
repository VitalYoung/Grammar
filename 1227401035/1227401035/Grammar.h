#include <iostream>
#include <string>

using namespace std;

struct Generate
{
	char left;			//����ʽ��
	string right;		//����ʽ�Ҳ�
	Generate * next;	//ָ����һ������ʽ����ָ��
	Generate(){left = '\0';next = NULL;}			//���캯����ʹ����ʽ����ʼ��
};

class Grammar
{
private:
	char start;	
	string Nonterminate;	
	string Terminate;	
	int pNum;	
	Generate* head;	
	void algorithm21();
	void algorithm22();
	string algorithm23();

	bool isRunAlgorithm25();
	void algorithm24And25();
	void algorithm26();
public:
	Grammar(string t,string n,char s,Generate* h = NULL,int num = 0); 
	Grammar(Grammar &g);
	~Grammar(){
		Generate *p,*q;
		p = head;
		p = p->next;
		while(p != NULL)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}
	void SetTerminate(string);	
	void SetNonterminate(string);	
	void SetStart(char);
	void SetGenerate(Generate* h);
	void Output();

	void deleteUselessGenerate();
	void removeSingleGenerate();
	void removeEGenerate();
};