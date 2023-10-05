#include "main.h"
extern int MAXSIZE;
class imp_res : public Restaurant
{
	customer *cur;
	customer *qHead, *qCur;
	customer *first, *last;
	int curSize,qSize;
	public:	
		imp_res() {
			cur= 0;
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
			p->next = p->prev = 0;
			delete p;
			curSize--;
			if(curSize==1)
				cur->next = cur->prev = nullptr;
		}
		void popQueue(){
			
			customer * temp = qHead;
			
			qHead = qHead->next;
			
			temp->next = temp->prev = nullptr;
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
		void shellSort(int pos){
			cout<<"SHELLSORT HERE"<<endl;
		}
		void PURPLE()
		{
			int MAX_ENERGY = 0;
			customer* p = first;
			int pos;
			for(int i=0; p; i++){
				if(MAX_ENERGY <= p->energy){
					MAX_ENERGY = p->energy;
					pos = i;
				}
			}
			shellSort(pos);

		}
		void REVERSAL()
		{
			
		}
		void UNLIMITED_VOID()
		{
			
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