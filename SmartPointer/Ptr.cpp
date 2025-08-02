#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <set>

// 가족 구성원 클래스.
class Member :public std::enable_shared_from_this<Member> {
	
	std::vector<std::shared_ptr<Member>> children; // 자식들 (shared_ptr로 소유)
	std::vector<std::weak_ptr<Member>> parents;   // 부모들 (weak_ptr, 순환 참조 방지)
	std::vector<std::weak_ptr<Member>> spouses;   // 배우자들 (weak_ptr)
	std::string name;                              // 이름 또는 식별자

public:
	// 생성자: 이름 초기화
	Member(const std::string& name) : name(name) {}

	// 부모 추가 함수 (중복 등록 방지 포함)
	void AddParent(const std::shared_ptr<Member>& parent) {
		// 이미 등록된 부모인지 검사
		for (const auto& p : parents) {
			if (auto sp = p.lock()) {
				if (sp == parent) return; // 이미 등록된 부모라면 종료
			}
		}
		parents.push_back(parent);               // 부모 목록에 추가 (weak_ptr 변환 자동)
		parent->AddChild(shared_from_this());    // 부모 객체에 자식으로 현재 객체 등록 (양방향)
	}

	// 배우자 추가 함수 (중복 등록 방지 및 양방향 동기화)
	void AddSpouse(const std::shared_ptr<Member>& spouse) {
		// 이미 배우자로 등록되어 있는지 검사
		for (const auto& w : spouses) {
			if (auto sp = w.lock()) {
				if (sp == spouse) return;       // 중복 시 종료
			}
		}

		spouses.push_back(spouse);                // 배우자 목록에 추가 (weak_ptr 변환 자동)

		// 상대 배우자에게도 현재 객체를 등록하도록 요청 (등록 안 되어 있다면)
		bool alreadyAdded = false;
		for (const auto& w : spouse->spouses) {
			if (auto sp = w.lock()) {
				if (sp.get() == this) {
					alreadyAdded = true;
					break;
				}
			}
		}
		if (!alreadyAdded) {
			spouse->AddSpouse(shared_from_this());
		}
	}

	// 자식 추가 함수 (중복 등록 검사 및 양방향 연결)
	void AddChild(const std::shared_ptr<Member>& child) {
		// 이미 등록된 자식인지 체크
		for (const auto& c : children) {
			if (c == child) return;    // 중복 시 종료
		}
		children.push_back(child);        // 자식 목록에 추가
		child->AddParent(shared_from_this());  // 자식 객체에 부모로 현재 객체 등록 (양방향)
	}

	// 자식 가져오기 (읽기 전용)
	const std::vector<std::shared_ptr<Member>>& GetChildren() const { return children; }

	// 부모 가져오기 (읽기 전용)
	const std::vector<std::weak_ptr<Member>>& GetParents() const { return parents; }

	// 배우자 가져오기 (읽기 전용)
	const std::vector<std::weak_ptr<Member>>& GetSpouses() const { return spouses; }


};

// 가족 관리 클래스
struct  Famliy {

	std::vector<std::shared_ptr<Member>> entire_family;  // 전체 가족 멤버 저장 공간

	// 두 사람 사이의 촌수를 BFS로 계산
	int Chon(Member* mem1, Member* mem2) {
		if (mem1 == mem2) return 0; // 같은 사람일 경우 0촌

		std::queue<std::pair<Member*, int>> q;  // BFS 탐색용 큐: (현재 사람, 현재 촌수)
		std::set<Member*> visited;               // 방문한 멤버 체크(중복방문 방지)

		q.push(std::make_pair(mem1, 0));        // 시작점 큐에 삽입 (0촌부터 시작)
		visited.insert(mem1);

		while (!q.empty()) {
			std::pair<Member*, int> elem = q.front();
			Member* curr = elem.first;           // 현재 탐색 대상 멤버
			int dist = elem.second;              // 현재까지 누적된 촌수
			q.pop();

			// 부모 탐색: weak_ptr이므로 lock() 후 확인
			for (auto& wp : curr->GetParents()) {
				if (auto p = wp.lock()) {
					if (p.get() == mem2) return dist + 1;   // 찾았으면 촌수 반환
					if (visited.insert(p.get()).second) {   // 아직 방문 안했으면
						q.push(std::make_pair(p.get(), dist + 1));
					}
				}
			}

			// 자식 탐색: shared_ptr이므로 바로 접근 가능
			for (auto& c : curr->GetChildren()) {
				if (c.get() == mem2) return dist + 1;
				if (visited.insert(c.get()).second) {
					q.push(std::make_pair(c.get(), dist + 1));
				}
			}

			// 배우자 탐색: weak_ptr이므로 lock() 후 확인
			for (auto& wp : curr->GetSpouses()) {
				if (auto s = wp.lock()) {
					if (s.get() == mem2) return dist + 1;
					if (visited.insert(s.get()).second) {
						q.push(std::make_pair(s.get(), dist + 1));
					}
				}
			}
		}

		return -1; // 두 사람 사이에 가족 관계가 없을 경우 -1 반환
	}
};


int main() {
	// Member 객체 생성
	auto m0 = std::make_shared<Member>("m0");
	auto m1 = std::make_shared<Member>("m1");
	auto m2 = std::make_shared<Member>("m2");
	auto m3 = std::make_shared<Member>("m3");
	auto m4 = std::make_shared<Member>("m4");

	// 배우자 관계 설정
	m0->AddSpouse(m1);
	m1->AddSpouse(m0);

	m3->AddSpouse(m4);
	m4->AddSpouse(m3);

	// 부모-자식 관계 설정 (m0, m1 부부의 자식 m2, m3)
	m0->AddChild(m2);
	m1->AddChild(m2);

	m0->AddChild(m3);
	m1->AddChild(m3);

	// Family 클래스에 가족 구성원 등록
	Famliy family;
	family.entire_family.push_back(m0);
	family.entire_family.push_back(m1);
	family.entire_family.push_back(m2);
	family.entire_family.push_back(m3);
	family.entire_family.push_back(m4);

	// 촌수 계산 예시
	std::cout << "촌수(m0, m2): " << family.Chon(m0.get(), m2.get()) << std::endl; // 1 (부모-자식)
	std::cout << "촌수(m2, m1): " << family.Chon(m2.get(), m1.get()) << std::endl; // 1 (자식-부모)
	std::cout << "촌수(m3, m4): " << family.Chon(m3.get(), m4.get()) << std::endl; // 1 (배우자)
	std::cout << "촌수(m2, m4): " << family.Chon(m2.get(), m4.get()) << std::endl; // 3 (자식->부모->배우자)

	return 0;
}