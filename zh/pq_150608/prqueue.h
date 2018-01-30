#ifndef PRQUEUE__H
#define PRQUEUE__H

#include <deque>
#include <queue>

template<class T,class Pred>
class predicate_queue
{
	std::deque<T> left_q;
	std::deque<T> right_q;
	std::deque<bool> bool_q;
	Pred p;
public:

	predicate_queue(Pred x = Pred()):p(x) {};

	void push(const T& a)
	{
		bool_q.push_back(p(*this,a));
		if (!bool_q.back())
		{
			left_q.push_front(a);
		}
		else
		{
			right_q.push_back(a);
		}
	}
	int size() const
	{
		return bool_q.size();
	}
	const T& at(const int& a) const
	{
		if (a < left_q.size())
		{
			return left_q.at(a);
		}
		else
		{
			return right_q.at(a-left_q.size());
		}
	}
	const T& front() const
	{
		if (!bool_q.front())
		{
			return left_q.back();
		}
		else
		{
			return right_q.front();
		}
	}
	T& front()
	{
		if (!bool_q.front())
		{
			return left_q.back();
		}
		else
		{
			return right_q.front();
		}
	}

	void pop()
	{
		if (!bool_q.front())
		{
			left_q.pop_back();
		}
		else
		{
			right_q.pop_front();
		}
		bool_q.pop_front();
	}
	const T& operator[] (const int& a) const
	{
		if (a < left_q.size())
		{
			return left_q.at(a);
		}
		else
		{
			return right_q.at(a - left_q.size());
		}
	}

	operator std::queue<T>() const
	{
		predicate_queue<T,Pred> cpy(*this);
		std::queue<T> res;
		while (cpy.size())
		{
			res.push(cpy.front());
			cpy.pop();
		}
		return res;
	}
};

#endif