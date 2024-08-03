#ifndef JAISUB_H_INCLUDED
#define JAISUB_H_INCLUDED

#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

vector <string> strfeatures({"Basic Subscription", "Tamil songs access", "English songs access", "Hindi Songs access", "Telugu songs access", "Kannada songs access", "Malayalam songs access", "Bengali songs access"});

class Plan {
public:
    string plan_name;
    double price;
    time_t validity;
    vector<bool> features;
    Plan(string name, double p, time_t v, vector<bool> f) {
        plan_name = name;
        price = p;
        validity = v;
        features = f;
    }

    void disp(){
        cout << "Plan Name: "<<plan_name << "\tPrice: " << price << "\tValidity: " << validity << endl;
    }

    bool operator>(double p){
        return price>p;
    }

    bool operator<(double p){
        return price<p;
    }

    bool operator>(Plan p){
        return price>p.price;
    }

    bool operator>=(Plan p){
        return price>p.price;
    }

    bool operator<(Plan p){
        return price<p.price;
    }

    bool operator== (Plan p){
        return ((price==p.price)&&(validity==p.validity)&&(features==p.features)&&(plan_name==p.plan_name));
    }

    friend std::ostream& operator<<(std::ostream& os, const Plan& pl) {
        os << "Plan Name: "<<pl.plan_name << "Price: " << pl.price << "\tValidity: " << pl.validity << endl;
        return os;
    }
};

vector <Plan> plans;

class AbstractSubscription {
protected:
    string planType;
    double price;
    time_t renewalDate;
    vector <bool> features;
    bool isPremium;

public:
    virtual void modifyPlan(time_t newRenewalDate) = 0;
    virtual void cancelSubscription() = 0;
    virtual void viewSubscriptionDetails() = 0;
};

class Subscription : public AbstractSubscription{
public:
    Subscription() {
        planType = "Free";
        price = 0.0;
        renewalDate = 0;
        isPremium = false;
        features = {0, 0, 0};
    }

    Subscription(string pla, double cost, time_t renewal, bool premium, vector<bool> s) {
        planType = pla;
        price = cost;
        renewalDate = renewal;
        isPremium = premium;
        features = s;
    }

    Subscription(Plan p) {
        planType = p.plan_name;
        price = p.price;
        time_t now = time(0);
        renewalDate = p.validity+now;
        isPremium = true;
        features = p.features;
    }

    Subscription operator+(const Subscription& other) {
        vector<bool> temp(features.size());
        for (int i=0;i<features.size();i++){
            temp[i]=(features[i]||other.features[i]);
        }
        Subscription result("Combined", price + other.price + 5, (max(renewalDate, other.renewalDate)), isPremium || other.isPremium, temp);
        return result;
    }

    virtual ~Subscription() {}

    string getplanType(){
        return planType;
    }

    double getprice(){
        return price;
    }

    time_t getrenewalDate(){
        return renewalDate;
    }

    bool getisPremium(){
        return isPremium;
    }

    void modifyPlan(string newPlan, double newPrice, time_t newRenewalDate, bool ispremium, vector<bool> v) {
        planType = newPlan;
        price = newPrice;
        renewalDate = newRenewalDate;
        cout << "Subscription plan modified to " << newPlan << " for $" << newPrice << endl << endl;
        isPremium = ispremium;
        features = v;
    }

    void modifyPlan(time_t newRenewalDate) {
        renewalDate = newRenewalDate;
    }

    void modifyPlan(Plan p) {
        planType = p.plan_name;
        price = p.price;
        time_t now = time(0);
        renewalDate = p.validity+now;
        isPremium = true;
        features = p.features;
    }

    void cancelSubscription() {
        planType = "Free";
        price = 0.0;
        string msg = "Subscription cancelled. Reverted to Free plan.\n";
        this->receiveNotification(msg);
        isPremium = false;
        renewalDate = 0;
        features = {0, 0, 0};
    }

