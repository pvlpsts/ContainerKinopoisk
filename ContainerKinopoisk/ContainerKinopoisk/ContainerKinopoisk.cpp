#include <iostream>
#include <list>
#include <iterator>
#include <cstddef>
#include<utility>
using namespace std;

enum class MPAA {
    G,
    PG,
    PG_13,
    R,
    NC_17
};
enum class Grade {
    One = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten
};
enum class Status {
    Production,
    Air,
    Finished
};

template<class T>
class MyListTemplate
{

public:
    T* head;
    T* tail;
    int size;

public:
    MyListTemplate() : head(nullptr), tail(nullptr), size(0) {}

    void freeMemory()
    {
        if (head == nullptr)
            return;

        T* current = head;
        T* nextNode = nullptr;

        for (int i = 0; i < size; i++)
        {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        this->size = 0;
        head = tail = nullptr;
    }

    void add(std::string Name)
    {
        if (size < 100)
        {
            T* newNode = new T(Name);
            newNode->next = nullptr;

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;

            }
            ++size;
        }
        else
            std::cout << "The size is already maximum" << std::endl;
    }

    void remove(std::string Name)
    {
        if (head == nullptr)
        {
            return;
        }

        if (head->getName() == Name)
        {
            if (head->next == head)
            {
                delete head;
                head = tail = nullptr;
                size = 0;
                return;
            }
            else
            {
                T* nodeToRemove = head;
                head = head->next;
                delete nodeToRemove;
            }
        }

        T* current = head->next;
        T* prev = head;

        while (current != head)
        {
            if (current->getName() == Name)
            {
                T* nodeToRemove = current;
                prev->next = current->next;
                if (current == tail) tail = prev;
                delete nodeToRemove;
                --size;
                current = prev->next;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }

    void print()
    {
        if (head == NULL)
            return;

        T* current = head;

        for (int i = 0; i < size; i++)
        {
            std::cout << current->getName() << std::endl;
            current = current->next;
        }
        std::cout << std::endl;
    }

    T& operator=(T& b)
    {
        if (this == &b)
            return *this;
        T* current = b.head;
        for (int i = 0; i < b.size; i++)
        {
            this->add(current->getName());
            current = current->next;
        }
        return *this;
    }

    ~MyListTemplate()
    {
        freeMemory();
    }

    bool operator==(MyListTemplate& b)
    {
        if (this->size != b.size)
            return false;
        else
        {
            bool f = true;
            T* curra = this->head;
            T* currb = b.head;
            for (int i = 0; i < this->size; i++)
            {
                if (curra->getName() != currb->getName())
                {
                    f = false;
                    break;
                }
                curra = curra->next;
                currb = currb->next;
            }
            return f;
        }
    }
    bool operator!=(MyListTemplate& b)
    {
        return !operator==(b);
    }

    void swap(MyListTemplate& b)
    {
        int tsize = this->size;
        this->size = b.size;
        b.size = tsize;
        T* ahead = this->head;
        this->head = b.head;
        b.head = ahead;
    }
    void swap(MyListTemplate& a, MyListTemplate& b)
    {
        a.swap(b);
    }

    void Swap(MyListTemplate& b) noexcept
    {
        std::swap(this->head, b.head);
        std::swap(this->tail, b.tail);
        std::swap(this->size, b.size);
    }

    int m_size()
    {
        return this->size;
    }
    int max_size()
    {
        return 100;
    }

    bool empty()
    {
        if (this->size == 0)
            return true;
        else return false;
    }

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        ~Iterator() {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++()
        {
            if (m_ptr == nullptr)
                return *this;
            else if (m_ptr->next == nullptr)
            {
                m_ptr = m_ptr->next;
                return *this;
            }
            else
            {
                m_ptr = m_ptr->next;
                while (m_ptr->next != nullptr)
                {
                    return *this;
                    m_ptr = m_ptr->next;
                }
            }
        }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        bool operator== (const Iterator& b) { return m_ptr == b.m_ptr; };
        bool operator!= (const Iterator& b) { return m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };
    Iterator begin() { return Iterator(this->head); }
    Iterator end() { return Iterator(nullptr); }

    struct ConstantIterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = T*;
        using reference = const T&;

        ConstantIterator(pointer ptr) : m_ptr(ptr) {}

        ~ConstantIterator() {}

        const reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }
        ConstantIterator& operator++()
        {
            if (m_ptr == nullptr)
                return *this;
            else if (m_ptr->next == nullptr)
            {
                m_ptr = m_ptr->next;
                return *this;
            }
            else
            {
                m_ptr = m_ptr->next;
                while (m_ptr->next != nullptr)
                {
                    return *this;
                    m_ptr = m_ptr->next;
                }
            }
        }
        ConstantIterator operator++(int) { ConstantIterator tmp = *this; ++(*this); return tmp; }
        bool operator== (const ConstantIterator& b) { return m_ptr == b.m_ptr; };
        bool operator!= (const ConstantIterator& b) { return m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };
    ConstantIterator cbegin() const { return ConstantIterator(this->head); }
    ConstantIterator cend()   const { return ConstantIterator(nullptr); }
};

class Person
{
protected:
    std::string Name;
public:
    Person* next;
    Person(std::string name)
    {
        this->Name = name;
        this->next = nullptr;
    }
    std::string getName()
    {
        return Name;
    }
    void setName(std::string name)
    {
        this->Name = name;
    }
};

class Date
{
protected:
    std::string date;
public:
    Date* next;
    Date(std::string date)
    {
        this->date = date;
        this->next = nullptr;
    }
    std::string getName()
    {
        return date;
    }
    void setName(std::string date)
    {
        this->date = date;
    }
};

class Episode
{
private:
    std::string Name;
    Date World_premiere();
public:
    Episode* next;
    Episode(std::string Name)
    {
        this->Name = Name;
        this->next = nullptr;
    }
    std::string getName()
    {
        return Name;
    }
    void setName(std::string name)
    {
        this->Name = name;
    }
    Date getWorldPremiere()
    {
        return World_premiere();
    }
    void setWorldPremiere(Date premiere)
    {
        this->World_premiere() = premiere;
    }
    void printWorldPremiere()
    {
        std::cout << "\tWorld premiere: "<< this->World_premiere().getName()<<std::endl;
        
    }
};

class Product
{
private:
    string Name;
    int Year;
    MyListTemplate<Person> Directors;
    unsigned long Budget;
    unsigned long World_box_office;
    MPAA MPAA_rating;
    int Timing_in_mins;
    MyListTemplate<Person> Starring;
    int Grades_sum = 0;
    int Grades_size = 0;
    double Rating;

    void setRating()
    {
        this->Rating = Grades_sum / Grades_size;
    }
protected:
    MyListTemplate<Date> World_premiere;
public:
    Product* next;
    Product()
    {
        this->next = NULL;
    }
    std::string getName()
    {
        return Name;
    }
    void setName(std::string name)
    {
        this->Name = name;
    }
    MyListTemplate<Person> getDirector()
    {
        return Directors;
    }
    void printDirectors()
    {
        std::cout << "Directed by: " << std::endl;
        this->Directors.print();
    }
    void addDirectors(std::string name)
    {
        this->Directors.add(name);
    }
    unsigned long getBudget()
    {
        return Budget;
    }
    void setBudget(unsigned long budget)
    {
        this->Budget = budget;
    }
    unsigned long getWorldBoxOffice()
    {
        return World_box_office;
    }
    void setWorldBoxOffice(unsigned long boxOffice)
    {
        this->World_box_office = boxOffice;
    }
    virtual MyListTemplate<Date> getWorldPremiere() = 0;
    void printPremiere()
    {
        World_premiere.print();
    }
    MPAA getMPAA()
    {
        return MPAA_rating;
    }
    void setMPAA(MPAA mpaa)
    {
        this->MPAA_rating = mpaa;
    }
    int getTimingInMins()
    {
        return Timing_in_mins;
    }
    void setTimingInMins(int timing)
    {
        this->Timing_in_mins = timing;
    }
    MyListTemplate<Person> getStarring()
    {
        return Starring;
    }
    void printName()
    {
        std::cout << this->getName() << std::endl;
    }
    void printStarring()
    {
        std::cout << "Starring: " << std::endl;
        this->Starring.print();
    }
    void addStarring(std::string name)
    {
        this->Starring.add(name);
    }
    void addGrade(Grade grade)
    {
        ++Grades_size;
        int value = static_cast<int>(grade);
        Grades_sum += value;
        setRating();
    }
    double getRating()
    {
        return Rating;
    }
    ~Product()
    {
        Directors.head = nullptr;
        Starring.head = nullptr;
    }
};

class Movie : public Product
{
private:

public:
    virtual MyListTemplate<Date> getWorldPremiere()
    {
        return World_premiere;
    }
    void setWorldPremiere(std::string date)
    {
        this->World_premiere.freeMemory();
        this->World_premiere.add(date);
    }

};

class Series : public Product
{
private:
    int Episodes_number = 0;
    MyListTemplate<Episode> Episodes;
    MyListTemplate<Date> premieres;
    int Seasons_number;
    Status Series_status;
    void setEpisodesNumber(int episodesNumber)
    {
        this->Episodes_number = episodesNumber;
    }
public:
    int getEpisodesNumber()
    {
        return Episodes_number;
    }
    MyListTemplate<Episode> getEpisodes()
    {
        return Episodes;
    }
    void addEpisode(std::string Name)
    {
        this->Episodes.add(Name);
        setEpisodesNumber(Episodes.m_size());
    }

    virtual MyListTemplate<Date> getWorldPremiere()
    {
        return premieres;
    }
    Status getStatus()
    {
        return Series_status;
    }
    void setStatus(Status status)
    {
        this->Series_status = status;
    }
    void printEpisodes()
    {
        std::cout << "Episodes: " << std::endl;
        Episodes.print();
    }
    void setWorldPremiere(std::string date)
    {
        this->World_premiere.freeMemory();
        this->World_premiere.add(date);
    }
    ~Series()
    {
        Episodes.head = nullptr;
    }
};

int main()
{
    Series s;
    s.setName("Game Of Thrones");

    s.addEpisode("Winter Is Coming");
    s.addEpisode("The Kingsroad");

    s.addStarring("Sean Bean");
    s.addStarring("Peter Dinklage");

    //s.printName();
    //s.printEpisodes();
    //s.printStarring();

    auto episodes = s.getEpisodes();
    for (auto it = episodes.begin(); it != episodes.end(); ++it)
    {
        std::cout << it->getName() << " ";
    }
    std::cout << std::endl;

    auto starring = s.getStarring();
    for (auto it = starring.begin(); it != starring.end(); ++it)
    {
        std::cout << it->getName() << " ";
    }
    return 0;
}
