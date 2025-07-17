#pragma once
#include <string>
#include <vector>

class Item {
public:
	std::string name;
	int sellIn; //상품 판매가능기간
	int quality; //sellIn이 줄어들수록 quality는 떨어진다.
	Item(std::string name, int sellIn, int quality) : name{name}, sellIn{sellIn}, quality{quality} {}
};

class GildedRose {
public:
	std::vector<Item>& items;
	GildedRose(std::vector<Item>& items);

	void updateQuality();
	//매일 자정 모든 아이템의 값들이 갱신됨
	//판매가능 기간이 지나면, 품질은 2배씩 빨리 떨어짐.
	//quality<0 불가
	//quality>50 불가
	//특수 Item: 
	// 1. Aged Brie: 시간 지날수록 품질 증가
	// 2. Sulfuras: 전설템, quality안떨어지고 절대 안팜
	// 3. Backstage Passes: 콘서트 티켓인데, 판매가능기간이 다가올수록 품질 증가, but 지나면 0이 됨.
	//                      sellIn<=10 에선 quality+=2, sellIn<=5에선 quality+=3;
};

