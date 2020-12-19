#include<iostream>
#include<thread>
#include<mutex>

#define CPP14_SOLUTION

bool       isWriterRunning;
bool       isReaderRunning;

#ifndef CPP14_SOLUTION

std::mutex writerMtx;
std::mutex readerMtx;
int        readerCounter = 0;

void writer()
{
    while(isWriterRunning)
    {
        writerMtx.lock();
        std::cout << "I am writing" << '\n';
        writerMtx.unlock();
    }
}

void reader(int reader_index)
{
    while (isReaderRunning)
    {
        readerMtx.lock();
        readerCounter++;
        if (readerCounter==1) writerMtx.lock();
        readerMtx.unlock();

        std::cout  <<"I am reading  reader: "<< reader_index << '\n';

        readerMtx.lock();
        readerCounter--;
        if (readerCounter==0) writerMtx.unlock();
        readerMtx.unlock();
    }
}

#else

#include <shared_mutex>
std::shared_timed_mutex sharedMtx;

void writer()
{
    while(isWriterRunning)
    {
        std::lock_guard<std::shared_timed_mutex> writerLock(sharedMtx);
        std::cout << "I am writing" << '\n';
    }
}

void reader(int reader_index)
{
    while (isReaderRunning)
    {
        std::shared_lock<std::shared_timed_mutex> readerLock(sharedMtx);
        std::cout  <<"I am reading  reader: "<< reader_index << '\n';
    }
}

#endif

int main()
{
    isWriterRunning = true;
    isReaderRunning = true;

    std::thread tReader1(reader,1);
    std::thread tReader2(reader,2);
    std::thread tReader3(reader,3);

    std::thread tWriter1(writer);
    std::thread tWriter2(writer);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    isWriterRunning = false;
    isReaderRunning = false;

    tReader1.join();
    tReader2.join();
    tReader3.join();
    tWriter1.join();
    tWriter2.join();

    return 0;
}
