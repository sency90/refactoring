#pragma once
#include "game.h"
#include <queue>
#include <map>
#define interface struct
#define Question std::string

namespace{
	constexpr int INIT_QUESTION_CNT = 50;
};

class Questions{
public:
	virtual Question getQuestion() {
		if(questions.empty()) {
			return std::string();
		}
		std::string ret = questions.front();
		questions.pop();
		return ret;
	}
	virtual void push(const Question & question) {
		questions.push(question);
	}
	virtual ~Questions() {}
private:
	std::queue<Question> questions;
};

class PopQuestions : public Questions {};
class ScienceQuestions : public Questions {};
class SportsQuestions : public Questions {};
class RockQuestions : public Questions {};

class QuestionsFactory {
private:
	std::map<std::string, Questions*> questionsDic;
public:
	Question getOneQuestion(const std::string & questionsName) const {
		if(questionsDic.count(questionsName) == 0) {
			return Question();
		}
		return questionsDic.at(questionsName)->getQuestion();
	}
	void setQuestions(const std::string & category) {
		if(category == "Pop") questionsDic["Pop"] = new PopQuestions();
		else if(category == "Science") questionsDic["Science"] = new ScienceQuestions();
		else if(category == "Sports") questionsDic["Sports"] = new SportsQuestions();
		else if(category == "Rock") questionsDic["Rock"] = new RockQuestions();
		else return;
		
		Questions & questions = *questionsDic.at(category);
		for(int i = 0; i < INIT_QUESTION_CNT; i++) {
			string question = category + " Question " + to_string(i);
			questions.push(question);
		}
	}
	void clear() {
		for(auto & it : questionsDic) {
			if(it.second != nullptr) {
				delete it.second;
			}
		}
		questionsDic.clear();
	}
	virtual ~QuestionsFactory() {
		clear();
	}
};



class GameRefactor: public IGame {
public:
	GameRefactor(): currentPlayer{0}, location{}, coins{} {
		questionsFactory.setQuestions("Pop");
		questionsFactory.setQuestions("Science");
		questionsFactory.setQuestions("Sports");
		questionsFactory.setQuestions("Rock");
	}

	void rolling(int roll) {
		//�÷��̾� ����
		currentPlayer = getNextPlayer(currentPlayer);

		//�ֻ��� ������
		cout << "They have rolled a " << roll << endl;

		//���� �����ε�, Ż�� ���н�
		if(isFailExitPenaltyBox(roll)) {
			cout << players[currentPlayer] << " is not getting out of the penalty box" << endl;
			return;
		}

		//���� �����ε�, Ż�� ������
		if(isSuccessExitPenaltyBox(roll)) {
			inPenaltyBox[currentPlayer] = false;
			cout << players[currentPlayer] << " is getting out of the penalty box" << endl;
		}

		//�ֻ��� ���ݸ�ŭ �̵�
		location[currentPlayer] = getNextLocation(location[currentPlayer], roll);

		//�̵��� ������ ���� Ǯ��
		askQuestion();
	}
	bool correctAnswerQuizAndReturnIsContinueGame() { //����
	//���������� ��� Ǯ ���� ����.
		if(inPenaltyBox[currentPlayer]) {
			return true;
		}

		//����
		cout << "Answer was correct!!!!" << endl;

		//���� UP
		coins[currentPlayer]++;
		cout << players[currentPlayer] << " now has "
			<< coins[currentPlayer] << " Gold Coins." << endl;

		return isContinueGameOrNot();
	}

	bool wrongAnswerQuizAndReturnIsContinueGame() { //Ʋ����

		//�����̸� ���� ��Ǯ����
		if(inPenaltyBox[currentPlayer]) {
			return CONTINUE_GAME;
		}

		//����, ��������.
		cout << "Question was incorrectly answered" << endl;
		cout << players[currentPlayer] + " was sent to the penalty box" << endl;

		inPenaltyBox[currentPlayer] = true;
		return CONTINUE_GAME;
	}
	bool isPlayable() {
		return (howManyPlayers() >= 2);
	}

	bool add(string playerName) {
		currentPlayer = -1;

		players.push_back(playerName);

		int playerIndex = howManyPlayers() - 1;
		location[playerIndex] = 0;
		coins[playerIndex] = 0;
		inPenaltyBox[playerIndex] = false;

		cout << playerName << " was added" << endl;
		cout << "They are player number " << players.size() << endl;
		return SUCCESS_ADD_PLAYER;
	}

	int howManyPlayers() {
		return (int)players.size();
	}

private:
	bool isSuccessExitPenaltyBox(int roll) {
		return inPenaltyBox[currentPlayer] && roll % 2 == 1;
	}

	bool isFailExitPenaltyBox(int roll) {
		return inPenaltyBox[currentPlayer] && roll % 2 == 0;
	}
	int getNextLocation(int currentPlace, int roll) {
		int nextLocation = currentPlace + roll;
		if(nextLocation >= 12) nextLocation -= 12;

		cout << players[currentPlayer] << "'s new location is " << nextLocation << endl;
		return nextLocation;
	}

	int getNextPlayer(int currentPlayer) {
		int nextPlayer = currentPlayer + 1;
		if(nextPlayer == players.size()) nextPlayer = 0;

		cout << players[nextPlayer] << " is the current player" << endl;
		return nextPlayer;
	}

	void askQuestion() {
		string category = currentCategory();
		cout << "The category is " << category << endl;
		cout << questionsFactory.getOneQuestion(category) << endl;
	}

	string currentCategory() {
		if(location[currentPlayer] % 4 == 0) return "Pop";
		if(location[currentPlayer] % 4 == 1) return "Science";
		if(location[currentPlayer] % 4 == 2) return "Sports";
		if(location[currentPlayer] % 4 == 3) return "Rock";
		return "";
	}

	bool isContinueGameOrNot() {
		bool isFinishGame = (coins[currentPlayer] == 6);
		return !isFinishGame;
	}

private:
	const bool CONTINUE_GAME = true;
	const bool SUCCESS_ADD_PLAYER = true;

	vector<string> players;

	int location[6];
	int coins[6];

	bool inPenaltyBox[6];
	QuestionsFactory questionsFactory;

	//list<string> popQuestions;
	//list<string> scienceQuestions;
	//list<string> sportsQuestions;
	//list<string> rockQuestions;

	int currentPlayer;
};