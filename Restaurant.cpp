#include "main.h"
/*initialize global variables
-restaurant circle DLL (tao X->next) (name: RTR_CDLL)
-waitqueue DLL queue
-TimeList DLL queue (includes order of customers enter the restaurants, include customers in waitqueue and in restaurant)
*/

class imp_res : public Restaurant
{

public:
    //ofstream outputFile; //clear for submit
    customer *X = new customer("", 0, nullptr, nullptr); // dummy node for restaurant
    // not sure: when size = 0, next pointer of X points to X itself or points to nullptr
    int sizeCDLL = 0;

    // initialize global variables
    customer *headWaitQueue = new customer("headWaitQueue", 0, nullptr, nullptr);
    customer *tailWaitQueue = new customer("tailWaitQueue", 0, headWaitQueue, nullptr);
    // headWaitQueue->next = tailWaitQueue; has been called in constructor
    int sizeWaitQueue = 0;

    customer *headTimeList = new customer("headTimeList", 0, nullptr, nullptr);
    customer *tailTimeList = new customer("tailTimeList", 0, headTimeList, nullptr);
    // headTimeList->next = tailTimeList; has been called in constructor
    int sizeTimeList = 0;

    imp_res();

    ~imp_res();
    void RED(string name, int energy);
    void BLUE(int num);
    void PURPLE();
    void REVERSAL();
    void UNLIMITED_VOID();
    void DOMAIN_EXPANSION();
    void LIGHT(int num);

    // helper functions

    void displayCDLL();
    void reverseDisplayCDLL();
    customer *getHead() { return X->next; }

    // for RED command
    void addFirstNodeCDLL(string name, int energy);
    void enqueueWaitQueue(string name, int energy);
    void enqueueTimeList(string name, int energy);
    void displayTimeList();
    void displayWaitQueue();

    // for BLUE command
    void clearCDLL();
    string dequeueTimeList();
    string removeCusHaveTableInTimeList();
    bool existedInCDLL(string name);
    void removeAtNameCDLL(string name);
    void insertWaitQueue2Restaurant(); // update CDLL and waitqueue
    string dequeueWaitQueue(int &energy);
    bool compareCustomerShellSort(customer *latter, customer* former) const;
    void REDQueue2Restaurant(string name, int energy);

    //for PURPLE command
    customer* nextByIndex(customer* start, int index);
    void swap(customer* cus1, customer* cus2);
    int inssort2(customer* start, int n, int incr);
    int shellSort(customer* start, customer* end);
    // for DOMAIN_EXPANSION command
    string readChuThuatSuTimeList(int index);
    bool removeAtNameWaitQueue(string name);
    string readOanLinhTimeList(int index);
    void clearANDprintOanLinhTimeList();
    void clearANDprintChuThuatSuTimeList();

    /*refactoring functions:

    void addCDLLClockwise(int energy, string name);
    void addCDLLCounterClockwise(int energy, string name);
    void addWaitQueue(int energy, string name);
    void addTimeList(int energy, string name);
    bool containsNameInCDLL(string name);
    bool containsNameInWaitQueue(string name);

    //for UNLIMITED command





    */
};

imp_res::imp_res()
{
    headWaitQueue->next = tailWaitQueue;
    headTimeList->next = tailTimeList;
    //outputFile.open("output.txt", std::ios::out); //clear for submit
};

imp_res::~imp_res()
{
    // remember to deallocate global variables
    // deallocate CDLL
    clearCDLL();
    delete X;
    X = nullptr;
    // deallocate TimeList
    for (int i = 0; i < sizeTimeList; i++)
        dequeueTimeList();
    delete headTimeList;
    headTimeList = nullptr;
    delete tailTimeList;
    tailTimeList = nullptr;
    // deallocate WaitQueue
    int energy;
    for (int i = 0; i < sizeWaitQueue; i++)
        dequeueWaitQueue(energy);
    delete headWaitQueue;
    headWaitQueue = nullptr;
    delete tailWaitQueue;
    tailWaitQueue = nullptr;
}