    virtual void viewSubscriptionDetails() {
        cout << "Subscription Details:" << endl;
        cout << "Plan Type: " << planType << endl;
        cout << "Price: $" << price << endl;
        if(renewalDate != 0){
            cout << "Renewal Date: " << ctime(&renewalDate);
        }
        cout << "Premium: " << (isPremium ? "Yes" : "No") << endl << endl;
        cout << "Features: \n";
        for(int i=0; i<features.size(); i++){
            if(features[i]==true)   cout << strfeatures[i] << endl;
        }
        cout << endl;

    }

    void receiveNotification(string message) {
        cout << "Notification: " << message << endl;
    }
};

template <class T> class user {
public:
    string name;
    T *mysub;

    stack<Subscription*> subscriptionStack;
    queue<Subscription*> subList;

public:
    user(string n, T* s) :name(n), mysub(s){
        subscriptionStack.push(s);
    }

    user(string n, Plan p) :name(n) {
        mysub = new T(p);
        subscriptionStack.push(mysub);
        subList.push(mysub);
    }

    void getInfo() {
        cout << "User info\nName : " << name << endl;
        mysub->viewSubscriptionDetails();
    }

    string getName(){
        return name;
    }

    template <class U> void changeplan(U *s){
        mysub = s;
        subscriptionStack.push(s);
    }

    void changeplan(Plan p){
        mysub->modifyPlan(p);
        subscriptionStack.push(new Subscription(*mysub));
    }

    void undoSubscriptionChange() {
        if (subscriptionStack.size() > 1) {
            subscriptionStack.pop();
            mysub = subscriptionStack.top();
            cout << "Last subscription change undone.\n";
        } else {
            cout << "No subscription changes to undo.\n";
        }
    }

    void printSubscriptionHistory() {
        cout << "Subscription History for User: " << name << endl;
        int count = 1;
        stack<T*> tempStack = subscriptionStack;
        while (!tempStack.empty()) {
            cout << count << ". ";
            tempStack.top()->viewSubscriptionDetails();
            tempStack.pop();
            count++;
        }
        cout << endl;
    }

    void addon(Subscription* s){
        subList.push(s);
    }

    void showsubList(){
        cout << "Subscriptions under User: " << name << endl;
        int count = 1;
        queue<Subscription*> tempq = subList;
        while (!tempq.empty()) {
            cout << count << ". ";
            tempq.front()->viewSubscriptionDetails();
            tempq.pop();
            count++;
        }
        cout << endl;
    }

    T* getSub(){
        return mysub;
    }
};

    // Creating individual plans
    Plan basic("BasicSubscription", 5.99, 30, {1,0,0,0,0,0,0,0});
    Plan tamil("TamilSubscription", 7.99, 30, {1,1,0,0,0,0,0,0});
    Plan english("EnglishSubscription", 7.99, 30, {1,0,1,0,0,0,0,0});
    Plan hindi("HindiSubscription", 7.99, 30, {1,0,0,1,0,0,0,0});
    Plan telugu("TeluguSubscription", 7.99, 30, {1,0,0,0,1,0,0,0});
    Plan kannada("KannadaSubscription", 7.99, 30, {1,0,0,0,0,1,0,0});
    Plan malayalam("MalayalamSubscription", 7.99, 30, {1,0,0,0,0,0,1,0});
    Plan bengali("BengalSubscription", 7.99, 30, {1,0,0,0,0,0,0,1});

    // Creating combo plans
    Plan combo1("Combo1", 12.99, 30, {1,1,1,0,0,0,0,0});
    Plan combo2("Combo2", 12.99, 30, {1,0,0,1,1,0,0,0});
    Plan combo3("Combo3", 12.99, 30, {1,0,0,0,0,1,1,0});

template <typename T> class node{
public:
    T key;
    node <T>* left;
    node <T>* right;

    node(T x) :key(x) {
        left = right = NULL;
    }

    node (double p, time_t v) :key(p,v) {
        left = right = NULL;
    }
};

