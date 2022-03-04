#ifndef ARRAYINT_H
#define ARRAYINT_H

#include <cassert> // ��� assert()
#include <iostream>

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    int getLength() {
        return m_length;
    }

    void erase()
    {
        delete[] m_data;

        // ����� ��� ����� ������� m_data �������� nullptr, ����� �� ������ �� ���� �������� ���������
        m_data = nullptr;
        m_length = 0;
    }

    // ������� resize �������� ������ �������. ��� ������������ �������� �����������. ������� ���������
    void resize(int newLength)
    {
        // ���� ������ ��� ������ ����� � return
        if (newLength == m_length)
            return;

        // ���� ����� ������� ������ ������ � ������ ��� � ����� return
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // ������ �����, ��� newLength >0
        // �������� ����� ������
        int* data = new int[newLength];

        // ����� ����� ����������� � ����������� ���������� ��������� � ����� ������
        // ����� ����������� ������� ���������, ������� �� ���� � ������� �� ��������
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            // ���������� �������� ��������
            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        // ������� ������ ������, ��� ��� �� ��� ��� �� �����
        delete[] m_data;

        // � ���������� ������ ������� ������� �����! �������� ��������, m_data ���������
        // �� ��� �� �����, �� ������� ��������� ��� ����� ����������� ���������� ������. ���������
        // ������ ���� ����������� ���������� � ��� �� ����� ����������, ����� ������ �� ������� ���������
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        // �������� ������������ ������������� �������
        assert(index >= 0 && index <= m_length);

        // ������� ����� ������ �� ���� ������� ������ ������� �������
        int* data = new int[m_length + 1];

        // �������� ��� �������� �� index-�
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        // ��������� ����� ������� � ����� ������
        data[index] = value;

        // �������� ��� �������� ����� ������������ ��������
        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];

        // ������� ������ ������ � ���������� ������ ���� ����� 
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) {
        insertBefore(value, m_length);
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }


    // task1 - start
    
    // 1.
    void pop_back() {
        this->resize(this->m_length - 1);
    }

    //2.
    void pop_front() {
        for (size_t i = 0; i < this->m_length - 1 ; i++) {
            this->m_data[i] = this->m_data[i + 1];
        }

        this->resize(this->m_length - 1);
    }

    //3.
    void sort() {
        int* m_temp = new int[this->m_length]{NULL};

        for (size_t i = 0; i < this->m_length; i++) {
            size_t iElemIndex = 0;

            for (size_t j = 0; j < this->m_length; j++) {
                if (i == j) {
                    continue;
                }

                if ((i < iElemIndex) && (this->m_data[i] == this->m_data[j])) { //�������� ����������� �� �������� ��������� "�������"
                    iElemIndex++;
                    break;
                }


                if (this->m_data[i] > this->m_data[j]) {
                    iElemIndex++;
                }

            }

            m_temp[iElemIndex] = this->m_data[i];
        }


        for (size_t k = 0; k < this->m_length; k++) {
            this->m_data[k] = m_temp[k];
        }

        delete[] m_temp;
    }

    //4.
    void print() const{
        for (size_t i = 0; i < this->m_length; i++) {
            std::cout << this->m_data[i] << std::endl;
        }
    }

    // task1 - end


    ~ArrayInt()
    {
        delete[] m_data;
    }
};

#endif