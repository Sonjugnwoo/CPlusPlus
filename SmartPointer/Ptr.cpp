#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <set>

// ���� ������ Ŭ����.
class Member :public std::enable_shared_from_this<Member> {
	
	std::vector<std::shared_ptr<Member>> children; // �ڽĵ� (shared_ptr�� ����)
	std::vector<std::weak_ptr<Member>> parents;   // �θ�� (weak_ptr, ��ȯ ���� ����)
	std::vector<std::weak_ptr<Member>> spouses;   // ����ڵ� (weak_ptr)
	std::string name;                              // �̸� �Ǵ� �ĺ���

public:
	// ������: �̸� �ʱ�ȭ
	Member(const std::string& name) : name(name) {}

	// �θ� �߰� �Լ� (�ߺ� ��� ���� ����)
	void AddParent(const std::shared_ptr<Member>& parent) {
		// �̹� ��ϵ� �θ����� �˻�
		for (const auto& p : parents) {
			if (auto sp = p.lock()) {
				if (sp == parent) return; // �̹� ��ϵ� �θ��� ����
			}
		}
		parents.push_back(parent);               // �θ� ��Ͽ� �߰� (weak_ptr ��ȯ �ڵ�)
		parent->AddChild(shared_from_this());    // �θ� ��ü�� �ڽ����� ���� ��ü ��� (�����)
	}

	// ����� �߰� �Լ� (�ߺ� ��� ���� �� ����� ����ȭ)
	void AddSpouse(const std::shared_ptr<Member>& spouse) {
		// �̹� ����ڷ� ��ϵǾ� �ִ��� �˻�
		for (const auto& w : spouses) {
			if (auto sp = w.lock()) {
				if (sp == spouse) return;       // �ߺ� �� ����
			}
		}

		spouses.push_back(spouse);                // ����� ��Ͽ� �߰� (weak_ptr ��ȯ �ڵ�)

		// ��� ����ڿ��Ե� ���� ��ü�� ����ϵ��� ��û (��� �� �Ǿ� �ִٸ�)
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

	// �ڽ� �߰� �Լ� (�ߺ� ��� �˻� �� ����� ����)
	void AddChild(const std::shared_ptr<Member>& child) {
		// �̹� ��ϵ� �ڽ����� üũ
		for (const auto& c : children) {
			if (c == child) return;    // �ߺ� �� ����
		}
		children.push_back(child);        // �ڽ� ��Ͽ� �߰�
		child->AddParent(shared_from_this());  // �ڽ� ��ü�� �θ�� ���� ��ü ��� (�����)
	}

	// �ڽ� �������� (�б� ����)
	const std::vector<std::shared_ptr<Member>>& GetChildren() const { return children; }

	// �θ� �������� (�б� ����)
	const std::vector<std::weak_ptr<Member>>& GetParents() const { return parents; }

	// ����� �������� (�б� ����)
	const std::vector<std::weak_ptr<Member>>& GetSpouses() const { return spouses; }


};

// ���� ���� Ŭ����
struct  Famliy {

	std::vector<std::shared_ptr<Member>> entire_family;  // ��ü ���� ��� ���� ����

	// �� ��� ������ �̼��� BFS�� ���
	int Chon(Member* mem1, Member* mem2) {
		if (mem1 == mem2) return 0; // ���� ����� ��� 0��

		std::queue<std::pair<Member*, int>> q;  // BFS Ž���� ť: (���� ���, ���� �̼�)
		std::set<Member*> visited;               // �湮�� ��� üũ(�ߺ��湮 ����)

		q.push(std::make_pair(mem1, 0));        // ������ ť�� ���� (0�̺��� ����)
		visited.insert(mem1);

		while (!q.empty()) {
			std::pair<Member*, int> elem = q.front();
			Member* curr = elem.first;           // ���� Ž�� ��� ���
			int dist = elem.second;              // ������� ������ �̼�
			q.pop();

			// �θ� Ž��: weak_ptr�̹Ƿ� lock() �� Ȯ��
			for (auto& wp : curr->GetParents()) {
				if (auto p = wp.lock()) {
					if (p.get() == mem2) return dist + 1;   // ã������ �̼� ��ȯ
					if (visited.insert(p.get()).second) {   // ���� �湮 ��������
						q.push(std::make_pair(p.get(), dist + 1));
					}
				}
			}

			// �ڽ� Ž��: shared_ptr�̹Ƿ� �ٷ� ���� ����
			for (auto& c : curr->GetChildren()) {
				if (c.get() == mem2) return dist + 1;
				if (visited.insert(c.get()).second) {
					q.push(std::make_pair(c.get(), dist + 1));
				}
			}

			// ����� Ž��: weak_ptr�̹Ƿ� lock() �� Ȯ��
			for (auto& wp : curr->GetSpouses()) {
				if (auto s = wp.lock()) {
					if (s.get() == mem2) return dist + 1;
					if (visited.insert(s.get()).second) {
						q.push(std::make_pair(s.get(), dist + 1));
					}
				}
			}
		}

		return -1; // �� ��� ���̿� ���� ���谡 ���� ��� -1 ��ȯ
	}
};


int main() {
	// Member ��ü ����
	auto m0 = std::make_shared<Member>("m0");
	auto m1 = std::make_shared<Member>("m1");
	auto m2 = std::make_shared<Member>("m2");
	auto m3 = std::make_shared<Member>("m3");
	auto m4 = std::make_shared<Member>("m4");

	// ����� ���� ����
	m0->AddSpouse(m1);
	m1->AddSpouse(m0);

	m3->AddSpouse(m4);
	m4->AddSpouse(m3);

	// �θ�-�ڽ� ���� ���� (m0, m1 �κ��� �ڽ� m2, m3)
	m0->AddChild(m2);
	m1->AddChild(m2);

	m0->AddChild(m3);
	m1->AddChild(m3);

	// Family Ŭ������ ���� ������ ���
	Famliy family;
	family.entire_family.push_back(m0);
	family.entire_family.push_back(m1);
	family.entire_family.push_back(m2);
	family.entire_family.push_back(m3);
	family.entire_family.push_back(m4);

	// �̼� ��� ����
	std::cout << "�̼�(m0, m2): " << family.Chon(m0.get(), m2.get()) << std::endl; // 1 (�θ�-�ڽ�)
	std::cout << "�̼�(m2, m1): " << family.Chon(m2.get(), m1.get()) << std::endl; // 1 (�ڽ�-�θ�)
	std::cout << "�̼�(m3, m4): " << family.Chon(m3.get(), m4.get()) << std::endl; // 1 (�����)
	std::cout << "�̼�(m2, m4): " << family.Chon(m2.get(), m4.get()) << std::endl; // 3 (�ڽ�->�θ�->�����)

	return 0;
}