#pragma once
#include <string>
#include <vector>

class Item {
public:
	std::string name;
	int sellIn; //��ǰ �ǸŰ��ɱⰣ
	int quality; //sellIn�� �پ����� quality�� ��������.
	Item(std::string name, int sellIn, int quality) : name{name}, sellIn{sellIn}, quality{quality} {}
};

class GildedRose {
public:
	std::vector<Item>& items;
	GildedRose(std::vector<Item>& items);

	void updateQuality();
	//���� ���� ��� �������� ������ ���ŵ�
	//�ǸŰ��� �Ⱓ�� ������, ǰ���� 2�辿 ���� ������.
	//quality<0 �Ұ�
	//quality>50 �Ұ�
	//Ư�� Item: 
	// 1. Aged Brie: �ð� �������� ǰ�� ����
	// 2. Sulfuras: ������, quality�ȶ������� ���� ����
	// 3. Backstage Passes: �ܼ�Ʈ Ƽ���ε�, �ǸŰ��ɱⰣ�� �ٰ��ü��� ǰ�� ����, but ������ 0�� ��.
	//                      sellIn<=10 ���� quality+=2, sellIn<=5���� quality+=3;
};

