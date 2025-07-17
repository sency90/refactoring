#include "gmock/gmock.h"
#include "alu.cpp"
#include "result.cpp"
#include "Status.h"

using namespace testing;
class ALUFixture : public Test {
private:
	constexpr static int NA = -1;
public:
	ALU alu;
	Result ret;
	void expect_eq(int *op1, int *op2, const std::string *opcode, Status expected_status, int expected_res = NA) {
		if(op1 != nullptr) alu.setOperand1(*op1);
		if(op2 != nullptr) alu.setOperand2(*op2);
		if(opcode != nullptr) alu.setOpcode(*opcode);

		alu.enableSignal(&ret);
		EXPECT_EQ(ret.getStatus(), expected_status);
		if(expected_status == Status::NORMAL) {
			EXPECT_EQ(ret.getResult(),expected_res);
		}

		if(op1 != nullptr) delete op1;
		if(op2 != nullptr) delete op2;
		if(opcode != nullptr) delete opcode;
	}
};

TEST_F(ALUFixture, ADDTest) {
	expect_eq(new int(10), new int(20), new std::string("ADD"), Status::NORMAL, 30);
}

TEST_F(ALUFixture, ADDTestOperand1Error) {
	expect_eq(nullptr, new int(20), new std::string("ADD"), Status::OPERAND1_WRONG);
}

TEST_F(ALUFixture, ADDTestOperand2Error) {
	expect_eq(new int(10), nullptr, new std::string("ADD"), Status::OPERAND2_WRONG);
}

TEST_F(ALUFixture, MULTest) {
	expect_eq(new int(10), new int(20), new std::string("MUL"), Status::NORMAL, 200);
}

TEST_F(ALUFixture, MULTestOperand1Error) {
	expect_eq(nullptr, new int(20), new std::string("MUL"), Status::OPERAND1_WRONG);
}

TEST_F(ALUFixture, MULTestOperand2Error) {
	expect_eq(new int(10), nullptr, new std::string("MUL"), Status::OPERAND2_WRONG);
}

TEST_F(ALUFixture, SUBTest) {
	expect_eq(new int(10), new int(20), new std::string("SUB"), Status::NORMAL, -10);
}

TEST_F(ALUFixture, SUBTestOperand1Error) {
	expect_eq(nullptr, new int(20), new std::string("SUB"), Status::OPERAND1_WRONG);
}

TEST_F(ALUFixture, SUBTestOperand2Error) {
	expect_eq(new int(10), nullptr, new std::string("SUB"), Status::OPERAND2_WRONG);
}

TEST_F(ALUFixture, OpcodeTestFail) {
	expect_eq(new int(10), new int(20), nullptr, Status::OPCODE_WRONG);
}