void imp_res::RED(string name, int energy)
{
    if (energy == 0)
        return;
    if (sizeCDLL == 0)
    {
        addFirstNodeCDLL(name, energy); // initilize the first customer & update X
        enqueueTimeList(name, energy);  // add node to timelist
        //cout << "check segmentation fault in RED command with the first customer " <<name << energy << endl;
        return;
    }
    else
    {
        if (sizeCDLL == MAXSIZE && sizeWaitQueue == MAXSIZE)
        {
            return;
            //cout << "check segmentation fault in RED command with no empty place " <<name << energy << endl;
        }
        else
        {
            // check whether name has existed in the queue and DLLcustomer
            bool existedName = false;
            // check in CDLL
            customer *walk = X->next;
            if (walk)
            {
                do
                {
                    if (walk->name == name)
                    {
                        existedName = true;
                        break;
                    }
                    walk = walk->next;
                } while (walk != X->next);
            }

            // check in WaitQueue
            walk = headWaitQueue->next;
            while (walk != tailWaitQueue)
            {
                if (walk->name == name)
                {
                    existedName = true;
                    break;
                }
                walk = walk->next;
            }

            if (!existedName)
            {
                if (sizeCDLL < MAXSIZE)
                {
                    if (sizeCDLL >= MAXSIZE / 2)
                    {
                        // find current customer for this case
                        // quy tac tim current customer:
                        // co nhieu vi tri sau khi tinh deu tra ve cung gia tri RES thi se chon vi tri dau tien tim duoc theo chieu kim dong ho
                        // chi co 1 gia tri RES lon nhat tim duoc thi chon gia tri do
                        customer *walk = X->next;
                        customer *currentTemp = X->next;
                        int res = 0;
                        if (walk)
                        {
                            do
                            {
                                int resTemp = abs(energy - walk->energy);
                                if (resTemp > res)
                                {
                                    res = resTemp;
                                    currentTemp = walk;
                                }
                                walk = walk->next;
                            } while (walk != X->next);
                        }
                        X->next = currentTemp; // gan current customer vao X->next
                    }
                    // add node to next/prev node of X->next
                    // remember: tro X->next (X) vao inserted node
                    if (energy >= X->next->energy)
                    {
                        customer *t = new customer(name, energy, nullptr, nullptr);
                        customer *Xnext = X->next;

                        t->prev = Xnext;
                        t->next = Xnext->next;
                        Xnext->next->prev = t;
                        Xnext->next = t;
                        sizeCDLL++;
                        X->next = t;
                    }
                    else
                    {
                        customer *t = new customer(name, energy, X->next->prev, X->next);
                        t->prev->next = t;
                        t->next->prev = t;
                        sizeCDLL++;
                        X->next = t;
                    }
                    // add node to timelist
                    enqueueTimeList(name, energy);
                }
                else
                {
                    // add node to waitqueue
                    enqueueWaitQueue(name, energy);
                    // add node to timelist
                    enqueueTimeList(name, energy);
                }
            }
        }
    }
     //cout << "check segmentation fault in RED command with " <<name << energy << endl;
}

void imp_res::REDQueue2Restaurant(string name, int energy)
{
    if (sizeCDLL == 0)
    {
        addFirstNodeCDLL(name, energy); // initilize the first customer & update X
        return;
    }
    else
    {
        if (sizeCDLL < MAXSIZE)
        {
            if (sizeCDLL >= MAXSIZE / 2)
            {
                // find current customer for this case
                // quy tac tim current customer:
                // Co nhieu vi tri sau khi tinh deu tra ve cung gia tri RES thi se chon vi tri dau tien tim duoc theo chieu kim dong ho
                // Chi co mot gia tri RES lon nhat tim duoc thi chon vi tri do
                customer *walk = X->next;
                customer *currentTemp = X->next;
                int res = 0;
                if (walk)
                {
                    do
                    {
                        int resTemp = abs(energy - walk->energy);
                        if (resTemp > res)
                        {
                            res = resTemp;
                            currentTemp = walk;
                        }
                        walk = walk->next;
                    } while (walk != X->next);
                }
                X->next = currentTemp; // gan current customer vao X->next
            }
            // add node to next/prev node of X->next
            // remember: tro X->next (X) vao inserted node
            if (energy >= X->next->energy)
            {
                customer *t = new customer(name, energy, nullptr, nullptr);
                customer *Xnext = X->next;

                t->prev = Xnext;
                t->next = Xnext->next;
                Xnext->next->prev = t;
                Xnext->next = t;
                sizeCDLL++;
                X->next = t;
            }
            else
            {
                customer *t = new customer(name, energy, X->next->prev, X->next);
                t->prev->next = t;
                t->next->prev = t;
                sizeCDLL++;
                X->next = t;
            }
        }
    }
    //cout << "check segmentation fault in REDqueue2restaurant command" << endl;
}

