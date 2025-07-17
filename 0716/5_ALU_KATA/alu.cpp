#include <string>
#include "result.cpp"
#include "Status.h"

class ALU {
public:
	void setOperand1(int operand1) {
		has_set_operand1 = true;
		this->operand1 = operand1;
	}

	void setOperand2(int operand2) {
		has_set_operand2 = true;
		this->operand2 = operand2;
	}

	void setOpcode(std::string OPCODE) {
		if(OPCODE == "ADD") this->opcodeEnum = ADD;
		else if(OPCODE == "SUB") this->opcodeEnum = SUB;
		else if(OPCODE == "MUL") this->opcodeEnum = MUL;
		else this->opcodeEnum = ETC;
	}

	void enableSignal(Result *r) {
		if(__SetErrorStatusWhenNotSetOperand(r)) return;
		if(__SetErrorStatusIfOpcodeInvalid(r)) return;

		int result = op_func[static_cast<int>(opcodeEnum)](operand1,operand2);
		r->setResultOnlyIfNormalStatus(result);
	}

private:
	bool has_set_operand1=false, has_set_operand2=false;
	int operand1, operand2;

	enum Enum{ ADD, SUB, MUL, ETC };
	Enum opcodeEnum = ETC;

private:
	bool __SetErrorStatusWhenNotSetOperand(Result *r) const {
		if(false == has_set_operand1) {
			r->setStatus(Status::OPERAND1_WRONG);
			return true;
		}
		else if(false == has_set_operand2) {
			r->setStatus(Status::OPERAND2_WRONG);
			return true;
		}
		return false;
	}

	bool __SetErrorStatusIfOpcodeInvalid(Result *r) const {
		if(this->opcodeEnum == ETC) {
			r->setStatus(Status::OPCODE_WRONG);
			return true;
		}
		return false;
	}

	static int __Add(int x, int y) { return x+y; }
	static int __Sub(int x, int y) { return x-y; }
	static int __Mul(int x, int y) { return x*y; }

	typedef int (*F)(int,int);
	F op_func[3] = {__Add, __Sub, __Mul};

};