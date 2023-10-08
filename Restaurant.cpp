#include "main.h"
class imp_res : public Restaurant
{
	customer *cur;
	customer *qHead, *qCur;
	customer *first, *last;
	int curSize,qSize;
	public:	
		imp_res() {
			cur=qHead = qCur = first = last =  nullptr;
			curSize =qSize =  0;
		};
		void deleteNode(customer* p){
			customer* pPrev = p->prev;
			customer* pNext = p->next;
			cur = p;
			if(cur->energy >0) cur = cur->next;
			else cur = cur->prev;
			if(pPrev) pPrev->next = pNext;
			if(pNext) pNext->prev = pPrev;
			// p->next = p->prev = 0;
			delete p;
			curSize--;
			if(curSize==1)
				cur->next = cur->prev = nullptr;
		}
		void popQueue(){
			
			customer * temp = qHead;
			
			qHead = qHead->next;
			
			// temp->next = temp->prev = nullptr;
			delete temp;
			if(qHead)
				qHead->prev = nullptr;
			qSize--;
		}
		void RED(string name, int energy)
		{
			
			if(!energy){
				return;
			}
			if(cur){
				customer *p = cur;
				for(int i =0; i<curSize; i++){
					if(name == p->name){
						return;
					}
					p = p->next;
				}
			}
			
			if(qHead){
				customer *p = qHead;
				for(int i=0; i<qSize; i++){
					if(name == p->name)
						return;
					p = p->next;
				}
			}
			
			if(curSize >= MAXSIZE){
				if(qSize < MAXSIZE){
					if(!qSize){
						qHead = qCur = new customer(name,energy,nullptr,nullptr);
					}
					else {
						qCur->next = new customer(name,energy,qCur,nullptr);
						qCur = qCur->next;
					}
					qSize++;
				}
				else return;
			}
			else {
				
				if(curSize < MAXSIZE/2){
					if(!cur){
						cur = new customer (name, energy, nullptr, nullptr);
						first = last = new customer(name, energy,nullptr,nullptr);
					}
					else{
						if(energy >= cur->energy){
							customer *cusNext = cur->next;
							if(cusNext){
								cur->next = new customer(name,energy,cur,cusNext);
								cur = cur->next;
								cusNext->prev = cur;
							}
							else {
								cur->next = new customer(name, energy, cur,nullptr);
								/// make cirly linked list
								
								cusNext= cur->next;
								cusNext->next = cur;
								cur->prev = cusNext;
								cur = cur->next;
								
							}
						}
						else{
							customer *cusPrev = cur->prev;
							if(cusPrev){
								cur->prev = new customer(name, energy, cusPrev, cur);
								cur  = cur->prev;
								cusPrev->next = cur;
							}
							else{
								cur->prev = new customer(name, energy, nullptr, cur);
								cusPrev = cur->prev;
								cusPrev->prev=  cur;
								cur->next = cusPrev;
								cur = cur->prev;
								///make cirly ll
							}
						}
						last->next = new customer(name,energy,last,nullptr);
						last = last->next;
					}
					curSize++;
				}
				else{
					bool isNegative = false;
					int res = 0;
					customer* p =cur;
					customer* pos = cur;
					for(int i=0; i<curSize; i++){
						if( res < abs(abs(energy) - abs(p->energy))){
							res = abs(abs(energy) - abs(p->energy));
							((abs(energy) - abs(p->energy))<0)? isNegative = true : isNegative = false;
							pos = p;
						}
						p = p->next;
					}
					cur = pos;
					if(!cur){
						cur = new customer (name, energy, nullptr, nullptr);
						first = last = new customer(name, energy,nullptr,nullptr);
					}
					else{
						if(energy >= cur->energy){
							customer *cusNext = cur->next;
							if(cusNext){
								cur->next = new customer(name,energy,cur,cusNext);
								cur = cur->next;
								cusNext->prev = cur;
							}
							else {
								cur->next = new customer(name, energy, cur,nullptr);
								
								cusNext= cur->next;
								cusNext->next = cur;
								cur->prev = cusNext;
								cur = cur->next;
								
							}
						}
						else{
							customer *cusPrev = cur->prev;
							if(cusPrev){
								cur->prev = new customer(name, energy, cusPrev, cur);
								cur  = cur->prev;
								cusPrev->next = cur;
							}
							else{
								cur->prev = new customer(name, energy, nullptr, cur);
								cusPrev = cur->prev;
								cusPrev->prev=  cur;
								cur->next = cusPrev;
								cur = cur->prev;
							}
						}
						last->next = new customer(name,energy,last,nullptr);
						last = last->next;
					}
					curSize++;
				}

			}
			
		}
		void BLUE(int num)
		{
			if(num >= curSize){
				num = curSize;
			}
			for(int i=0; i< num; i++){
				customer* cus = cur;
				for(int j=0; j<curSize; j++){
					if(cus->name == first->name){
						deleteNode(cus);
						break;
					}
					else{
						cus = cus->next;
					}
				}
				first = first->next;
				if(first){
					first->prev->next = nullptr;
					delete first->prev;
					first->prev = nullptr;
				}
				else{
					last = nullptr; // = first
				}
			}
			for(int i=0; i < num; i++){
				
				if(qSize){
					customer* cus = qHead;
					string name = cus->name;
					int energy = cus->energy;
					popQueue();
					RED(name,energy);
				}
				else break;
			}
		}
		int inssort(customer*p, int n , int incr){
			int N = 0;
			for(int i = incr; i<n; i+=incr){
				int q = incr;
				
				while(q--){
					p = p->next;
				}
				customer* p1 = p;
				for(int j =i; j>= incr; j-=incr){
					q = incr;
					customer* p2 = p1;
					while(q--){
						p2 = p2->prev;
					}
					if(abs(p2->energy) < abs(p1->energy) && incr != 1){
						if(p==p1){
							p = p2;
						}
						customer* prevP2 = p2->prev;
						customer* nextP2 = p2->next;
						customer* prevP1 = p1->prev;
						customer* nextP1 = p1->next;
						customer* temp = p2;
						p2 = p1;
						p1 = temp;
						if(prevP2){
							prevP2 ->next = p2;
							p2->prev = prevP2;
						}
						else{
							qHead = p2;
							p2->prev = nullptr;
						}
						p2->next = nextP2;
						nextP2->prev = p2;

						if(nextP1){
							nextP1 ->prev = p1;
							p1->next = nextP1;
						}
						else{
							qCur = p1;
							p1->next = nullptr;
						}
						p1->prev = prevP1;
						prevP1->next = p1;
						N++;
					}
					if(abs(p2->energy) < abs(p1->energy) && incr ==1){
						if(p==p1) p = p2;
						customer* prevNode = p2->prev;
						customer* nextNode = p1->next;
						customer* temp = p2;
						p2 = p1;
						p1 = temp;
						p2->next = p1;
						p1->prev = p2;
						p1->next = nextNode;
						if(nextNode) nextNode->prev = p1;
						else qCur = p1;
						p2->prev = prevNode;
						if(prevNode) prevNode->next = p2;
						else qHead  = p2;
						N++;
					}
					q = incr;
					while(q--){
						p1= p1->prev;
					}
				}
			}
			return N;
		}
		int shellSort(int n){
			int N = 0;
			customer* p = qHead;
			for(int i= n/2; i>2; i/=2){
				for(int j =0; j<i; j++){
					N+=inssort(p,n-j, i);
					cout<<endl;
					p =qHead;
					int pos = j;
					while(pos--){
						p = p->next;
					}
					p = p->next;
				}
			}
			N+=inssort(qHead,n,1);
			return N;
		}
		void PURPLE() // con` bug
		{
			int MAX_ENERGY = 0;
			customer* p = qCur;
			int pos;
			for(int i=qSize; p; i--){
				if(MAX_ENERGY <= p->energy){
					MAX_ENERGY = p->energy;
					pos = i;
				}
				p = p->prev;
			}
			BLUE(shellSort(pos) % MAXSIZE);
		}
		void REVERSAL() //sai
		{
			customer *p = cur;
			for(int i =0; i<curSize; i++){
				customer* temp = p->next;
				p->next = p->prev;
				p->prev = temp;
				p = p->next;
			}
			
		}
		void UNLIMITED_VOID()
		{
			if(curSize < 4) return;
			customer* minPos = cur; 
			customer* target = cur;
			int res = INT_MAX;
			int targetSize = 0;
			customer* p = cur;
			for(int i =0; i<curSize; i++){
				for(int size = 4; size < curSize; size++){
					int sum = 0;
					
					customer* pp =p;
					int minEnergy = pp->energy;
					minPos = pp;
					sum += pp->energy;
					for(int k=1; k< size; k++){
						pp = pp->next;
						sum+= pp->energy;
						if(pp->energy < minEnergy){
							minEnergy = pp->energy;
							minPos = pp;
						}
					}
					if(res > sum){
						res = sum;
						targetSize = size;
						target = p;
					}
				}
				p = p->next;
			}
			cout<<minPos->energy<<endl;
			while(targetSize--){
				target->print();
				target = target->next;
			}
		}
		void DOMAIN_EXPANSION()
		{
			int pos = 0;
			int neg = 0;
			customer *p = cur;
			for(int i =0; i<curSize; i++){
				if(p->energy < 0){
					neg +=p->energy;
				}
				else 
					pos+= p->energy;
				p = p->next;

			}
			p = qHead;
			for(int i =0; i< qSize; i++){
				if(p->energy < 0){
					neg +=p->energy;
				}
				else 
					pos+= p->energy;
				p = p->next;
			}

			if((-neg) > pos){
				customer* p = last;
				while (p)
				{
					if(p->energy > 0){
						customer * temp = p;
						customer* nextPos = p->next;
						customer* prevPos = p->prev;
						if(prevPos) prevPos->next = nextPos;
						if(nextPos) nextPos->prev = prevPos;

						customer* cus= cur;
						for(int i=0; i< curSize; i++){
							if(cus->name == temp->name){
								deleteNode(cus);
								break;
							}
						}

						p = p->prev;
						temp->next = temp->prev = nullptr;
						delete temp;
					}
					else p = p->prev;
				}
				
			}
			else {
				customer* p = last;
				while (p)
				{
					if(p->energy < 0){
						customer * temp = p;
						customer* nextPos = p->next;
						customer* prevPos = p->prev;
						if(prevPos) prevPos->next = nextPos;
						if(nextPos) nextPos->prev = prevPos;

						customer* cus= cur;
						for(int i=0; i< curSize; i++){
							if(cus->name == temp->name){
								cus->print();
								deleteNode(cus);
								break;
							}
							cus = cus->next;
						}

						p = p->prev;
						temp->next = temp->prev = nullptr;
						delete temp;
					}
					else p = p->prev;
				}
			}

			while(curSize < MAXSIZE){
				if(qSize){
					customer* cus = qHead;
					string name = cus->name;
					int energy = cus->energy;
					popQueue();
					RED(name,energy);
				}
				else break;
			}
		}
		void LIGHT(int num)
		{
			cout<<"----------------------"<<endl;
			if(num > 0){
				customer *p = cur;
				for(int i =0; i<curSize; i++){
					p->print();
					p = p->next;
				}
			}
			else if(num < 0){
				customer * p = cur;
				for(int i=0; i<curSize; i++){
					p->print();
					p = p->prev;
				}
			}
			else {
				customer *p = qHead;
				for(int i=0; i<qSize ; i++){
					p->print();
					p = p->next;
				}
			}
		}
};
// old tc
// RED ABC -123
// RED BCD 456
// RED DEF 1
// RED A 123
// RED B -98
// RED C 12
// RED D -12
// RED E 1
// RED H 50

// RED X 1
// RED Y 2
// RED Z 3
// RED M 4
// RED G 100