void imp_res::BLUE(int num)
{
    // by-default: num > 0
    if (num >= sizeCDLL)
        num = sizeCDLL;

    // clear CDLL
    if (num == sizeCDLL)
    {
        // clear all CDLL
        clearCDLL();
        // X->next = nullptr; already
        // clear MAXSIZE first customers in timelist (first in the timelist)
        for (int i = 0; i < num; i++)
        {
            dequeueTimeList();
        }
    }
    else
    {
        for (int i = 0; i < num; i++)
        {
            // Tim customer name theo thu tu vao nha hang som nhat den gan day.
            // xoa name of customer in timelist
            string name = removeCusHaveTableInTimeList(); //include sizeTimeList--

            // tro X->next vao customer co name tim duoc (customer can xoa)
            customer *walk = X->next;
            if (walk)
            {
                do
                {
                    if (walk->name == name)
                    {
                        X->next = walk;
                        break;
                    }
                    walk = walk->next;
                } while (walk != X->next);
            }
            // luu tam temp X->next de assign lai sau khi xoa customer
            customer *tempXnext = X->next;
            if (X->next && X->next->energy > 0)
                tempXnext = X->next->next;
            else
                tempXnext = X->next->prev;
            if (sizeCDLL == 1)
                tempXnext = nullptr;

            // remove customer in CDLL
            removeAtNameCDLL(name); // include sizeCDLL--;

            // update X->next
            X->next = tempXnext;
        }
    }
    // step: void function with loop (read waitqueue, run RED <name> <energy>)
    insertWaitQueue2Restaurant();

    //cout << "check segmentation fault in BLUE command" <<"with number =" << num << endl;
}
void imp_res::PURPLE()
{
    // SORT THEO THU TU GIAM DAN
    // tim vi tri cua KH co max abs(energy) in waitqueue
    // if 2 waiting customers co cung energy -> chon thang duoc them gan nhat
    customer *maxAbsE = headWaitQueue->next;
    customer *walk = headWaitQueue->next;
    while (walk != tailWaitQueue)
    {
        if (abs(walk->energy) >= abs(maxAbsE->energy))
        { //>= de chon thang duoc them gan nhat
            maxAbsE = walk;
        }
        walk = walk->next;
    }

    //step: shell sort
    int n = shellSort(headWaitQueue->next, maxAbsE);
    //cout<<"the number of swaps is "<<n<<endl;
    //displayCDLL();
    //displayWaitQueue();
    //displayTimeList();

    
    if (n % MAXSIZE != 0)
        BLUE(n % MAXSIZE);

    //cout << "check segmentation fault in PURPLE command" << endl;
}
void imp_res::REVERSAL()
{
    if (sizeCDLL == 0)
        return;
    string nameX = X->next->name; // point X->next when reversal step
    // 2 queues have dummy head, but not dummy tail
    customer *walk = X->next;
    customer *headPositive = new customer("Positive", 0, nullptr, nullptr);
    customer *headNegative = new customer("Negative", 0, nullptr, nullptr);
    customer *tailPositive = headPositive;
    customer *tailNegative = headNegative;
    if (walk)
    {
        do
        {
            if (walk->energy > 0)
            {
                customer *newPositive = new customer(walk->name, walk->energy, tailPositive, nullptr);
                tailPositive->next = newPositive;
                tailPositive = newPositive;
            }
            else
            {
                // case: walk->energy < 0
                customer *newNegative = new customer(walk->name, walk->energy, tailNegative, nullptr);
                tailNegative->next = newNegative;
                tailNegative = newNegative;
            }
            walk = walk->prev;
        } while (walk != X->next);
    }

    walk = X->next;
    customer *walkPositive = tailPositive;
    customer *walkNegative = tailNegative;
    if (walk)
    {
        for (int i = 0; i < sizeCDLL; i++)
        {
            if (walk->energy > 0)
            {
                walk->name = walkPositive->name;
                walk->energy = walkPositive->energy;
                walkPositive = walkPositive->prev;
                if (walk->name == nameX)
                    X->next = walk; // update X->next
            }
            else
            {
                // case: walk->energy < 0
                walk->name = walkNegative->name;
                walk->energy = walkNegative->energy;
                walkNegative = walkNegative->prev;
                if (walk->name == nameX)
                    X->next = walk; // update X->next
            }
            walk = walk->prev;
        }
    }

    // deallocate dynamic memory: 2 queue positive and negative
    walk = headPositive;
    customer *posDeleted = headPositive;
    while (walk != nullptr)
    {
        posDeleted = walk;
        walk = walk->next;
        delete posDeleted;
        posDeleted = nullptr;
    }

    walk = headNegative;
    customer *negDeleted = headNegative;
    while (walk != nullptr)
    {
        negDeleted = walk;
        walk = walk->next;
        delete negDeleted;
        negDeleted = nullptr;
    }
    //cout << "check segmentation fault in REVERSAL command" << endl;
}
void imp_res::UNLIMITED_VOID()
{
    //base case
    if(sizeCDLL < 4){
        //cout<<"sizeCDLL = "<<sizeCDLL<<"so return the function UNLIMITED_VOID"<<endl;
        return;
    }
    //cout<<"sizeCDLL = "<<sizeCDLL<<endl;

    //initialize current variable as the first case (with size=4 and subHead = X->next)
    int sizeUnlimited = 4;
    int sumUnlimited = 0;
    customer* subHead = X->next;
    customer* walk0 = X->next;
    for(int i=0; walk0 && i<sizeUnlimited; i++){
        sumUnlimited += walk0->energy;
        walk0 = walk0->next;
    }

    //traverse all cases to find sumE minimum
    for(int size=4; size <= sizeCDLL; size++){
        ////cout<<"with sizeConsidered = "<<size<<endl;
        customer* walk = X->next;
        for(int i=0; i<sizeCDLL; i++){
            //role of loop: traverse walk = each customer in CDLL
            int sizeUnlimitedtemp = size;
            int sumUnlimitedtemp = 0;
            customer* subHeadtemp = walk;
            customer* walkSub = walk;
            // for(int i=0; i < sizeUnlimitedtemp; i++){
            //     sumUnlimitedtemp += walkSub->energy;
            //     //cout<<walkSub->name<<"-"<<walkSub->energy<<" -> "<<flush;
            //     walkSub = walkSub->next;
            // }
            // //cout<<"sumUnlimitedtemp = "<<sumUnlimitedtemp<<endl;

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
                ////cout<<"update current with sizeUnlimited = "<<sizeUnlimited<<"subHead at"<<subHead->name<<"-"<<subHead->energy<<"sum ="<<sumUnlimited<<endl;
            }

            //loop: traversal to next customer
            walk = walk->next;
        }
    }

    //find the position whose energy is minimum
    //variable: customer* subHead(already), subTail, posEnergyMin;
    // int sizeUnlimited (already), int indexE
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
    ////cout to check the result: from subHead to subTail, posEnergyMin
    // //cout<<" subHead = "<<subHead->name<<"-"<<subHead->energy<<flush;
    // //cout<<" subTail = "<<subTail->name<<"-"<<subTail->energy<<flush;
    // //cout<<" posEnergyMin = "<<posEnergyMin->name<<"-"<<posEnergyMin->energy<<flush;
    // //cout<<" sizeUnlimited = "<<sizeUnlimited<<endl;

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
        for(int i=0; i < sizeUnlimited-indexE ; i++){ 
            //print sizeUnlimited-indexE customers from posEnergyMin to subTail
            walkPrint->print();
            walkPrint = walkPrint->next;
        }
        walkPrint = subHead;
        for(int i=0; i < indexE; i++){
            //print indexE customers from subHead to posEnergyMin->prev
            walkPrint->print();
            walkPrint = walkPrint->next;
        }
    }



    //cout << "check segmentation fault in UNLIMITED_VOID command" << endl;
}
void imp_res::DOMAIN_EXPANSION()
{
    // calculate oanlinh score and chuthuatsu score
    //place: trong ban an va trong hang cho
    int chuThuatSuScore = 0, oanLinhScore = 0;
    customer *walk = X->next;
    if (walk == nullptr)
    {
        //cout << "check segmentation fault in DOMAIN_EXPANSION command" << endl;
        return;
    }
    //tranverse in CDLL
    if (walk)
    {
        do
        {
            if (walk->energy > 0)
            {
                chuThuatSuScore += walk->energy;
            }
            else
            {
                oanLinhScore += abs(walk->energy);
            }
            walk = walk->next;
        } while (walk != X->next);
    }
    //traverse in WaitQueue
    walk = headWaitQueue->next;
    while (walk != tailWaitQueue)
    {
        if (walk->energy > 0)
        {
            chuThuatSuScore += walk->energy;
        }
        else
        {
            oanLinhScore += abs(walk->energy);
        }
        walk = walk->next;
    }

    // step: duoi chuthuatsu hoac oanlinh
    // duoi trong waitqueue,timelist -> CDLL,timelist + update X->next
    if (chuThuatSuScore >= oanLinhScore)
    {
        int index = 0;
        // duoi toan bo oan linh khoi CDLL and WaitQueue theo TimeList
        string OLname = readOanLinhTimeList(index); // include: using print function
        while(OLname != ""){
            // find and clear customer in WaitQueue
            bool removeAtWaitQueue = removeAtNameWaitQueue(OLname);
            // true: we have removed customer in waitqueue
            // false: we have not removed customer in waitqueue,
            // so we need to remove customer in Restaurant
            //tro X->next vao customer co name tim duoc (customer can xoa)
            if (removeAtWaitQueue == false)
            {
                customer *walk = X->next;
                if (walk)
                {
                    do
                    {
                        if (walk->name == OLname)
                        {
                            X->next = walk;
                            break;
                        }
                        walk = walk->next;
                    } while (walk != X->next);
                }

                //luu tam temp X->next de assign lai sau khi xoa customer
                customer* tempXnext = X->next;
                if(X->next->energy > 0) tempXnext = X->next->next;
                else tempXnext = X->next->prev;
                if(sizeCDLL == 1) tempXnext = nullptr;

                //remove customer in CDLL
                removeAtNameCDLL(OLname); //include sizeCDLL--;

                //update X->next
                X->next = tempXnext;
            }

            // loop: traversal to next customer
            OLname = readOanLinhTimeList(++index); // include: using print function
        
        }
        clearANDprintOanLinhTimeList();
    }
    else
    {
        int index = 0;
        // duoi toan bo chu thuat su khoi CDLL and WaitQueue theo TimeList
        string CTSname = readChuThuatSuTimeList(index); // include: using print function
        while (CTSname != "")
        {
            // find and clear customer in WaitQueue
            bool removeAtWaitQueue = removeAtNameWaitQueue(CTSname);
            // true: we have removed customer in waitqueue
            // false: we have not removed customer in waitqueue,
            // so we need to remove customer in Restaurant
            //tro X->next vao customer co name tim duoc (customer can xoa)
            if (removeAtWaitQueue == false)
            {
                customer *walk = X->next;
                if (walk)
                {
                    do
                    {
                        if (walk->name == CTSname)
                        {
                            X->next = walk;
                            break;
                        }
                        walk = walk->next;
                    } while (walk != X->next);
                }

                //luu tam temp X->next de assign lai sau khi xoa customer
                customer* tempXnext = X->next;
                if(X->next->energy > 0) tempXnext = X->next->next;
                else tempXnext = X->next->prev;
                if(sizeCDLL == 1) tempXnext = nullptr;

                //remove customer in CDLL
                removeAtNameCDLL(CTSname); //include sizeCDLL--;

                //update X->next
                X->next = tempXnext;
            }

            // loop: traversal to next customer
            CTSname = readChuThuatSuTimeList(++index); // include: using print function
        }
        clearANDprintChuThuatSuTimeList();
    }

    // step: xep hang doi vao ban trong cua restaurant
    insertWaitQueue2Restaurant();

    // remember to deallocate dynamic memory

    //cout << "check segmentation fault in DOMAIN_EXPANSION command" << endl;
}
void imp_res::LIGHT(int num)
{
    if (num > 0)
    {
        customer *walk = X->next;
        if (walk == nullptr)
        {
            //cout << "check segmentation fault: light " << num << endl;
            return;
        }
        if (walk)
        {
            do
            {
                walk->print();
                walk = walk->next;
            } while (walk && walk != X->next);
        }
    }
    else if (num < 0)
    {
        customer *walk = X->next;
        if (walk == nullptr)
        {
            //cout << "check segmentation fault: light " << num << endl;
            return;
        }
        if (walk)
        {
            do
            {
                walk->print();
                walk = walk->prev;
            } while (walk != X->next);
        }
    }
    else
    {
        // case: num == 0
        customer *walk = headWaitQueue->next;
        while (walk != tailWaitQueue)
        {
            walk->print();
            walk = walk->next;
        }
    }
    //cout << "check segmentation fault: light " << num << endl;
}

