#include <iostream>
#include <cstring>

template <class T>
class linkedList
{
    struct Node
    {
        T val;
        Node* next;
        Node (T x = 0, Node* p = nullptr): val(x), next(p){}
    };

public:
    linkedList(): head(new Node){end = head;}
    ~linkedList();
    linkedList(const linkedList &);
    linkedList(linkedList &&);

    void add(T);
    linkedList operator+(const linkedList&)const;
    void display() const;

private:
    Node* head;
    Node* end;
};

template <class T>
linkedList<T>::linkedList(const linkedList &source): head(new Node)
{
    Node *p1 = head, *p2 = source.head;
    while (p2->next != nullptr)
    {
        p2 = p2->next;
        p1->next = new Node(p2->val);
        p1 = p1->next;
    }
    end = p1;
}

template <class T>
linkedList<T>::linkedList(linkedList &&source): head(source.head), end(source.end)
{
    source.head = nullptr;
}

template <class T>
linkedList<T>::~linkedList()
{
    Node *pre;
    while (head != nullptr)
    {
        pre = head;
        head = head->next;
        delete pre;
    }
}

template <class T>
void linkedList<T>::add(T a)
{
    end->next = new Node(a);
    end = end->next;
}

template <class T>
linkedList<T> linkedList<T>::operator+(const linkedList<T> &other)const
{
    linkedList<T> res;
    Node *p = res.head, *p1 = this->head->next, *p2 = other.head->next;
    while (p1 != nullptr)
    {
        p->next = new Node(p1->val);
        p = p->next;
        p1 = p1->next;
    }
    while (p2 != nullptr)
    {
        p->next = new Node(p2->val);
        p = p->next;
        p2 = p2->next;
    }
    return res;
}

template <class T>
void linkedList<T>::display() const
{
    Node *p = head -> next;
    while (p != nullptr)
    {
        std::cout << p->val;
        if (p->next != nullptr)
            std::cout << ' ';
        p = p->next;
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    char *s = new char[10];
    int n, m;
    std::cin >> s >> n >> m;
    if (std::strcmp(s, "int") == 0)
    {
        linkedList<int> *link1 = new linkedList<int>;
        linkedList<int> *link2 = new linkedList<int>;
        int tmp;
        for (int i = 0; i < n; i++)
        {
            std::cin >> tmp;
            link1->add(tmp);
        }
        for (int i = 0; i < m; i++)
        {
            std::cin >> tmp;
            link2->add(tmp);
        }
        ((*link1)+(*link2)).display();
    }
    else if (std::strcmp(s, "char") == 0)
    {
        linkedList<char> *link1 = new linkedList<char>;
        linkedList<char> *link2 = new linkedList<char>;
        char tmp;
        for (int i = 0; i < n; i++)
        {
            std::cin >> tmp;
            link1->add(tmp);
        }
        for (int i = 0; i < m; i++)
        {
            std::cin >> tmp;
            link2->add(tmp);
        }
        ((*link1)+(*link2)).display();
    }
    else if (std::strcmp(s, "double") == 0)
    {
        linkedList<double> *link1 = new linkedList<double>;
        linkedList<double> *link2 = new linkedList<double>;
        double tmp;
        for (int i = 0; i < n; i++)
        {
            std::cin >> tmp;
            link1->add(tmp);
        }
        for (int i = 0; i < m; i++)
        {
            std::cin >> tmp;
            link2->add(tmp);
        }
        ((*link1)+(*link2)).display();
    }
    return 0;
}