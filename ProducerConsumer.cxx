/*
Producer consumer problem
Bounded buffer problem
*/

#include <bits/stdc++.h>
#include <thread>

using namespace std;

class BoundedBuffer
{
	private:
	mutex lock;
	condition_variable cond;
	queue<int> buffer;
	size_t size;
	
	public:
	BoundedBuffer(size_t s)
	: size(s)
	{}
	void add(int val)
	{
		unique_lock<mutex> locker(lock);
		cond.wait(locker, [this](){return buffer.size()<size;});
		buffer.push(val);
		cout << "Buffer(" << buffer.size() << ") add: " << val << endl;
		locker.unlock();
		cond.notify_all();
		return;
	}
	int remove()
	{
		unique_lock<mutex> locker(lock);
		cond.wait(locker, [this](){return buffer.size()>0;});
		int val = buffer.front();
		buffer.pop();
		cout << "Buffer (" << buffer.size() << ") remove: " << val << endl;
		locker.unlock();
		cond.notify_all();
		return val;
	}
};
	
class Producer
{
	private:
	BoundedBuffer& b;
	public:
	Producer(BoundedBuffer& b)
	: b(b)
	{}
	
	void execute()
	{
		int val = 0;
		while(true)
		{
			cout << "Produced: " << ++val << endl;
			b.add(val);
			std::this_thread::sleep_for (std::chrono::seconds(rand()%2));
		}
	}
};

class Consumer
{
	private:
	BoundedBuffer& b;
	public:
	Consumer(BoundedBuffer& b)
	: b(b)
	{}
	
	void execute()
	{
		int val;
		while(true)
		{
			val = b.remove();
			cout << "Consumed: " << val << endl;;
			std::this_thread::sleep_for (std::chrono::seconds(rand()%5));
		}
	}
};

int main()
{
	BoundedBuffer b(3);
	Producer p(b);
	Consumer c(b);
	
	thread t1(Producer::execute, p);
	thread t2(Consumer::execute, c);
	t1.join();
	t2.join();
}