// helper functions
void imp_res::displayCDLL()
{
    //cout << "Display: " << flush;
    if (X->next == nullptr)
    {
        //cout << "sizeCDLL = 0" << endl;
        return;
    }
    customer *p = X->next;
    do
    {
        //cout << p->name << "-" << p->energy <<"    ";
        p = p->next;
    } while (p != X->next);
    //cout << "sizeCDLL = " << this->sizeCDLL << endl;
}

void imp_res::reverseDisplayCDLL()
{
    //cout << "Reverse display: " << flush;
    if (X->next == nullptr)
    {
        //cout << "sizeCDLL = 0" << endl;
        return;
    }
    customer *p = X->next;
    do
    {
        //cout << p->name << "-" << p->energy <<"    ";
        p = p->prev;
    } while (p != X->next);
    //cout << "sizeCDLL = " << this->sizeCDLL << endl;
}
void imp_res::addFirstNodeCDLL(string name, int energy)
{
    customer *first = new customer(name, energy, nullptr, nullptr);
    first->prev = first;
    first->next = first;
    X->next = first;
    sizeCDLL++;
}
void imp_res::enqueueWaitQueue(string name, int energy)
{
    customer *entry = new customer(name, energy, nullptr, nullptr);
    entry->next = tailWaitQueue;
    entry->prev = tailWaitQueue->prev;
    tailWaitQueue->prev = entry;
    entry->prev->next = entry;
    sizeWaitQueue++;
}
void imp_res::enqueueTimeList(string name, int energy)
{
    customer *entry = new customer(name, energy, nullptr, nullptr);
    entry->next = tailTimeList;
    entry->prev = tailTimeList->prev;
    tailTimeList->prev = entry;
    entry->prev->next = entry;
    sizeTimeList++;
}
void imp_res::displayTimeList()
{
    customer *walk = headTimeList->next;
    while (walk != tailTimeList)
    {
        //cout << walk->name << "-" << walk->energy << " -> " << flush;
        walk = walk->next;
    }
    //cout << "sizeTimeList = " << sizeTimeList << endl;
}
void imp_res::displayWaitQueue()
{
    customer *walk = headWaitQueue->next;
    while (walk != tailWaitQueue)
    {
        //cout << walk->name << "-" << walk->energy << " -> " << flush;
        walk = walk->next;
    }
    //cout << "sizeWaitQueue = " << sizeWaitQueue << endl;
}
void imp_res::clearCDLL()
{
    // clear all nodes
    if (sizeCDLL == 0)
        return;
    X->next->prev->next = nullptr;
    customer *walk = X->next;
    while (walk != nullptr)
    {
        customer *temp = walk;
        walk = walk->next;
        delete temp;
        temp = nullptr;
    }
    X->next = nullptr;
    sizeCDLL = 0;
}
string imp_res::dequeueTimeList()
{
    // remove first node in timelist
    if (sizeTimeList == 0)
        return "empty timelist, we cannot dequeue";
    customer *first = headTimeList->next;
    string temp = first->name;
    headTimeList->next = first->next;
    first->next->prev = headTimeList;
    delete first;
    first = nullptr; // deallocate memory
    sizeTimeList--;
    return temp;
}
string imp_res::removeCusHaveTableInTimeList(){
    if (sizeTimeList == 0)
        return "empty timelist, we cannot dequeue";
    customer *walk = headTimeList->next;
    while(!existedInCDLL(walk->name)){
        walk = walk->next;
    }
    string temp = walk->name;
    walk->prev->next = walk->next;
    walk->next->prev = walk->prev;
    delete walk;
    walk = nullptr;
    sizeTimeList--;
    return temp;

}
bool imp_res::existedInCDLL(string name){
    customer* walk = X->next;
    if(walk){
        do{
            if(walk->name == name) return true;
            walk = walk->next;
        }while(walk != X->next);
    }
    return false;
}

