#include <iostream>
#include <cstdint>
#include <limits>
#include <cstdlib>
#include <cassert>
#include <stack>

using namespace std;

using data_type = size_t;


namespace ugly_solution {

class hanoi_tower
{
	class tower {
		stack<data_type> disks_ = {};
		string name_ = {};

	public:
		explicit tower(const string& name) { name_ = name; }

		data_type size() const { return disks_.size(); }

		bool empty() const { return disks_.empty(); }

		void clear() { while (!disks_.empty()) { disks_.pop(); } }

		bool push(data_type disk) {
			if (disks_.empty() || disks_.top() > disk) {
				disks_.push(disk);
				return true;
			}

			return false;
		}

		bool move_to(tower& t) {
			if (!disks_.empty() && t.push(disks_.top())) {
				disks_.pop();
				cout << "move " << t.disks_.top() << (" from " + name_ + " to " + t.name_).c_str() << endl;
				return true;
			}

			return false;
		}

	};

	tower A, B, C;
	const data_type disk_number_ = 0;

protected:
	void init(data_type disk_number)
	{
		if (disk_number <= 0) {
			return;
		}

		A.clear();
		B.clear();
		C.clear();

		for (data_type i = disk_number; i > 0; i--) {
			A.push(i);
		}
	}


	/*void move_from_A_to_C(data_type disk_number);
	void move_from_A_to_B(data_type disk_number);
	void move_from_B_to_A(data_type disk_number);
	void move_from_B_to_C(data_type disk_number);
	void move_from_C_to_A(data_type disk_number);
	void move_from_C_to_B(data_type disk_number);*/


	void move_from_A_to_C(data_type disk_number)
	{
		if (disk_number == 1) {
			A.move_to(C);
			return;
		}

		move_from_A_to_B(disk_number - 1);
		move_from_A_to_C(1);
		move_from_B_to_C(disk_number - 1);
	}

	void move_from_A_to_B(data_type disk_number)
	{
		if (disk_number == 1) {
			A.move_to(B);
			return;
		}

		move_from_A_to_C(disk_number - 1);
		move_from_A_to_B(1);
		move_from_C_to_B(disk_number - 1);
	}

	void move_from_B_to_A(data_type disk_number)
	{
		if (disk_number == 1) {
			B.move_to(A);
			return;
		}

		move_from_B_to_C(disk_number - 1);
		move_from_B_to_A(1);
		move_from_C_to_A(disk_number - 1);
	}

	void move_from_B_to_C(data_type disk_number)
	{
		if (disk_number == 1) {
			B.move_to(C);
			return;
		}

		move_from_B_to_A(disk_number - 1);
		move_from_B_to_C(1);
		move_from_A_to_C(disk_number - 1);
	}

	void move_from_C_to_A(data_type disk_number)
	{
		if (disk_number == 1) {
			C.move_to(A);
			return;
		}

		move_from_C_to_B(disk_number - 1);
		move_from_C_to_A(1);
		move_from_B_to_A(disk_number - 1);
	}

	void move_from_C_to_B(data_type disk_number)
	{
		if (disk_number == 1) {
			C.move_to(B);
			return;
		}

		move_from_C_to_A(disk_number - 1);
		move_from_C_to_B(1);
		move_from_A_to_B(disk_number - 1);
	}


public:
	explicit hanoi_tower(data_type disk_number)
		: A("A"), B("B"), C("C"), disk_number_(disk_number)
	{
		init(disk_number);
	}

	void solve() {
		cout << "testing " << disk_number_ << " disks......" << endl;
		move_from_A_to_C(disk_number_);
		assert(A.empty());
		assert(B.empty());
		assert(C.size() == disk_number_);
		cout << "success!" << endl;
	}
};

void test()
{
	if (0) {
		for (data_type i = 1; i < 10; i++) {
			hanoi_tower(i).solve();
		}
	}

	hanoi_tower(5).solve();
}

}

namespace c_style_solution {

void hanoi_impl(data_type disk_number, char from, char buffer, char to)
{
	if (disk_number == 1) {
		cout << "move disk " << disk_number << " from " << from << " to " << to << endl;
	} else {
		hanoi_impl(disk_number - 1, from, to, buffer);
		cout << "move disk " << disk_number << " from " << from << " to " << to << endl;
		hanoi_impl(disk_number - 1, buffer, from, to);
	}
}

void hanoi(data_type disk_number)
{
	cout << "resoving " << disk_number << " disks" << endl;
	hanoi_impl(disk_number, 'A', 'B', 'C');
	cout << "success!" << endl;
}

void test()
{
	hanoi(3);
	
	
}


};



int main()
{
	//ugly_solution::test();

	c_style_solution::test();

	system("pause");
}
