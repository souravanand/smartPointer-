#include<iostream>
using namespace std;
template<typename T>
class Unique_ptr{
    private:
    T* ptr;

    public:
    Unique_ptr():ptr(nullptr){cout<<"default const"<<endl;}

    Unique_ptr(T* ptr):ptr(ptr){cout<<"parametrized const"<<endl;}

    Unique_ptr(Unique_ptr const &ptr)=delete;

    Unique_ptr& operator=(Unique_ptr const &ptr)=delete;

    Unique_ptr(Unique_ptr &&dyingobject)
    {
        clean_up();
        cout<<"Move const"<<endl;
        ptr=dyingobject.ptr;
        dyingobject.ptr=nullptr;
        
    }

    Unique_ptr& operator=(Unique_ptr &&ptr)
    {
        clean_up();
        this->ptr=ptr;
        ptr=nullptr;
        cout<<"Move assignment "<<endl;
        return *this;
    }

    T& operator*()
    {
        return  *(this->ptr);
    }
    void clean_up()
    {
        if(ptr!=nullptr)
        {
            ptr=nullptr;
        }

    }
    template<typename T1>
  friend ostream& operator<<(ostream& out,Unique_ptr<T1>& obj);
    ~Unique_ptr()
    {
        cout<<"Destr"<<endl;
         if(ptr!=nullptr)
        {
            delete[] ptr;
        }
    }
  

};
template<typename T>
ostream& operator<<(ostream& out,Unique_ptr<T>& obj)
{
    out<<obj.ptr<<endl;
    return out;
}

int main()
{
    Unique_ptr<string>x(new string("abcdef"));
    cout<<*x;
    Unique_ptr<string>y=move(x);
    cout<<*y;

}
