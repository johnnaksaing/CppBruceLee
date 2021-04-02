#pragma once
#include "fibonacci.h"

//���, �޸������̼� ���� �ݺ����� �Ἥ ����ϱ�
int fibo_loop(int n)
{
	if (n == 1 || n == 2) { return 1; }
	else
	{
		int a = 1; int b = 1;
		int result = 1;

		for (int i = 2; i < n; i++)
		{
			result += b;
			b = a;
			a = result;
		}
		return result;
	}
}

//��͸� �̿��� ���. O(2^n), �ݽ��� �������� ����.
int fibo_NaiveRecursive(int n)
{
	if (n == 1 || n == 2) { return 1; }
	else return fibo_NaiveRecursive(n - 2) + fibo_NaiveRecursive(n - 1);
}

//���� ���. Liner�� ȣ���̶� ���� ���� ������ ����.
int fibo_TailRecursive_inner(int n, int result0, int result1)
{
	if (n == 1 || n == 2) { return result1; }
	else return { fibo_TailRecursive_inner(n - 1, result1 , result0 + result1) };
}

int fibo_TailRecursive(int n)
{
	return fibo_TailRecursive_inner(n, 1, 1);
}


//���� ��ȹ��. ������ ����� �����صΰ� �ʿ��Ҷ� ������ ����, ��͸� ���� �ʾ� ������, �޸� �������� ���� ��� ���� �Ἥ ���� ������ ����. O(n)

//vector�� ����� ����, ���ڸ� ��� vector�� static�� �ƴ϶� �� ȣ�⸶�� O(n)�� �ɸ���.
int fibo_Dynamic_vector(int n)
{
	std::vector<int> fibos = std::vector<int>(n);
	fibos[0] = 1; fibos[1] = 1;

	for (int i = 2; i < n; i++)
	{
		fibos[i] = fibos[i - 1] + fibos[i - 2];
	}

	return fibos[n - 1];
}

//vector ��� map�� ����� ����
int fibo_Dynamic(int n)
{
	static std::map<int, int> fibos;
	fibos[1] = 1, fibos[2] = 1;

	if (fibos.find(n) == fibos.end())
	{
		for (int i = 2; i <= n; i++)
		{
			fibos[i] = fibos[i - 1] + fibos[i - 2];
		}
	}

	return fibos[n];
}


//���ø� ��Ÿ���α׷���(TMP). ���� ������ ������ �ð��� «������ ������� ��Ÿ���� ������ ���δ�.
// ����ü ������ ��� ���Ͽ�

//������ ������ �� �� ���� ����� ����� �� ���� �Ѱ����� �ִ�.
int fibo_TMP0(int n)
{
	if (n == 1 || n == 2) { return 1; }
	//else return fibo<n-1>; // error : constant
	else return -1;
}

//��Ÿ�ӿ� ���������ϰ� ��Ʋ�� TMP.
int fibo_TMP1(int n)
{
	if (n == 1 || n == 2) { return 1; }
	else return 0;
}

//���� ǥ���� �̿�
int fibo_Lambda_Recursive(int n)
{
	auto fibo = [](int n_, auto& fibo) ->int {
		if (n_ == 1 || n_ == 2) return 1;
		else return fibo(n_ - 1, fibo) + fibo(n_ - 2, fibo);
	};

	return fibo(n, fibo);
}

//�̰� vector�� �� ����?
int fibo_Lambda_Dynamic(int n)
{
	static std::map<int, int> fibos;
	fibos[0] = 1, fibos[1] = 1;

	auto fibo = [](int n, auto& fibo)->int {

		if (!fibos[n - 1])
		{
			fibos[n - 1] = fibo(n - 1, fibo) + fibo(n - 2, fibo);
		}

		return fibos[n - 1];
	};

	return fibo(n, fibo);
}

int fibo_Matrix(int n)
{
	if (n == 0) return 0;
	Matrix2x2 fibo = Matrix2x2(
		1, 1,
		1, 0
	);

	Matrix2x2 a = Matrix2x2(
		1, 0,
		0, 1
	);

	//a_i�� m00 : i��° �Ǻ���ġ ��
	for (int i = 1; i < n; i++)
	{
		a = a * fibo;
	}

	return a.getM00();
}


//b�� n��
Matrix2x2 matrix_pow(Matrix2x2& b, int n)
{
	Matrix2x2 a = Matrix2x2(
		1,0,
		0,1
	);
	if (n == 0) { return a; }
	else if (n == 1) { return b; }

	//std::cout << n ;
	if (n & 0x1) {
		//n�� Ȧ��
		a = matrix_pow(b, (n - 1) / 2);
		a = a * a * b;
	}
	else {
		//n�� ¦��
		a = matrix_pow(b, n / 2);
		a = a * a;
	}
	return a;
}

