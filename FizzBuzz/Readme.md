# extendable-FizzBuzz
Ref : https://www.tomdalling.com/blog/software-design/fizzbuzz-in-too-much-detail/

> 1부터 15까지 숫자 중
3의 배수일 때 Fizz, 5의 배수일 때 Buzz를 출력하고, 3과 5의 배수일 때 FizzBuzz를 출력하고, 나머지 경우면 그냥 숫자를 출력하는 함수를 작성해주세요.

라고 리퀘스트가 들어왔다고 해봅시다.


## Naive Approach

```C++
for(int i = 1; i <= 15; i++)
{
	if (i%3 == 0 && i % 5 == 0)
		std::cout << "FizzBuzz";
	else  if(i%3 == 0)
		std::cout << "Fizz";
	else  if (i%5 == 0)
		std::cout << "Buzz";
	else
		std::cout << i;
	std::cout << endl;
}
```
정도로 구현할 수 있겠네요.
조건문을 공부하려고 하는 개발자라면 접해봤을 수도 있겠습니다.

여기서 만약에 클라이언트가 새로운 조건을 추가하고 싶어한다고 가정해보죠. 
> 7의 배수에는 Zazz를 출력했으면 좋겠어요. 
> 5랑 7이면 BuzzZazz, 3,5,7이면 FizzBuzzZazz. 되죠?
> 
조건 한 개 추가했을 뿐인데, 경우의 수가 여러 개 추가됩니다. **"7로만 나눠지는 경우",** **"3과 7"**, **"5와 7"**, **"3,5,7 모두"**. 기존 경우가 4가지였으니 두 배가 된 겁니다.
조건이 더 많아지면 어떻게 될까요? 11, 13, 17로 나눠떨어지는 수가 추가한다면 if-else문에 몇개를 더 추가해야 할까요? 2^n으로 늘어나는 경우의 수는 누가 추가해야 할까요? 바로 너입니다.

## Rules

그러니 확장성을 고려해서 다시 설계해 봅시다. 규칙으로 들어온 수가 무엇이든, 몇 개가 있든 작동했으면 좋겠네요. 

해당 int로 나누어 떨어질 때 string을 담은 자료구조를 하나 만들어봅시다.
```C++
#include <map>
#include <string>

std::map<int, std::string> Rules { {3,"Fizz"},{5,"Buzz"} }
```
그리고 코드를 이렇게 구현해주면...

```C++
for (int i = 1; i <= n; i++)
{
	std::string s = "";

	//conditions
	bool bDefault = true;
	for (const  auto& iter : Rules)
	{
		if (i % iter.first == 0)
		{
			s += Rules[iter.first];
			bDefault = false;
		}
	}
	//default
	if (bDefault)
	{
		s = std::to_string(i);
	}
	
	std::cout << s << std::endl;
}
```
매 숫자마다 Rules에 해당하는 게 있는지 확인할 수 있겠네요.

## 추가 확장

여기서 클라이어트가 **"나누어 떨어짐"** 말고 다른 조건을 가져온다고 가정해보면 어떨까요?
> 1부터 10까지 중 to_string(i)인 경우는 숫자 대신에 Yass로 출력되게 할 수는 없나요?

범위가 15까지밖에 안 되니까 반복문을 두 개로 나눌 생각을 하셨습니까? 당장 임시방편은 가능하겠지만 코드가 확장될 때, 예를 들면 범위가 1~100으로 확장되고, Yass가 10~30, 50~70, 90~100으로 나뉘는 등 반복문을 새로 쪼개야 하는 상황이 오면 결국 확장성에서 또 발목을 잡히게 됩니다.

이런 경우는 해당 조건을 함수로 만들어서 Rules에 담아야 하겠네요.

```C++
std::map<Condition,std::string> Rules_extended;

Rules_extended[Div(3)] = "Fizz";
Rules_extended[Div(5)] = "Buzz";
Rules_extended[Between(1,10)] = "Yass";
```
Condition 객체를 만드는 방법은... 생각 좀 해보고 다음 시간에 적겠습니다.