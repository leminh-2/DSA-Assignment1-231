#include "main.h"
/*initialize global variables
-restaurant circle DLL (tao currentNode) (name: RTR_CDLL)
-waitqueue DLL queue
-timelist DLL queue (includes order of customers enter the restaurants, include customers in waitqueue and in restaurant)
*/
class imp_res : public Restaurant
{
public:
	imp_res(){};
	~imp_res()
	{
		remember to deallocate global variables;
	}
	void RED(string name, int energy)
	{
		cout << name << " " << energy << endl;

		// pseudocode
		if (energy == 0)
			return;
		if (size_DLL == 0)
		{
			// initialize the first customer
			// update currentNode
			// add node to timelist
		}
		else
		{
			if (size_DLL == MAXSIZE && size_queue == MAXSIZE)
			{
			}
			else
			{
				// check whether name has existed in the queue and DLLcustomer
				bool existed = checkNameExists(name);
				check in timelist //"ABC" "abc" "Abc" là những thằng khác tên -> không cần xét case-sensitive
					if (!existed)
				{
					if (size_DLL < MAXSIZE)
					{
						if (size_DLL >= MAXSIZE / 2)
						{
							// find current customer for this case
							// quy tac tim current customer:
							// Có nhiều vị trí sau khi tính đều trả về cùng giá trị RES thì sẽ chọn vị trí đầu tiên tìm được theo chiều kim đồng hồ.
							// Chỉ có một giá trị RES lớn nhất tìm được thì chọn vị trí đó.
							customer *currentTemp = new customer();
							currentTemp = currentNode;
							customer *walk = new customer();
							walk = currentNode;
							int res = 0;
							do
							{
								int resTemp = abs(energy - walk->energy);
								if (resTemp > res)
								{
									res = resTemp;
									currentTemp = walk;
								}
								walk = walk->next;
							} while (walk != currentNode);
							currentNode = currentTemp;
						// DLL have currentNode
						parameter:
							customer *walk, gán currentNode = walk;
						}
						// add node to next/prev node of currentNode
						// remember: tro currentNode (X) vao inserted node
						if (energy >= currentNode->energy)
						{
							add clockwise node(next);
							add node to timelist
						}
						else
						{
							add counter - clockwise node(prev);
							add node to timelist
						}
					}
					else
					{
						// add node to waitqueue
						// add node to timelist
					}
				}
			}
		}
		// end pseudo-code

		// remember to deallocate dynamic memory
	}
	void BLUE(int num)
	{
		// by-default: num > 0
		cout << "blue " << num << endl;
		if (num >= size_DLL)
			num = size_DLL;

		// step: xoa customers ra khoi DLL
		if (num == size_DLL)
		{
			// chay ham clear DLL restaurant
			currentNode = nullptr;
			// clear MAXSIZE first customers in timelist (first in first out)
		}
		else
		{
			// rule: đuổi NUM vị khách theo thứ tự vào nhà hàng từ sớm nhất đến gần đây nhất.
			// loop num times to remove num customers{
			string imp_res::dequeueTimeList() tra ve tring cua customer cần đuổi

				tìm customer in restaurant trùng name value->trỏ vào currentNode
					customer *walk = currentNode;
			do
			{
				if (walk->name == name)
				{
					currentNode = walk;
					break;
				}
				walk = walk->next;
			} while (walk != currentNode);

			// xu ly currentNode X
			customer *currentNodeAfterRemove = currentNode;
			if (currentNode->energy > 0)
				currentNodeAfterRemove = currentNode->next;
			else
				currentNodeAfterRemove = currentNode->prev; // case: customer->energy < 0
			if (size_restaurant == 1)
				currentNodeAfterRemove = nullptr; // case: size_restaurant = 1

			remove customer(input parameter
							: name) // function from circular DLL
				// update currentNode
				currentNode = currentNodeAfterRemove;

			// note: call remove function from class DLL (already included size--;)
		}

		// step: void function with loop (read waitqueue, run RED <name> <energy>)
		write insertWait2Restaurant()
		{
			// case: size_waitqueue > (maxsize - size_restaurant) -> chen (maxsize - size_restaurant) customers vào restaurant
			// case: size_waitqueue < (maxsize - size_restaurant) -> chen size_waitqueue customers vào restaurant
			// case: size_waitqueue = (maxsize - size_restaurant) -> chen size_waitqueue customers vào restaurant
			int compareWaitRestaurant = size_waitqueue - (MAXSIZE - size_restaurant);
			if (compareWaitRestaurant > 0)
			{
				// chen (maxsize - size_restaurant) customers vào restaurant
				for (int i = 0; i < (MAXSIZE - size_restaurant); i++)
				{
					// read waitqueue
					// xoa head of queue
					// run RED <name> <energy>
				}
			}
			else
			{
				// chen size_waitqueue customers vào restaurant
				for (int i = 0; i < size_waitqueue; i++)
				{
					// read waitqueue
					// xoa head of queue
					// run RED <name> <energy>
				}
			}
		}

		// remember to deallocate dynamic memory
	}
	void PURPLE()
	{
		// SORT THEO THU TU GIAM DAN
		cout << "purple" << endl;
		// tim vi tri cua KH co max abs(energy) in waitqueue
		// if 2 waiting customers có cùng energy -> chọn thằng được thêm gần nhất
		customer *maxE = head of queue;
		customer *walk = maxE->next();
		while (walk != nullptr)
		{
			if (walk->energy >= maxE->energy)
				maxE = walk; // operator >= để chọn thằng được thêm gần nhất
			walk = walk->next;
		}

		// step: shell sort
		void nextByIndex(customer* start, int index){
			customer* walk = start;
			for(int i=0; i<index; i++){
				walk = walk->next;
			}
			return walk;
		}
		void swap(customer* cus1, customer* cus2){
			int energy = cus1->energy;
			string name = cus1->name;
			cus1->energy = cus2->energy;
			cus1->name = cus2->name;
			cus2->energy = energy;
			cus2->name = name;
		}
		int inssort2(customer* start, int n, int incr){
			int swap = 0;
			for(int i=incr; i<n; i+=incr){
				int j=i;
				customer* posJ = nextByIndex(start, j);
				customer* posJMinusIncr = nextByIndex(start, j-incr);
				while(j>=incr && compare(posJ,posJMinusIncr)){
					swap(posJ,posJMinusIncr);
					swap++;

					j-=incr;
					if(j<incr) break;
					posJ = nextByIndex(start, j);
					posJMinusIncr = nextByIndex(start, j-incr);
				}
			}
			return swap;
		}
		int shellSort(customer* start, customer* end){
			//find the number of customers in the list]
			int result = 0;
			int n=0;
			customer* walk = start;
			while(walk != end){
				n++;
				walk = walk->next;
			}
			n++;

			for(int i=n/2; i>=1; i/=2){
				if(i == 2) continue;
				for(int j=0; j<i; j++){
					result += inssort2(nextByIndex(start,j), n-j, i);
				}
			}
			result += inssort2(start, n, 1);

			return result;
		}

		if (n % MAXSIZE != 0)
			this->BLUE(n % MAXSIZE);

		// remember to deallocate dynamic memory
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
		// read restaurant to create 2 queue positive and negative DLL
		customer *walk = new customer();
		walk = currentNode;
		initialize 2 queue do
		{
			if (walk->energy > 0)
			{
				add node to queue positive
			}
			else
			{
				add node to queue negative
			}
			walk = walk->prev; // prev vì traverse nguoc chieu kim dong ho
		}while (walk != currentNode);

		customer *tailPositive, tailNegative trỏ vào node cuối của 2 queue

		// traverse all nodes in restaurant and change the energy
		// confusion: after REVERSAL, x point to energy -12
		//when begining: X->next point to energy -12
		walk = currentNode;
		for (int i = 0; i < size_restaurant; i++)
		{
			if (walk->energy > 0)
			{
				walk->energy = tailPositive->energy;
				walk->name = tailPositive->name;
				tailPositive = tailPositive->prev;
			}
			else
			{
				walk->energy = tailNegative->energy;
				walk->name = tailNegative->name;
				tailNegative = tailNegative->prev;
			}
			walk = walk->next;
		}

	remember:
		clear 2 queues positive and negative(deallocate the dynamic memory)
		// remember to deallocate dynamic memory
	}
	void UNLIMITED_VOID()
	{
		//base case
		if(sizeCDLL < 4) return;

		//initialize current variable as the first case (with size=4 and subHead = X->next)
		int sizeUnlimited = 4;
		int sumUnlimited = 0;
		customer* subHead = X->next;
		customer* walk0 = X->next;
		for(int i=0; i<sizeUnlimited; i++){
			sumUnlimited += walk0->energy;
			walk0 = walk0->next;
		}
		
		//traverse all cases to find sumE minimum
		for(size start from 4 and end to sizeCDLL; size++){
			for(customer* walk: start = X->next; end = X->next->prev){
				//tinh sum of energy and determine the size of sublist
				int sizeUnlimitedtemp = size;
				int sumUnlimitedtemp = 0;
				customer* subHeadtemp = walk;
				for(int i=0; i<sizeUnlimitedtemp; i++){
					sumUnlimitedtemp += subHeadtemp->energy;
					subHeadtemp = subHeadtemp->next;
				}

				//compare temp variable with current variable using boolean change
				bool change;
				//change = true: choose the temp variable
				//change = false: choose the current variable
				if(sumUnlimitedtemp > sumUnlimited){
					//do nothing
					change = false;
				}
				else if(sumUnlimitedtemp < sumUnlimited){
					//update temp variable
					change = true;
				}
				else{
					//case: sumtemp == sumUnlimited
					if(sizeUnlimitedtemp > sizeUnlimited){
						//update temp variable
						change = true;
					}
					else if(sizeUnlimitedtemp < sizeUnlimited){
						//do nothing
						change = false;
					}
					else{
						//case: sizeUnlimitedtemp == sizeUnlimited
						change = true;
					}
				}
				if(change){
					//update current variable
					sizeUnlimited = sizeUnlimitedtemp;
					sumUnlimited = sumUnlimitedtemp;
					subHead = subHeadtemp;
				}
			}
		}

		//find the position whose energy is minimum
		//variable: customer* subHead(already), subTail, posEnergyMin; int sizeUnlimited (already)
		customer* subTail = subHead;
		for(int i=0; i<sizeUnlimited-1; i++){
			subTail = subTail->next;
		}
		
		customer* posEnergyMin = subHead;
		int indexE = 0;
		customer* walkMin = subHead;
		for(int i=0; i<sizeUnlimited; i++){
			if(posEnergyMin->energy > walkMin->energy){
				posEnergyMin = walkMin;
				indexE = i;
			}
			walkMin = walkMin->next;
		}
		//here: subTail, posEnergyMin, indexE is already

		//print the result
		if(subHead == posEnergyMin){
			//case: subHead == posEnergyMin
			//action: print from subHead to subTail
			customer* walkPrint = subHead;
			for(int i=0; i<sizeUnlimited; i++){
				walkPrint->print();
				walkPrint = walkPrint->next;
			}
		}
		else{
			//case: posEnergyMin == subTail or posEnergyMin in (subHead, subTail)
			//action: print from posEnergyMin to subTail, subHead to posEnergyMin->prev
			customer* walkPrint = posEnergyMin;
			for(int i=0; i<sizeUnlimited-indexE; i++){ 
				//print sizeUnlimited-indexE customers from posEnergyMin to subTail
				walkPrint->print();
				walkPrint = walkPrint->next;
			}
			walkPrint = subHead;
			for(int i=0; i<indexE; i++){
				//print indexE customers from subHead to posEnergyMin->prev
				walkPrint->print();
				walkPrint = walkPrint->next;
			}

		}




		cout << "unlimited_void" << endl;

		// remember to deallocate dynamic memory
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
		// calculate oanlinh score and chuthuatsu score
		int chuThuatSuScore = 0, oanLinhScore = 0;
		customer *walk = new customer();
		walk = currentNode;
		do
		{
			if (walk->energy > 0)
				chuThuatSuScore += walk->energy;
			else
				oanLinhScore += walk->energy;
			walk = walk->next;
		} while (walk != currentNode);
		oanLinhScore = abs(oanLinhScore);

		// step: duoi chuthuatsu or oanlinh
		if (chuThuatSuScore >= oanLinhScore)
		{
			int index = 0;
			// đuổi toàn bo oan linh
			string OLname = readOanLinhTimeList(index); //include: using print function
			while(OLname != ""){
				//find and clear customer in WaitQueue
				bool removeAtWaitQueue = removeAtNameWaitQueue(string CTSname);
				//true: we have remove customer in waitqueue
				//false: we have not remove customer in waitqueue, 
				//so we need to remove customer in Restaurant

				if(removeAtWaitQueue == false){
					//tro X->next vao customer co name tim duoc (customer can xoa)
					customer* walk = X->next;
					if(walk){
						do{
							if(walk->name == OLname){
								X->next = walk;
								break;
							}
							walk = walk->next;
						} while(walk != X->next);
					}
					//luu tam temp X->next de assign lai sau khi xoa customer
					customer* tempXnext = X->next;
					if(X->next->energy > 0) tempXnext = X->next->next;
					else tempXnext = X->next->prev;
					if(sizeCDLL == 1) tempXnext = nullptr;

					//remove customer in CDLL
					removeAtNameCDLL(string OLname); //include sizeCDLL--;

					//update X->next
            		X->next = tempXnext;
				}
				//loop to find next customer
				CTSname = readOanLinhTimeList(++index); //include: using print function		
			}
			//function clearANDprintOanLinhTimeList
			
		}
		else
		{
			int index = 0;
			// đuổi toàn bộ chu thuat su
			string CTSname = readChuThuatSuTimeList(index); //include: using print function
			//build lai dua tren string dequeueTimeList();
			while(CTSname != ""){
				//find and clear customer in WaitQueue
				bool removeAtWaitQueue = removeAtNameWaitQueue(string CTSname);
				//true: we have removed customer in waitqueue
				//false: we have not removed customer in waitqueue, 
				//so we need to remove customer in Restaurant

				if(removeAtWaitQueue == false){
					//tro X->next vao customer co name tim duoc (customer can xoa)
					customer* walk = X->next;
					if(walk){
						do{
							if(walk->name == CTSname){
								X->next = walk;
								break;
							}
							walk = walk->next;
						} while(walk != X->next);
					}
					//luu tam temp X->next de assign lai sau khi xoa customer
					customer* tempXnext = X->next;
					if(X->next->energy > 0) tempXnext = X->next->next;
					else tempXnext = X->next->prev;
					if(sizeCDLL == 1) tempXnext = nullptr;

					//remove customer in CDLL
					removeAtNameCDLL(string CTSname); //include sizeCDLL--;

					//update X->next
            		X->next = tempXnext;
				}
				//loop to find next customer
				CTSname = readChuThuatSuTimeList(++index); //include: using print function		
			}
			//function clearANDprintChuThuatSuTimeList
			
		}

		// step: xep hàng đợi vào restaurant
		insertWait2Restaurant();

		// remember to deallocate dynamic memory
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
		if (num > 0)
		{
			customer *walk = new customer();
			walk = currentNode;
			do
			{
				cout << walk->name << "-" << walk->energy << endl;
				walk = walk->next;
			} while (walk != currentNode);
		}
		else if (num < 0)
		{
			customer *walk = new customer();
			walk = currentNode;
			do
			{
				cout << walk->name << "-" << walk->energy << endl;
				walk = walk->prev;
			} while (walk != currentNode);
		}
		else
		{
			// case: num == 0
			customer *walk = new customer();
			walk = head of waitqueue;
			while (walk != nullptr)
			{
				cout << walk->name << "-" << walk->energy << endl;
				walk = walk->next;
			}
		}
		// remember to deallocate dynamic memory
	}
};