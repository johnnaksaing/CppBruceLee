#pragma once
#include "fibonacci.h"

//재귀, 메모이제이션 없이 반복문을 써서 계산하기
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

//재귀를 이용한 방법. O(2^n), 콜스택 폭발위험 있음.
int fibo_NaiveRecursive(int n)
{
	if (n == 1 || n == 2) { return 1; }
	else return fibo_NaiveRecursive(n - 2) + fibo_NaiveRecursive(n - 1);
}

//꼬리 재귀. Liner한 호출이라 스택 터질 위험이 적다.
int fibo_TailRecursive_inner(int n, int result0, int result1)
{
	if (n == 1 || n == 2) { return result1; }
	else return { fibo_TailRecursive_inner(n - 1, result1 , result0 + result1) };
}

int fibo_TailRecursive(int n)
{
	return fibo_TailRecursive_inner(n, 1, 1);
}


//동적 계획법. 기존의 계산을 저장해두고 필요할때 꺼내어 쓰며, 재귀를 쓰지 않아 빠르고, 메모리 영역에서 스택 대신 힙을 써서 터질 걱정도 적다. O(n)

//vector를 사용한 구현, 숫자를 담는 vector가 static이 아니라서 매 호출마다 O(n)이 걸린다.
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

//vector 대신 map을 사용한 구현
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


//탬플릿 메타프로그래밍(TMP). 많은 연산을 컴파일 시간에 짬때리는 방법으로 런타임의 연산을 줄인다.
// 구조체 선언은 헤더 파일에

//컴파일 시점에 알 수 없는 상수는 사용할 수 없는 한계점이 있다.
int fibo_TMP0(int n)
{
	if (n == 1 || n == 2) { return 1; }
	//else return fibo<n-1>; // error : constant
	else return -1;
}

//런타임에 결정가능하게 비틀은 TMP.
int fibo_TMP1(int n)
{
	if (n == 1 || n == 2) { return 1; }
	else return 0;
}

//람다 표현식 이용
int fibo_Lambda_Recursive(int n)
{
	auto fibo = [](int n_, auto& fibo) ->int {
		if (n_ == 1 || n_ == 2) return 1;
		else return fibo(n_ - 1, fibo) + fibo(n_ - 2, fibo);
	};

	return fibo(n, fibo);
}

//이거 vector로 못 쓰나?
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

	//a_i의 m00 : i번째 피보나치 수
	for (int i = 1; i < n; i++)
	{
		a = a * fibo;
	}

	return a.getM00();
}


//b를 n번
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
		//n은 홀수
		a = matrix_pow(b, (n - 1) / 2);
		a = a * a * b;
	}
	else {
		//n은 짝수
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

//점화식의 일반해. 컴퓨터에서는 오차가 너무 크다.
float fibo_relation(int n)
{
	float root5 = std::sqrt(5.0f);
	return (1 / root5) * (std::pow((1 + root5) / 2, n) + std::pow((1 - root5) / 2, n));
}


//멀티스레드
//로 구하는방법은 나중에

/*
int main() {

	//O(2^n) 방법들
	__PRINT_FIBO_AND_NAME__(12, fibo_NaiveRecursive);
	__PRINT_FIBO_AND_NAME__(12, fibo_TailRecursive);
	
	//O(n) 방법들
	__PRINT_FIBO_AND_NAME__(12, fibo_loop);
	
	__PRINT_FIBO_AND_NAME__(12, fibo_Dynamic);
	__PRINT_FIBO_AND_NAME__(12, fibo_Dynamic_vector);

	//람다 표현식 사용
	__PRINT_FIBO_AND_NAME__(12, fibo_Lambda_Recursive);
	__PRINT_FIBO_AND_NAME__(12, fibo_Lambda_Dynamic);

	//O(log n) 방법들
	__PRINT_FIBO_AND_NAME__(12, fibo_relation);

	__PRINT_FIBO_AND_NAME__(12, fibo_Matrix);
	__PRINT_FIBO_AND_NAME__(12, fibo_Matrix_DnQ_callstack);
	__PRINT_FIBO_AND_NAME__(12, fibo_Matrix_DnQ_math);

	//O(1) 방법...?
	std::cout << fibo_TMP(12) << " : fibo_TMP" << "\n";
	__PRINT_FIBO_AND_NAME__(12, fibo_constexpr);

	return 0;
}
*/