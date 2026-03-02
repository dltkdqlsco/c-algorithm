#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

/**
typename T : 큐에 저장할 데이터의 실제 타입이다.

typename Container = vector <T> : 데이터를 실제로 담아두는 저장소 역할을 한다.
    vector<T>가 기본으로 설정되어 있다.

typename Predicate = less<T> : 어떤 데이터가 우선순위가 높은지 결정하는
기준이다. less<T>는 내림차순/최대 힙이다. 즉, 값이 클수록 우선순위가 높다는
뜻이다. greater<T>를 넣으면 값이 작을수록 우선순위가 높은 최소 힙이 된다.

 */
template <typename T, typename Container = vector<T>,
          typename Predicate = less<T>>
class PriorityQueue {
public:
  void push(const T &data) {
    _heap.push_back(data);

    // 여기서 static_cast를 사용한 이유는 size()함수는 보통 size_t(부호 없는 큰
    // 정수)타입으로 반환한다. 이를 안전하게 int로 변환해주기 위해서 이다.
    // (int)로 캐스팅하는 방법도 있는데 static_cast로 하는 이유는 더 명확하고
    // 안전한 캐스팅을 제공하기 때문이다. (int)는 전형 상관 없는 타입끼리도
    // 캐스팅이 가능하다 그래서 나중에 버그가 발생할때 찾기가 어렵다. 하지만
    // static_cast는 변환 간으한 타입끼리만 허용한다. 그래서 컴파일 타임에
    // 오류를 잡아낼 수 있다.
    int now = static_cast<int>(_heap.size()) - 1;

    while (now > 0) {
      // -1를 하는 이유는 인덱스가 0부터 시작하기 때문이다.
      int next = (now - 1) / 2; // 현재 위치의 부모 인덱스 계산

      // now가 next보다 우선순위가 낮다면 교환이 필요없다.
      // 최대 힙에서는 now가 next보다 작아야 한다. - less
      // 최소 힙에서는 now가 next보다 커야 한다. - greater
      if (_predicate(_heap[now], _heap[next]))
        break;

      ::swap(_heap[now], _heap[next]);
      now = next;
    }
  }

  void pop() {
    _heap[0] = _heap.back();
    _heap.pop_back();

    int now = 0;

    while (true) {
      int left = now * 2 + 1;
      int right = now * 2 + 2;

      if (left >= (int)_heap.size())
        break;

      int next = now;

      if (_predicate(_heap[next], _heap[left]))
        next = left;

      if (right < (int)_heap.size() && _predicate(_heap[next], _heap[right]))
        next = right;

      if (next == now)
        break;

      ::swap(_heap[now], _heap[next]);
      now = next;
    }
  }

  T &top() { return _heap[0]; }

  bool empty() { return _heap.empty(); }

private:
  // Container가 vector<int>라면, 이줄은 vector<int> _heap;과 똑같아진다.
  Container _heap = {}; // 데이터를 담을 실제 저장소 객체 생성
  // Predicate가 less<int>라면, 이줄은 less<int> _predicate;가 된다.
  Predicate _predicate = {}; // 비교를 수행할 실제 판단 도구 객체 생성
};

int main() {
  PriorityQueue<int, vector<int>, greater<int>> pq;

  pq.push(100);
  pq.push(300);
  pq.push(200);
  pq.push(500);
  pq.push(400);

  while (pq.empty() == false) {
    int value = pq.top();
    pq.pop();

    cout << value << endl;
  }

  return 0;
}
