#pragma once
#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include <vector>
#include <map>

#define __PRINT_FIBO_AND_NAME__(n,fibo) print_with_name(n,fibo,#fibo)
//#define __PRINT_FIBO__N_NAME_FLOAT__(n,fibo) print_with_name<float>(n,fibo,#fibo)

//#define fibo_TMP(n) fibo<n>::value

// �־��� �Լ��� n��°(n > 0) �Ǻ���ġ ���� ȭ�鿡 ���� �׽�Ʈ �Լ�. int�� �ƴ� �ٸ� �ڷ������� ���� �����ϴ�.
template<typename T = int>
void print_for_test(int n, T(*fibo)(int))
{
	std::cout << fibo(n);
}

template<typename T = int>
void print_with_name(int n, T(*fibo)(int), std::string name)
{
	print_for_test<T>(n, fibo); std::cout << " : " /* << #fibo * */ << name << " \n";
}
/*
template<typename T = int>
void print_for_test(int n, T(*fibo)(int));

template<typename T = int>
void print_with_name(int n, T(*fibo)(int), std::string name);
*/

int fibo_loop(int n);

int fibo_NaiveRecursive(int n);
int fibo_TailRecursive_inner(int n, int result0, int result1);
int fibo_TailRecursive(int n);

int fibo_Dynamic_vector(int n);
int fibo_Dynamic(int n);

int fibo_TMP0(int n);
int fibo_TMP1(int n);

//���ø� ��Ÿ���α׷���(TMP). ���� ������ ������ �ð��� «������ ������� ��Ÿ���� ������ ���δ�.
template<int N>
struct fibo
{
	enum { value = fibo<N - 1>::value + fibo<N - 2>::value };
};
//�ش� �ڵ�� �������� ������ ������ ��.

template<>
struct fibo<1>
{
	enum { value = 1 };
};

template<>
struct fibo<2>
{
	enum { value = 1 };
};

//constexpr ����
//https://stackoverflow.com/questions/16219711/undefined-symbols-for-constexpr-function

//���C++�� �̿��� TMP�� ���� ȿ�� : constexpr
constexpr int fibo_constexpr(int n)
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

int fibo_Lambda_Recursive(int n);
int fibo_Lambda_Dynamic(int n);


//���
class Matrix2x2
{
private:

	int m[2][2];

public:
	Matrix2x2(
		int m00 = 1, int m01 = 0,
		int m10 = 0, int m11 = 1
	) {
		m[0][0] = m00; m[0][1] = m01;
		m[1][0] = m10; m[1][1] = m11;
	};

	/*
	Matrix2x2(
		int matrix[2][2]
	) {
		Matrix2x2::m00 = matrix[0][0]; Matrix2x2::m01 = matrix[0][1];
		Matrix2x2::m10 = matrix[1][0], Matrix2x2::m11 = matrix[1][1];
	};
	*/

	~Matrix2x2() {};

	Matrix2x2 operator + (Matrix2x2& b)
	{
		return Matrix2x2(
			m[0][0] + b.m[0][0], m[0][1] + b.m[0][1],
			m[1][0] + b.m[1][0], m[1][1] + b.m[1][1]
		);
	}

	Matrix2x2 operator * (Matrix2x2& b)
	{
		return Matrix2x2(
			m[0][0] * b.m[0][0] + m[0][1] * b.m[1][0], m[0][0] * b.m[0][1] + m[0][1] * b.m[1][1],
			m[1][0] * b.m[0][0] + m[1][1] * b.m[1][0], m[1][0] * b.m[0][1] + m[1][1] * b.m[1][1]
		);
	}

	int getM00() const { return m[0][0]; }
};

Matrix2x2 matrix_pow(Matrix2x2& b, int n);
int fibo_Matrix(int n);

int fibo_Matrix_DnQ_callstack(int n);

int fibo_Matrix_DnQ_math(int n);
float fibo_relation(int n);