void imp_res::removeAtNameCDLL(string name)
{
    // given: name is already existed in CDLL, we dont need to find name

    if (sizeCDLL == 1)
    {
        delete X->next;
        X->next = nullptr;
        sizeCDLL--;
        return;
    }
    else
    {
        customer *walk = X->next;
        if (walk == nullptr)
            return; // case: sizeCDLL = 0
        while (walk && walk->name != name)
        {
            walk = walk->next;
        }
        walk->prev->next = walk->next;
        walk->next->prev = walk->prev;
        delete walk;
        walk = nullptr;
        sizeCDLL--;
    }
}
string imp_res::dequeueWaitQueue(int &energy)
{
    // remove first node in waitqueue
    if (sizeWaitQueue == 0)
        return "empty waitqueue, we cannot dequeue";
    customer *first = headWaitQueue->next;
    string temp = first->name;
    energy = first->energy;
    headWaitQueue->next = first->next;
    first->next->prev = headWaitQueue;
    delete first;
    first = nullptr; // deallocate memory
    sizeWaitQueue--;
    return temp;
}

void imp_res::insertWaitQueue2Restaurant()
{
    // case: size_waitqueue > (maxsize - size_restaurant) -> chen (maxsize - size_restaurant) customers vao restaurant
    // case: size_waitqueue < (maxsize - size_restaurant) -> chen size_waitqueue customers vao restaurant
    // case: size_waitqueue = (maxsize - size_restaurant) -> chen size_waitqueue customers vao restaurant
    int compare = sizeWaitQueue - (MAXSIZE - sizeCDLL);
    int sizeInserted = 0;

    // consider number of inserted customers
    if (compare > 0)
    {
        // chen (maxsize - size_restaurant) customers vao restaurant
        sizeInserted = MAXSIZE - sizeCDLL;
    }
    else
    {
        // chen size_waitqueue customers vao restaurant
        sizeInserted = sizeWaitQueue;
    }

    for (int i = 0; i < sizeInserted; i++)
    {
        int energy = 0;
        string name = "";
        // read waitqueue
        // xoa head of queue
        // xoa khoi timelist
        name = dequeueWaitQueue(energy);

        // run RED <name> <energy>
        REDQueue2Restaurant(name, energy);
    }
}
Restaurant::customer* imp_res::nextByIndex(customer* start, int index){
    customer* walk = start;
    for(int i=0; i<index; i++){
        walk = walk->next;
    }
    return walk;
}
void imp_res::swap(customer* cus1, customer* cus2){
    int energy = cus1->energy;
    string name = cus1->name;
    cus1->energy = cus2->energy;
    cus1->name = cus2->name;
    cus2->energy = energy;
    cus2->name = name;
}
int imp_res::inssort2(customer* start, int n, int incr){
    int swapCount = 0;
    for(int i=incr; i<n; i+=incr){
        int j=i;
        customer* posJ = nextByIndex(start, j);
        customer* posJMinusIncr = nextByIndex(start, j-incr);
        while(j>=incr && compareCustomerShellSort(posJ,posJMinusIncr)){
            swap(posJ,posJMinusIncr);
            swapCount++;

            j-=incr;
            if(j<incr) break;
            posJ = nextByIndex(start, j);
            posJMinusIncr = nextByIndex(start, j-incr);
        }
    }
    return swapCount;
}
int imp_res::shellSort(customer* start, customer* end){
    //find the number of customers in the list
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
        ////cout<<"gap = "<<i<<" :";
        //displayWaitQueue();
    }
    result += inssort2(start, n, 1);
    //displayWaitQueue();
    return result;
}
bool imp_res::compareCustomerShellSort(customer *latter,customer* former) const
{
    // sort theo thu tu giam dan
    // true: we need swap bc |former| < |latter|
    // false: we dont need swap bc |former| > |latter|

    if (abs(latter->energy) < abs(former->energy))
        return false;
    else if (abs(latter->energy) > abs(former->energy))
        return true;
    else
    {
        // confusion tu de bai: Truong hop khach hang co cung GIA TRI TUYET DOI ENERGY voi nhau thi khach hang nao den truoc duoc xem la lon hon.
        customer *walk = headTimeList->next;
        while (walk != nullptr)
        {
            if (walk->name == latter->name)
                return true;
            else if (walk->name == former->name)
                return false;
            walk = walk->next;
        }
    }
    return false;
}

