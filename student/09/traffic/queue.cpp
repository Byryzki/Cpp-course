#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle) :
    first_(nullptr),
    last_(nullptr),
    is_green_(false),
    cycle_(cycle)
{

}

Queue::~Queue()
{
    while(first_ != nullptr)
    {
        dequeue(1);
    }
}

void Queue::enqueue(string reg)
{
    if(is_green_)
    {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
    }

    else
    {
        Vehicle* new_car = new Vehicle;
        new_car -> reg_num = reg;
        new_car -> next = nullptr;

        if ( first_ == nullptr )
        {
            first_ = new_car;
            last_ = new_car;
        }
        else
        {
            last_-> next = new_car;
            last_ = new_car;
        }
    }

}

void Queue::dequeue(unsigned int cycle) // korjaa
{
    for(unsigned int i = 0; i < cycle; ++i)
    {
        if(first_ == nullptr)
            {
                break;
            }

            string reg = first_ -> reg_num;
            Vehicle* second = first_ -> next;

            delete first_;
            first_ = second;
            if(first_ != nullptr)
            {
                first_ -> prev = nullptr;
            }
            else
            {
                last_ = nullptr;
            }
    }
}

void Queue::switch_light()
{
    if(is_green_)
    {
        is_green_ = false;
        print();
    }
    else
    {
        is_green_ = true;
        int del = 0;
        Vehicle* current = first_;

        if(current == nullptr)
        {
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        }

        else
        {
            std::cout << "GREEN: Vehicle(s) ";
            for(unsigned int i = 0; i < cycle_; ++i)
            {
                std::cout << current -> reg_num << " ";

                current = current -> next;
                ++del;
                if(current == nullptr)
                {
                    break;
                }
            }
            std::cout << "can go on" << std::endl;

            dequeue(del);
            is_green_ = false;
        }
    }      
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print()
{
    string light;
    if(is_green_)
    {
        light = "GREEN";
    }
    else
    {
        light = "RED";
    }

    if(first_ == nullptr) //tyhjö lista
    {
        std::cout << light << ": No vehicles waiting in traffic lights" << std::endl;
    }
    else
    {
        std::cout << light << ": Vehicle(s) ";
        Vehicle* current = first_;
        while(current -> next != nullptr)
        {
            std::cout << current -> reg_num << " ";

            current = current -> next;
        }
        std::cout << current -> reg_num << " ";
        std::cout << "waiting in traffic lights" << std::endl;
    }
}


