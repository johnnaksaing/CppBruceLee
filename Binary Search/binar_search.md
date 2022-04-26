

[읽어보면 좋은 링크](./https://www.acmicpc.net/board/view/83220)
왜 헷갈리는가? 구간설정이 탄탄하지 못해서.

```[left,right]```인 경우 ```left == right```일 때 종결해주어야 한다.  

```[left,right)```인 경우 ```func(left)```는 ```true```여야 하고 ```func(right)```는 ```false```여야 하며, 루프가 끝날 때 답은 ```right```이 된다.

### 풀어보면 좋은 문제
백준 2343 기타 레슨

