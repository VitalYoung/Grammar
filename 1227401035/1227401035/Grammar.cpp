#include "Grammar.h"

/*public methods*/
Grammar::Grammar(std::string t, std::string n, char s, Generate *h, int p)
{
	Terminate = t;
	Nonterminate = n;
	start = s;
	if(h == NULL)
	{
		head = new Generate;
	}else
	{
		Grammar::SetGenerate(h);
	}
	pNum = p;
}
Grammar::Grammar(Grammar &g)
{
	this->start = g.start;
	this->Nonterminate = g.Nonterminate;
	this->Terminate = g.Terminate;
	this->head = new Generate;
	Generate *pH = this->head;
	Generate *p = g.head;
	p = p->next;
	while(p != NULL)
	{
		Generate *pNextG = new Generate;
		pNextG->left = p->left;
		pNextG->right = p->right;
		pNextG->next = NULL;
		pH->next = pNextG;
		pH = pNextG;
		p = p->next;
	}
}
//输入终止符
void Grammar::SetTerminate(string t)
{
	Terminate = t;
}
void Grammar::SetNonterminate(string n)
{
	Nonterminate = n;
}
void Grammar::SetStart(char s)
{
	start = s;
}
void Grammar::SetGenerate(Generate* h)
{
	Generate *p = h;
	Generate *pGenerate;
	pGenerate = head;
	p = p->next;
	while(p != NULL)
	{
		Generate *pNextG = new Generate;
		pNextG->left = p->left;
		pNextG->right = p->right;
		pNextG->next = NULL;
		pGenerate->next = pNextG;
		pGenerate = pNextG;
		p = p->next;
	}
}
void Grammar::deleteUselessGenerate()
{
	Grammar::algorithm21();
	Grammar::algorithm22();
    Grammar::removeSameGenerate();
}
void Grammar::removeSingleGenerate()
{
	this->algorithm26();
    Grammar::removeSameGenerate();
}
void Grammar::removeEGenerate()
{
	this->algorithm24And25();
    Grammar::removeSameGenerate();
}
void Grammar::removeSameGenerate()
{
    Generate *pGenerate = new Generate;
    Generate *p = head;
    Generate *q;
    Generate *pG = pGenerate;
    Generate *qG;
    int flag = 1;
    p = p->next;
    while(p != NULL)
    {
        flag = 1;
        qG = pGenerate;
        qG = qG->next;
        while (qG != NULL) {
            if (p->left == qG->left && p->right == qG->right) {
                flag = 0;
                break;
            }
            qG = qG->next;
        }
        if (flag == 1) {
            Generate *pNextG = new Generate;
            pNextG->left = p->left;
            pNextG->right = p->right;
            pNextG->next = NULL;
            pG->next = pNextG;
            pG = pNextG;
        }
        q = p;
        p = p->next;
        delete q;
    }
    this->head = pGenerate;
}
void Grammar::Output()
{
	int flag = 1;
	for(int i=0;i<this->Nonterminate.length();i++)
	{
		flag = 1;
		Generate *p = head;
		p = p->next;
		cout<<this->Nonterminate[i]<<"->";
		while(p != NULL)
		{
			if(p->left == this->Nonterminate[i])
			{
				if(flag == 1)
				{
					flag = 0;
					cout<<p->right;
				}else
				{
					cout<<"|"<<p->right;
				}
				
			}
			p = p->next;
		}
		cout<<endl;
	}
	
}
/*private methods*/
//算法2.1  算法2.2 删除无用产生式
void Grammar::algorithm21()
{
	string Vn = "";
	string Vnt = Vn + this->Terminate;
	Generate *p = this->head;
	/**/
	bool isContinue = true;//判定Vn 是否增加了
	while(isContinue)
	{
		int flag = 1;
		isContinue = false;
		p = this->head;
		p = p->next;
		while(p != NULL)
		{
			
			flag = 1;
			for(int i=0;i<p->right.length();i++)
			{
				if(Vnt.find(p->right[i]) == (-1))
				{
					flag = 0;
					break;
				}
			}
			if(flag == 1)
			{
				//Vn增大
				
				if(Vnt.find(p->left) == (-1))
				{
					isContinue = true;
					Vn = Vn + p->left;
					Vnt = Vnt + p->left;
				}
			}
			
			p = p->next;
		}
	}
	
	/*筛选*/
	p = this->head;
	p = p->next;
	int flag = 1;
	Generate *pHead = new Generate;
	Generate *pN = pHead;
	while(p != NULL)
	{
		flag = 1;
		for(int i=0;i<p->right.length();i++)
		{
			if(Vnt.find(p->right[i]) == (-1))
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
		{
			Generate *pNextG = new Generate;
			pNextG->left = p->left;
			pNextG->right = p->right;
			pNextG->next = NULL;
			pN->next = pNextG;
			pN = pNextG;
		}
		p = p->next;
	}
	Grammar::SetNonterminate(Vn);
	Grammar::SetGenerate(pHead);
}
void Grammar::algorithm22()
{
	string Vn = "";
	Vn = Vn + this->start;
	string Vt = "";
	Generate *p;
	bool isContinue = true;//判定Vn Vt 是否增加了
	while(isContinue)
	{
		int flag = 1;
		isContinue = false;
		p = this->head;
		p = p->next;
		while(p != NULL)
		{
			flag = 1;
			if(Vn.find(p->left) != -1)
			{
				/*
				for(int i=0;i<p->right.length();i++)
				{
					if(this->Nonterminate.find(p->right[i]) != (-1))
					{
						if(Vn.find(p->right[i]) == (-1))
						{
							isContinue = true;
							Vn = Vn + p->right[i];
						}
					}else
					{
						if(this->Terminate.find(p->right[i]) != (-1))
						{
							if(Vt.find(p->right[i]) == (-1))
							{
								//Vt增大
								isContinue = true;
								Vt = Vt + p->right[i];
							}
						}
					}
				}*/
				/**/
				for(int i=0;i<p->right.length();i++)
				{
					if(this->Nonterminate.find(p->right[i]) == (-1))
					{
						flag = 0;
						break;
					}
				}
				
				if(flag == 1)
				{
					//Vn增大
					for(int i=0;i<p->right.length();i++)
					{
						if(Vn.find(p->right[i]) == (-1))
						{
							isContinue = true;
							Vn = Vn + p->right[i];
						}
					}
				}
				/**/
			}
			/**/
			flag = 1;
			if(Vn.find(p->left) != -1)
			{
				for(int i=0;i<p->right.length();i++)
				{
					if(this->Terminate.find(p->right[i]) == (-1))
					{
						flag = 0;
						break;
					}
				}
				if(flag == 1)
				{
					
					for(int i=0;i<p->right.length();i++)
					{
						if(Vt.find(p->right[i]) == (-1))
						{
							//Vt增大
							isContinue = true;
							Vt = Vt + p->right[i];
						}
					}
				}
			}/**/
			p = p->next;
		}
	}
	/*筛选*/
	string Vnt = Vt + Vn;
	int flag = 1;
	p = this->head;
	p = p->next;
	Generate *pHead = new Generate;
	Generate *pN = pHead;
	while(p != NULL)
	{
		if(Vnt.find(p->left) != -1)
		{
			for(int i=0;i<p->right.length();i++)
			{
				if(Vnt.find(p->right[i]) == (-1))
				{
					flag = 0;
					break;
				}
			}
			if(flag == 1)
			{
				//Vn增大
				Generate *pNextG = new Generate;
				pNextG->left = p->left;
				pNextG->right = p->right;
				pNextG->next = NULL;
				pN->next = pNextG;
				pN = pNextG;
			}
		}
		p = p->next;
	}
	Grammar::SetGenerate(pHead);
}
/*算法2.3找出可推导出ε的非终结符
 *算法2.4、算法2.4消除ε-产生式
 */
string Grammar::algorithm23()
{
	string W;
	Generate *p = this->head;
	/**/
	bool isContinue = true;//判定W 是否增加了
	p = p->next;
	while(p != NULL)
	{
		if(p->right == "&")//ε-产生式
		{
			if(W.find(p->left) == -1)
			{
				W = W + p->left;
			}
		}
		p = p->next;
	}
	int flag = 1;
	while(isContinue)
	{
		isContinue = false;
		p = this->head;
		p = p->next;
		while(p != NULL)
		{
			flag = 1;
			for(int i=0;i<p->right.length();i++)
			{
				if(W.find(p->right[i]) == (-1))
				{
					flag = 0;
					break;
				}
			}
			if(flag == 1)
			{
				if(W.find(p->left) == (-1))
				{
					W = W+p->left;
					isContinue = true;
				}
			}
			p = p->next;
		}
	}

	return W;
}
/*判定执行算法2.4或算法2.5*/
bool Grammar::isRunAlgorithm25()
{
	string W = this->algorithm23();
	if(W.find(this->start) == -1)
	{
		return false;
	}else
	{
		return true;
	}
}
/*产生新的 P*/
Generate* addGenerate(Generate *pG,Generate *pNode,string w)
{
	int count = 0;
	Generate *p = pG;
	string right = "";
	string W_="",NonW_="";
    if(pNode->right == "&")
        return NULL;
	for(int i=0;i<pNode->right.length();i++)
	{
		if(pNode->right[i] == '&')
			break;
		if(w.find(pNode->right[i]) != -1)
		{
			W_ = W_ + pNode->right[i];
			count ++;
		}else
		{
			NonW_ = NonW_ + pNode->right[i];
		}
	}

	for(int j=0;j<(1<<count);j++)
	{
		right = NonW_;
		int r,y,index = 0;
		r = j;
		while(1)
		{
			y = r%2;
			r = r/2;
			if(y == 1)
			{
				right = right + W_[index];
			}
			index ++;
			if(r == 0)
			{
				break;
			}
		}
		if(right != "&")
		{
			Generate *pNextG = new Generate;
			pNextG->left = pNode->left;
			pNextG->right = right;
			pNextG->next = NULL;
			p->next = pNextG;
			p = pNextG;
		}
	}
	return p;
}
void Grammar::algorithm24And25()
{
	string W = Grammar::algorithm23();
	string NonW = "";
	string Vnt = this->Nonterminate + this->Terminate;
	//产生Vnt - W
	for(int i=0;i<Vnt.length();i++)
	{
		if(W.find(Vnt[i]) == -1)
		{
			NonW = NonW + Vnt[i];
		}
	}
	
	Generate *p = this->head;
	p = p->next;
	Generate *pGenerate = new Generate;
	Generate *pH = pGenerate;
	while(p != NULL)
	{
        pH = (addGenerate(pH,p,W)==NULL)?pH:addGenerate(pH,p,W);
		p = p->next;
	}
	if(this->isRunAlgorithm25())
	{
		Generate *pNextG = new Generate;
		pNextG->left = this->start;
		pNextG->right = "&";
		pNextG->next = NULL;
		pH->next = pNextG;
		pH = pNextG;
	}
	Grammar::SetGenerate(pGenerate);
}
void Grammar::algorithm26()
{
	//算法2.6 消除单产生式
	Generate *p;
	Generate *pGenerate = new Generate;
	Generate *pH = pGenerate;
	string Wi = "";
	int flag = 1;
	bool isContinue = true;//判定Wi 是否增加了
	for(int i=0;i<this->Nonterminate.length();i++)
	{
		char left = this->Nonterminate[i];
		Wi = left;
		isContinue = true;
		while(isContinue)
		{
			isContinue = false;
			p = this->head;
			p = p->next;
			//构造Wi
			while(p != NULL)
			{
				if(Wi.find(p->left) != -1)
				{
					/*
					flag = 1;
					for(int j=0;j<p->right.length();j++)
					{
						if(this->Nonterminate.find(p->right[j]) == -1)
						{
							flag = 0;
							break;
						}
					}
					if(flag == 1)
					{
						for(int k=0;k<p->right.length();k++)
						{
							if(Wi.find(p->right[k]) == -1)
								Wi = Wi + p->right[k];
						}
						
					}
					*/
					if(p->right.length() ==1 && this->Nonterminate.find(p->right) != -1)
					{
						if(Wi.find(p->right) == -1)
						{
							isContinue = true;
							Wi = Wi + p->right;
						}
					}
				}
				p = p->next;
			}
		}
		//构造Pi
		p = this->head;
		p = p->next;
		string right = "";
		while(p != NULL)
		{
			if(Wi.find(p->left) != -1)
			{
				right = p->right;
				
				if(!(right.length()==1 &&this->Nonterminate.find(right) != -1))
				{
					Generate *pNextG = new Generate;
					pNextG->left = left;
					pNextG->right = right;
					pNextG->next = NULL;
					pH->next = pNextG;
					pH = pNextG;
				}
			}
			p = p->next;
		}
	}
	Grammar::SetGenerate(pGenerate);
}
