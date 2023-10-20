#include "PmergeMe.hpp"

static void dqInsert(std::deque<int> &dq, size_t beg, size_t end)
{
        if(dq[beg] > dq[end])
        {
            int tmp = dq[end];
            dq[end] = dq[beg];
            dq[beg] = tmp;
        }
}

static void dqMerge(std::deque<int> &dq, size_t beg, size_t mid, size_t end)
{
    std::deque<int> left(dq.begin() + beg, dq.begin() + mid + 1);
    std::deque<int> right(dq.begin() + mid + 1, dq.begin() + end + 1);
    size_t left_i = 0;
    size_t right_i = 0;
    for (size_t i = beg; i < end + 1; ++i)
    {
        if (right_i == right.size())
        {
            dq[i] = left[left_i];
            ++left_i;
        }
        else if (left_i == left.size())
        {
            dq[i] = right[right_i];
            ++right_i;
        }
        else if (left[left_i] < right[right_i])
        {
            dq[i] = left[left_i];
            ++left_i;
        }
        else
        {
            dq[i] = right[right_i];
            ++right_i;
        }
    }
}

static void dqSort(std::deque<int> &dq, size_t beg, size_t end)
{
    if (end - beg >= 2)
    {
        size_t mid = (beg + end) / 2;
        dqSort(dq, beg, mid);
        dqSort(dq, mid + 1, end);
        dqMerge(dq, beg, mid, end);
    }
    else
        dqInsert(dq, beg, end);
}

static void vcInsert(std::vector<int> &vc, size_t beg, size_t end)
{
	if(vc[beg] > vc[end])
	{
		int tmp = vc[end];
		vc[end] = vc[beg];
		vc[beg] = tmp;
	}
}

static void vcMerge(std::vector<int> &vc, size_t beg, size_t mid, size_t end)
{
	std::vector<int> left(vc.begin() + beg, vc.begin() + mid + 1);
    std::vector<int> right(vc.begin() + mid + 1, vc.begin() + end + 1);
	
    size_t left_i = 0;
    size_t right_i = 0;
    for (size_t i = beg; i < end + 1; ++i)
    {
        if (right_i == right.size())
        {
            vc[i] = left[left_i];
            ++left_i;
        }
        else if (left_i == left.size())
        {
            vc[i] = right[right_i];
            ++right_i;
        }
        else if (left[left_i] < right[right_i])
        {
            vc[i] = left[left_i];
            ++left_i;
        }
        else
        {
            vc[i] = right[right_i];
            ++right_i;
        }
    }
}

static void vcSort(std::vector<int> &vc, size_t beg, size_t end)
{
	if (end - beg >= 2)
    {
        size_t mid = (beg + end) / 2;
        vcSort(vc, beg, mid);
        vcSort(vc, mid + 1, end);
        vcMerge(vc, beg, mid, end);
    }
    else
        vcInsert(vc, beg, end);
}

int MergeInsertSort(std::deque<int> args)
{
    std::deque<int> dq(args);
    size_t beg = 0;
    size_t end = dq.size() - 1;

    std::vector<int> vc;
    vc.insert(vc.begin(), args.begin(), args.end());

	clock_t time_d;
	time_d = clock();
    dqSort(dq, beg, end);
	time_d = clock() - time_d;

	clock_t time_v;
	time_v = clock();
    vcSort(vc, beg, end);
	time_v = clock() - time_v;
   
    std::cout << "Before : " << std::endl;
	if(args.size() > 10)
	{
		for (size_t i = 0; i < args.size() && i < 10; ++i)
		{
			std::cout << args[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
	else
	{
		for (size_t i = 0; i < args.size() && i < 10; ++i)
			std::cout << args[i] << " ";
	}
    std::cout << std::endl;
    std::cout << "After : " << std::endl;
	if(args.size() > 10)
	{
		for (size_t i = 0; i < dq.size() && i < 10; ++i)
		{
			std::cout << dq[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
	else{
		for (size_t i = 0; i < dq.size() && i < 10; ++i)
			std::cout << dq[i] << " ";
	}
	std::cout << std::endl;
    std::cout << "Time to process a range of " << dq.size() << " elements with std::deque : " << std::fixed << std::setprecision(6)<<(float)time_d/CLOCKS_PER_SEC << " sec"<< std::endl;
    std::cout << std::endl;
	
	std::cout << "Before : " << std::endl;
	if(args.size() > 10)
	{
    	for (size_t i = 0; i < args.size() && i < 10; ++i)
		{
			std::cout << args[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
	else{
		for (size_t i = 0; i < args.size() && i < 10; ++i)
			std::cout << args[i] << " ";
	}
    std::cout << std::endl;
    std::cout << "After : " << std::endl;
	if(args.size() > 10)
	{
		for (size_t i = 0; i < vc.size() && i < 10; ++i)
		{
			std::cout << vc[i] << " ";
		}
		std::cout << "[...]" << std::endl;
	}
	else
	{
		for (size_t i = 0; i < vc.size() && i < 10; ++i)
		{
			std::cout << vc[i] << " ";
		}
	}
	std::cout << std::endl;
    std::cout << "Time to process a range of " << vc.size() << " elements with std::vector : " << std::fixed << std::setprecision(6)<<(float)time_v/CLOCKS_PER_SEC << " sec"<< std::endl;
	return EXIT_SUCCESS;
}