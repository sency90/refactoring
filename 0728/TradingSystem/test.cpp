#include "gmock/gmock.h"
#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
#include "kiwer_api.cpp"
#define interface struct

using namespace testing;

//첫번째 해야할 일
//ToDo를 작성한다.
//실습 문제에서 요구한걸 다시 봐보자.
//
//[기본 기능]
//	1. selectStockBroker()
//	2. login(id, pw)
//	3. buy(stockCode, price, qty)
//	4. sell(stockCode, price, qty)
//	5. getPrice(stockCode)
//
//[고급 기능]
//	1. buyNiceTiming(code, totalMoney)
//	2. sellNiceTiming(code, qty)
//위의 기능들이 전부 AutoTradingSystem Class에서 구현되어야 한다.

TEST(AutoTradingSystemTest, SelectStockBroker) {
	MockStockBroker mockStockBroker;
	AutoTradingSystem autoTradingSystem;
	autoTradingSystem.selectStockBroker(&mockStockBroker);

	EXPECT_EQ(autoTradingSystem.getStockBroker(), &mockStockBroker);
}

TEST(AutoTradingSystemTest, Login) {
	MockStockBroker mockStockBroker;
	AutoTradingSystem autoTradingSystem;
	autoTradingSystem.selectStockBroker(&mockStockBroker);

	const std::string VALID_ID = "valid_id";
	const std::string VALID_PW = "valid_pw";
	EXPECT_CALL(mockStockBroker, login(VALID_ID, VALID_PW))
		.Times(1);

	autoTradingSystem.login(VALID_ID, VALID_PW);
}

TEST(AutoTradingSystemTest, Login_WhenBrokerNotSet_Throws) {
	AutoTradingSystem autoTradingSystem;
	//autoTradingSystem.selectStockBroker(&mockStockBroker); -- This function has not been called.

	const std::string VALID_ID = "valid_id";
	const std::string VALID_PW = "valid_pw";
	EXPECT_THROW({ autoTradingSystem.login(VALID_ID, VALID_PW); }, std::logic_error);
}

TEST(AutoTradingSystemTest, Buy) {
	MockStockBroker mockStockBroker;
	AutoTradingSystem autoTradingSystem;
	autoTradingSystem.selectStockBroker(&mockStockBroker);

	const std::string VALID_ID = "valid_id";
	const std::string VALID_PW = "valid_pw";
	EXPECT_CALL(mockStockBroker, login(VALID_ID, VALID_PW))
		.Times(1);
	autoTradingSystem.login(VALID_ID, VALID_PW);

	const std::string VALID_STOCK_CODE = "000372";
	const int VALID_PRICE = 70000;
	const int VALID_QTY = 3;
	EXPECT_CALL(mockStockBroker, buy(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY))
		.Times(1);
	autoTradingSystem.buy(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY);
}

TEST(AutoTradingSystemTest, Buy_WhenNotLogin_Throws) {
	MockStockBroker mockStockBroker;
	AutoTradingSystem autoTradingSystem;
	autoTradingSystem.selectStockBroker(&mockStockBroker);

	const std::string VALID_STOCK_CODE = "000372";
	const int VALID_PRICE = 70000;
	const int VALID_QTY = 3;
	EXPECT_THROW({ autoTradingSystem.buy(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY); }, std::logic_error);
}

TEST(AutoTradingSystemTest, Buy_WhenNotLoginAndNotSelectStockBroker_Throws) {
	AutoTradingSystem autoTradingSystem;

	const std::string VALID_STOCK_CODE = "000372";
	const int VALID_PRICE = 70000;
	const int VALID_QTY = 3;
	EXPECT_THROW({ autoTradingSystem.buy(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY); }, std::runtime_error);
}

TEST(AutoTradingSystemTest, Sell) {
	MockStockBroker mockStockBroker;
	AutoTradingSystem autoTradingSystem;
	autoTradingSystem.selectStockBroker(&mockStockBroker);

	const std::string VALID_ID = "valid_id";
	const std::string VALID_PW = "valid_pw";
	EXPECT_CALL(mockStockBroker, login(VALID_ID, VALID_PW))
		.Times(1);
	autoTradingSystem.login(VALID_ID, VALID_PW);

	const std::string VALID_STOCK_CODE = "000372";
	const int VALID_PRICE = 70000;
	const int VALID_QTY = 3;
	EXPECT_CALL(mockStockBroker, sell(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY))
		.Times(1);
	autoTradingSystem.sell(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY);
}
TEST(AutoTradingSystemTest, Sell_WhenNotLogin_Throws) {
	MockStockBroker mockStockBroker;
	AutoTradingSystem autoTradingSystem;
	autoTradingSystem.selectStockBroker(&mockStockBroker);

	const std::string VALID_STOCK_CODE = "000372";
	const int VALID_PRICE = 70000;
	const int VALID_QTY = 3;
	EXPECT_THROW({ autoTradingSystem.sell(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY); }, std::logic_error);
}

TEST(AutoTradingSystemTest, Sell_WhenNotLoginAndNotSelectStockBroker_Throws) {
	AutoTradingSystem autoTradingSystem;

	const std::string VALID_STOCK_CODE = "000372";
	const int VALID_PRICE = 70000;
	const int VALID_QTY = 3;
	EXPECT_THROW({ autoTradingSystem.sell(VALID_STOCK_CODE, VALID_PRICE, VALID_QTY); }, std::runtime_error);
}
