#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class memory
{
public:
    int data;
    bool isAllocated;
    memory *prev;
    memory *next;
};

void NewBlock(memory **head_pointer, int i)
{
    memory *createdNode = new memory();
    createdNode->data = i;
    createdNode->isAllocated = false;
    createdNode->next = (*head_pointer);
    createdNode->prev = NULL;

    if ((*head_pointer) != NULL)
        (*head_pointer)->prev = createdNode;

    (*head_pointer) = createdNode;
}

void printResult(memory *node)
{
    memory *last;
    while (node != NULL)
    {
        last = node;
        if (last->prev == NULL)
        {
            cout << "|" << string(last->data, (last->isAllocated == false ? '-' : '+')) << "|"
                 << " " << last->data << (last->isAllocated == false ? " (free)" : " (allocated)") << endl;
        }
        else
        {
            cout << "|";
            if (last->isAllocated)
            {
                cout << string(last->data, '+') << "| " << last->data << " (allocated)" << endl;
            }
            else
            {
                cout << string(last->data, '-') << "| " << last->data << " (free)" << endl;
            }
        }
        node = node->next;
    }

    cout << endl;
}

memory *firstFit(memory *head_pointer, int data)
{
    cout << "First Fit Allocation: " << data << endl;
    memory *node = head_pointer;
    while (node != NULL)
    {
        if (data <= node->data and node->isAllocated == false)
        {
            node->isAllocated = true;
            if (data - node->data != 0)
            {
                memory *createdNode = new memory();
                createdNode->isAllocated = false;
                createdNode->next = node->next;
                createdNode->prev = node;
                createdNode->data = node->data - data;
                node->next = createdNode;
                node->data = data;
            }

            cout << "Memory Allocated!" << endl;
            cout << endl;
            return node;
        }
        node = node->next;
    }
    cout << "Memory not allocated, not enough free memory. ";
    cout << endl;

    return head_pointer;
}

memory *nextFit(memory *head_pointer, int data)
{
    cout << "Next Fit Allocation: " << data << endl;
    memory *node = head_pointer;
    while (node != NULL)
    {
        if (data <= node->data and node->isAllocated == false)
        {
            node->isAllocated = true;
            if (data - node->data != 0)
            {
                memory *createdNode = new memory();
                createdNode->isAllocated = false;
                createdNode->next = node->next;
                createdNode->prev = node;
                createdNode->data = node->data - data;
                node->next = createdNode;
                node->data = data;
            }

            cout << "Memory Allocated!" << endl;
            cout << endl;
            return node;
        }
        node = node->next;
    }
    cout << "Memory not allocated, not enough free memory" << endl;
    cout << endl;

    return head_pointer;
}

memory *best_fit(memory *head_pointer, int data)
{
    cout << "Best Fit Allocation: " << data << endl;
    memory *node = head_pointer;
    memory *best = NULL;
    while (node != NULL)
    {
        if (node->isAllocated != true)
        {
            if (data <= node->data && (best == NULL || node->data < best->data))
            {
                best = node;
            }
        }
        node = node->next;
    }

    if (best != NULL)
    {
        best->isAllocated = true;
        if (data < best->data)
        {
            memory *createdNode = new memory();
            createdNode->isAllocated = false;
            createdNode->next = best->next;
            createdNode->prev = best;
            createdNode->data = best->data - data;
            best->next = createdNode;
            best->data = data;
        }

        cout << "Memory Allocated!" << endl;
        cout << endl;
    }
    else
    {
        cout << "Memory not allocated, not enough free memory" << endl;
        cout << endl;
    }
    return best;
}

memory *worst_fit(memory *head_pointer, int data)
{
    cout << "Worst Fit Allocation: " << data << endl;
    memory *node = head_pointer;
    memory *worst = NULL;
    while (node != NULL)
    {
        if (node->isAllocated != true)
        {
            if (data <= node->data && (worst == NULL || node->data > worst->data))
            {
                worst = node;
            }
        }
        node = node->next;
    }

    if (worst != NULL)
    {
        worst->isAllocated = true;
        if (data < worst->data)
        {
            memory *createdNode = new memory();
            createdNode->isAllocated = false;
            createdNode->next = worst->next;
            createdNode->prev = worst;
            createdNode->data = worst->data - data;
            worst->next = createdNode;
            worst->data = data;
        }

        cout << "Memory Allocated!" << endl;
        cout << endl;
    }
    else
    {
        cout << "Memory not allocated, not enough free memory" << endl;
        cout << endl;
    }
    return worst;
}
void mergeMemory(memory *&head)
{
    cout << "Merging fragmented memory" << endl;
    cout << endl;
    memory *current = head;
    int freeMemory = 0;

    while (current != nullptr)
    {
        if (!current->isAllocated)
        {
            freeMemory += current->data;

            if (current == head)
            {
                head = current->next;
                delete current;
                current = head;
            }
            else
            {
                memory *prev = head;
                while (prev->next != current)
                {
                    prev = prev->next;
                }
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        }
        else
        {
            current = current->next;
        }
    }

    if (freeMemory > 0)
    {
        int remainder = freeMemory % 8;
        int size = freeMemory - remainder;

        int i = 1;
        while (size > 0)
        {
            memory *newNode = new memory();
            newNode->data = 8 * i;
            newNode->isAllocated = false;
            if (newNode->data > size)
            {
                remainder += size;
                break;
            }
            current = head;
            if (head == nullptr)
            {
                head = newNode;
                newNode->prev = nullptr;
            }
            else
            {
                current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = newNode;
                newNode->prev = current;
            }

            size -= 8 * i;
            i++;
        }

        if (remainder > 0)
        {
            memory *newNode = new memory();
            newNode->data = remainder;
            newNode->isAllocated = false;

            if (head == nullptr)
            {
                head = newNode;
                newNode->prev = nullptr;
            }
            else
            {
                current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = newNode;
                newNode->prev = current;
            }
        }
    }
}

int main()
{
    cout << "Legend: " << endl;
    cout << "+ - Allocated memory" << endl;
    cout << "- - Free memory" << endl;
    cout << endl;
    memory *node = NULL;
    memory *temp = nullptr;
    NewBlock(&node, 64);
    NewBlock(&node, 56);
    NewBlock(&node, 48);
    NewBlock(&node, 40);
    node->isAllocated = true;
    NewBlock(&node, 32);
    NewBlock(&node, 24);
    node->isAllocated = true;
    NewBlock(&node, 16);
    NewBlock(&node, 8);
    printResult(node);
    temp = firstFit(node, 14);
    printResult(node);
    nextFit(node, 10);
    printResult(node);
    temp = firstFit(node, 7);
    printResult(node);
    temp = best_fit(node, 3000);
    printResult(node);
    temp = worst_fit(node, 1);
    printResult(node);
    mergeMemory(node);
    printResult(node);
    temp = best_fit(node, 30);
    printResult(node);
    temp = firstFit(node, 10);
    printResult(node);
    mergeMemory(node);
    printResult(node);
    memory *current = node;
    while (current != nullptr)
    {
        memory *temp = current;
        current = current->next;
        delete temp;
    }
}