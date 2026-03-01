#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

// shared_ptr : 참조 카운팅 방식의 스마트 포인터
// 여러 개의 shared_ptr이 하나의 객체를 동시에 가리킬 수 있다.
// 객체를 가리키는 포인터의 개수를 세고 있다가, 그 개수가 0이 되는 순간 메모리를
// 자동으로 해제한다.
using NodeRef = shared_ptr<struct Node>;

struct Node {
  Node() {}
  Node(const string &data) : data(data) {}

  string data;
  vector<NodeRef> children;
};

NodeRef createTree() {
  // shared_ptr을 만들 때 new를 직접 쓰는 대신 std::make_shared<T> 함수를
  // 사용하는 것이 좋다. new를 사용하게 되면 객체와 제어 블록 할달을 따로해서 총
  // 2번의 메모리 할당이 일어난다. make_shared<T>는 객체와 제어 블록을 한 번에
  // 할당하여 메모리 할당 횟수를 줄이고 성능을 향상시킨다.
  NodeRef root = make_shared<Node>("R1 개발실");
  {
    // shared_ptr이 객체를 가리키는 포인터의 개수를 세고 있다고 했다.
    // node라는 지역 변수가 "디자인팀" 객체를 가리킨다. 이때 참조 카운트가 1이
    // 된다. root->children이라는 vector에 node를 집어넣으면 vector안의 요소도
    // "디지인팀" 객체를 가리키게 된다. 즉, node변수와 vector가 객체를 공동
    // 소유하가 된어 참조 횟수는 2가 된다.
    NodeRef node = make_shared<Node>("디자인팀");
    root->children.push_back(node);
    {
      NodeRef leaf = make_shared<Node>("전투");
      node->children.push_back(leaf);
    }
    {
      NodeRef leaf = make_shared<Node>("경제");
      node->children.push_back(leaf);
    }
    {
      NodeRef leaf = make_shared<Node>("스토리");
      node->children.push_back(leaf);
    }
  }
  {
    NodeRef node = make_shared<Node>("프로그래밍팀");
    root->children.push_back(node);
    {
      NodeRef leaf = make_shared<Node>("서버");
      node->children.push_back(leaf);
    }
    {
      NodeRef leaf = make_shared<Node>("클라");
      node->children.push_back(leaf);
    }
    {
      NodeRef leaf = make_shared<Node>("엔진");
      node->children.push_back(leaf);
    }
  }
  {
    NodeRef node = make_shared<Node>("아트팀");
    root->children.push_back(node);
    {
      NodeRef leaf = make_shared<Node>("배경");
      node->children.push_back(leaf);
    }
    {
      NodeRef leaf = make_shared<Node>("캐릭터");
      node->children.push_back(leaf);
    }
  }
  return root;
}

void PrintTree(NodeRef root, int depth) {
  for (int i = 0; i < depth; i++) {
    cout << "- ";
  }
  cout << root->data << endl;

  // 재귀를 통해서 모든 노드를 방문해서 트리를 출력한다.
  for (NodeRef &child : root->children) {
    PrintTree(child, depth + 1);
  }
}

int GetHeight(NodeRef root) {
  int height = 1;
  for (NodeRef &child : root->children) {
    height = max(height, GetHeight(child) + 1);
  }
  return height;
}

int main() {
  NodeRef root = createTree();
  PrintTree(root, 0);
  int height = GetHeight(root);
  cout << "tree height : " << height << endl;
}