template <typename T> node<T>* ll(node<T>* x){
    node <T> *y=x->right;
    node <T> *t1 = y->left;
    x->right = t1;
    y->left = x;
    return y;
}

template <typename T> node <T>* rr(node <T>* x){
    node <T>*y = x->left;
    node <T>*t1 = y->right;
    x->left = t1;
    y->right = x;
    return y;
}
template <typename T> node<T>* splay(node <T> *root, T p, int ch){
    static int fl = 0;
    if (root == NULL){
        if (ch == 1){
            root = new node<T>(p);
            return root;
        } else {
            fl = 1;
            cout << "Element not found\n";
            return root;
        }
    } else if (root->key > p){
        root->left = splay(root->left, p, ch);
        if (fl != 1) root = rr(root);
    } else if (root->key < p){
        root->right = splay(root->right, p, ch);
        if (fl != 1) root = ll(root);
    } else {
        if (ch!=1 && root->key==p){
            return root;
        }
    }
    return root;
}

template <typename T> void preorder(node <T>*root){
    static int i=0;
    if (root != NULL && i<3){
        plans[root->key].disp();
        i++;
        preorder(root->left);
        preorder(root->right);
    }
}

    node <int>* rootSpl = NULL;
    map <string, int> planIndex;
void loadplans(){
    plans.push_back(basic);
    plans.push_back(tamil);
    plans.push_back(english);
    plans.push_back(hindi);
    plans.push_back(telugu);
    plans.push_back(kannada);
    plans.push_back(malayalam);
    plans.push_back(bengali);
    plans.push_back(combo1);
    plans.push_back(combo2);
    plans.push_back(combo3);
    for(int i=0; i<plans.size(); i++){
        planIndex[plans[i].plan_name]=i;
        rootSpl = splay(rootSpl, i, 1);
    }
}

int subscriptionWork() {
    loadplans();
    time_t now = time(0);
    Subscription mySubscription;
    user <Subscription> u2(userName, &mySubscription);
        int ch, x, ch2, ch3;
        string pn;
    node <Plan>* r;
    do {
        cout << "\tMenu\n1. View Subscription Details\n2. Modify Current Plan\n3. Exit\nEnter choice: ";
        cin >> ch;
        switch(ch){
        case 1:
            u2.getInfo();
            break;
        case 2:
            cout << "\tMenu\n1. Recharge/Modify\n2. Undo Last Modification\n3. Add new Subscription\n4. Cancel Subscription\5. Exit\nEnter choice:";
            cin >> ch2;
            if (ch2==1||ch2==3){
                cout << "   Plans recommended based on your previous activity\n";
                preorder(rootSpl);
                cout << "Choose how to proceed\n1. Display all plans\n2. Enter from recommended list\n Enter choice: ";
                cin >> ch3;
                if (ch3==1){
                        cout << "Choose one from the below plans \n";
                    for (int i=0; i<plans.size(); i++){
                        plans[i].disp();
                    }
                }
                cout << "Enter the plan's name you wish to choose: ";
                cin >> pn;

                rootSpl=splay(rootSpl, planIndex[pn], 2);
                if (ch2==1) u2.changeplan(plans[planIndex[pn]]);
                else if (ch2==3){
                    u2.addon(new Subscription(plans[planIndex[pn]]));
                    u2.showsubList();
                }
                cout << "Your subscription has been updated successfully\n" << endl;
            } else if (ch2==2){
                u2.undoSubscriptionChange();
            } else if (ch2==5){
                continue;
            } else if(ch2==4){
                u2.mysub->cancelSubscription();
            }else {
                cout << "Invalid choice\n";
            }
            break;
        case 3:
            continue;
        default:
            cout << "Invalid choice\n";
        }
    } while(ch!=3);
    return 0;
}

#endif // JAISUB_H_INCLUDED
