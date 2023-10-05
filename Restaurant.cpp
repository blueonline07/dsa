#include "main.h"
extern int MAXSIZE;
class imp_res : public Restaurant
{
	customer *start, *end,*cur;
	customer *qHead, *qCur;
	customer *first, *last;
	int curSize,qSize;
	public:	
		imp_res() {
			start = end = cur= 0;
			curSize =qSize =  0;
		};
		customer* getQueue(){
			return qHead;
		}
		void popQueue(){
			customer * temp = qHead;
			qHead = qHead->next;
			temp->next = temp->prev = nullptr;
			delete temp;
			qHead->prev = nullptr;
		}
		void RED(string name, int energy)
		{
			if(!energy){
				return;
			}
			if(start){
				customer *p = start;
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
						start = end =  cur = new customer (name, energy, nullptr, nullptr);
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
								cur = cur->next;
								/// make cirly linked list
								cur->next = start;
								start->prev = cur;
								end = cur;
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
								cur = cur->prev;
								///make cirly ll
								end->next = cur;
								cur->prev = end;
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
						start = end =  cur = new customer (name, energy, nullptr, nullptr);
						first = last=  new customer(name,energy,nullptr,nullptr);
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
								cur = cur->next;
								/// make cirly linked list
								cur->next = start;
								start->prev = cur;
								end = cur;
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
								cur = cur->prev;
								///make cirly ll
								end->next = cur;
								cur->prev = end;
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
						customer *temp = cus;

						if(temp == cur){
							if(cur->energy > 0) cur = cur->next;
							else cur = cur->prev;
						}
						customer *cusPrev = cus->prev;
						customer *cusNext = cus->next;
						temp->next = nullptr;
						temp->prev = nullptr;
						delete temp;
						if(cusPrev)
							cusPrev->next = cusNext;
						if(cusNext)
							cusNext->prev = cusPrev;
						curSize--;
						break;
					}
					else{
						cus = cus->next;
					}
				}
				first = first->next;
				first->prev->next = nullptr;
				delete first->prev;
				first->prev = nullptr;
			}
			for(int i=0; i < num; i++){
				if(qSize){
					customer* cus = getQueue();
					string name = cus->name;
					int energy = cus->energy;
					RED(name,energy);   /// sai do start = null
					popQueue();
				}
			}
		}
		void PURPLE()
		{
			
		}
		void REVERSAL()
		{
			
		}
		void UNLIMITED_VOID()
		{
			
		}
		void DOMAIN_EXPANSION()
		{
			
		}
		void LIGHT(int num)
		{
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