bool imp_res::removeAtNameWaitQueue(string name)
{
    customer *walk = headWaitQueue->next;
    while (walk && walk != tailWaitQueue)
    {
        if (walk->name == name)
        {
            walk->next->prev = walk->prev;
            walk->prev->next = walk->next;
            delete walk;
            walk = nullptr;
            sizeWaitQueue--;
            return true;
        }
        walk = walk->next;
    }
    return false;
}


string imp_res::readOanLinhTimeList(int index)
{
    if (sizeTimeList == 0)
        return "";
    string name = "";
    customer *walk = headTimeList->next;
    int indextemp = 0;
    while(walk && walk!= tailTimeList){
        if(walk->energy < 0){
            if(indextemp == index){
                return walk->name;
            }
            indextemp++;
        }
        walk = walk->next;
    }
    return name;
}
string imp_res::readChuThuatSuTimeList(int index)
{ 
    if (sizeTimeList == 0)
        return "";
    string name = "";
    customer *walk = headTimeList->next;
    int indextemp = 0;
    while(walk && walk!= tailTimeList){
        if(walk->energy > 0){
            if(indextemp == index){
                return walk->name;
            }
            indextemp++;
        }
        walk = walk->next;
    }
    return name;
}
void imp_res::clearANDprintOanLinhTimeList(){
    //in tu tre den som
    if(sizeTimeList == 0) return;
    customer* walk = tailTimeList->prev;
    while(walk && walk != headTimeList){
        if(walk->energy < 0){
            walk->print();
            walk->next->prev = walk->prev;
            walk->prev->next = walk->next;
            customer* walkPrev = walk->prev;
            delete walk;
            walk = walkPrev;
            sizeTimeList--;
            continue;
        }
        walk = walk->prev;
    }
}
void imp_res::clearANDprintChuThuatSuTimeList(){
    //in tu tre den som
    if(sizeTimeList == 0) return;
    customer* walk = tailTimeList->prev;
    while(walk && walk != headTimeList){
        if(walk->energy > 0){
            walk->print();
            walk->next->prev = walk->prev;
            walk->prev->next = walk->next;
            customer* walkPrev = walk->prev;
            delete walk;
            walk = walkPrev;
            sizeTimeList--;
            continue;
        }
        walk = walk->prev;
    }
}
