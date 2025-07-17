#pragma once
#include "Status.h"

class Result
{
    Status status = Status::NOT_CALCED_YET;
    int result;

    //status -1 : 결과 안나옴
    //status 0 : 성공
    //status 1 : Operand1이 잘못됨
    //status 2 : Operand2가 잘못됨
    //status 3 : OPCODE가 잘못되었음
    //status 65535 : 결과 없음

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