int fibo_Matrix_DnQ_callstack(int n)
{
	if (n == 0) return 0;
	Matrix2x2 a = Matrix2x2(
		1, 1,
		1, 0
	);
	a = matrix_pow(a, n - 1);
		
	return a.getM00();
}

int fibo_Matrix_DnQ_math(int n)
{
	static std::map<int, int> fibos;
	fibos[0] = 0, fibos[1] = 1;
	if (n == 0 || n == 1) return n;

	if (fibos[n] != 0) { return fibos[n]; }
	else
	{
		//F_2k = (2*F_k-1 + F_k) * F_k
		if ((n % 2) == 0)
		{
			int k = n / 2;
			int fibo_k = fibo_Matrix_DnQ_math(k);
			int fibo_k1 = fibo_Matrix_DnQ_math(k - 1);
			fibos[n] = (2 * fibo_k1 + fibo_k) * fibo_k;
		}
		//F_2k-1 = F_k ^ 2 + F_k-1 ^ 2
		else
		{
			int k = (n + 1) / 2;
			int fibo_k = fibo_Matrix_DnQ_math(k);
			int fibo_k1 = fibo_Matrix_DnQ_math(k - 1);
			fibos[n] = fibo_k * fibo_k + fibo_k1 * fibo_k1;
		}
	}
	return fibos[n];

}

//��ȭ���� �Ϲ���. ��ǻ�Ϳ����� ������ �ʹ� ũ��.
float fibo_relation(int n)
{
	float root5 = std::sqrt(5.0f);
	return (1 / root5) * (std::pow((1 + root5) / 2, n) + std::pow((1 - root5) / 2, n));
}


#include <thread>
#include <future>

//��Ƽ������
//�� ���ϴ¹���� ���߿�

int fibo_multithread_recursive(int n)
{
	int result = 0;
	if (n == 1 || n == 2) { result = 1; }
	else
	{
		std::future<int> x, y;

		x = std::async(std::launch::async, fibo_multithread_recursive, n - 1);
		y = std::async(std::launch::async, fibo_multithread_recursive, n - 2);

		//return x + y;
		result = x.get() + y.get();
	}
	
	return result;
}

int fibo_multithread_dynamic(int n) 
{
	static std::map<int, int> fibos;
	fibos[0] = 1, fibos[1] = 1, fibos[2] = 2, fibos[3] = 3, fibos[4] = 5;

	auto fibo = [](int n, auto& fibo)->int {

		if (!fibos[n - 1])
		{
			fibos[n - 1] = fibo(n - 1, fibo) + fibo(n - 2, fibo);
		}

		return fibos[n - 1];
	};

	//thread t(fibo);
	
	//std::thread t = std::thread(fibo,n,fibo);	
	std::future<int> x = std::async(std::launch::async, fibo_multithread_dynamic, n - 1);

	return x.get();
}



int fibo_nacci() {

	//O(2^n) �����
	__PRINT_FIBO_AND_NAME__(12, fibo_NaiveRecursive);
	__PRINT_FIBO_AND_NAME__(12, fibo_TailRecursive);
	__PRINT_FIBO_AND_NAME__(12, fibo_loop);
	
	//O(n) �����
	__PRINT_FIBO_AND_NAME__(12, fibo_Dynamic);
	__PRINT_FIBO_AND_NAME__(12, fibo_Dynamic_vector);

	//���� ǥ���� ���
	__PRINT_FIBO_AND_NAME__(12, fibo_Lambda_Recursive);
	__PRINT_FIBO_AND_NAME__(12, fibo_Lambda_Dynamic);

	//O(log n) �����
	__PRINT_FIBO_AND_NAME__(12, fibo_relation);

	__PRINT_FIBO_AND_NAME__(12, fibo_Matrix);

	__PRINT_FIBO_AND_NAME__(12, fibo_Matrix_DnQ_callstack);
	__PRINT_FIBO_AND_NAME__(12, fibo_Matrix_DnQ_math);

	//O(1) ���...?
	std::cout << fibo_TMP(12) << " : fibo_TMP" << "\n";
	__PRINT_FIBO_AND_NAME__(12, fibo_constexpr);

	//multithread
	//15���� ������ ��
	__PRINT_FIBO_AND_NAME__(12, fibo_multithread_recursive);
	//__PRINT_FIBO_AND_NAME__(13, fibo_multithread_dynamic);
	return 0;
}
