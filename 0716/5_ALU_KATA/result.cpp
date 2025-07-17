#pragma once
#include "Status.h"

class Result
{
    Status status = Status::NOT_CALCED_YET;
    int result;

    //status -1 : ��� �ȳ���
    //status 0 : ����
    //status 1 : Operand1�� �߸���
    //status 2 : Operand2�� �߸���
    //status 3 : OPCODE�� �߸��Ǿ���
    //status 65535 : ��� ����

public:
    void setStatus(Status status) {
        this->status = status;
    }

    void setResultOnlyIfNormalStatus(int result) {
        this->result = result;
        this->status = Status::NORMAL;
    }

    Status getStatus() {
        return status;
    }

    int getResult() {
        return result;
    }
};