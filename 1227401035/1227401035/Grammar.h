#include <iostream>
#include <string>

using namespace std;

struct Generate
{
	char left;			//生成式左部
	string right;		//生成式右部
	Generate * next;	//指向下一个生成式结点的指针
	Generate(){left = '\0';next = NULL;}			//构造函数，使生成式结点初始化
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
    void removeSameGenerate();

	void deleteUselessGenerate();
	void removeSingleGenerate();
	void removeEGenerate();
};