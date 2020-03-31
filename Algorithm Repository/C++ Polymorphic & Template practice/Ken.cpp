//copyright Peng,Ziwei 2019

#include<iostream>
#include<string>

using namespace std;

class Graph{
protected:
    double area;
    double record;
public:
    Graph(){
        area=0;
        record=0;
    }
    virtual ~Graph(){}
    static size_t get_random_num(int modules){
        return rand() % modules + 1;
    }
    virtual string getname() = 0;
    virtual string getpara() = 0;
    double getarea(){
        return area;
    }
    double getrecord(){
        return record;
    }
    int process(){
        cout<<this->getname()<<": "<<this->getpara()<<string(", area=?");
        cin>>record;
        if (record<0){
            return -1;
        }
        if (record==this->getarea())
            cout<<"Your answer is correct"<<endl<<endl;
        else
            cout<<"Your answer is incorrect"<<endl<<endl;
        return 0;
    }
};

class parallelogram:public Graph{
protected:
    size_t width,height;
public:
    parallelogram(){
        width=get_random_num(10);
        height=get_random_num(10);
        area=width*height;
    }
    string getname(){
        return string("parallelogram");
    }
    string getpara(){
        return string("width=")+to_string(width)+string(", height=")+to_string(height);
    }
};

class rectangle:public parallelogram{
public:
    rectangle(){}
    string getname(){
        return string("rectangle");
    }
    string getpara(){
        return string("width=")+to_string(width)+string(", height=")+to_string(height);
    }
};

class square:public rectangle{
public:
    square(){
        height=width;
        area=width*width;
    }
    string getname(){
        return string("square");
    }
    string getpara(){
        return string("width=")+to_string(width);
    }
};

class diamond:public parallelogram{
public:
    diamond(){
        area=area/2;
    }
    string getname(){
        return string("diamond");
    }
    string getpara(){
        return string("diagnal1=")+to_string(width)+string(", diagnal2=")+to_string(height);
    }
};

class trapezoid:public Graph{
protected:
    size_t width1,width2,height;
public:
    trapezoid(){
        width1=get_random_num(10);
        width2=get_random_num(10);
        height=get_random_num(10);
        area=(width1+width2)*height/2;
    }
    string getname(){
        return string("trapezoid");
    }
    string getpara(){
        return string("width1=")+to_string(width1)+string(", width2=")+to_string(width2)+string(", height=")+to_string(height);
    }
};

template <typename T>
class List{
private:
    struct node{
        Graph * graph;
        node * next;
    };
    node *head,*now;
public:
    void init(){
        head = new node;
        head->graph=nullptr;
        head->next=nullptr;
        now=head;
    }
    List(){
        init();
    }
    void Release(){
        iterator pre=this->gethead();
        for (iterator it=this->begin();it!=nullptr;++it){
            pre.SafeRelease();
            pre=it;
        }
        pre.SafeRelease();
    }
    ~List(){
        //Release();
    }
    template<typename G>
    void do_record(G& p){
        auto *temp = new node;
        temp->graph=&p;
        temp->next=nullptr;
        now->next=temp;
        now=temp;
    }

    friend class iterator;

    class iterator
    {
    private:
        using value_type = node;
        using reference = value_type&;
        using pointer = value_type*;

        pointer p;

    public:

        iterator(pointer t = nullptr) : p(t) { }
        ~iterator(){p=nullptr;}

        bool operator !=(const iterator& i)
        {
            return p != i.p;
        }

        bool operator ==(const iterator& i)
        {
            return p == i.p;
        }

        iterator& operator++()
        {
            p = p->next;
            return *this;
        }

        reference operator *()
        {
            return *p;
        }

        void SafeRelease(){
            if (p->graph!=nullptr){
                delete p->graph;
                p->graph=nullptr;
            }
            delete p;
            p=nullptr;
        }
    };
    iterator gethead() {return iterator(head);}
    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(now); }
};

int main(){

    //Graph initlist[5]={new parallelogram(),new rectangle(),new diamond(),new diamond(),new square()};
    //Graph& p=static_cast<typeid(initlist[Graph::get_random_num(5)])> (new Graph()); //wrong

    int ans,status=0;
    List<Graph>* l=(List<Graph>*)malloc(sizeof(List<Graph>));
    l->init();
    srand((unsigned)time(NULL));
    cout<<"Practicing. Input negative value to halt."<<endl;
    while (status>=0) {
        ans=Graph::get_random_num(5);
        switch (ans){
            case 0:{
                Graph& p = * new parallelogram();
                if ((status=p.process())>=0)
                    l->do_record(p);
                else delete &p;
                break;
            }
            case 1:{
                Graph& p = * new rectangle();
                if ((status=p.process())>=0)
                    l->do_record(p);
                else delete &p;
                break;
            }
            case 2:{
                Graph& p = * new diamond();
                if ((status=p.process())>=0)
                    l->do_record(p);
                else delete &p;
                break;
            }
            case 3:{
                Graph& p = * new trapezoid();
                if ((status=p.process())>=0)
                    l->do_record(p);
                else delete &p;
                break;
            }
            case 4:{
                Graph& p = * new square();
                if ((status=p.process())>=0)
                    l->do_record(p);
                else delete &p;
                break;
            }
        }
    }
    cout<<endl<<"Reviewing..."<<endl;

    int correct=0,wrong=0;

    for (auto it=l->begin();it!=nullptr;++it){
        cout<<(*it).graph->getname()<<": "<<(*it).graph->getpara()<<string(", answer=")<<(*it).graph->getrecord()<<((*it).graph->getrecord()==(*it).graph->getarea()?(++correct,string(" V")):(++wrong,string(" X")))<<endl;
    }

    cout<<endl<<"Total: "<<correct+wrong<<", Correct: "<<correct<<endl;

    l->Release();
    free(l);

    return 0;
}